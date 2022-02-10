#include "CameraProperty.h"
class CameraInfo{
public:
    explicit CameraInfo(){
    }
    QVariantList m_maxW {0,0,0};
    QVariantList m_maxH {0,0,0};
    QVariantList m_mac{0,0,0};
    QVariantList m_ip{0,0,0};

    QVariantList m_exposureTimeMax{0,0,0};
    QVariantList m_exposureTimeMin{0,0,0};

    QVariantList m_upExposureTime{0,0,0};
    QVariantList m_downExposureTime{0,0,0};

    QVariantList m_rDigitialMax{0,0,0};
    QVariantList m_rDigitialMin{0,0,0};
    QVariantList m_rDigitialCurrent {0,0,0};

    QVariantList m_gDigitialMax{0,0,0};
    QVariantList m_gDigitialMin{0,0,0};
    QVariantList m_gDigitialCurrent {0,0,0};

    QVariantList m_bDigitialMax{0,0,0};
    QVariantList m_bDigitialMin{0,0,0};
    QVariantList m_bDigitialCurrent {0,0,0};

    QVariantList m_triggerMode {0,0,0};

    QVariantList m_exposureGainCurrent {0,0,0};
    QVariantList m_exposureGainMax{0,0,0};
    QVariantList m_exposureGainMin{0,0,0};

    QVariantList m_triggerDelayCurrent {0,0,0};
    QVariantList m_triggerDelayMax{0,0,0};
    QVariantList m_triggerDelayMin{0,0,0};

    QVariantList m_vflip{false,false,false};
    QVariantList m_hflip{false,false,false};
};
QVariantList CameraProperty::maxW()
{
    return m_d->m_maxW;
}

void CameraProperty::setMaxW(QVariantList value)
{
    m_d->m_maxW=value;
    emit maxWChanged();
}

QVariantList CameraProperty::maxH()
{
    return m_d->m_maxH;
}

void CameraProperty::setMaxH(QVariantList value)
{
    m_d->m_maxH=value;
    emit maxHChanged();
}

QVariantList CameraProperty::mac()
{
    return m_d->m_mac;
}

void CameraProperty::setMac(QVariantList value)
{
    m_d->m_mac=value;
    emit macChanged();
}

QVariantList CameraProperty::ip()
{
    return m_d->m_ip;
}

void CameraProperty::setIp(QVariantList value)
{
    m_d->m_ip=value;
    emit ipChanged();
}

QVariantList CameraProperty::exposureTimeMax()
{
    return m_d->m_exposureTimeMax;
}

void CameraProperty::setExposureTimeMax(QVariantList value)
{
    m_d->m_exposureTimeMax=value;
    emit exposureTimeMaxChanged();
}

QVariantList CameraProperty::exposureTimeMin()
{
    return m_d->m_exposureTimeMin;
}

void CameraProperty::setExposureTimeMin(QVariantList vaule)
{
    m_d->m_exposureTimeMin=vaule;
    emit exposureTimeMinChanged();
}

QVariantList CameraProperty::upExposureTime()
{
    return m_d->m_upExposureTime;
}

void CameraProperty::setUpExposureTime(QVariantList vaule)
{
    m_d->m_upExposureTime=vaule;
    emit upExposureTimeChanged();
}

QVariantList CameraProperty::downExposureTime()
{
    return m_d->m_downExposureTime;
}

void CameraProperty::setDownExposureTime(QVariantList vaule)
{
    m_d->m_downExposureTime=vaule;
    emit downExposureTimeChanged();
}

QVariantList CameraProperty::rDigitialMax()
{
    return m_d->m_rDigitialMax;
}

void CameraProperty::setRDigitialMax(QVariantList value)
{
    m_d->m_rDigitialMax=value;
    emit rDigitialMaxChanged();
}

QVariantList CameraProperty::rDigitialMin()
{
    return m_d->m_rDigitialMin;
}

void CameraProperty::setRDigitialMin(QVariantList value)
{
    m_d->m_rDigitialMin=value;
    emit rDigitialMinChanged();
}

QVariantList CameraProperty::rDigitialCurrent()
{
    return m_d->m_rDigitialCurrent;
}

void CameraProperty::setRDigitialCurrent(QVariantList value)
{
    m_d->m_rDigitialCurrent=value;
    emit rDigitialCurrentChanged();
}

QVariantList CameraProperty::gDigitialMax()
{
    return m_d->m_gDigitialMax;
}

void CameraProperty::setGDigitialMax(QVariantList value)
{
    m_d->m_gDigitialMax=value;
    emit gDigitialMaxChanged();
}

QVariantList CameraProperty::gDigitialMin()
{
    return m_d->m_gDigitialMin;
}

void CameraProperty::setGDigitialMin(QVariantList value)
{
    m_d->m_gDigitialMin=value;
    emit gDigitialMinChanged();
}

QVariantList CameraProperty::gDigitialCurrent()
{
    return m_d->m_gDigitialCurrent;
}

void CameraProperty::setGDigitialCurrent(QVariantList value)
{
    m_d->m_gDigitialCurrent=value;
    emit gDigitialCurrentChanged();
}

QVariantList CameraProperty::bDigitialMax()
{
    return m_d->m_bDigitialMax;
}

void CameraProperty::setBDigitialMax(QVariantList value)
{
    m_d->m_bDigitialMax=value;
    emit bDigitialMaxChanged();
}

QVariantList CameraProperty::bDigitialMin()
{
    return m_d->m_bDigitialMin;
}

void CameraProperty::setBDigitialMin(QVariantList value)
{
    m_d->m_bDigitialMin=value;
    emit bDigitialMinChanged();
}

QVariantList CameraProperty::bDigitialCurrent()
{
    return m_d->m_bDigitialCurrent;
}

void CameraProperty::setBDigitialCurrent(QVariantList value)
{
    m_d->m_bDigitialCurrent=value;
    emit bDigitialCurrentChanged();
}

QVariantList CameraProperty::triggerMode()
{
    return m_d->m_triggerMode;
}

void CameraProperty::setTriggerMode(QVariantList value)
{
    m_d->m_triggerMode=value;
    emit triggerModeChanged();
}

QVariantList CameraProperty::exposureGainCurrent()
{
    return m_d->m_exposureGainCurrent;
}

void CameraProperty::setExposureGainCurrent(QVariantList value)
{
    m_d->m_exposureGainCurrent=value;
    emit exposureGainCurrentChanged();
}

QVariantList CameraProperty::exposureGainMax()
{
    return m_d->m_exposureGainMax;
}

void CameraProperty::setExposureGainMax(QVariantList value)
{
    m_d->m_exposureGainMax=value;
    emit exposureGainMaxChanged();
}

QVariantList CameraProperty::exposureGainMin()
{
    return m_d->m_exposureGainMin;
}

void CameraProperty::setExposureGainMin(QVariantList value)
{
    m_d->m_exposureGainMin=value;
    emit exposureGainMinChanged();
}

QVariantList CameraProperty::triggerDelayCurrent()
{
    return m_d->m_triggerDelayCurrent;
}

void CameraProperty::setTriggerDelayCurrent(QVariantList value)
{
    m_d->m_triggerDelayCurrent=value;
    emit triggerDelayCurrentChanged();
}

QVariantList CameraProperty::triggerDelayMax()
{
    return m_d->m_triggerDelayMax;
}

void CameraProperty::setTriggerDelayMax(QVariantList value)
{
    m_d->m_triggerDelayMax=value;
    emit triggerDelayMaxChanged();
}

QVariantList CameraProperty::triggerDelayMin()
{
    return m_d->m_exposureTimeMin;
}

void CameraProperty::setTriggerDelayMin(QVariantList value)
{
    m_d->m_exposureTimeMin=value;
    emit triggerDelayMinChanged();
}

QVariantList CameraProperty::vflip()
{
    return m_d->m_vflip;
}

void CameraProperty::setVflip(QVariantList value)
{
    m_d->m_vflip=value;
    emit vflipChanged();
}

QVariantList CameraProperty::hflip()
{
    return m_d->m_hflip;
}

void CameraProperty::setHflip(QVariantList value)
{
    m_d->m_hflip=value;
    emit hflipChanged();
}

CameraProperty::CameraProperty(std::shared_ptr<camera::camera> one,
                               std::shared_ptr<camera::camera> two,
                               std::shared_ptr<camera::camera> three)
    :m_d(std::make_shared<CameraInfo>())
{
    m_cameras[0]=one;
    m_cameras[1]=two;
    m_cameras[2]=three;
    initParam();
}
void CameraProperty::setTriggerMode(int id, int mode)
{
    camera::t_trig_mode value;
    switch (mode) {
    case 0:value=camera::t_trig_mode::not_trig;
        break;
    case 1:value=camera::t_trig_mode::hardware;
        break;
    case 2:value=camera::t_trig_mode::software;
        break;
    default:break;
    }
    m_cameras[id]->trigger_mode(value);
    QVariantList tmp= triggerMode();
    tmp.replace(id,mode);
    setTriggerMode(tmp);
}

void CameraProperty::setR_digitial(int id, int value)
{
    LOGGER_DEBUG("修改相机%dR通道增益:%d",id,value);
    m_cameras[id]->rgain(value);
    QVariantList tmp= rDigitialCurrent();
    tmp.replace(id,value);
    setRDigitialCurrent(tmp);
}

void CameraProperty::setG_digitial(int id, int value)
{
    LOGGER_DEBUG("修改相机%dG通道增益:%d",id,value);
    m_cameras[id]->ggain(value);
    QVariantList tmp= gDigitialCurrent();
    tmp.replace(id,value);
    setGDigitialCurrent(tmp);
}

void CameraProperty::setB_digitial(int id, int value)
{
    LOGGER_DEBUG("修改相机%dB通道增益:%d",id,value);
    m_cameras[id]->bgain(value);
    QVariantList tmp= bDigitialCurrent();
    tmp.replace(id,value);
    setBDigitialCurrent(tmp);
}

void CameraProperty::setExposureGain(int id, int value)
{
    LOGGER_DEBUG("修改相机%d曝光增益:%d",id,value);
    m_cameras[id]->exposure_gain(value);
    QVariantList tmp= exposureGainCurrent();
    tmp.replace(id,value);
    setExposureGainCurrent(tmp);
}

void CameraProperty::setTriggerDelay(int id, int value)
{
    LOGGER_DEBUG("修改相机%d触发延迟:%d",id,value);
    m_cameras[id]->trigger_delay(value);
    QVariantList tmp= triggerDelayCurrent();
    tmp.replace(id,value);
    setTriggerDelayCurrent(tmp);
}

void CameraProperty::setvFlip(int id, bool value)
{
    LOGGER_DEBUG("修改相机%d垂直翻转:%d",id,value);
    m_cameras[id]->vflip(value);
    QVariantList tmp= vflip();
    tmp.replace(id,value);
    setVflip(tmp);
}

void CameraProperty::sethFlip(int id, bool value)
{
    LOGGER_DEBUG("修改相机%d水平翻转:%d",id,value);
    m_cameras[id]->hflip(value);
    QVariantList tmp= hflip();
    tmp.replace(id,value);
    setHflip(tmp);
}

void CameraProperty::setExposuse(int id, int value)
{
    LOGGER_DEBUG("修改相机%d曝光时间:%d",id,value);
    m_cameras[id]->exposure_time(value);
    QVariantList tmp= upExposureTime();
    tmp.replace(id,value);
    setUpExposureTime(tmp);
}

void CameraProperty::setUpExposuse(int id, int value)
{
    QVariantList tmp= upExposureTime();
    tmp.replace(id,value);
    setUpExposureTime(tmp);
    emit sigCameraBrightTime(QString(m_cameras[id]->uid().c_str()),value);
}

void CameraProperty::setDownpExposuse(int id, int value)
{
    QVariantList tmp= downExposureTime();
    tmp.replace(id,value);
    setDownExposureTime(tmp);
    emit sigCameraDarkTime(QString(m_cameras[id]->uid().c_str()),value);
}

void CameraProperty::saveCameraConfig()
{
    switch (GlobalObject::g_grainType) {
        case GrainType::WHEAT: saveCameraConfig("wheat");
        break;
        case GrainType::RICE: saveCameraConfig("wheat");
        break;
        case GrainType::CRON: saveCameraConfig("wheat");
        break;
        case GrainType::SORGHUM: saveCameraConfig("wheat");
        break;
        default:saveCameraConfig("wheat");
        break;
    }
}

void CameraProperty::initParam()
{
    QVariantList maxW;
    QVariantList maxH;
    QVariantList ip;
    QVariantList mac;
    QVariantList exposureTimeMax;
    QVariantList exposureTimeMin;
    QVariantList rDigitialMax;
    QVariantList rDigitialMin;
    QVariantList gDigitialMax;
    QVariantList gDigitialMin;
    QVariantList bDigitialMax;
    QVariantList bDigitialMin;
    QVariantList exposureGainMax;
    QVariantList exposureGainMin;
    QVariantList triggerDelayMax;
    QVariantList triggerDelayMin;
    QVariantList vflip;
    QVariantList hflip;
    for(auto& it:m_cameras){
        maxW.append(it->max_w());
        maxH.append(it->max_h());
        ip.append(QString(it->ip().c_str()));
        mac.append(QString(it->mac().c_str()));
        std::uint32_t Min , Max;
        it->exposure_time_range(&Min,&Max);
        exposureTimeMin.append(Min);
        exposureTimeMax.append(Max);

        LOGGER_DEBUG("曝光时间最小值:%d - 曝光时间最大值:%d",Min,Max);

        it->rgain_range(&Min,&Max);
        rDigitialMax.append(Max);
        rDigitialMin.append(Min);
        LOGGER_DEBUG("r通道增益最小值:%d - r通道增益最大值:%d",Min,Max);

        it->ggain_range(&Min,&Max);
        gDigitialMax.append(Max);
        gDigitialMin.append(Min);
        LOGGER_DEBUG("g通道增益最小值:%d - g通道增益最大值:%d",Min,Max);

        it->bgain_range(&Min,&Max);
        bDigitialMax.append(Max);
        bDigitialMin.append(Min);
        LOGGER_DEBUG("b通道增益最小值:%d - b通道增益最大值:%d",Min,Max);

        it->exposure_gain_range(&Min,&Max);
        exposureGainMax.append(Max);
        exposureGainMin.append(Min);
        LOGGER_DEBUG("曝光增益最小值:%d - 曝光增益最大值:%d",Min,Max);

        it->trigger_delay_range(&Min,&Max);
        triggerDelayMax.append(Max);
        triggerDelayMin.append(Min);
        LOGGER_DEBUG("触发延迟最小值:%d - 触发延迟最大值:%d",Min,Max);

        vflip.append(it->vflip());
        hflip.append(it->hflip());
        LOGGER_DEBUG("水平翻转:%d - 垂直翻转:%d",it->vflip(),it->hflip());
    }
    setMaxW(maxW);
    setMaxH(maxH);
    setIp(ip);
    setMac(mac);
    setExposureTimeMin(exposureTimeMin);
    setExposureTimeMax(exposureTimeMax);
//    setTriggerDelayMin(triggerDelayMin);
//    setTriggerDelayMax(triggerDelayMax);
    setRDigitialMin(rDigitialMin);
    setRDigitialMax(rDigitialMax);
    setGDigitialMin(gDigitialMin);
    setGDigitialMax(gDigitialMax);
    setBDigitialMin(bDigitialMin);
    setBDigitialMax(bDigitialMax);
    setExposureGainMax(exposureGainMax);
    setExposureGainMin(exposureGainMin);
    setVflip(vflip);
    setHflip(hflip);

//    m_cameras[0]->rgain(2100);
//    m_cameras[0]->ggain(1000);
//    m_cameras[0]->bgain(1800);

//    m_cameras[1]->rgain(2100);
//    m_cameras[1]->ggain(1000);
//    m_cameras[1]->bgain(1800);

//    m_cameras[2]->rgain(2200);
//    m_cameras[2]->ggain(1000);
//    m_cameras[2]->bgain(1800);
//    m_cameras[2]->exposure_time(880);
}

void CameraProperty::setCameraInfo()
{
    switch (GlobalObject::g_grainType) {
        case GrainType::WHEAT: readConfig("wheat");
        break;
        case GrainType::RICE: readConfig("wheat");
        break;
        case GrainType::CRON: readConfig("wheat");
        break;
        case GrainType::SORGHUM: readConfig("wheat");
        break;
    default:readConfig("wheat");
        break;
    }
}

void CameraProperty::readConfig(QString grainType)
{
    QJsonObject rootObj = getConfig();
    if(rootObj.contains(grainType)){
        QJsonObject objNode = rootObj.value(grainType).toObject();
        if(objNode.contains("Camera"))
        {
            QJsonObject obj = objNode.value("Camera").toObject();
            if(obj.contains("cameraOne")){
                QJsonObject tmp=obj.value("cameraOne").toObject();
                if(tmp.contains("DownExposureTime")){
                    emit sigCameraDarkTime(QString(m_cameras[0]->uid().c_str()),tmp.value("DownExposureTime").toInt());
                    QVariantList varlist = downExposureTime();
                    varlist.replace(0,tmp.value("DownExposureTime").toInt());
                    setDownExposureTime(varlist);
                    LOGGER_DEBUG("上相机暗畅曝光时间:%d",tmp.value("DownExposureTime").toInt());
                }
                if(tmp.contains("UPExposureTime")){
                    emit sigCameraBrightTime(QString(m_cameras[0]->uid().c_str()),tmp.value("UPExposureTime").toInt());
                    QVariantList varlist = upExposureTime();
                    varlist.replace(0,tmp.value("UPExposureTime").toInt());
                    setUpExposureTime(varlist);
                    LOGGER_DEBUG("上相机明畅曝光时间:%d",tmp.value("UPExposureTime").toInt());
                }
                if(tmp.contains("ExposureGain")){
                    setExposureGain(0,
                                    tmp.value("ExposureGain").toInt());
                    LOGGER_DEBUG("上相机曝光增益:%d",tmp.value("ExposureGain").toInt());
                }
//                if(tmp.contains("TriggerDelay")){
//                    setTriggerDelay(0,tmp.value("TriggerDelay").toInt());
//                    LOGGER_DEBUG("上相机触发延迟:%d",tmp.value("TriggerDelay").toInt());
//                }
                if(tmp.contains("RGain")){
                    setR_digitial(0,tmp.value("RGain").toInt());
                    LOGGER_DEBUG("上相机R通道增益:%d",tmp.value("RGain").toInt());
                }
                if(tmp.contains("GGain")){
                    setG_digitial(0,tmp.value("GGain").toInt());
                    LOGGER_DEBUG("上相机G通道增益:%d",tmp.value("GGain").toInt());
                }
                if(tmp.contains("BGain")){
                    setB_digitial(0,tmp.value("BGain").toInt());
                    LOGGER_DEBUG("上相机B通道增益:%d",tmp.value("BGain").toInt());
                }
                if(tmp.contains("vFlip")){
                    setvFlip(0,tmp.value("vFlip").toBool());
                    LOGGER_DEBUG("上相机垂直翻转:%d",tmp.value("vFlip").toBool());
                }
                if(tmp.contains("hFlip")){
                    sethFlip(0,tmp.value("hFlip").toBool());
                    LOGGER_DEBUG("上相机水平翻转:%d",tmp.value("hFlip").toBool());
                }
            }
            if(obj.contains("cameraTwo")){
                QJsonObject tmp=obj.value("cameraTwo").toObject();
                if(tmp.contains("DownExposureTime")){
                    emit sigCameraDarkTime(QString(m_cameras[1]->uid().c_str()),tmp.value("DownExposureTime").toInt());
                    QVariantList varlist = downExposureTime();
                    varlist.replace(1,tmp.value("DownExposureTime").toInt());
                    setDownExposureTime(varlist);
                    LOGGER_DEBUG("下相机暗畅曝光时间:%d",tmp.value("DownExposureTime").toInt());
                }
                if(tmp.contains("UPExposureTime")){
                    emit sigCameraBrightTime(QString(m_cameras[1]->uid().c_str()),tmp.value("UPExposureTime").toInt());
                    QVariantList varlist = upExposureTime();
                    varlist.replace(1,tmp.value("UPExposureTime").toInt());
                    setUpExposureTime(varlist);
                    LOGGER_DEBUG("下相机明畅曝光时间:%d",tmp.value("UPExposureTime").toInt());
                }
                if(tmp.contains("ExposureGain")){
                    setExposureGain(1,
                                    tmp.value("ExposureGain").toInt());
                    LOGGER_DEBUG("下相机曝光增益:%d",tmp.value("ExposureGain").toInt());
                }
//                if(tmp.contains("TriggerDelay")){
//                    setTriggerDelay(1,tmp.value("TriggerDelay").toInt());
//                    LOGGER_DEBUG("下相机触发延迟:%d",tmp.value("TriggerDelay").toInt());
//                }
                if(tmp.contains("RGain")){
                    setR_digitial(1,tmp.value("RGain").toInt());
                    LOGGER_DEBUG("下相机R通道增益:%d",tmp.value("RGain").toInt());
                }
                if(tmp.contains("GGain")){
                    setG_digitial(1,tmp.value("GGain").toInt());
                    LOGGER_DEBUG("下相机G通道增益:%d",tmp.value("GGain").toInt());
                }
                if(tmp.contains("BGain")){
                    setB_digitial(1,tmp.value("BGain").toInt());
                    LOGGER_DEBUG("下相机B通道增益:%d",tmp.value("BGain").toInt());
                }
                if(tmp.contains("vFlip")){
                    setvFlip(1,tmp.value("vFlip").toBool());
                    LOGGER_DEBUG("下相机垂直翻转:%d",tmp.value("vFlip").toBool());
                }
                if(tmp.contains("hFlip")){
                    sethFlip(1,tmp.value("hFlip").toBool());
                    LOGGER_DEBUG("下相机水平翻转:%d",tmp.value("hFlip").toBool());
                }
            }
            if(obj.contains("cameraThree")){
                QJsonObject tmp=obj.value("cameraThree").toObject();
                if(tmp.contains("UPExposureTime")){
                    setExposuse(2,tmp.value("UPExposureTime").toInt());
                    LOGGER_DEBUG("流量相机暗畅曝光时间:%d",tmp.value("DownExposureTime").toInt());
                }
                if(tmp.contains("ExposureGain")){
                    setExposureGain(2,
                                    tmp.value("ExposureGain").toInt());
                    LOGGER_DEBUG("流量相机曝光增益:%d",tmp.value("ExposureGain").toInt());
                }
//                if(tmp.contains("TriggerDelay")){
//                    setTriggerDelay(2,tmp.value("TriggerDelay").toInt());
//                    LOGGER_DEBUG("流量相机触发延迟:%d",tmp.value("TriggerDelay").toInt());
//                }
                if(tmp.contains("RGain")){
                    setR_digitial(2,tmp.value("RGain").toInt());
                    LOGGER_DEBUG("流量相机R通道增益:%d",tmp.value("RGain").toInt());
                }
                if(tmp.contains("GGain")){
                    setG_digitial(2,tmp.value("GGain").toInt());
                    LOGGER_DEBUG("流量相机G通道增益:%d",tmp.value("GGain").toInt());
                }
                if(tmp.contains("BGain")){
                    setB_digitial(2,tmp.value("BGain").toInt());
                    LOGGER_DEBUG("流量相机B通道增益:%d",tmp.value("BGain").toInt());
                }
                if(tmp.contains("vFlip")){
                    setvFlip(2,tmp.value("vFlip").toBool());
                    LOGGER_DEBUG("流量相机垂直翻转:%d",tmp.value("vFlip").toBool());
                }
                if(tmp.contains("hFlip")){
                    sethFlip(2,tmp.value("hFlip").toBool());
                    LOGGER_DEBUG("流量相机水平翻转:%d",tmp.value("hFlip").toBool());
                }
            }
        }
    }

}

void CameraProperty::saveCameraConfig(QString grainType)
{
    QJsonObject rootObj = getConfig();
    if(rootObj.contains(grainType)){
        QJsonObject objNode = rootObj.find(grainType).value().toObject();
        if(objNode.contains("Camera"))
        {
            QJsonObject obj = objNode.find("Camera").value().toObject();
            if(obj.contains("cameraOne")){
                QJsonObject tmp=obj.find("cameraOne").value().toObject();
                if(tmp.contains("DownExposureTime")){
                    tmp.find("DownExposureTime").value()=downExposureTime().at(0).toInt();
                    LOGGER_DEBUG("上相机暗场曝光时间:%d",downExposureTime().at(0).toInt());
                }
                if(tmp.contains("UPExposureTime")){
                    tmp.find("UPExposureTime").value()=upExposureTime().at(0).toInt();
                    LOGGER_DEBUG("上相机明场曝光时间:%d",upExposureTime().at(0).toInt());
                }
                if(tmp.contains("ExposureGain")){
                    tmp.find("ExposureGain").value()=exposureGainCurrent().at(0).toInt();
                    LOGGER_DEBUG("上相机曝光增益:%d",exposureGainCurrent().at(0).toInt());
                }
//                if(tmp.contains("TriggerDelay")){
//                    tmp.find("TriggerDelay").value()=triggerDelayCurrent().at(0).toInt();
//                    LOGGER_DEBUG("上相机触发延迟:%d",triggerDelayCurrent().at(0).toInt());
//                }
                if(tmp.contains("RGain")){
                    tmp.find("RGain").value()=rDigitialCurrent().at(0).toInt();
                    LOGGER_DEBUG("上相机R通道增益:%d",rDigitialCurrent().at(0).toInt());
                }
                if(tmp.contains("GGain")){
                    tmp.find("GGain").value()=gDigitialCurrent().at(0).toInt();
                    LOGGER_DEBUG("上相机G通道增益:%d",gDigitialCurrent().at(0).toInt());
                }
                if(tmp.contains("BGain")){
                    tmp.find("BGain").value()=bDigitialCurrent().at(0).toInt();
                    LOGGER_DEBUG("上相机B通道增益:%d",bDigitialCurrent().at(0).toInt());
                }
                if(tmp.contains("vFlip")){
                    tmp.find("vFlip").value()=vflip().at(0).toBool();
                    LOGGER_DEBUG("上相机垂直翻转:%d",vflip().at(0).toBool());
                }
                if(tmp.contains("hFlip")){
                    tmp.find("hFlip").value()=hflip().at(0).toBool();
                    LOGGER_DEBUG("上相机水平翻转:%d",hflip().at(0).toBool());
                }
                obj.find("cameraOne").value()=tmp;
            }
            if(obj.contains("cameraTwo")){
                QJsonObject tmp=obj.find("cameraTwo").value().toObject();
                if(tmp.contains("DownExposureTime")){
                    tmp.find("DownExposureTime").value()=downExposureTime().at(1).toInt();
                    LOGGER_DEBUG("下相机暗场曝光时间:%d",downExposureTime().at(1).toInt());
                }
                if(tmp.contains("UPExposureTime")){
                    tmp.find("UPExposureTime").value()=upExposureTime().at(1).toInt();
                    LOGGER_DEBUG("下相机明场曝光时间:%d",upExposureTime().at(1).toInt());
                }
                if(tmp.contains("ExposureGain")){
                    tmp.find("ExposureGain").value()=exposureGainCurrent().at(1).toInt();
                    LOGGER_DEBUG("下相机曝光增益:%d",exposureGainCurrent().at(1).toInt());
                }
//                if(tmp.contains("TriggerDelay")){
//                    tmp.find("TriggerDelay").value()=triggerDelayCurrent().at(1).toInt();
//                    LOGGER_DEBUG("下相机触发延迟:%d",triggerDelayCurrent().at(1).toInt());
//                }
                if(tmp.contains("RGain")){
                    tmp.find("RGain").value()=rDigitialCurrent().at(1).toInt();
                    LOGGER_DEBUG("下相机R通道增益:%d",rDigitialCurrent().at(1).toInt());
                }
                if(tmp.contains("GGain")){
                    tmp.find("GGain").value()=gDigitialCurrent().at(1).toInt();
                    LOGGER_DEBUG("下相机G通道增益:%d",gDigitialCurrent().at(1).toInt());
                }
                if(tmp.contains("BGain")){
                    tmp.find("BGain").value()=bDigitialCurrent().at(1).toInt();
                    LOGGER_DEBUG("下相机B通道增益:%d",bDigitialCurrent().at(1).toInt());
                }
                if(tmp.contains("vFlip")){
                    tmp.find("vFlip").value()=vflip().at(1).toBool();
                    LOGGER_DEBUG("下相机垂直翻转:%d",vflip().at(1).toBool());
                }
                if(tmp.contains("hFlip")){
                    tmp.find("hFlip").value()=hflip().at(1).toBool();
                    LOGGER_DEBUG("下相机水平翻转:%d",hflip().at(1).toBool());
                }
                obj.find("cameraTwo").value()=tmp;
            }
            if(obj.contains("cameraThree")){
                QJsonObject tmp=obj.find("cameraThree").value().toObject();
                if(tmp.contains("UPExposureTime")){
                    tmp.find("UPExposureTime").value()=upExposureTime().at(2).toInt();
                    LOGGER_DEBUG("流量相机曝光时间:%d",upExposureTime().at(2).toInt());
                }
                if(tmp.contains("ExposureGain")){
                    tmp.find("ExposureGain").value()=exposureGainCurrent().at(2).toInt();
                    LOGGER_DEBUG("流量相机曝光增益:%d",exposureGainCurrent().at(2).toInt());
                }
//                if(tmp.contains("TriggerDelay")){
//                    tmp.find("TriggerDelay").value()=triggerDelayCurrent().at(2).toInt();
//                    LOGGER_DEBUG("流量相机触发延迟:%d",triggerDelayCurrent().at(0).toInt());
//                }
                if(tmp.contains("RGain")){
                    tmp.find("RGain").value()=rDigitialCurrent().at(2).toInt();
                    LOGGER_DEBUG("流量相机R通道增益:%d",rDigitialCurrent().at(2).toInt());
                }
                if(tmp.contains("GGain")){
                    tmp.find("GGain").value()=gDigitialCurrent().at(2).toInt();
                    LOGGER_DEBUG("流量相机G通道增益:%d",gDigitialCurrent().at(2).toInt());
                }
                if(tmp.contains("BGain")){
                    tmp.find("BGain").value()=bDigitialCurrent().at(2).toInt();
                    LOGGER_DEBUG("流量相机B通道增益:%d",bDigitialCurrent().at(2).toInt());
                }
                if(tmp.contains("vFlip")){
                    tmp.find("vFlip").value()=vflip().at(2).toBool();
                    LOGGER_DEBUG("流量相机垂直翻转:%d",vflip().at(2).toBool());
                }
                if(tmp.contains("hFlip")){
                    tmp.find("vFlip").value()=hflip().at(2).toBool();
                    LOGGER_DEBUG("流量相机水平翻转:%d",hflip().at(2).toBool());
                }
                obj.find("cameraThree").value()=tmp;
            }
            objNode.find("Camera").value()=obj;
        }
        rootObj.find(grainType).value()=objNode;
    }
    QFile File(QApplication::applicationDirPath()+"/config.json");
    QJsonDocument doc;
    doc.setObject(rootObj);
    File.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    File.write(doc.toJson());
    File.close();
}

