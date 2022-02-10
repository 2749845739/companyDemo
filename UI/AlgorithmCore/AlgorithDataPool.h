#ifndef ALGORITHDATAPOOL_H
#define ALGORITHDATAPOOL_H
#include "algorithm/graineval/graineval_api.hpp"
#include "generator/dcdf_generator.h"
#include "GlobalParameter.h"
#include <QThread>
#include <QThreadPool>
struct AlgorithmData{
    /// 所有颗粒分类结果
    std::vector<std::pair<algorithm::wheat_t, float>> recs;
    /// 批次样本中颗粒分割图（A相机反射，B相机反射，A相机透射，B相机透射，A相机Mask，B相机Mask）
    std::vector<std::vector<std::shared_ptr<cv::Mat>>> im_segment;
};

class AlgorithDataPool
{
public:
    explicit AlgorithDataPool();
    void process(AlgorithmData &res);
public:
    std::queue<AlgorithmData> m_algorithmData;
    std::queue<AlgorithmData> m_algorithmDataToUI;
    std::mutex m_mutex;
    std::mutex m_mutexToUI;
    std::condition_variable cond;
    std::condition_variable condToUI;
};
class ParseAlgorithmData : public QThread {
    Q_OBJECT
public:
    explicit ParseAlgorithmData(std::shared_ptr<AlgorithDataPool> dataPool,
                                QObject* parent=nullptr);
    void run();
    void stopThread();
signals:
    void sigData(AlgorithmData);
private:
    std::shared_ptr<AlgorithDataPool> m_dataPool;
    bool m_stop {false};
};
class AlgorithmDataToUI:public QRunnable{
public:
    AlgorithmDataToUI(std::shared_ptr<AlgorithDataPool> dataPool,AlgorithmData);
    void run() override;
private:
    std::shared_ptr<AlgorithDataPool> m_dataPool;
    AlgorithmData m_data;
};
class ProductionAlgorithmDataToUI:public QObject{
    Q_OBJECT
public:
    explicit ProductionAlgorithmDataToUI(std::shared_ptr<AlgorithDataPool>
                                         dataPool,QObject* parent=nullptr);
public slots:
    void getAlgorithmData(AlgorithmData);
private:
    std::shared_ptr<AlgorithDataPool> m_dataPool;
};

class ConsumerAlgorithmDataToUI:public QThread {
    Q_OBJECT
public:
    explicit ConsumerAlgorithmDataToUI(std::shared_ptr<AlgorithDataPool> datapool
                                       ,QObject* parent=nullptr);
    void run() override;
    void stopThread();
signals:
    void sigToModel(QImage img,int type);
    void sigFilishedRound();
private:
    std::shared_ptr<AlgorithDataPool> m_dataPool;
    bool m_stop {false};
};
#endif // ALGORITHDATAPOOL_H
