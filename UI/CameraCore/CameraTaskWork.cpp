#include "CameraTaskWork.h"
#include "AbstractCameraState.h"

bool CameraTaskWork::isStart()
{
    return m_isStart;
}

void CameraTaskWork::setIsStart(bool value)
{
    m_isStart=value;
    emit isStartChanged();
}

bool CameraTaskWork::isPause()
{
    return m_isPause;
}

void CameraTaskWork::setIsPause(bool value)
{
    m_isPause=value;
    emit isPauseChanged();
}

bool CameraTaskWork::isStop()
{
    return m_isStop;
}

void CameraTaskWork::setIsStop(bool value)
{
    m_isStop=value;
    emit isStopChanged();
}

bool CameraTaskWork::isStoped()
{
    return m_isStoped;
}

void CameraTaskWork::setIsStoped(bool value)
{
    m_isStoped=value;
    emit isStopedChanged();
}

int CameraTaskWork::currentStatus()
{
    return m_currntStates;
}

void CameraTaskWork::setCurrentStatus(int value)
{
    m_currntStates=value;
    emit currentStatusChanged();
}

bool CameraTaskWork::changeMode()
{
    return m_canChangeMode;
}

void CameraTaskWork::setChangeMode(bool value)
{
    m_canChangeMode=value;
    emit changeModeChanged();
}

bool CameraTaskWork::isCalibrate()
{
    return m_isCalibrate;
}

void CameraTaskWork::setIsCalibrate(bool value)
{
    m_isCalibrate=value;
    emit isCalibrateChanged();
}

bool CameraTaskWork::isGraping()
{
    return m_isGraping;
}

void CameraTaskWork::setIsGraping(bool value)
{
    m_isGraping=value;
    emit isGrapingChanged();
}

QVariantList CameraTaskWork::cameraOneRate()
{
    return m_cameraOneRate;
}

void CameraTaskWork::setCameraOneRate(QVariantList value)
{
    m_cameraOneRate=value;
    emit cameraOneRateChanged();
}

QVariantList CameraTaskWork::cameraTwoRate()
{
    return m_cameraTwoRate;
}

void CameraTaskWork::setCameraTwoRate(QVariantList value)
{
    m_cameraTwoRate=value;
    emit cameraTwoRateChanged();
}

//int CameraTaskWork::currntStates()
//{
//    return m_currntStates;
//}

void CameraTaskWork::setCurrntStates(int value)
{
    switch (value) {
    case 0:m_policy=cpolicy::none;
           m_states[0]->handel(shared_from_this());
        break;
    case 1:m_policy=cpolicy::ulight;
           m_states[0]->handel(shared_from_this());
           m_states[1]->handel(shared_from_this());
           m_isCalibrate=true;
           GlobalObject::g_instance()->saveImgEnable(false);
        break;
    case 2:m_policy=cpolicy::dlight;
           m_states[0]->handel(shared_from_this());
           m_states[2]->handel(shared_from_this());
           m_isCalibrate=true;
           GlobalObject::g_instance()->saveImgEnable(false);
        break;
    case 3:m_policy=cpolicy::inturn;
           m_states[0]->handel(shared_from_this());
           m_states[3]->handel(shared_from_this());
           m_isCalibrate=true;
           GlobalObject::g_instance()->saveImgEnable(false);
        break;
    default:break;
    }
    setCurrentStatus(value);
}

void CameraTaskWork::start(bool value)
{
    if(value){
        setIsStart(true);
        setIsPause(false);
        setIsStop(false);
        setIsStoped(false);
    }else{
        setIsStart(true);
        setIsPause(true);
        setIsStop(false);
        setIsStoped(false);
    }
    LOGGER_DEBUG("start task:%d",value);
    m_generator->run(value);
    GlobalObject::g_instance()->saveImgEnable(true);
}

void CameraTaskWork::stop()
{
    setCurrentStatus(0);
    setIsStart(false);
    setIsPause(false);
    setIsStop(true);
    setIsStoped(false);
    m_generator->stop();
}

void CameraTaskWork::setUpExposeTime(int id,int value)
{
    LOGGER_DEBUG("设置相机的明场曝光:%d",value);
    id==0?emit sigUpExpouse(QString(m_ucam->uid().c_str()),value):
          emit sigUpExpouse(QString(m_dcam->uid().c_str()),value);
}

void CameraTaskWork::setDwonExposeTime(int id, int value)
{
    LOGGER_DEBUG("设置相机的暗场曝光:%d",value);
    id==0?emit sigDownExpouse(QString(m_ucam->uid().c_str()),value):
          emit sigDownExpouse(QString(m_dcam->uid().c_str()),value);
}

void CameraTaskWork::grapImg()
{
    setIsGraping(true);
    m_MultilightCameraDateCore->GrapImg();
}

void CameraTaskWork::openDir()
{
    QDesktopServices::openUrl(QUrl(QApplication::applicationDirPath()
                                   +"/grapImg"));
}

CameraTaskWork::CameraTaskWork(std::shared_ptr<camera::camera> ucam,
                               std::shared_ptr<camera::camera> dcam,
                               std::shared_ptr<board::board> bd,
                               std::string grain_type,
                               std::string abnormal_type,
                               QObject* parent)
  :QObject(parent),m_ucam(ucam),m_dcam(dcam),m_timer(new QTimer(this))
{
    m_states.insert(0,new CameraNonetState(this));
    m_states.insert(1,new CameraUlightState(this));
    m_states.insert(2,new CameraDlightState(this));
    m_states.insert(3,new CameraInturnState(this));
    //m_cameraState=m_states[0];
    m_generator=std::make_shared<calibrate::calibrator>(ucam,dcam,bd,
                                                        grain_type,abnormal_type);
    m_MultilightCameraDateCore=std::make_shared<MultilightCameraDateCore>();
    m_generator->attach(m_MultilightCameraDateCore);
    connect(m_MultilightCameraDateCore.get(),&MultilightCameraDateCore::sigsaveimg,[this](bool value){
        emit sigGrapImg(value);
        setIsGraping(false);
    });
    m_boardStatus=std::make_shared<BoardStatus>();
    bd->attach(m_boardStatus);
    connect(m_boardStatus.get(),&BoardStatus::sigResetStatus,[this]{
        setIsStart(false);
        setIsPause(false);
        setIsStop(false);
        setIsStoped(true);
        LOGGER_DEBUG("slotReset");
    });
    connect(m_boardStatus.get(),&BoardStatus::sigGrapStart,[this]{
        LOGGER_DEBUG("GrapStarth");
        setChangeMode(false); //正常开始拍照
    });
    connect(m_boardStatus.get(),&BoardStatus::sigGrapFinsh,[this]{
        LOGGER_DEBUG("GrapFinsh");//正常拍照结束
        setChangeMode(true);
        setCurrentStatus(0);
        setIsCalibrate(false);
    });
    m_timer->setInterval(1000);
    connect(m_timer,&QTimer::timeout,this,&CameraTaskWork::slotCameraRates);
    m_timer->start();
}
void CameraTaskWork::slotCameraRates()
{
    QVariantList rate;
    float collectFrameRate;
    std::uint32_t lostFrameRate;
    std::uint32_t currentFrameRate;
    m_ucam->get_frame_rate(&collectFrameRate,&lostFrameRate);
    currentFrameRate = m_MultilightCameraDateCore->getShowFramRate() - m_frontFrameRate;
    //m_frontFrameRate=m_MultilightCameraDateCore->getShowFramRate();
    rate.append(QString::number(collectFrameRate,'f',1));
    rate.append(QString::number(lostFrameRate));
    rate.append(QString::number(currentFrameRate));
    setCameraOneRate(rate);

    rate.clear();
    m_dcam->get_frame_rate(&collectFrameRate,&lostFrameRate);
    currentFrameRate = m_MultilightCameraDateCore->getShowFramRate() - m_frontFrameRate;
    m_frontFrameRate=m_MultilightCameraDateCore->getShowFramRate();
    rate.append(QString::number(collectFrameRate,'f',1));
    rate.append(QString::number(lostFrameRate));
    rate.append(QString::number(currentFrameRate));
    setCameraTwoRate(rate);
}
