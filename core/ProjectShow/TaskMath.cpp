#include "TaskMath.h"
#include <QJsonObject>
#include <QFile>
#include <QDir>
#include <QApplication>
#include <QJsonParseError>
#include "Login.h"
std::atomic<int> g_count(0); // 前几次不算
std::atomic<int> g_num  {0}; // 几次少于10颗
std::atomic<int> g_segImgCount(0); // 小图索引
TaskMath::TaskMath(std::shared_ptr<MathBaseModel> m):m_MathBaseModel(m)
{
}
void TaskMath::run()
{
    f();
}
void TaskMath::setCallBack(TaskMath::func p)
{
    f=p;
}

TaskCreateHandler::TaskCreateHandler(std::shared_ptr<MathBaseModel> m):TaskMath(m)
{
    setCallBack([this]{
        GZ_S32 ret ;
        std::string grain_type=m_MathBaseModel->setGrainType().toStdString();
        ret = GZ_GrainEval_Create(m_MathBaseModel->m_base->handler,grain_type);
        ret==0?emit GrainEval_Create_Status(true):emit GrainEval_Create_Status(false);
    });
}

TaskProcess::TaskProcess(std::shared_ptr<MathBaseModel> m):TaskMath(m)
{
    setCallBack([this]{
        g_count++;
        GZ_GrainEval_Result_S result;
        std::lock_guard<std::mutex> l(m_MathBaseModel->m_base->m_mutex);
        GZ_GrainEval_Process(m_MathBaseModel->m_base->handler, m_MathBaseModel->m_base->m_input_data, m_MathBaseModel->m_base->m_result);
        if(g_num>0){
        }else {
            if(m_MathBaseModel->m_base->m_result.common_result.seg_result.size()<=20&&g_count>2){
                emit finshedDetect();
                g_num++;
            }
        }
       /*else{
            g_num=0;
        }*/
        if(m_MathBaseModel->m_base->m_result.common_result.seg_result.size()==0){
           //emit detectEmptyGrain();
        }
        m_MathBaseModel->realShowQuota(result);
        for(int i=0;i<m_MathBaseModel->m_base->m_result.common_result.seg_result.size();i++){
            std::vector<std::shared_ptr<cv::Mat>> vecMat;
            for(int j=0;j<6;j++){
             vecMat.push_back(std::make_shared<cv::Mat>(m_MathBaseModel->m_base->m_result.common_result.seg_result.at(i).at(j)->clone()));
            }
            result.common_result.seg_result.push_back(vecMat);
        }
#ifdef INFO_LOG
        qDebug() << "[TASKMATH-INFO] TaskProcess, wheat result size: " << result.wheat_result.vec_recs.size();
#endif  // INFO_LOG
        m_MathBaseModel->m_base->m_queue.push(result);
        m_MathBaseModel->m_base->m_result.common_result.seg_result.clear();//清空算法图片缓存
        m_MathBaseModel->m_base->cond.notify_one();//通知消费者生产者产品库不为空.
    }
    );
}

TaskDynamicResult::TaskDynamicResult(std::shared_ptr<MathBaseModel> m):TaskMath(m)
{
    setCallBack([this]{
        std::lock_guard<std::mutex> l(m_MathBaseModel->m_base->m_mutex);
        g_segImgCount=0;
        g_num=0;
        g_count=0;
        m_MathBaseModel->m_base->m_result.common_result.weights=GlobalObject::g_instance()->m_weights;
        GZ_GrainEval_Statistic_Wheat_BatchDynamic(m_MathBaseModel->m_base->handler, m_MathBaseModel->m_base->m_result);
        //result across signal get
         QVector<QStringList>record = m_MathBaseModel->setQuota();
         emit GrainEval_finshed();
         emit sigResult(record[0],record[1],record[2],"");
         m_MathBaseModel->m_base->m_result={};//重置result
         GlobalObject::g_instance()->m_weights.clear();
    }
    );
}

ParseMathDate::ParseMathDate(std::shared_ptr<MathBaseModel>m):m_MathBaseModel(m),m_stop(false)
{

}

ParseMathDate::ParseMathDate():m_stop(false)
{

}

void ParseMathDate::setM_MathBaseModel(std::shared_ptr<MathBaseModel> model)
{
   m_MathBaseModel= model;
}
void ParseMathDate::run()
{
    while (true) {
        std::unique_lock<std::mutex> l(m_MathBaseModel->m_base->m_mutex);
        if(m_MathBaseModel->m_base->m_queue.empty()){
            m_MathBaseModel->m_base->cond.wait(l);//消费者等待生产者"产品库缓冲区不为空"这一条件发生.
            if(m_stop) return;
        }
        GZ_GrainEval_Result_S result;
        result=m_MathBaseModel->m_base->m_queue.front();
#ifdef INFO_LOG
        qDebug()<< "[TASKMATH-INFO] run() seg result size:" << result.common_result.seg_result.size();
#endif  // INFO_LOG
        imgDataStruct imgData;
        imgData.imgData=result.common_result.seg_result;
#ifdef INFO_LOG
        qDebug()<<"[TASKMATH-INFO] run() wheat recs size:"<<result.wheat_result.vec_recs.size();
#endif  // INFO_LOG
        m_MathBaseModel->setSegtype(imgData,result);
        m_MathBaseModel->m_base->m_queue.pop();
#ifdef INFO_LOG
        qDebug()<<"[TASKMATH-INFO] run() wheat type size:"<<imgData.wheatType.size();
#endif  // INFO_LOG
        emit sigpushImg(imgData);
        l.unlock();
    }
}

void ParseMathDate::stopThread()
{
    m_stop=true;
    m_MathBaseModel->m_base->cond.notify_all();
}

TaskPushImgData::TaskPushImgData(std::shared_ptr<MathBaseModel> m, imgDataStruct data):TaskMath(m),m_data(data)
{
    setCallBack([this]{
        std::unique_lock<std::mutex> l(m_MathBaseModel->m_base->m_mutex_img);
        while(m_MathBaseModel->m_base->m_queueImg.size()==100){
            m_MathBaseModel->m_base->condImg_notfull.wait(l);//等待消费者说没满
        }
        m_MathBaseModel->m_base->m_queueImg.push(m_data);
        m_MathBaseModel->m_base->condImg_notempty.notify_one();//通知消费者拿数据
        l.unlock();
    });
}

ProductionImgData::ProductionImgData(std::shared_ptr<MathBaseModel> m):m_MathBaseModel(m)
{

}

void ProductionImgData::push_back(imgDataStruct data)
{
    //如果来不及消费 这块会达到线程池最大线程
#ifdef INFO_LOG
    qDebug() << "[TASKMATH-INFO] results from alg data size: " << data.imgData.size();
#endif  // INFO_LOG
    TaskPushImgData* Imgtask = new TaskPushImgData(m_MathBaseModel,data);
    QThreadPool::globalInstance()->start(Imgtask);
}

ConsumerImgData::ConsumerImgData(std::shared_ptr<MathBaseModel> m):m_MathBaseModel(m),m_stop(false)
{

}

void ConsumerImgData::run()
{
    while (true) {
        std::unique_lock<std::mutex> l(m_MathBaseModel->m_base->m_mutex_img);
        if(m_MathBaseModel->m_base->m_queueImg.empty()){
            m_MathBaseModel->m_base->condImg_notempty.wait(l);//等待生产者发送不为空的信号
            if(m_stop){
                return;
            }
        }
        imgDataStruct data=m_MathBaseModel->m_base->m_queueImg.front();
#ifdef INFO_LOG
        qDebug()<<"[TASKMATH-INFO] ConsumerImgData"<<data.wheatType.size();
#endif  // INFO_LOG
        int num=0;
        saveSegpng(data);
        for(auto& it:data.imgData){
            for(int i=0;i<4;i++){
                //cv::Mat tmp=it.at(i)->clone();
                BGR2RGB(it.at(i)->data,it.at(i)->cols,it.at(i)->rows);
                QImage img(it.at(i)->data,it.at(i)->cols,it.at(i)->rows,it.at(i)->cols*3, QImage::Format_RGB888,0,0);
                //only send 80
                if(num<=20){
                    emit sigtoShow(img,m_MathBaseModel->getSegtype(data,num));//这边必须为阻塞连接
                }
                else{
                    break;
                }
                if(m_stop){
                    return;
                }
            }
            num++;
        }
        emit finshedOne();
        m_MathBaseModel->m_base->m_queueImg.pop();
        m_MathBaseModel->m_base->condImg_notfull.notify_one();//消费者说用了一条，没满，可以拿数据了
        l.unlock();
    }
}

void ConsumerImgData::stopThread()
{
    m_stop=true;
    m_MathBaseModel->m_base->condImg_notempty.notify_all();
}

void ConsumerImgData::saveSegpng(imgDataStruct& imgs)
{
    int num = 0;
#ifdef INFO_LOG
    qDebug()<<"[TASKMATH-INFO] save seg image, data size: "
            << imgs.imgData.size() << ", wheat type size: "<<imgs.wheatType.size();
#endif  // INFO_LOG
    for(auto& it:imgs.imgData){
        QString dirname="";
        int type = m_MathBaseModel->getSegtype(imgs,num);
        switch (type){
        case 0: break;
        case 1: dirname="1/";break;
        case 2: dirname="2/";break;
        case 3: dirname="3/";break;
        case 4: dirname="4/";break;
        case 5: dirname="5/";break;
        case 6: dirname="6/";break;
        default: qDebug() << "[TASKMATH-ERROR] save image failed"; break;
        }
        num++;
        if(dirname==""){
            continue;
        }
        //for(int i=0;i<2;i++){

            cv::Mat image_one=*it[0];

            cv::Mat image_two=*it[1];

            cv::Mat result(image_one.rows,image_one.cols+
            image_two.cols+1,image_one.type());

            image_one.colRange(0,image_one.cols).
            copyTo(result.colRange(0,image_one.cols));

            image_two.colRange(0,image_two.cols).copyTo(
            result.colRange(image_one.cols+1,result.cols));
            QString imgName= QApplication::applicationDirPath()+"/segResult/"+dirname+ QString::number(g_segImgCount++)+".png";
            QByteArray b1=imgName.toLatin1();
            cv::imwrite(b1.data(),result);
            if(dirname=="1/"||dirname=="6/"){
                QString imgName= QApplication::applicationDirPath()+"/segResult/"+"7/"+ QString::number(g_segImgCount++)+".png";
                QByteArray b1=imgName.toLatin1();
                cv::imwrite(b1.data(),result);
            }
       // }
    }
#ifdef INFO_LOG
    qDebug() << "[TASKMATH-INFO] saveSegpngFinshed, data size: " << imgs.imgData.size();
#endif  // INFO_LOG
}

void ConsumerImgData::setM_MathBaseModel(std::shared_ptr<MathBaseModel>model)
{
    m_MathBaseModel=model;
}

TaskReleaseHandler::TaskReleaseHandler(std::shared_ptr<MathBaseModel> m):TaskMath(m)
{
    setCallBack([this]{
        GZ_S32 ret ;
        ret=GZ_GrainEval_Release(m_MathBaseModel->m_base->handler);
        ret==0?emit GrainEval_Release_Status(true):emit GrainEval_Release_Status(false);
    });
}

TaskSavePic::TaskSavePic(std::vector<SaveImgData> data,
                         std::shared_ptr<MathBaseModel> MathBaseModel,float value):
    m_imgData(data),m_weight(value)
{
    m_MathBaseModel=MathBaseModel;
}

void TaskSavePic::run()
{
    QString weight= QString::number(m_weight, 'f', 3);
    if(m_imgData.size()!=4){
        return;
    }
    for(int i=0;i<4;i++){
        QByteArray b1=QString(m_imgData[i].imgName.arg(weight)).toLatin1();
        bool ret=false;
        ret = cv::imwrite(b1.data(),*(m_imgData[i].ImgData.get()));
        if(!ret) qDebug() << "[TASKMATH-ERROR] save image false";
    }
}
