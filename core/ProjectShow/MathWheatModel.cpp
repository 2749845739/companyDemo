#include "MathWheatModel.h"
#include <numeric>
class ResultDataPrivate{
public:
    QString m_bbMassRatio  {};
    QString m_bbParticlesRatio  {};
    QString m_syMassRatio  {};
    QString m_syParticlesRatio  {};
    QString m_smMassRatio    {};
    QString m_smParticlesRatio   {};

    QString m_csMassRatio  {};
    QString m_csParticlesRatio  {};
    QString m_psMassRatio  {};
    QString m_psParticlesRatio  {};
    QString m_hpMassRatio    {};
    QString m_hpParticlesRatio   {};

    QString m_massRatio   {};
    QString m_particlesPatio   {};

    QString m_unsound  {"0.0"}; //不完善粒
    QString m_impurities {"0.0"};// 杂质
    QString m_moisture {"0.0"};// 水分
    QString m_exoticWheat {"0.0"}; //异种粮比例
    QString m_thousandWeight {"0.0"}; // 千粒重
    QString m_jiejiemai {"0.0"}; // 节节麦比例
    QString m_white_count_Wheat {""}; //白麦
    QString m_white_weight_Wheat {""};

    QString m_red_count_Wheat {""}; //白麦
    QString m_red_weight_Wheat {""};

    QString m_volumeWeight {"0.0"}; //白麦

    QString m_binbMassRatio  {};
    QString m_binbParticlesRatio  {};
    int m_wheatUnsoundType  {1};
};
MathWheatModel::MathWheatModel(std::shared_ptr<BaseParameter> base)
    :MathBaseModel(base),m_resultData(std::make_shared<ResultDataPrivate>())
{
    //qRegisterMetaType<processResult>("processResult");
    getconfig();

}
QString MathWheatModel::bbMassRatio()
{
    return m_resultData->m_bbMassRatio;
}

void MathWheatModel::setBbMassRatio(QString ratio)
{
    m_resultData->m_bbMassRatio=ratio;
    emit bbMassRatioChanged();
}

QString MathWheatModel::bbParticlesRatio()
{
    return m_resultData->m_bbParticlesRatio;
}

void MathWheatModel::setBbParticlesRatio(QString ratio)
{
    m_resultData->m_bbParticlesRatio=ratio;
    emit bbParticlesRatioChanged();
}

QString MathWheatModel::syMassRatio()
{
    return  m_resultData->m_syMassRatio;
}

void MathWheatModel::setSyMassRatio(QString ratio)
{
    m_resultData->m_syMassRatio=ratio;
    emit syMassRatioChanged();
}

QString MathWheatModel::syParticlesRatio()
{
    return m_resultData->m_syParticlesRatio;
}

void MathWheatModel::setSyParticlesRatio(QString ratio)
{
    m_resultData->m_syParticlesRatio=ratio;
    emit syParticlesRatioChanged();
}

QString MathWheatModel::smMassRatio()
{
    return  m_resultData->m_smMassRatio;
}

void MathWheatModel::setSmMassRatio(QString ratio)
{
    m_resultData->m_smMassRatio=ratio;
    emit smMassRatioChanged();
}

QString MathWheatModel::smParticlesRatio()
{
    return m_resultData->m_smParticlesRatio;
}

void MathWheatModel::setSmParticlesRatio(QString ratio)
{
    m_resultData->m_smParticlesRatio=ratio;
    emit smParticlesRatioChanged();
}

QString MathWheatModel::csMassRatio()
{
    return  m_resultData->m_csMassRatio;
}

void MathWheatModel::setCsMassRatio(QString ratio)
{
    m_resultData->m_csMassRatio=ratio;
    emit csMassRatioChanged();
}

QString MathWheatModel::csParticlesRatio()
{
    return m_resultData->m_csParticlesRatio;
}

void MathWheatModel::setCsParticlesRatio(QString ratio)
{
    m_resultData->m_csParticlesRatio=ratio;
    emit csParticlesRatioChanged();
}

QString MathWheatModel::psMassRatio()
{
    return m_resultData->m_psMassRatio;
}

void MathWheatModel::setPsMassRatio(QString ratio)
{
    m_resultData->m_psMassRatio=ratio;
    emit psMassRatioChanged();
}

QString MathWheatModel::psParticlesRatio()
{
    return m_resultData->m_psParticlesRatio;
}

void MathWheatModel::setPsParticlesRatio(QString ratio)
{
#ifdef INFO_LOG
    qDebug() << "[MATH-WHEAT] setPsParticlesRatio:" << ratio;
#endif  // INFO_LOG
    m_resultData->m_psParticlesRatio=ratio;
    emit psParticlesRatioChanged();
}

QString MathWheatModel::hpMassRatio()
{
    return m_resultData->m_hpMassRatio;
}

void MathWheatModel::setHpMassRatio(QString ratio)
{
    m_resultData->m_hpMassRatio=ratio;
    emit hpMassRatioChanged();
}

QString MathWheatModel::hpParticlesRatio()
{
    return m_resultData->m_hpParticlesRatio;
}

void MathWheatModel::setHpParticlesRatio(QString  ratio)
{
    m_resultData->m_hpParticlesRatio=ratio;
    emit hpParticlesRatioChanged();
}

QString MathWheatModel::massRatio()
{
    return m_resultData->m_massRatio;
}

void MathWheatModel::setMassRatio(QString ratio)
{
    m_resultData->m_massRatio=ratio;
    emit massRatioChanged();
}

QString MathWheatModel::particlesRatio()
{
    return m_resultData->m_particlesPatio;
}

void MathWheatModel::setParticlesRatio(QString ratio)
{
    m_resultData->m_particlesPatio=ratio;
    emit particlesRatioChanged();
}

QString MathWheatModel::unsound()
{
    return m_resultData->m_unsound;
}

void MathWheatModel::setUnsound(QString value)
{
    m_resultData->m_unsound=value;
    emit unsoundChanged();
}

QString MathWheatModel::impurities()
{
    return m_resultData->m_impurities;
}

void MathWheatModel::setImpurities(QString value)
{
    m_resultData->m_impurities=value;
#ifdef INFO_LOG
    qDebug() << "[MATH-WHEAT] impuriyies:" << value <<", "<< m_resultData->m_impurities;
#endif  // INFO_LOG
    emit impuritiesChanged();
}

QString MathWheatModel::moisture()
{
    return m_resultData->m_moisture;
}

void MathWheatModel::setMoisture(QString value)
{
    m_resultData->m_moisture=value;
    emit moistureChanged();
}

QString MathWheatModel::exoticWheat()
{
    return m_resultData->m_exoticWheat;
}

void MathWheatModel::setExoticWheat(QString value)
{
    m_resultData->m_exoticWheat=value;
    emit exoticWheatChanged();
}

QString MathWheatModel::thousandWeight()
{
    return m_resultData->m_thousandWeight;
}

void MathWheatModel::setThousandWeight(QString value)
{
    m_resultData->m_thousandWeight=value;
    emit thousandWeightChanged();
}

QString MathWheatModel::jiejiemai()
{
    return m_resultData->m_jiejiemai;
}

void MathWheatModel::setJiejiemai(QString value)
{
    m_resultData->m_jiejiemai=value;
    emit jiejiemaiChanged();
}

QString MathWheatModel::white_count_Wheat()
{
    return m_resultData->m_white_count_Wheat;
}

void MathWheatModel::setWhite_count_Wheat(QString value)
{
    m_resultData->m_white_count_Wheat=value;
    emit whiteWheat_count_Changed();
}

QString MathWheatModel::volumeWeight()
{
    return m_resultData->m_volumeWeight;
}

void MathWheatModel::setVolumeWeight(QString value)
{
    m_resultData->m_volumeWeight=value;
    emit volumeWeightChanged();
}

QString MathWheatModel::binbMassRatio()
{
    return m_resultData->m_binbMassRatio;
}

void MathWheatModel::setBinbMassRatio(QString value)
{
    m_resultData->m_binbMassRatio=value;
    emit binbMassRatioChanged();
}

QString MathWheatModel::binbParticlesRatio()
{
    return m_resultData->m_binbParticlesRatio;
}

void MathWheatModel::setBinbParticlesRatio(QString value)
{
    m_resultData->m_binbParticlesRatio=value;
    emit binbParticlesRatioChanged();
}

QString MathWheatModel::m_white_weight_Wheat()
{
    return m_resultData->m_white_weight_Wheat;
}

void MathWheatModel::setM_white_weight_Wheat(QString value)
{
     m_resultData->m_white_weight_Wheat=value;
     emit m_white_weight_WheatChanged();
}

QString MathWheatModel::red_count_Wheat()
{
    return m_resultData->m_red_count_Wheat;
}

void MathWheatModel::setRed_count_Wheat(QString value)
{
    m_resultData->m_red_count_Wheat=value;
    emit red_count_WheatChanged();
}

QString MathWheatModel::red_weight_Wheat()
{
    return m_resultData->m_red_weight_Wheat;
}

void MathWheatModel::setRed_weight_Wheat(QString value)
{
    m_resultData->m_red_weight_Wheat=value;
    emit red_weight_WheatChanged();
}

int MathWheatModel::wheatUnsoundType()
{
    return m_resultData->m_wheatUnsoundType;
}

void MathWheatModel::setWheatUnsoundType(int value)
{
    m_resultData->m_wheatUnsoundType=value;
    emit wheatUnsoundTypeChanged();
}

void MathWheatModel::getconfig()
{
    QJsonObject rootObj = getConfig();
     if (rootObj.contains("wheatUnsoundType")) {
         m_unsoundType=rootObj.value("wheatUnsoundType").toInt();
         setWheatUnsoundType(m_unsoundType);
     }
}

void MathWheatModel::clear()
{
    setMassRatio("");
    setParticlesRatio("");
    setUnsound("");
    setImpurities("");
    setMoisture("");
    setBbMassRatio("");
    setBbParticlesRatio("");
    setSyMassRatio("");
    setSyParticlesRatio("");
    setSmMassRatio("");
    setSmParticlesRatio("");
    setCsMassRatio("");
    setCsParticlesRatio("");
    setPsMassRatio("");
    setPsParticlesRatio("");
    setHpMassRatio("");
    setHpParticlesRatio("");
    setBinbMassRatio("");
    setBinbParticlesRatio("");
    setM_white_weight_Wheat("");
    setWhite_count_Wheat("");
    setRed_count_Wheat("");
    setRed_weight_Wheat("");
}


QVector<QStringList> MathWheatModel::setQuota()
{
    float cm , hpvalue;
    float mass=0.0;
    float particles=0.0;
    QStringList normal;
    for(int i=0;i<m_base->m_result.wheat_result.weight_ratio.size();i++){
        switch (m_base->m_result.wheat_result.weight_ratio.at(i).first) {
        case wheat_t::bb: {
            QString bb=QString::number(m_base->m_result.wheat_result.weight_ratio.at(i).second*100,'f',1);
            cm=bb.toFloat();
            mass+=bb.toFloat();
            setBbMassRatio(bb);
            normal<<bb;
            break;
        }
        case wheat_t::sy:
        {
            QString sy=QString::number(m_base->m_result.wheat_result.weight_ratio.at(i).second*100,'f',1);
            setSyMassRatio(sy);
            normal<<sy;
            mass+=sy.toFloat();
            break;
        }
        case wheat_t::sm:
        {
            QString sm=QString::number(m_base->m_result.wheat_result.weight_ratio.at(i).second*100,'f',1);
            setSmMassRatio(sm);
            mass+=sm.toFloat();
            normal<<sm;
            break;
        }
        case wheat_t::cs:
        {
            QString cs=QString::number(m_base->m_result.wheat_result.weight_ratio.at(i).second*100,'f',1);
            setCsMassRatio(cs);
            mass+=cs.toFloat();
            normal<<cs;
            break;
        }
        case wheat_t::ps:
        {
            QString ps=QString::number(m_base->m_result.wheat_result.weight_ratio.at(i).second*100,'f',1);
            setPsMassRatio(ps);
            mass+=ps.toFloat();
            normal<<ps;
            break;
        }
        case wheat_t::hp:
        {
            QString hp=QString::number(m_base->m_result.wheat_result.weight_ratio.at(i).second*100,'f',1);
            setHpMassRatio(hp);
            hpvalue=hp.toFloat();
            if(m_unsoundType==1) mass+=hp.toFloat();
            normal<<hp;
            break;
        }
        default:break;
        }
    }
    if(m_unsoundType==1){
        setBinbMassRatio(QString::number(cm+hpvalue,'f',1));
    }else if(m_unsoundType==2){
        setBinbMassRatio(QString::number(cm,'f',1));
    }
    for(int i=0;i<m_base->m_result.wheat_result.count_ratio.size();i++){
        switch (m_base->m_result.wheat_result.count_ratio.at(i).first) {
        case wheat_t::bb:
            setBbParticlesRatio(QString::number(m_base->m_result.wheat_result.count_ratio.at(i).second*100,'f',1));
            particles+=QString::number(m_base->m_result.wheat_result.count_ratio.at(i).second*100,'f',1).toFloat();
#ifdef INFO_LOG
            qDebug() << "[MATH-WHEAT] bb" <<
                QString::number(m_base->m_result.wheat_result.count_ratio.at(i).second*100,'f',1).toFloat();
#endif  // INFO_LOG
             cm=QString::number(m_base->m_result.wheat_result.count_ratio.at(i).second*100,'f',1).toFloat();
            break;
        case wheat_t::sy:
            setSyParticlesRatio(QString::number(m_base->m_result.wheat_result.count_ratio.at(i).second*100,'f',1));
            particles+=QString::number(m_base->m_result.wheat_result.count_ratio.at(i).second*100,'f',1).toFloat();
#ifdef INFO_LOG
            qDebug() << "[MATH-WHEAT] sy"<<
                QString::number(m_base->m_result.wheat_result.count_ratio.at(i).second*100,'f',1).toFloat();
#endif  // INFO_LOG
            break;
        case wheat_t::sm:
            setSmParticlesRatio(QString::number(m_base->m_result.wheat_result.count_ratio.at(i).second*100,'f',1));
            particles+=QString::number(m_base->m_result.wheat_result.count_ratio.at(i).second*100,'f',1).toFloat();
#ifdef INFO_LOG
            qDebug() << "[MATH-WHEAT] sm"<<
                QString::number(m_base->m_result.wheat_result.count_ratio.at(i).second*100,'f',1).toFloat();
#endif  // INFO_LOG
            break;
        case wheat_t::cs:
            setCsParticlesRatio(QString::number(m_base->m_result.wheat_result.count_ratio.at(i).second*100,'f',1));
            particles+=QString::number(m_base->m_result.wheat_result.count_ratio.at(i).second*100,'f',1).toFloat();
#ifdef INFO_LOG
             qDebug() << "[MATH-WHEAT] cs"
                <<QString::number(m_base->m_result.wheat_result.count_ratio.at(i).second*100,'f',1).toFloat();
#endif  // INFO_LOG
            break;
        case wheat_t::ps:
            setPsParticlesRatio(QString::number(m_base->m_result.wheat_result.count_ratio.at(i).second*100,'f',1));
            particles+=QString::number(m_base->m_result.wheat_result.count_ratio.at(i).second*100,'f',1).toFloat();
#ifdef INFO_LOG
            qDebug() << "[MATH-WHEAT] particles"<<particles;
            qDebug() << "[MATH-WHEAT] ps"<<
                QString::number(m_base->m_result.wheat_result.count_ratio.at(i).second*100,'f',1).toFloat();
#endif  // INFO_LOG
            break;
        case wheat_t::hp:
            setHpParticlesRatio(QString::number(m_base->m_result.wheat_result.count_ratio.at(i).second*100,'f',1));
#ifdef INFO_LOG
             qDebug() << "[MATH-WHEAT] hp"<<
                QString::number(m_base->m_result.wheat_result.count_ratio.at(i).second*100,'f',1).toFloat();
#endif  // INFO_LOG
             hpvalue=QString::number(m_base->m_result.wheat_result.count_ratio.at(i).second*100,'f',1).toFloat();
             if(m_unsoundType==1) particles+=hpvalue;
            break;
        default:break;
        }
    }
    if(m_unsoundType==1){
        setBinbParticlesRatio(QString::number(cm+hpvalue,'f',1));
    }else if(m_unsoundType==2){
        setBinbParticlesRatio(QString::number(cm,'f',1));
    }

#ifdef INFO_LOG
    qDebug() << "[MATH-WHEAT] mass:"<< mass << "particles:"<<particles;
#endif  // INFO_LOG
    setMassRatio(QString::number(mass,'f',1));
    setParticlesRatio(QString::number(particles,'f',1));
    normal<<QString::number(mass,'f',1);

    QString white_cout="0.0", white_weight="0.0";
    white_cout=QString::number(m_base->m_result.wheat_result.whiteWheat_count_ratio*100,'f',1);
    white_weight=QString::number(m_base->m_result.wheat_result.whiteWheat_wei_ratio*100,'f',1);
    setWhite_count_Wheat(white_cout);
    setM_white_weight_Wheat(white_weight);

    auto vec_count = m_base->m_result.wheat_result.final_unsound_count;
    int total_count = std::accumulate(vec_count.begin(),vec_count.end(),0);
    if(total_count==0){
        setRed_count_Wheat("0.0");
        setRed_weight_Wheat("0.0");
    }else{
        setRed_count_Wheat(QString::number(100-white_cout.toFloat(),'f',1));
        setRed_weight_Wheat(QString::number(100-white_weight.toFloat(),'f',1));
    }
    //to ai
    {
        QStringList resultCountValue;
        QStringList resultWeightValue;
        for (int i=0;i<m_base->m_result.wheat_result.final_unsound_count.size();i++ ) {
            resultCountValue<<QString::number(m_base->m_result.wheat_result.final_unsound_count.at(i),'f',1);
        }
        for (int i=0;i<m_base->m_result.wheat_result.final_unsound_weight.size();i++ ) {
            resultWeightValue<<QString::number(m_base->m_result.wheat_result.final_unsound_weight.at(i),'f',1);
        }
        float weight;
        for(auto& it:GlobalObject::g_instance()->m_weights){
            weight+=it;
        }
        resultCountValue<<QString::number(particles,'f',1);
        resultWeightValue<<QString::number(mass,'f',1);

        resultWeightValue<<QString::number(weight,'f',1);
        //emit sigResult(resultCountValue,resultWeightValue);
        return QVector<QStringList> {normal,resultCountValue,resultWeightValue};
    }
}

void MathWheatModel::realShowQuota(GZ_GrainEval_Result_S& result)
{
    result.wheat_result.vec_recs=m_base->m_result.wheat_result.vec_recs;
    float ratio=0.0;
    for(auto& it:m_base->m_result.wheat_result.weight_ratio){
        if(it.first==wheat_t::zc){
            continue;
        }
        ratio+=it.second;
    }
    setUnsound(QString::number(ratio *100,'f',2));
    setImpurities(QString::number(m_base->m_result.wheat_result.impurity_ratio*100,'f',2));
    setMoisture(QString::number(m_base->m_result.wheat_result.moisture*100,'f',2));
    setExoticWheat(QString::number(m_base->m_result.wheat_result.exoticWheat_ratio*100,'f',2));
    setThousandWeight(QString::number(m_base->m_result.wheat_result.thousandWeight*100,'f',2));
    setJiejiemai(QString::number(m_base->m_result.wheat_result.jiejiemai_ratio*100,'f',2));

    setVolumeWeight(QString::number(m_base->m_result.wheat_result.volumeWeight*100,'f',2));
}

void MathWheatModel::setSegtype(imgDataStruct& imgData,GZ_GrainEval_Result_S& result)
{
    imgData.wheatType=result.wheat_result.vec_recs;
#ifdef INFO_LOG
    qDebug() << "[MATH-WHEAT] setSegtype" << imgData.wheatType.size();
#endif  // INFO_LOG
}

int MathWheatModel::getSegtype(imgDataStruct& data,int num)
{
    return static_cast<int>(data.wheatType.at(num).first);
}

QString MathWheatModel::setGrainType()
{
    return "wheat";
}
