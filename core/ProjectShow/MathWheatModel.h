#ifndef MATHWHEATMODEL_H
#define MATHWHEATMODEL_H
#include "MathBaseModel.h"
class ResultDataPrivate;
//struct processResult{
//    float unsound; //不完善粒
//    float impurities;// 杂质
//    float moisture;// 水分
//    float exoticWheat; //异种粮比例
//    float thousandWeight; // 千粒重
//    float jiejiemai;  // 节节麦比例
//    float whiteWheat; //白麦
//    float volumeWeight;//容重
//    processResult(){
//        unsound=0.0;
//        impurities=0.0;
//        moisture=0.0;
//        exoticWheat=0.0;
//        thousandWeight=0.0;
//        jiejiemai=0.0;
//        whiteWheat=0.0;
//        volumeWeight=0.0;
//    }
//};
class MathWheatModel:public MathBaseModel
{
    Q_OBJECT
    Q_PROPERTY(QString bbMassRatio READ bbMassRatio WRITE setBbMassRatio NOTIFY bbMassRatioChanged)
    Q_PROPERTY(QString bbParticlesRatio READ bbParticlesRatio WRITE setBbParticlesRatio NOTIFY bbParticlesRatioChanged)
    Q_PROPERTY(QString syMassRatio READ syMassRatio WRITE setSyMassRatio NOTIFY syMassRatioChanged)
    Q_PROPERTY(QString syParticlesRatio READ syParticlesRatio WRITE setSyParticlesRatio NOTIFY syParticlesRatioChanged)

    Q_PROPERTY(QString smMassRatio READ smMassRatio WRITE setSmMassRatio NOTIFY smMassRatioChanged)
    Q_PROPERTY(QString smParticlesRatio READ smParticlesRatio WRITE setSmParticlesRatio NOTIFY smParticlesRatioChanged)

    Q_PROPERTY(QString csMassRatio READ csMassRatio WRITE setCsMassRatio NOTIFY csMassRatioChanged)
    Q_PROPERTY(QString csParticlesRatio READ csParticlesRatio WRITE setCsParticlesRatio NOTIFY csParticlesRatioChanged)

    Q_PROPERTY(QString psMassRatio READ psMassRatio WRITE setPsMassRatio NOTIFY psMassRatioChanged)
    Q_PROPERTY(QString psParticlesRatio READ psParticlesRatio WRITE setPsParticlesRatio NOTIFY psParticlesRatioChanged)

    Q_PROPERTY(QString hpMassRatio READ hpMassRatio WRITE setHpMassRatio NOTIFY hpMassRatioChanged)
    Q_PROPERTY(QString hpParticlesRatio READ hpParticlesRatio WRITE setHpParticlesRatio NOTIFY hpParticlesRatioChanged)

    Q_PROPERTY(QString massRatio READ massRatio WRITE setMassRatio NOTIFY massRatioChanged)
    Q_PROPERTY(QString particlesRatio READ particlesRatio WRITE setParticlesRatio NOTIFY particlesRatioChanged)

    Q_PROPERTY(QString unsound READ unsound WRITE setUnsound NOTIFY unsoundChanged)
    Q_PROPERTY(QString impurities READ impurities WRITE setImpurities NOTIFY impuritiesChanged)
    Q_PROPERTY(QString moisture READ moisture WRITE setMoisture NOTIFY moistureChanged)
    Q_PROPERTY(QString exoticWheat READ exoticWheat WRITE setExoticWheat NOTIFY exoticWheatChanged)
    Q_PROPERTY(QString thousandWeight READ thousandWeight WRITE setThousandWeight NOTIFY thousandWeightChanged)
    Q_PROPERTY(QString jiejiemai READ jiejiemai WRITE setJiejiemai NOTIFY jiejiemaiChanged)
    Q_PROPERTY(QString white_count_Wheat READ white_count_Wheat WRITE setWhite_count_Wheat NOTIFY whiteWheat_count_Changed)
    Q_PROPERTY(QString volumeWeight READ volumeWeight WRITE setVolumeWeight NOTIFY volumeWeightChanged)

    Q_PROPERTY(QString binbMassRatio READ binbMassRatio WRITE setBinbMassRatio NOTIFY binbMassRatioChanged)

    Q_PROPERTY(QString binbParticlesRatio READ binbParticlesRatio WRITE setBinbParticlesRatio NOTIFY binbParticlesRatioChanged)

    Q_PROPERTY(QString m_white_weight_Wheat READ m_white_weight_Wheat WRITE setM_white_weight_Wheat NOTIFY m_white_weight_WheatChanged)

    Q_PROPERTY(QString red_count_Wheat READ red_count_Wheat WRITE setRed_count_Wheat NOTIFY red_count_WheatChanged)

    Q_PROPERTY(QString red_weight_Wheat READ red_weight_Wheat WRITE setRed_weight_Wheat NOTIFY red_weight_WheatChanged)

    Q_PROPERTY(int wheatUnsoundType READ wheatUnsoundType WRITE setWheatUnsoundType NOTIFY wheatUnsoundTypeChanged)

public:
    explicit MathWheatModel(std::shared_ptr<BaseParameter> base);
    QString bbMassRatio();
    void setBbMassRatio(QString);

    QString bbParticlesRatio();
    void setBbParticlesRatio(QString);

    QString syMassRatio();
    void setSyMassRatio(QString);

    QString syParticlesRatio();
    void setSyParticlesRatio(QString);

    QString smMassRatio();
    void setSmMassRatio(QString);

    QString smParticlesRatio();
    void setSmParticlesRatio(QString);

    QString csMassRatio();
    void setCsMassRatio(QString);

    QString csParticlesRatio();
    void setCsParticlesRatio(QString);

    QString psMassRatio();
    void setPsMassRatio(QString);


    QString psParticlesRatio();
    void setPsParticlesRatio(QString);

    QString hpMassRatio();
    void setHpMassRatio(QString);

    QString hpParticlesRatio();
    void setHpParticlesRatio(QString);

    QString massRatio();
    void setMassRatio(QString);

    QString particlesRatio();
    void setParticlesRatio(QString);

    QString unsound();
    void setUnsound(QString value);

    QString impurities();
    void setImpurities(QString value);

    QString moisture();
    void setMoisture(QString value);

    QString exoticWheat();
    void setExoticWheat(QString value);

    QString thousandWeight();
    void setThousandWeight(QString value);

    QString jiejiemai();
    void setJiejiemai(QString value);

    QString white_count_Wheat();
    void setWhite_count_Wheat(QString value);

    QString volumeWeight();
    void setVolumeWeight(QString value);

    QString binbMassRatio();
    void setBinbMassRatio(QString value);

    QString binbParticlesRatio();
    void setBinbParticlesRatio(QString value);

    QString m_white_weight_Wheat();
    void setM_white_weight_Wheat(QString value);

    QString red_count_Wheat();
    void setRed_count_Wheat(QString value);

    QString red_weight_Wheat();
    void setRed_weight_Wheat(QString value);

    int wheatUnsoundType();
    void setWheatUnsoundType(int value);

Q_INVOKABLE void clear();

private:
    void getconfig();
signals:
    void bbMassRatioChanged();
    void bbParticlesRatioChanged();
    void syMassRatioChanged();
    void syParticlesRatioChanged();
    void smMassRatioChanged();
    void smParticlesRatioChanged();
    void csMassRatioChanged();
    void csParticlesRatioChanged();
    void psMassRatioChanged();
    void psParticlesRatioChanged();
    void hpMassRatioChanged();
    void hpParticlesRatioChanged();

    void massRatioChanged();
    void particlesRatioChanged();

    void sigResult(QStringList,QStringList);

    void unsoundChanged();
    void impuritiesChanged();
    void moistureChanged();
    void exoticWheatChanged();
    void thousandWeightChanged();
    void jiejiemaiChanged();
    void whiteWheat_count_Changed();
    void volumeWeightChanged();

    void binbMassRatioChanged();
    void binbParticlesRatioChanged();

    void m_white_weight_WheatChanged();
    void red_count_WheatChanged();
    void red_weight_WheatChanged();

    void wheatUnsoundTypeChanged();
public:
    QVector<QStringList> setQuota() override;
    void realShowQuota(GZ_GrainEval_Result_S& result) override;
    void setSegtype(imgDataStruct&,GZ_GrainEval_Result_S&) override;
    int  getSegtype(imgDataStruct&,int num) override;
    QString setGrainType() override;
private:
    std::shared_ptr<ResultDataPrivate> m_resultData;
    int m_unsoundType    {1};
};

#endif // MATHWHEATMODEL_H
