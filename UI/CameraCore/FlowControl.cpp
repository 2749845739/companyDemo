#include "FlowControl.h"
#include <QApplication>
#include "Gzlogger.h"
bool FlowControl::boardStart()
{
    return m_boardStart;
}

void FlowControl::setBoardStart(bool value)
{
    m_boardStart=value;
    emit boardStartChanged();
    LOGGER_DEBUG("BoardStart:%d",m_boardStart);
}

bool FlowControl::boardPause()
{
    return m_boardPause;
}

void FlowControl::setBoardPause(bool value)
{
    m_boardPause=value;
    emit boardPauseChanged();
    LOGGER_DEBUG("boardPause:%d",m_boardPause);
}

bool FlowControl::boardStop()
{
    return m_boardStop;
}

void FlowControl::setBoardStop(bool value)
{
    m_boardStop=value;
    emit boardStopChanged();
    LOGGER_DEBUG("boardStop:%d",m_boardStop);
}

int FlowControl::startLine()
{
    return m_startLine;
}

void FlowControl::setStartLine(int value)
{
    m_startLine=value;
    emit startLineChanged();
}

int FlowControl::endLine()
{
    return m_endLine;
}

void FlowControl::setEndLine(int value)
{
    m_endLine=value;
    emit endLineChanged();
}

int FlowControl::targetArea()
{
    return m_targetArea;
}

void FlowControl::setTargetArea(int value)
{
    m_targetArea=value;
    emit targetAreaChanged();
}

int FlowControl::startTime()
{
    return m_startTime;
}

void FlowControl::setStartTime(int value)
{
    m_startTime=value;
    emit startTimeChanged();
}

int FlowControl::endTime()
{
    return m_endTime;
}

void FlowControl::setEndTime(int value)
{
    m_endTime=value;
    emit endTimeChanged();
}

QVariantList FlowControl::flowCameraRate()
{
    return m_flowCameraRate;
}

void FlowControl::setFlowCameraRate(QVariantList value)
{
    m_flowCameraRate=value;
    emit flowCameraRateChanged();
}

bool FlowControl::boardStoping()
{
    return m_boardStoping;
}

void FlowControl::setBoardStoping(bool value)
{
    m_boardStoping=value;
    emit boardStopingChanged();
}

FlowControl::FlowControl(std::shared_ptr<camera::camera> cam,
                         std::shared_ptr<board::board> bd,
                         std::shared_ptr<FlowCameraDateCore>
                         flowCameraDateCorel):m_flowCameraDateCorel(flowCameraDateCorel),
  m_timer(new QTimer(this))
{
    m_flowControl=std::make_shared<generator::flow_control>
            (cam,bd,QApplication::applicationDirPath().toStdString()+"/flowmodel/fc_template.png"
             ,m_startLine, m_endLine, m_targetArea, 20, 10);
    m_flowControl->init_state();
    setBoardStart(false);
    setBoardPause(false);
    setBoardStop(true);
    setBoardStoping(false);
    if(Login::MainTainUser) cam->attach(m_flowCameraDateCorel);
    m_camera=cam;
    m_timer->setInterval(1000);
    connect(m_timer,&QTimer::timeout,this,&FlowControl::slotCameraRate);
    m_timer->start();
    m_flowStatus = std::make_shared<FlowStatus>();

    m_flowControl->attach(m_flowStatus);
    m_boardStatus=std::make_shared<BoardStatus>();
    bd->attach(m_boardStatus);

    connect(m_boardStatus.get(),&BoardStatus::sigResetStatus,[this]{
        if(Login::MainTainUser){
            setBoardStart(false);
            setBoardPause(false);
            setBoardStoping(false);
            setBoardStop(true);
            LOGGER_DEBUG("slotReset");
        }
    });
    connect(m_boardStatus.get(),&BoardStatus::sigKeypressed,this,&FlowControl::sigKeyPressed);
    connect(m_boardStatus.get(),&BoardStatus::sigRecyleStatus,this,&FlowControl::sigRecyleStatus);
    connect(m_flowStatus.get(),&FlowStatus::sigResetStatus,[this]{
        emit sigremainSample();
        LOGGER_DEBUG("slotReset");
        setBoardStart(false);
        setBoardPause(false);
        setBoardStoping(false);
        setBoardStop(true);
    });
    connect(m_flowStatus.get(),&FlowStatus::signoSample,[this]{
        emit signoSample();
        setBoardStart(false);
        setBoardPause(false);
        setBoardStop(false);
        setBoardStoping(true);
    });
//    connect(m_flowStatus.get(),&FlowStatus::sigenable,[this]{
//        setBoardStart(false);
//        setBoardPause(false);
//        setBoardStop(false);
//        setBoardStoping(true);
//    });
    connect(m_flowStatus.get(),&FlowStatus::sigenable,this,&FlowControl::slotsBoardStoping);
}

void FlowControl::run()
{
    //QThread::msleep(3000);
    LOGGER_DEBUG("start task");
    setBoardStart(true);
    setBoardPause(false);
    setBoardStop(false);
    setBoardStoping(false);
    //QtConcurrent::run(m_flowControl.get(),&generator::flow_control::run);
    m_flowControl->run();
    GlobalObject::g_instance()->saveImgEnable(true);
}

void FlowControl::pause()
{
    LOGGER_DEBUG("pause task");
    setBoardStart(false);
    setBoardPause(true);
    setBoardStop(false);
    setBoardStoping(false);
    m_flowControl->pause();
}

void FlowControl::stop()
{
//    setBoardStart(false);
//    setBoardPause(false);
//    setBoardStop(true);
    LOGGER_DEBUG("force stop");
    setBoardStart(false);
    setBoardPause(false);
    setBoardStop(false);
    setBoardStoping(true);
    m_flowControl->stop();
}

void FlowControl::setStart_Line(int value)
{
    LOGGER_DEBUG("修改流量相机起始线:%d",value);
    m_flowControl->start_line(value);
    setStartLine(value);
    m_flowCameraDateCorel->setparmeter(value,endLine(),targetArea());
}

void FlowControl::setEnd_Line(int value)
{
    LOGGER_DEBUG("修改流量相机终止线:%d",value);
    m_flowControl->stop_line(value);
    setEndLine(value);
    m_flowCameraDateCorel->setparmeter(startLine(),value,targetArea());
}

void FlowControl::setTarget_Area(int value)
{
    LOGGER_DEBUG("修改流量相机区域:%d",value);
    m_flowControl->target_size(value);
    setTargetArea(value);
    m_flowCameraDateCorel->setparmeter(startLine(),endLine(),value);
}

void FlowControl::setFirstTime(int value)
{
    LOGGER_DEBUG("修改流量相机开始时间:%d",value);
    m_flowControl->start_seconds(value);
    setStartTime(value);
}

void FlowControl::setLastTime(int value)
{
    LOGGER_DEBUG("修改流量相机结束时间:%d",value);
    m_flowControl->stop_seconds(value);
    setEndTime(value);
}

void FlowControl::saveCameraConfig()
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

int FlowControl::grabImg()
{
    camera::frame frame;
    m_flowCameraDateCorel->setSaveImg();
    return m_camera->get_frame(&frame);
}

void FlowControl::openDir()
{
    QDesktopServices::openUrl(QUrl(QApplication::applicationDirPath()
                                   +"/flowImg"));
}

void FlowControl::clearSegResult()
{
    QString segResultPath="rm -rf " + QApplication::applicationDirPath()+"/segResult";
    QByteArray b=segResultPath.toLatin1();
    system(b.data());

    QDir dir(QApplication::applicationDirPath());
    dir.mkdir("segResult");
    dir.cd("segResult");
//    dir.mkdir("0");
    dir.mkdir("1");
    dir.mkdir("2");
    dir.mkdir("3");
    dir.mkdir("4");
    dir.mkdir("5");
    dir.mkdir("6");
    dir.mkdir("7");
}

void FlowControl::readConfig()
{
    QString grainType;
    switch (GlobalObject::g_grainType) {
        case GrainType::WHEAT: grainType="wheat";
        break;
        case GrainType::RICE: grainType="wheat";
        break;
        case GrainType::CRON: grainType="wheat";
        break;
        case GrainType::SORGHUM: grainType="wheat";
        break;
    default:grainType="wheat";
        break;
    }
    QJsonObject rootObj = getConfig();
    if(rootObj.contains(grainType)){
        QJsonObject objNode = rootObj.value(grainType).toObject();
        if(objNode.contains("Camera"))
        {
            QJsonObject obj = objNode.value("Camera").toObject();
            if(obj.contains("cameraThree")){
                QJsonObject tmp=obj.value("cameraThree").toObject();
                if(tmp.contains("startLine")){
                    setStart_Line(tmp.value("startLine").toInt());
                    LOGGER_DEBUG("流量相机起始线:%d",tmp.value("startLine").toInt());
                }
                if(tmp.contains("endLine")){
                    setEnd_Line(tmp.value("endLine").toInt());
                    LOGGER_DEBUG("流量相机终止线:%d",tmp.value("endLine").toInt());
                }
                if(tmp.contains("targetArea")){
                    setTarget_Area(tmp.value("targetArea").toInt());
                    LOGGER_DEBUG("流量相机区域:%d",tmp.value("targetArea").toInt());
                }
                if(tmp.contains("startTime")){
                    setFirstTime(tmp.value("startTime").toInt());
                    LOGGER_DEBUG("流量开始时间:%d",tmp.value("startTime").toInt());
                }
                if(tmp.contains("endTime")){
                    setLastTime(tmp.value("endTime").toInt());
                    LOGGER_DEBUG("流量结束时间:%d",tmp.value("endTime").toInt());
                }
            }
        }
    }
    m_flowCameraDateCorel->setparmeter(m_startLine,m_endLine,m_targetArea);
}

void FlowControl::saveCameraConfig(QString grainType)
{
    QJsonObject rootObj = getConfig();
    if(rootObj.contains(grainType)){
        QJsonObject objNode = rootObj.find(grainType).value().toObject();
        if(objNode.contains("Camera"))
        {
            QJsonObject obj = objNode.find("Camera").value().toObject();
            if(obj.contains("cameraThree")){
                QJsonObject tmp=obj.find("cameraThree").value().toObject();
                if(tmp.contains("startLine")){
                    tmp.find("startLine").value()=startLine();
                    LOGGER_DEBUG("流量相机起始线:%d",startLine());
                }
                if(tmp.contains("endLine")){
                    tmp.find("endLine").value()=endLine();
                    LOGGER_DEBUG("流量相机终止线:%d",endLine());
                }
                if(tmp.contains("targetArea")){
                    tmp.find("targetArea").value()=targetArea();
                    LOGGER_DEBUG("流量相机区域:%d",targetArea());
                }
                if(tmp.contains("startTime")){
                    tmp.find("startTime").value()=startTime();
                    LOGGER_DEBUG("流量开始时间:%d",startTime());
                }
                if(tmp.contains("endTime")){
                    tmp.find("endTime").value()=endTime();
                    LOGGER_DEBUG("流量开始时间:%d",endTime());
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

void FlowControl::slotCameraRate()
{
    QVariantList rate;
    float collectFrameRate;
    std::uint32_t lostFrameRate;
    std::uint32_t currentFrameRate;
    m_camera->get_frame_rate(&collectFrameRate,&lostFrameRate);
    currentFrameRate = m_flowCameraDateCorel->getShowFramRate() - m_frontFrameRate;
    m_frontFrameRate=m_flowCameraDateCorel->getShowFramRate();
    rate.append(QString::number(collectFrameRate,'f',1));
    rate.append(QString::number(lostFrameRate));
    rate.append(QString::number(currentFrameRate));
    setFlowCameraRate(rate);
}

void FlowControl::slotsBoardStoping()
{
    emit sigenable();
    setBoardStart(false);
    setBoardPause(false);
    setBoardStop(false);
    setBoardStoping(true);
}

FlowStatus::FlowStatus(QObject *parent):QObject(parent){}

void FlowStatus::handle_fc_status(generator::notify_code nc)
{
    switch (nc) {
    case generator::notify_code::pre_start:
    break;
    case generator::notify_code::remain_sample:
        emit sigResetStatus();
    break;
    case generator::notify_code::no_sample:
        emit signoSample();
    break;
    case generator::notify_code::start:
    break;
    case generator::notify_code::loop_finish:
        emit sigenable();
        LOGGER_DEBUG("loop finish");
    break;
    case generator::notify_code::stop:
    break;
    default:
    break;
    }
}


