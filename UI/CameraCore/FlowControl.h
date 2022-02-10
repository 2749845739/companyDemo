#ifndef FLOWCONTROL_H
#define FLOWCONTROL_H

#include <QObject>
#include <QTimer>
#include <generator/flow_control.h>
#include <QDebug>
#include <QDesktopServices>
#include <QtConcurrent>
#include "GlobalParameter.h"
#include "FrameDateCore.h"
#include "Login.h"
class FlowStatus:public QObject,public generator::fc_status_observer
{
    Q_OBJECT
public:
    explicit FlowStatus(QObject* parent=nullptr);
    void handle_fc_status(generator::notify_code s) override;
signals:
    void sigResetStatus();
    void signoSample();
    void sigenable();
};

class FlowControl:public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool boardStart READ boardStart WRITE setBoardStart NOTIFY boardStartChanged)
    Q_PROPERTY(bool boardPause READ boardPause WRITE setBoardPause NOTIFY boardPauseChanged)
    Q_PROPERTY(bool boardStop READ boardStop WRITE setBoardStop NOTIFY boardStopChanged)
    Q_PROPERTY(bool boardStoping READ boardStoping WRITE setBoardStoping NOTIFY boardStopingChanged)
    Q_PROPERTY(int startLine READ startLine WRITE setStartLine NOTIFY startLineChanged)
    Q_PROPERTY(int endLine READ endLine WRITE setEndLine NOTIFY endLineChanged)
    Q_PROPERTY(int targetArea READ targetArea WRITE setTargetArea NOTIFY targetAreaChanged)
    Q_PROPERTY(int startTime READ startTime WRITE setStartTime NOTIFY startTimeChanged)
    Q_PROPERTY(int endTime READ endTime WRITE setEndTime NOTIFY endTimeChanged)
    Q_PROPERTY(QVariantList flowCameraRate READ flowCameraRate WRITE setFlowCameraRate NOTIFY flowCameraRateChanged)
public:
    bool boardStart();
    void setBoardStart(bool value);

    bool boardPause();
    void setBoardPause(bool value);

    bool boardStop();
    void setBoardStop(bool value);

    int startLine();
    void setStartLine(int value);

    int endLine();
    void setEndLine(int value);

    int targetArea();
    void setTargetArea(int value);

    int startTime();
    void setStartTime(int value);

    int endTime();
    void setEndTime(int value);

    QVariantList flowCameraRate();
    void setFlowCameraRate(QVariantList value);

    bool boardStoping();
    void setBoardStoping(bool value);
signals:
    void boardStartChanged();
    void boardPauseChanged();
    void boardStopChanged();
    void startLineChanged();
    void endLineChanged();
    void targetAreaChanged();
    void startTimeChanged();
    void endTimeChanged();
    void flowCameraRateChanged();
    void boardStopingChanged();
public:
    explicit FlowControl(std::shared_ptr<camera::camera> cam,
                         std::shared_ptr<board::board> bd,
                         std::shared_ptr<FlowCameraDateCore> flowCameraDateCorel);
    Q_INVOKABLE void run();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();
    // 设置起始线
    Q_INVOKABLE void setStart_Line(int value);
    // 设置终止线
    Q_INVOKABLE void setEnd_Line(int value);
    // 设置区域
    Q_INVOKABLE void setTarget_Area(int value);
    //设置第一次震动时间
    Q_INVOKABLE void setFirstTime(int value);
    //设置最后一次震动时间
    Q_INVOKABLE void setLastTime(int value);
    Q_INVOKABLE void saveCameraConfig();

    Q_INVOKABLE int grabImg();
    Q_INVOKABLE void openDir();
    Q_INVOKABLE void clearSegResult();
public:
    inline std::shared_ptr<FlowStatus> getFlowStatus(){
        return m_flowStatus;
    }
public:
    void readConfig();
private:
    void saveCameraConfig(QString);
private slots:
    void slotCameraRate();
    void slotsBoardStoping();
signals:
    void signoSample();
    void sigremainSample();
    void sigenable();
    void sigKeyPressed();
    void sigRecyleStatus(bool);
private:
    std::shared_ptr<generator::flow_control> m_flowControl;
    bool m_boardStart {false};
    bool m_boardPause {false};
    bool m_boardStop  {false};
    bool m_boardStoping {false};
    int m_startLine   {10};
    int m_endLine {1000};
    int m_targetArea {75};
    int m_startTime {15};
    int m_endTime {15};
    std::shared_ptr<FlowCameraDateCore> m_flowCameraDateCorel;
    std::shared_ptr<camera::camera> m_camera;
    QTimer* m_timer;
    std::uint32_t m_frontFrameRate  {0};
    QVariantList m_flowCameraRate{"0","0","0"};
    std::shared_ptr<FlowStatus> m_flowStatus;
    std::shared_ptr<BoardStatus> m_boardStatus;
};
#endif // FLOWCONTROL_H
