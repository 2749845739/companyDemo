#include "AlgorithDataPool.h"

AlgorithDataPool::AlgorithDataPool(){
        qRegisterMetaType<AlgorithmData>("AlgorithmData");
}

void AlgorithDataPool::process(AlgorithmData &res){
    std::lock_guard<std::mutex> l(m_mutexToUI);
    m_algorithmDataToUI.push(res);
    condToUI.notify_all();
}

ParseAlgorithmData::ParseAlgorithmData(std::shared_ptr<AlgorithDataPool> dataPool,
                                       QObject *parent):QThread(parent),m_dataPool(dataPool)
{}

void ParseAlgorithmData::run()
{
    while (true) {
        std::unique_lock<std::mutex> l(m_dataPool->m_mutex);
        if(m_dataPool->m_algorithmData.empty()){
            m_dataPool->cond.wait(l);
        }
        if(m_stop) return;
        auto it=m_dataPool->m_algorithmData.front();
        //m_dataPool->m_algorithmDataToUI.push(it);
        emit sigData(it);
        m_dataPool->m_algorithmData.pop();
        l.unlock();
    }
}

void ParseAlgorithmData::stopThread()
{
    m_stop=true;
    m_dataPool->cond.notify_all();
}

AlgorithmDataToUI::AlgorithmDataToUI(std::shared_ptr<AlgorithDataPool> dataPool,
    AlgorithmData data):m_data(data),m_dataPool(dataPool)
{}

void AlgorithmDataToUI::run()
{
    std::unique_lock<std::mutex> l(m_dataPool->m_mutexToUI);
    m_dataPool->m_algorithmDataToUI.push(m_data);
    m_dataPool->condToUI.notify_all();
    l.unlock();
}

ProductionAlgorithmDataToUI::ProductionAlgorithmDataToUI(std::shared_ptr<AlgorithDataPool> dataPool, QObject *parent):m_dataPool(dataPool)
{}

void ProductionAlgorithmDataToUI::getAlgorithmData(AlgorithmData data)
{
    // 如果来不及消费 这块会达到线程池最大线程
    AlgorithmDataToUI* task=new AlgorithmDataToUI(m_dataPool,data);
    QThreadPool::globalInstance()->start(task);
}

ConsumerAlgorithmDataToUI::ConsumerAlgorithmDataToUI(std::shared_ptr<AlgorithDataPool>
                                                     datapool,QObject* parent):QThread(parent),m_dataPool(datapool)
{}

void ConsumerAlgorithmDataToUI::run()
{
    while (true) {
        std::unique_lock<std::mutex> l(m_dataPool->m_mutexToUI);
        if(m_dataPool->m_algorithmDataToUI.empty()){
            m_dataPool->condToUI.wait(l);//等待生产者发送不为空的信号
        }
        if(m_stop) return;
        auto it=m_dataPool->m_algorithmDataToUI.front();
        LOGGER_DEBUG("小图张数:%d",it.recs.size());
        //界面实时显示
        int num=0;
        for(auto& img:it.im_segment){
            for(int i=0;i<2;i++){
                BGR2RGB(img.at(i)->data,img.at(i)->cols,img.at(i)->rows);
                QImage pic(img.at(i)->data,img.at(i)->cols,img.at(i)->rows,img.at(i)->cols*3, QImage::Format_RGB888,0,0);
                if(num<80){
                    emit sigToModel(pic,static_cast<int>(it.recs.at(num).first));//这边必须为阻塞连接
                }else{
                    break;
                }
            }
            if(m_stop){
                return;
            }
            num++;
        }
        m_dataPool->m_algorithmDataToUI.pop();
        emit sigFilishedRound();
        l.unlock();
    }
}

void ConsumerAlgorithmDataToUI::stopThread()
{
    m_stop=true;
    m_dataPool->condToUI.notify_all();
}
