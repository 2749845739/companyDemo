#include "AlgorithmManager.h"

AlgorithmManager::AlgorithmManager(std::shared_ptr<generator::dcdf_engine> dcdf_engine,
                                   std::string dev_id):algorithm::dcdf(dcdf_engine,dev_id){
    findgraineval();
}

void AlgorithmManager::findgraineval()
{
    int res = scan_plugin(QString(QApplication::applicationDirPath()+
                                  "/graineval_plugin").toStdString());
    if(res==-1){
        if(CMessageBox::ShowInfo("算法版本有误，是否继续",nullptr,CMessageBox::StandardButton::YesNo)!=0){
            qApp->quit();
        }
    }
    if(res==-2){
        if(CMessageBox::ShowInfo("算法插件丢失，是否继续",nullptr,CMessageBox::StandardButton::YesNo)!=0){
            qApp->quit();
        }
    }
    //    // 寻找插件
    //    auto lib_path = boost::dll::fs::path(QString(QApplication::applicationDirPath()+
    //            "/graineval_plugin").toStdString()) / ALG_PLUGIN_NAME;
    //    try {
    //      boost::dll::shared_library lib(lib_path, boost::dll::load_mode::append_decorations);
    //      // 没有symbol
    //      if (!lib.has(GRAINEVAL_CREATOR_SYMBOL)){
    //          if(CMessageBox::ShowInfo("算法版本有误，是否继续",nullptr,CMessageBox::StandardButton::YesNo)!=0){
    //              qApp->quit();
    //          }
    //      }
    //      m_plib = boost::dll::import_alias<boost::shared_ptr<algorithm::graineval_api>()>
    //              (boost::move(lib), GRAINEVAL_CREATOR_SYMBOL)();
    //    } catch (std::exception e) {
    //      // 库文件/库目录不存在
    //      if(CMessageBox::ShowInfo("算法插件丢失，是否继续",nullptr,CMessageBox::StandardButton::YesNo)!=0){
    //          qApp->quit();
    //      }
    //    }
}


AlgorithmProcess::AlgorithmProcess(std::shared_ptr<AbstractAlgorithm> abstractAlgorithm,algorithm::result res):
    m_res(res)
{
    m_AbstractAlgorithm=abstractAlgorithm;
}
void AlgorithmProcess::run()
{
    //m_AbstractAlgorithm->porcess(std::make_shared<algorithm::result>(m_res));
}

AlgorithmResult::AlgorithmResult(std::shared_ptr<AbstractAlgorithm> abstractAlgorithm,algorithm::result res):
    m_AbstractAlgorithm(abstractAlgorithm),m_res(res){}

void AlgorithmResult::run()
{
    //m_AbstractAlgorithm->dynamic_result(std::make_shared<algorithm::result>(m_res));
}

AlgorithmProcessth::AlgorithmProcessth(std::shared_ptr<AbstractAlgorithm> abstractAlgorithm, QObject *parent):QThread(parent),m_AbstractAlgorithm(abstractAlgorithm)
{

}

void AlgorithmProcessth::run()
{
    while (true) {
        GlobalObject::g_instance()->m_sm.acquire();
        if(m_isStop) return;
        //std::unique_lock<std::mutex> l(GlobalObject::g_instance()->m_mutex);
        algorithm::result res;
        if(!GlobalObject::g_instance()->m_res.empty()){
            res=GlobalObject::g_instance()->m_res.front();
            GlobalObject::g_instance()->m_res.pop();
        }
        //l.unlock();
        m_AbstractAlgorithm->porcess(res);
    }
}

AlgorithmProcessth::~AlgorithmProcessth()
{
    m_isStop=true;
    GlobalObject::g_instance()->m_sm.release();
    wait();
    quit();
}

AlgorithmMeargeImg::AlgorithmMeargeImg(int index, QObject *parent):
    m_index(index)
{

}
std::atomic<std::uint64_t> g_imgCoutOne  {0};
void AlgorithmMeargeImg::run()
{
    while (true) {
        GlobalObject::g_instance()->m_saveSema[m_index].acquire();
        if(m_isStop) return;
        int num = 0;
        if(!GlobalObject::g_instance()->m_mulitRes[m_index].empty()){
            algorithm::result res= GlobalObject::g_instance()->m_mulitRes[m_index].front();
            GlobalObject::g_instance()->m_mulitRes[m_index].pop();
            for(auto &it:res.im_segment){
                QString dirname="";
                int type = static_cast<int>(res.wheat.recs.at(num).first);
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
                cv::Mat image_one=*it[0];
                cv::Mat image_two=*it[1];
                cv::Mat result = cv::Mat::zeros(cv::Size(image_one.cols * 2, image_one.rows), CV_8UC3);
                image_one.copyTo(result(cv::Rect(0, 0, image_one.cols, image_one.rows)));
                image_two.copyTo(result(cv::Rect(image_two.cols, 0, image_two.cols, image_two.rows)));
                QString imgName= QApplication::applicationDirPath()+"/segResult/"+dirname+ QString::number(g_imgCoutOne++)+".png";
                QByteArray b1=imgName.toLatin1();
                cv::imwrite(b1.data(),result);
                if(dirname=="1/"||dirname=="6/"){
                    QString imgName= QApplication::applicationDirPath()+"/segResult/"+"7/"+ QString::number(g_imgCoutOne++)+".png";
                    QByteArray b1=imgName.toLatin1();
                    cv::imwrite(b1.data(),result);
                }
            }
        }
    }
}

AlgorithmMeargeImg::~AlgorithmMeargeImg()
{
    m_isStop=true;
    GlobalObject::g_instance()->m_saveSema[m_index].release();
    wait();
    quit();
}


