#ifndef CAMERATASKWORK_H
#define CAMERATASKWORK_H
#include <QObject>
#include <memory>
#include <QHash>
#include <QTimer>
#include <QDesktopServices>
#include "calibrate/calibrate.h"
#include "FrameDateCore.h"
#include "GlobalParameter.h"
class AbstractCameraState;
enum class cpolicy : std::uint32_t {
  none,     // 正常运行
  ulight,   // 上光源点亮
  dlight,   // 下光源点亮
  inturn,   // 上下光源交替点亮
};

class CameraTaskWork:public QObject,public std::enable_shared_from_this<CameraTaskWork>
{
    Q_OBJECT
    Q_PROPERTY(bool isStart READ isStart WRITE setIsStart NOTIFY isStartChanged)
    Q_PROPERTY(bool isPause READ isPause WRITE setIsPause NOTIFY isPauseChanged)
    Q_PROPERTY(bool isStop READ isStop WRITE setIsStop NOTIFY isStopChanged)
    Q_PROPERTY(bool isStoped READ isStoped WRITE setIsStoped NOTIFY isStopedChanged)
    Q_PROPERTY(int currentStatus READ currentStatus WRITE setCurrentStatus NOTIFY currentStatusChanged)
    Q_PROPERTY(bool changeMode READ changeMode WRITE setChangeMode NOTIFY changeModeChanged)
    Q_PROPERTY(bool isCalibrate READ isCalibrate WRITE setIsCalibrate NOTIFY isCalibrateChanged)
    Q_PROPERTY(bool isGraping READ isGraping WRITE setIsGraping NOTIFY isGrapingChanged)
    Q_PROPERTY(QVariantList cameraOneRate READ cameraOneRate WRITE setCameraOneRate NOTIFY cameraOneRateChanged)
    Q_PROPERTY(QVariantList cameraTwoRate READ cameraTwoRate WRITE setCameraTwoRate NOTIFY cameraTwoRateChanged)
public:
    bool isStart();
    void setIsStart(bool value);

    bool isPause();
    void setIsPause(bool value);

    bool isStop();
    void setIsStop(bool value);

    bool isStoped();
    void setIsStoped(bool value);

    int currentStatus();
    void setCurrentStatus(int value);

    bool changeMode();
    void setChangeMode(bool value);

    bool isCalibrate();
    void setIsCalibrate(bool value);

    bool isGraping();
    void setIsGraping(bool value);

    QVariantList cameraOneRate();
    void setCameraOneRate(QVariantList value);

    QVariantList cameraTwoRate();
    void setCameraTwoRate(QVariantList value);
signals:
    void isStartChanged();
    void isPauseChanged();
    void isStopChanged();
    void isStopedChanged();
    void currentStatusChanged();
    void changeModeChanged();
    void isCalibrateChanged();
    void isGrapingChanged();
    void cameraOneRateChanged();
    void cameraTwoRateChanged();
public:
    //int currntStates();
    Q_INVOKABLE void setCurrntStates(int value);
    Q_INVOKABLE void start(bool value);
    Q_INVOKABLE void stop();
    Q_INVOKABLE void setUpExposeTime(int id,int value);
    Q_INVOKABLE void setDwonExposeTime(int id,int value);
    Q_INVOKABLE void grapImg();
    Q_INVOKABLE void openDir();
public:
    inline std::shared_ptr<calibrate::calibrator> getCalibrate(){
        return m_generator;
    }
public:
    CameraTaskWork(std::shared_ptr<camera::camera> ucam,
                   std::shared_ptr<camera::camera> dcam,
                   std::shared_ptr<board::board> bd,
                   std::string grain_type,
                   std::string abnormal_type,
                   QObject* parent=nullptr);
    cpolicy m_policy   {cpolicy::none};
    std::shared_ptr<MultilightCameraDateCore> m_MultilightCameraDateCore;
signals:
    void sigGrapImg(bool flag);
    void sigUpExpouse(QString,int);
    void sigDownExpouse(QString,int);
private slots:
    void slotCameraRates();
private:
    int m_currntStates {0};
    QHash<int,AbstractCameraState*> m_states;
    std::shared_ptr<calibrate::calibrator> m_generator;
    std::shared_ptr<BoardStatus> m_boardStatus;
    std::shared_ptr<camera::camera> m_ucam;
    std::shared_ptr<camera::camera> m_dcam;
    QTimer* m_timer;
    std::uint32_t m_frontFrameRate {0};
private:
    bool m_isStart {false};
    bool m_isPause {false};
    bool m_isStop {false};
    bool m_isStoped {true};
    bool m_canChangeMode  {true};
    bool m_isCalibrate {false};
    bool m_isGraping   {false};

    QVariantList m_cameraOneRate{"0","0","0"};
    QVariantList m_cameraTwoRate{"0","0","0"};
};


#endif // CAMERATASKWORK_H
