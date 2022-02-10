#include "AlgorithmDataCore.h"
int g_runCount=0;
AlgorithmDataCore::AlgorithmDataCore(QObject* parent):QObject(parent)
{
    m_dataPool=std::make_shared<AlgorithDataPool>();
   // m_parseAlgorithmData=new ParseAlgorithmData(m_dataPool,this);
    m_consumerAlgorithmDataToUI=new ConsumerAlgorithmDataToUI(m_dataPool,this);
    //m_productionAlgorithmDataToUI=new ProductionAlgorithmDataToUI(m_dataPool,this);
    //m_parseAlgorithmData->start();
    m_consumerAlgorithmDataToUI->start();
//    connect(m_parseAlgorithmData,&ParseAlgorithmData::sigData,
//            m_productionAlgorithmDataToUI,&ProductionAlgorithmDataToUI::getAlgorithmData);
    m_segGrainRequireImage=new SegGrainRequireImage(this);
    connect(m_consumerAlgorithmDataToUI,&ConsumerAlgorithmDataToUI::sigToModel
            ,m_segGrainRequireImage,&SegGrainRequireImage::getCameraImage);
    for(int i=0;i<THREAD_COUNT+1;i++){
        m_merage[i]=new AlgorithmMeargeImg(i,this);
        m_merage[i]->start();
    }
}

AlgorithmDataCore::~AlgorithmDataCore()
{
    //m_parseAlgorithmData->stopThread();
    m_consumerAlgorithmDataToUI->stopThread();
   // m_parseAlgorithmData->wait();
    //m_parseAlgorithmData->quit();

    m_consumerAlgorithmDataToUI->wait();
    m_consumerAlgorithmDataToUI->quit();
}

void AlgorithmDataCore::setAbstractAlgorithmType()
{
    switch (GlobalObject::g_grainType) {
    case GrainType::WHEAT: m_AbstractAlgorithm=std::make_shared
                <AlgorithmWheatTypeFactor>(m_dataPool)->createAlgorithm();
    default:m_AbstractAlgorithm=std::make_shared
                <AlgorithmWheatTypeFactor>(m_dataPool)->createAlgorithm();;
        break;
    }
    emit sigAbstractAlgorithm(m_AbstractAlgorithm.get());
    m_algorithmDataProcess=std::make_shared<AlgorithmDataProcess>(m_AbstractAlgorithm);
    m_algorithmDataDynamicResult=std::make_shared<AlgorithmDataDynamicResult>(m_AbstractAlgorithm);
    if(!m_process){
        m_process=new AlgorithmProcessth(m_AbstractAlgorithm,this);
        m_process->start();
    }
}

//void AlgorithmDataCore::handle_dcdf_frame(generator::dcdf_frame frame)
//{
//    std::shared_ptr<cv::Mat> pua = std::make_shared<cv::Mat>(
//      cv::Mat(frame.ua->h, frame.ua->w, CV_8UC3, frame.ua->data.get()).clone());
//    std::shared_ptr<cv::Mat> pub = std::make_shared<cv::Mat>(
//      cv::Mat(frame.ub->h, frame.ub->w, CV_8UC3, frame.ub->data.get()).clone());
//    std::shared_ptr<cv::Mat> pda = std::make_shared<cv::Mat>(
//      cv::Mat(frame.da->h, frame.da->w, CV_8UC3, frame.da->data.get()).clone());
//    std::shared_ptr<cv::Mat> pdb = std::make_shared<cv::Mat>(
//      cv::Mat(frame.db->h, frame.db->w, CV_8UC3, frame.db->data.get()).clone());
//    AlgorithmProcess* Processtask=new AlgorithmProcess(m_plib,frame.id,frame.wei,
//                         frame.time_str,frame.grain_type,frame.abnormal_type,
//                         {pua, pub, pda, pdb},m_AbstractAlgorithm,m_res);
//    QThreadPool::globalInstance()->start(Processtask);
//}

//void AlgorithmDataCore::dynamic_result()
//{
//    auto algorithmRes=new AlgorithmResult(m_plib,m_AbstractAlgorithm,m_res);
//    QThreadPool::globalInstance()->start(algorithmRes);
//}

AlgorithmDataProcess::AlgorithmDataProcess(std::shared_ptr<AbstractAlgorithm> abstractAlgorithm)
{
    m_AbstractAlgorithm=abstractAlgorithm;
}
static int picsize=0;
void AlgorithmDataProcess::batch_result(algorithm::result res)
{
    LOGGER_DEBUG("batch_result");
    if(g_runCount++>100) return;

    picsize+=res.im_segment.size();
    LOGGER_DEBUG("----------------所有小图张数:%d---------------",picsize);
    LOGGER_DEBUG("----------------每次小图张数:%d---------------",res.im_segment.size());
    //    AlgorithmProcess* Processtask=new AlgorithmProcess(m_AbstractAlgorithm,res);
    //    QThreadPool::globalInstance()->start(Processtask);
    // std::unique_lock<std::mutex> l(GlobalObject::g_instance()->m_mutex);
    GlobalObject::g_instance()->m_res.push(res);
    //l.unlock();
    GlobalObject::g_instance()->m_sm.release();

    int truck=res.im_segment.size()/THREAD_COUNT;
    int end=res.im_segment.size()%THREAD_COUNT;
    for(int num=0; num<THREAD_COUNT;num++){
        algorithm::result datacopy;
        for(int i=num*truck;i<(num+1)*truck;i++){
            std::vector<std::shared_ptr<cv::Mat>> vecMatcopy;
            for(int j=0;j<2;j++){
                vecMatcopy.push_back(std::make_shared<cv::Mat>(
                                         res.im_segment.at(i).at(j)->clone()));
            }
            datacopy.wheat.recs.push_back(res.wheat.recs.at(i));
            datacopy.im_segment.push_back(vecMatcopy);
        }
        if(truck>0){
            GlobalObject::g_instance()->m_mulitRes[num].push(datacopy);
            GlobalObject::g_instance()->m_saveSema[num].release();
        }
    }
    if(end!=0){
        algorithm::result datacopy;
        for(int i=THREAD_COUNT*truck;i<res.im_segment.size();i++){
            std::vector<std::shared_ptr<cv::Mat>> vecMatcopy;
            for(int j=0;j<2;j++){
                vecMatcopy.push_back(std::make_shared<cv::Mat>(
                                         res.im_segment.at(i).at(j)->clone()));
            }
            datacopy.wheat.recs.push_back(res.wheat.recs.at(i));
            datacopy.im_segment.push_back(vecMatcopy);
        }
        GlobalObject::g_instance()->m_mulitRes[THREAD_COUNT].push(datacopy);
        GlobalObject::g_instance()->m_saveSema[THREAD_COUNT].release();
    }
}

AlgorithmDataDynamicResult::AlgorithmDataDynamicResult(std::shared_ptr<AbstractAlgorithm> abstractAlgorithm)
{
    m_AbstractAlgorithm=abstractAlgorithm;
}

void AlgorithmDataDynamicResult::sample_result(algorithm::result res)
{
    LOGGER_DEBUG("sample_result");
    picsize=0;
    g_runCount=0;
    //    AlgorithmResult* algorithmRes=new AlgorithmResult(m_AbstractAlgorithm,res);
    //    QThreadPool::globalInstance()->start(algorithmRes);
    m_AbstractAlgorithm->dynamic_result(res);
}
