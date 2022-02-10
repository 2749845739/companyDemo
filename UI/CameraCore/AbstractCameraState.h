#ifndef ABSTRACTCAMERASTATE_H
#define ABSTRACTCAMERASTATE_H
#include <QObject>
#include <memory>
class CameraTaskWork;
class AbstractCameraState:public QObject
{
    Q_OBJECT
public:
    explicit AbstractCameraState(QObject* parent=nullptr);
    virtual void handel(std::shared_ptr<CameraTaskWork>)=0;
};
class CameraNonetState:public AbstractCameraState{
    Q_OBJECT
public:
    explicit CameraNonetState(QObject*parent=nullptr);
    void handel(std::shared_ptr<CameraTaskWork>) override;
};
class CameraUlightState:public AbstractCameraState{
    Q_OBJECT
public:
    explicit CameraUlightState(QObject* parent);
    void handel(std::shared_ptr<CameraTaskWork>) override;
};
class CameraDlightState:public AbstractCameraState{
    Q_OBJECT
public:
    explicit CameraDlightState(QObject* parent);
    void handel(std::shared_ptr<CameraTaskWork>) override;
};
class CameraInturnState:public AbstractCameraState{
    Q_OBJECT
public:
    explicit CameraInturnState(QObject* parent);
    void handel(std::shared_ptr<CameraTaskWork>) override;
};
#endif // ABSTRACTCAMERASTATE_H
