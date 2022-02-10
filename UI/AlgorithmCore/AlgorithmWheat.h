#ifndef ALGORITHMWHEAT_H
#define ALGORITHMWHEAT_H
#include "AbstractAlgorithmType.h"
#include "AlgorithDataPool.h"
class GrainQuota;
class WheatPicSort:public QRunnable{
public:
    explicit WheatPicSort(AlgorithmData data);
    void run() override;
private:
    AlgorithmData m_data;
};
class AlgorithmWheat:public AbstractAlgorithm
{
    Q_OBJECT
    Q_PROPERTY(QVariantList shengya READ shengya WRITE setShengya NOTIFY shengyaChanged)
    Q_PROPERTY(QVariantList chongshi READ chongshi WRITE setChongshi NOTIFY chongshiChanged)
    Q_PROPERTY(QVariantList posun READ posun WRITE setPosun NOTIFY posunChanged)
    Q_PROPERTY(QVariantList shengmei READ shengmei WRITE setShengmei NOTIFY shengmeiChanged)
    Q_PROPERTY(QVariantList binban READ binban WRITE setBinban NOTIFY binbanChanged)
    Q_PROPERTY(QVariantList chimei READ chimei WRITE setChimei NOTIFY chimeiChanged)
    Q_PROPERTY(QVariantList heipei READ heipei WRITE setHeipei NOTIFY heipeiChanged)
    Q_PROPERTY(QVariantList allRatio READ allRatio WRITE setAllRatio NOTIFY allRatioChanged)
    Q_PROPERTY(QVariantList weightNormal READ weightNormal WRITE setWeightNormal NOTIFY weightNormalChanged)
public:
    QVariantList shengya();
    void setShengya(QVariantList value);

    QVariantList chongshi();
    void setChongshi(QVariantList value);

    QVariantList posun();
    void setPosun(QVariantList value);

    QVariantList shengmei();
    void setShengmei(QVariantList value);

    QVariantList binban();
    void setBinban(QVariantList value);

    QVariantList chimei();
    void setChimei(QVariantList value);

    QVariantList heipei();
    void setHeipei(QVariantList value);

    QVariantList allRatio();
    void setAllRatio(QVariantList value);

    QVariantList weightNormal();
    void setWeightNormal(QVariantList value);
signals:
    void shengyaChanged();
    void chongshiChanged();
    void posunChanged();
    void shengmeiChanged();
    void binbanChanged();
    void chimeiChanged();
    void heipeiChanged();
    void allRatioChanged();
    void weightNormalChanged();
signals:
    void sigMergeImg(QVariantList fileName);
public:
    explicit AlgorithmWheat(std::shared_ptr<AlgorithDataPool> dataPool,QObject*parent=nullptr);
    void porcess(algorithm::result& res) override;
    void dynamic_result(algorithm::result& res) override;
    Q_INVOKABLE bool printResult() override;
    Q_INVOKABLE void getSegTypeImg(int type) override;
private:
    std::shared_ptr<AlgorithDataPool> m_dataPool;
    GrainQuota* m_grainQuota;
    QStringList m_weightRatio;
    QStringList m_countRatio;
    QString m_mass;
    QString m_particles;
    std::uint32_t m_count {0};
};
class AlgorithmWheatTypeFactor:public AbstractAlgorithmTypeFactor{
public:
    explicit AlgorithmWheatTypeFactor(std::shared_ptr<AlgorithDataPool> dataPool);
    std::shared_ptr<AbstractAlgorithm> createAlgorithm() override;
private:
    std::shared_ptr<AlgorithDataPool> m_dataPool;
};
#endif // ALGORITHMWHEAT_H
