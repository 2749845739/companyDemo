#include "ManagerMath.h"
#include "Login.h"
ManagerMath::ManagerMath(QObject *parent):m_providerImg(new DisplaySegImgProvider),
    QObject(parent),m_timer(new QTimer(this)),m_basePara(std::make_shared<BaseParameter>())
{
    m_MathBaseModel=std::make_shared<MathBaseModel>(m_basePara);
    init();
//cv::Mat auim = cv::imread("/home/chpan/QtCode/mathtest/21-UW-PUL01-0000_5_20210708091023_0009_00_00_AU.bmp");
//au_im_data=std::make_shared<cv::Mat>(auim);
//m_vec_data.push_back(au_im_data);
//m_vec_data.push_back(au_im_data);
//m_vec_data.push_back(au_im_data);
//m_vec_data.push_back(au_im_data);
}

ManagerMath::~ManagerMath()
{
    disconnect(m_consumerThread.get(),0,0,0);
    m_parseMathdate->stopThread();
    m_parseMathdate->wait();
    m_parseMathdate->quit();

    m_consumerThread->stopThread();
    m_consumerThread->wait();
    m_consumerThread->quit();
}

void ManagerMath::init()
{
    m_parseMathdate=std::make_shared<ParseMathDate>(m_MathBaseModel);
    m_parseMathdate->start();

    m_consumerThread=std::make_shared<ConsumerImgData>(m_MathBaseModel);
    m_ProductThread=std::make_shared<ProductionImgData>(m_MathBaseModel);

    connect(m_parseMathdate.get(),&ParseMathDate::sigpushImg,m_ProductThread.get(),&ProductionImgData::push_back,Qt::BlockingQueuedConnection);
    m_consumerThread->start();
    connect(m_consumerThread.get(),&ConsumerImgData::sigtoShow,this,&ManagerMath::getImgFormMath,Qt::BlockingQueuedConnection);
    connect(m_consumerThread.get(),&ConsumerImgData::finshedOne,this,&ManagerMath::startGeiImage);
//   m_timer->setInterval(10000);
//   connect(m_timer,&QTimer::timeout,this,&ManagerMath::prossDataTest);
}


void ManagerMath::initMathModel(int num)
{
    switch (num) {
    case 0:m_MathBaseModel->m_base->m_grainType=GrainType::WHEAT;
        m_MathBaseModel=std::make_shared<MathWheatModel>(m_basePara);
        m_parseMathdate->setM_MathBaseModel(m_MathBaseModel);
        m_consumerThread->setM_MathBaseModel(m_MathBaseModel);
        emit sigGainType(m_MathBaseModel->m_base->m_grainType,m_MathBaseModel.get());
        break;
    case 1:m_MathBaseModel->m_base->m_grainType=GrainType::RICE;
        break;
    case 2:m_MathBaseModel->m_base->m_grainType=GrainType::CRON;
        break;
    default:break;
    }
    TaskCreateHandler* task=new TaskCreateHandler(m_MathBaseModel);
    connect(task,&TaskCreateHandler::GrainEval_Create_Status,this,&ManagerMath::createHanderResult);
    QThreadPool::globalInstance()->start(task);
}

void ManagerMath::releaseModel()
{
    TaskReleaseHandler* task=new TaskReleaseHandler(m_MathBaseModel);
    connect(task,&TaskReleaseHandler::GrainEval_Release_Status,this,&ManagerMath::releaseHanderResult);
    QThreadPool::globalInstance()->start(task);
}

void ManagerMath::processData(std::vector<im_data> data)
{
#ifdef INFO_LOG
    qDebug() << "[MANAGERMATH-INFO] processData:" << data.size();
#endif  // INFO_LOG
    TaskProcess* task=new TaskProcess(m_MathBaseModel);
    connect(task,&TaskProcess::finshedDetect,this,&ManagerMath::finshedDetect);
    //connect(task,&TaskProcess::processData,this,&ManagerMath::getProcessData);
    connect(task,&TaskProcess::detectEmptyGrain,this,&ManagerMath::emptyGain);
    task->m_MathBaseModel->m_base->m_input_data.vec_data=data;
    QThreadPool::globalInstance()->start(task);
}

void ManagerMath::dynamicResult()
{
    TaskDynamicResult* task=new TaskDynamicResult(m_MathBaseModel);
    connect(task,&TaskDynamicResult::GrainEval_finshed,this,&ManagerMath::dynamicFinshed);
    connect(task,&TaskDynamicResult::sigResult,this,&ManagerMath::sigRecord);
    QThreadPool::globalInstance()->start(task);
}

void ManagerMath::savePng(std::vector<SaveImgData> data,float weight)
{
    TaskSavePic* task=new TaskSavePic(data,m_MathBaseModel,weight);
    QThreadPool::globalInstance()->start(task);
}

void ManagerMath::clearImg()
{
    m_providerImg->m_view.clear();
    m_index=0;
}

void ManagerMath::timerStart()
{
    m_timer->start();
}

void ManagerMath::timerStop()
{
    m_timer->stop();
}

void ManagerMath::prossDataTest()
{
    TaskProcess* task=new TaskProcess(m_MathBaseModel);
    task->m_MathBaseModel->m_base->m_input_data.vec_data=m_vec_data;
    QThreadPool::globalInstance()->start(task);
}

void ManagerMath::getSegTypeImg(int type)
{
    QString dirName="";
    switch (type) {
    case 0:break;
    case 1:dirName ="1/";break;
    case 2:dirName ="2/";break;
    case 3:dirName ="3/";break;
    case 4:dirName ="4/";break;
    case 5:dirName ="5/";break;
    case 6:dirName ="6/";break;
    case 7:dirName ="7/";break;
    default:break;
    }
    QDir dir(QApplication::applicationDirPath()+"/segResult/"+dirName);
    QFileInfoList fileList=dir.entryInfoList(QDir::NoDotAndDotDot|QDir::Files,QDir::Time);
#ifdef INFO_LOG
    qDebug() << "[MANAGERMATH-INFO] " << fileList.length();
#endif  // INFO_LOG
    QVariantList fileName;
    for(auto &it:fileList){
        fileName.append(it.absoluteFilePath());
    }
    emit sigresultImg(fileName);
}

void ManagerMath::clearDir()
{
    QString segResultPath="rm -rf " + QApplication::applicationDirPath()+"/segResult";
    QByteArray b=segResultPath.toLatin1();
    system(b.data());

    QDir dir(QApplication::applicationDirPath());
    dir.mkdir("segResult");
    dir.cd("segResult");
    dir.mkdir("0");
    dir.mkdir("1");
    dir.mkdir("2");
    dir.mkdir("3");
    dir.mkdir("4");
    dir.mkdir("5");
    dir.mkdir("6");
    dir.mkdir("7");
}

void ManagerMath::getWeight(float value)
{
    if(!GlobalObject::g_instance()->m_saveImgData.empty()){
       std::vector<SaveImgData> it;
        it.push_back(GlobalObject::g_instance()->m_saveImgData.front().at(0));
        it.push_back(GlobalObject::g_instance()->m_saveImgData.front().at(1));
        it.push_back(GlobalObject::g_instance()->m_saveImgData.front().at(2));
        it.push_back(GlobalObject::g_instance()->m_saveImgData.front().at(3));
        GlobalObject::g_instance()->m_saveImgData.pop();
        savePng(it,value);
    }
}

void ManagerMath::openchm()
{
     QDesktopServices::openUrl(QApplication::applicationDirPath()+"/GzDocument.chm");
}

void ManagerMath::getImgFormMath(QImage &img,int type)
{
    if(++m_index==80) {
        m_index=0;
        return;
    }
    m_providerImg->updateImage(m_index,img);
    emit addImgtoView(m_index,type);
}
