/**
 * @file dirver.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-11-03
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "UI/dirver/dirver.h"

Dirver::Dirver():m_cameraInterface(std::make_shared<CameraInterface>()),
    m_boardInterface(std::make_shared<BoardInterface>()),
    m_dateCore(std::make_shared<FrameDateCore>()),
    m_flowCameraDateCorel(std::make_shared<FlowCameraDateCore>())
{}
bool Dirver::init()
{
    if(m_cameraInterface->findCamera() && m_boardInterface->findBoard()){
        m_dcdfCore=std::make_shared<generator::dcdf_engine>(m_boardInterface->m_board,
                                                            m_cameraInterface->m_one,
                                                            m_cameraInterface->m_two
                                                            ,"","");
        m_dcdfCore->stop();
        if(!Login::MainTainUser) m_dcdfCore->start();
        if(Login::MainTainUser) m_dcdfCore->attach(m_dateCore);
        m_flowControl=std::make_shared<FlowControl>
                (m_cameraInterface->m_three,m_boardInterface->m_board,m_flowCameraDateCorel);
        m_cameraTaskWork=std::make_shared<CameraTaskWork>(m_cameraInterface->m_one,
                                                          m_cameraInterface->m_two,
                                                          m_boardInterface->m_board,
                                                          "","");
        connect(m_cameraInterface->m_cameraProperty.get(),
                &CameraProperty::sigCameraBrightTime,this
                ,&Dirver::slotSetCameraBright);
        connect(m_cameraInterface->m_cameraProperty.get(),
                &CameraProperty::sigCameraDarkTime,this
                ,&Dirver::slotSetCameraDark);
        connect(m_cameraTaskWork.get(),&CameraTaskWork::sigUpExpouse,this,&Dirver::slotSetCameraBright);
        connect(m_cameraTaskWork.get(),&CameraTaskWork::sigDownExpouse,this,&Dirver::slotSetCameraDark);
        connect(GlobalObject::g_instance(),&GlobalObject::sigSaveImg,this,&Dirver::slotSaveImgEnable);
        //        if(!Login::MainTainUser){
        m_algorithmManager=std::make_shared<AlgorithmManager>(m_dcdfCore,GlobalObject::g_deviceName.toStdString());
        m_algorithmDataCore=std::make_shared<AlgorithmDataCore>();
        if(!Login::MainTainUser){
            m_algorithmManager->start();
        }else {
            m_algorithmManager->stop();
        }
        m_dcdfSave=std::make_shared<algorithm::dcdf_save>(m_dcdfCore,
                                                          m_cameraTaskWork->getCalibrate(),
                                                          QString(QApplication::applicationDirPath()+"/original/").toStdString()
                                                          ,GlobalObject::g_deviceName.toStdString());
        GlobalObject::g_saveOriginalImg?m_dcdfSave->enable():m_dcdfSave->disable();
        //        }
    }else{
        //初始化业务失败
        return false;
    }
    return true;
}

void Dirver::initAllParamter()
{
    if(m_algorithmManager&&m_algorithmDataCore){
        m_algorithmManager->detach(m_algorithmDataCore->getAlgorithmDataDynamicResult());
        m_algorithmManager->detach(m_algorithmDataCore->getAlgorithmDataProcess());
    }
    if(m_cameraInterface&&m_flowControl&&m_boardInterface){
        m_boardInterface->m_boardProperty->initBoard();
        m_cameraInterface->m_cameraProperty->setCameraInfo();
        m_flowControl->readConfig();
        //        if(!Login::MainTainUser){
        switch (GlobalObject::g_grainType) {
        case GrainType::WHEAT:
            m_dcdfCore->set_grain_type(GlobalObject::g_grainTyoe.toStdString());
            m_dcdfCore->set_abnormal_type(GlobalObject::g_childType.toStdString());
            m_cameraTaskWork->getCalibrate()->set_grain_type(GlobalObject::g_grainTyoe.toStdString());
            m_cameraTaskWork->getCalibrate()->set_abnormal_type(GlobalObject::g_childType.toStdString());
            //m_sqlSampleId=new SqlWheatSampleId(this);
            break;
        default:;
            m_dcdfCore->set_grain_type(GlobalObject::g_grainTyoe.toStdString());
            m_dcdfCore->set_abnormal_type(GlobalObject::g_childType.toStdString());
            m_cameraTaskWork->getCalibrate()->set_grain_type(GlobalObject::g_grainTyoe.toStdString());
            m_cameraTaskWork->getCalibrate()->set_abnormal_type(GlobalObject::g_childType.toStdString());
            //m_sqlSampleId=new SqlWheatSampleId(this);
            break;
        }
        m_algorithmDataCore->setAbstractAlgorithmType();
        //emit sigSqlSampleId(m_sqlSampleId);
        m_algorithmManager->attach(m_algorithmDataCore->getAlgorithmDataDynamicResult());
        m_algorithmManager->attach(m_algorithmDataCore->getAlgorithmDataProcess());
    }
    //    }
    //m_boardInterface->m_boardProperty->query_recycle();
}

void Dirver::dcdfStart()
{
    m_dcdfCore->start();
}

void Dirver::dcdfStop()
{
    m_dcdfCore->stop();
}
void Dirver::slotSetCameraBright(QString uid,int time)
{
    LOGGER_DEBUG("修改相机%s明场曝光时间:%d",uid.toStdString().c_str(),time);
    m_dcdfCore->set_reflection_exposure(uid.toStdString(),time);
    m_cameraTaskWork->getCalibrate()->set_reflection_exposure(uid.toStdString(),time);
}
void Dirver::slotSetCameraDark(QString uid,int time)
{
    LOGGER_DEBUG("修改相机%s暗场曝光时间:%d",uid.toStdString().c_str(),time);
    m_dcdfCore->set_transmission_exposure(uid.toStdString(),time);
    m_cameraTaskWork->getCalibrate()->set_transmission_exposure(uid.toStdString(),time);
}

void Dirver::slotSaveImgEnable(bool value)
{
    value?m_dcdfSave->enable():m_dcdfSave->disable();
}
