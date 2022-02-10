#include "GlobalParameter.h"
#include "QDebug"
//GlobalObject* GlobalObject::g_globObject=nullptr;
GrainType GlobalObject::g_grainType=GrainType::WHEAT;
QString GlobalObject::g_deviceName="";
bool GlobalObject::g_saveOriginalImg=false;
QString GlobalObject::g_sampleId="";
QString GlobalObject::g_grainTyoe="";
QString GlobalObject::g_childType="";
GlobalObject::GlobalObject(QObject *parent):QObject(parent)
{
    qRegisterMetaType<GrainType>("GrainType");
    readConfig();
    for(int i=0;i<THREAD_COUNT;i++){
        m_mulitRes[i]=std::queue<algorithm::result>();
    }
}

void GlobalObject::readConfig()
{
    QJsonObject rootObj = getConfig();
    if(rootObj.contains("deviceName")){
        g_deviceName=rootObj.value("deviceName").toString();
    }
    if(rootObj.contains("saveOriginalImg")){
        g_saveOriginalImg=rootObj.value("saveOriginalImg").toBool();
    }
    if(rootObj.contains("grainType")){
        g_grainTyoe=rootObj.value("grainType").toString();
    }else{
        g_grainTyoe="00";
    }
    if(rootObj.contains("childType")){
        g_childType=rootObj.value("childType").toString();
    }else{
        g_childType="99";
    }
}

QString GlobalObject::getSampleid()
{
    QString it=GlobalObject::g_sampleId;
    return it;
}

void GlobalObject::setSampleid()
{
    GlobalObject::g_sampleId=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
}

void GlobalObject::saveImgEnable(bool value)
{
    emit sigSaveImg(value);
}

void GlobalObject::setGrainType(int type)
{
    switch (type) {
    case 0: g_grainType=GrainType::RICE;
        break;
    case 1: g_grainType=GrainType::WHEAT;
        break;
    case 2: g_grainType=GrainType::CRON;
        break;
    case 3: g_grainType=GrainType::SORGHUM;;
        break;
    default:break;
    }
}

void GlobalObject::closeSystem()
{
    system("poweroff");
}

BoardStatus::BoardStatus(QObject *parent):QObject(parent)
{}

void BoardStatus::handle_frame(std::string uid, board::frame frame)
{

}

void BoardStatus::handle_status(std::string uid, uint32_t status)
{
    std::cout<<"UI-handle_status:"<< static_cast<int>(status)<<std::endl;
    switch (status) {
    case BOARD_STATUS_READY:
        LOGGER_DEBUG("stop");
        emit sigResetStatus();
        break;
    case DCAMERA_STATUS_READY:
        LOGGER_DEBUG("DCAMERA_STATUS_READY");
        emit sigGrapFinsh();
        break;
    case UCAMERA_STATUS_RUN:
        LOGGER_DEBUG("CAMERA_START_STRAT");
        emit sigGrapStart();
        break;
    case KEY_STATUS_RUNNING:
        LOGGER_DEBUG("KEY_STATUS_RUNNING");
        emit sigKeypressed();
        break;
    case RECYCLE_STATUS_RUNNING:
        LOGGER_DEBUG("RECYCLE_STATUS_RUNNING");
        emit sigRecyleStatus(true);
        break;
    case RECYCLE_STATUS_READY:
        LOGGER_DEBUG("RECYCLE_STATUS_READY");
        emit sigRecyleStatus(false);
        break;
    default:break;
    }
//    if(status==BOARD_STATUS_READY){
//        LOGGER_DEBUG("stop");
//        emit sigResetStatus();
//    }if(status==DCAMERA_STATUS_READY){
//        LOGGER_DEBUG("DCAMERA_STATUS_READY");
//        emit sigGrapFinsh();
//    }if(status==UCAMERA_STATUS_RUN){
//        LOGGER_DEBUG("CAMERA_START_STRAT");
//        emit sigGrapStart();
//    }
}

SavePng::SavePng(QList<QImage> img,QObject *parent):QObject(parent),m_img(img)
{}

void SavePng::run()
{
    bool res=false;
    for(auto& it:m_img){
        res=it.save(QString(QApplication::applicationDirPath()+"/grapImg/%1.png").
                       arg(QDateTime::currentDateTime().toString("yyyy-dd-HH hh-mm-ss-zzz")));
        if(!res){
            emit sigfinshed(false);
            break;
        }
    }
    emit sigfinshed(true);
}
