#ifndef CAMERAINTERFACE_H
#define CAMERAINTERFACE_H
#include "module/camera/driver.h"
#include "module/camera/camera.h"
#include "module/camera/common.h"
#include "generator/dcdf_generator.h"
#include "FrameDateCore.h"
#include "CameraProperty.h"
#include "CMessageBox.h"
class CameraInterface:public QObject
{
    Q_OBJECT
public:
    explicit CameraInterface();
    bool findCamera();
    void initGenerator();
//private slots:
//    void slotSetCameraBright(QString,int);
//    void slotSetCameraDark(QString,int);
public:
    std::shared_ptr<CameraProperty> m_cameraProperty;
    std::shared_ptr<camera::camera> m_one;
    std::shared_ptr<camera::camera> m_two;
    std::shared_ptr<camera::camera> m_three;
};

#endif // CAMERAINTERFACE_H
