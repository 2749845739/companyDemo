#include "AbstractCameraState.h"
#include "CameraTaskWork.h"
AbstractCameraState::AbstractCameraState(QObject* parent):QObject(parent){}
CameraNonetState::CameraNonetState(QObject *parent):AbstractCameraState(parent){}

void CameraNonetState::handel(std::shared_ptr<CameraTaskWork> m)
{
    if(m->currentStatus()==1){
        if(m->isCalibrate()){
            m->getCalibrate()->ulight(false);
            m->setIsCalibrate(false);
        }else {
            m->getCalibrate()->ulight(true);
            m->setIsCalibrate(true);
        }
    }else if(m->currentStatus()==2){
        if(m->isCalibrate()){
            m->getCalibrate()->dlight(false);
            m->setIsCalibrate(false);
        }else {
            m->getCalibrate()->dlight(true);
            m->setIsCalibrate(true);
        }
    }else if(m->currentStatus()==3){
        if(m->isCalibrate()){
            m->getCalibrate()->inturn(false);
            m->setIsCalibrate(false);
        }else {
            m->getCalibrate()->inturn(true);
            m->setIsCalibrate(true);
        }
    }
}

CameraUlightState::CameraUlightState(QObject *parent):AbstractCameraState(parent){}

void CameraUlightState::handel(std::shared_ptr<CameraTaskWork> m)
{
    m->getCalibrate()->ulight(true);
}

CameraDlightState::CameraDlightState(QObject *parent):AbstractCameraState(parent){}

void CameraDlightState::handel(std::shared_ptr<CameraTaskWork> m)
{
    m->getCalibrate()->dlight(true);
}

CameraInturnState::CameraInturnState(QObject *parent):AbstractCameraState(parent){}

void CameraInturnState::handel(std::shared_ptr<CameraTaskWork> m)
{
    m->getCalibrate()->inturn(true);
}
