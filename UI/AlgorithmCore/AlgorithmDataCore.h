#ifndef ALGORITJMDATECORE_H
#define ALGORITJMDATECORE_H
#include "generator/dcdf_generator.h"
#include "GlobalParameter.h"
#include "AlgorithmManager.h"
#include "AbstractAlgorithmType.h"
#include "AlgorithmWheat.h"
#include "RequireImage.h"
#include "../../algorithm/graineval/dcdf.h"
class AlgorithmDataProcess;
class AlgorithmDataDynamicResult;
class AlgorithmDataCore:public QObject
{
    Q_OBJECT
public:
    explicit AlgorithmDataCore(QObject* parent=nullptr);
    ~AlgorithmDataCore();
public:
    void setAbstractAlgorithmType();
public:
    inline SegGrainRequireImage* getSegGrainRequireImage(){
        return m_segGrainRequireImage;
    }
    inline ConsumerAlgorithmDataToUI* getConsumerAlgorithmDataToUI(){
        return m_consumerAlgorithmDataToUI;
    }
    inline std::shared_ptr<AlgorithmDataProcess> getAlgorithmDataProcess(){
        if(m_algorithmDataProcess) {
            return m_algorithmDataProcess;
        }
        return nullptr;
    }
    inline std::shared_ptr<AlgorithmDataDynamicResult> getAlgorithmDataDynamicResult(){
        if(m_algorithmDataDynamicResult) {
            return m_algorithmDataDynamicResult;
        }
        return nullptr;
    }
protected:
    //void handle_dcdf_frame(generator::dcdf_frame frame) override;
signals:
    void sigAbstractAlgorithm(AbstractAlgorithm*);
public slots:
    //void dynamic_result();
private:
    std::shared_ptr<AbstractAlgorithm> m_AbstractAlgorithm;
    std::shared_ptr<AlgorithDataPool> m_dataPool;
    //ParseAlgorithmData* m_parseAlgorithmData;
    ConsumerAlgorithmDataToUI* m_consumerAlgorithmDataToUI;
    //ProductionAlgorithmDataToUI* m_productionAlgorithmDataToUI;
    SegGrainRequireImage* m_segGrainRequireImage;
    std::shared_ptr<AlgorithmDataProcess> m_algorithmDataProcess;
    std::shared_ptr<AlgorithmDataDynamicResult> m_algorithmDataDynamicResult;
    AlgorithmProcessth* m_process {nullptr};
    AlgorithmMeargeImg* m_merage[4];
};
class AlgorithmDataProcess :public algorithm::ge_obs_batch_result{
public:
    explicit AlgorithmDataProcess(std::shared_ptr<AbstractAlgorithm> abstractAlgorithm
                                  );
    void batch_result(algorithm::result res) override;
private:
    std::shared_ptr<AbstractAlgorithm> m_AbstractAlgorithm;
};
class AlgorithmDataDynamicResult:public algorithm::ge_obs_sample_result{
public:
    explicit AlgorithmDataDynamicResult(std::shared_ptr<AbstractAlgorithm> abstractAlgorithm);
    void sample_result(algorithm::result res) override;
private:
    std::shared_ptr<AbstractAlgorithm> m_AbstractAlgorithm;
};

#endif // ALGORITJMDATECORE_H
