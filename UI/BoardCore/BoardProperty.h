#ifndef BOARDPROPERTY_H
#define BOARDPROPERTY_H
#include <QObject>
#include <QThread>
#include "GlobalParameter.h"
#include "module/board/board.h"
#include "Login.h"
#define SLMOTOR 1  //送料电机序号
#define CMMOTOR 0  //仓门电机序号
class BoardControlPrivate;
class BoardProperty:public QObject
{
    Q_OBJECT
    Q_PROPERTY(int slDirection READ slDirection WRITE setSlDirection NOTIFY slDirectionChanged)
    Q_PROPERTY(int slPositiveSpeed READ slPositiveSpeed WRITE setSlPositiveSpeed NOTIFY slPositiveSpeedChanged)
    Q_PROPERTY(int slNegativeSpeed READ slNegativeSpeed WRITE setSlNegativeSpeed NOTIFY slNegativeSpeedChanged)
    Q_PROPERTY(int slPrePosition READ slPrePosition WRITE setSlPrePosition NOTIFY slPrePositionChanged)
    Q_PROPERTY(int slStartPosition READ slStartPosition WRITE setSlStartPosition NOTIFY slStartPositionChanged)
    Q_PROPERTY(int slStopPosition READ slStopPosition WRITE setSlStopPosition NOTIFY slStopPositionChanged)
    Q_PROPERTY(int cmDirection READ cmDirection WRITE setCmDirection NOTIFY cmDirectionChanged)
    Q_PROPERTY(int cmPositiveSpeed READ cmPositiveSpeed WRITE setCmPositiveSpeed NOTIFY cmPositiveSpeedChanged)
    Q_PROPERTY(int cmNegativeSpeed READ cmNegativeSpeed WRITE setCmNegativeSpeed NOTIFY cmNegativeSpeedChanged)
    Q_PROPERTY(int cmPrePosition READ cmPrePosition WRITE setCmPrePosition NOTIFY cmPrePositionChanged)
    Q_PROPERTY(int inputVibrate READ inputVibrate WRITE setInputVibrate NOTIFY inputVibrateChanged)
    Q_PROPERTY(int clearVibrate READ clearVibrate WRITE setClearVibrate NOTIFY clearVibrateChanged)
    Q_PROPERTY(bool openOnVibrate READ openOnVibrate WRITE setOpenOnVibrate NOTIFY openOnVibrateChanged)
    Q_PROPERTY(bool closeOnVibrate READ closeOnVibrate WRITE setCloseOnVibrate NOTIFY closeOnVibrateChanged)
    Q_PROPERTY(int maxTrigger READ maxTrigger WRITE setMaxTrigger NOTIFY maxTriggerChanged)
    Q_PROPERTY(bool isStop READ isStop WRITE setIsStop NOTIFY isStopChanged)
    Q_PROPERTY(bool isPause READ isPause WRITE setIsPause NOTIFY isPauseChanged)
    Q_PROPERTY(int triggerDlay READ triggerDlay WRITE setTriggerDlay NOTIFY triggerDlayChanged)
    Q_PROPERTY(float centerRate READ centerRate WRITE setCenterRate NOTIFY centerRateChanged)
    Q_PROPERTY(int outputRate READ outputRate WRITE setOutputRate NOTIFY outputRateChanged)
    Q_PROPERTY(float vibrationRate READ vibrationRate WRITE setVibrationRate NOTIFY vibrationRateChanged)
    Q_PROPERTY(int voltage READ voltage WRITE setVoltage NOTIFY voltageChanged)
public:
    int slDirection();
    void setSlDirection(int value);

    int slPositiveSpeed();
    void setSlPositiveSpeed(int value);

    int slNegativeSpeed();
    void setSlNegativeSpeed(int value);

    int slPrePosition();
    void setSlPrePosition(int value);

    int slStartPosition();
    void setSlStartPosition(int value);

    int slStopPosition();
    void setSlStopPosition(int value);

    int cmDirection();
    void setCmDirection(int value);

    int cmPositiveSpeed();
    void setCmPositiveSpeed(int value);

    int cmNegativeSpeed();
    void setCmNegativeSpeed(int value);

    int cmPrePosition();
    void setCmPrePosition(int value);

    int inputVibrate();
    void setInputVibrate(int value);

    int clearVibrate();
    void setClearVibrate(int value);

    bool openOnVibrate();
    void setOpenOnVibrate(bool value);

    bool closeOnVibrate();
    void setCloseOnVibrate(bool value);

    int maxTrigger();
    void setMaxTrigger(int value);

    int isStop();
    void setIsStop(bool value);

    int isPause();
    void setIsPause(bool value);

    int triggerDlay();
    void setTriggerDlay(int value);

    float centerRate();
    void setCenterRate(float value);

    int outputRate();
    void setOutputRate(int value);

    float vibrationRate();
    void setVibrationRate(float value);

    int voltage();
    void setVoltage(int value);
signals:
    void slDirectionChanged();
    void slPositiveSpeedChanged();
    void slNegativeSpeedChanged();
    void slPrePositionChanged();
    void slStartPositionChanged();
    void slStopPositionChanged();
    void cmDirectionChanged();
    void cmPositiveSpeedChanged();
    void cmNegativeSpeedChanged();
    void cmPrePositionChanged();
    void inputVibrateChanged();
    void clearVibrateChanged();
    void openOnVibrateChanged();
    void closeOnVibrateChanged();
    void maxTriggerChanged();
    void isStopChanged();
    void isPauseChanged();
    void triggerDlayChanged();
    void centerRateChanged();
    void outputRateChanged();
    void vibrationRateChanged();
    void voltageChanged();
public:
    explicit BoardProperty(std::shared_ptr<board::board> board);
public:
    //设置当前控制板任务，成功完成设置后，控制板状态应转为ready
    Q_INVOKABLE void setTask(int value);
    //获取当前控制板任务
    Q_INVOKABLE board::e_task getTask();
    //开始当前任务，控制板由ready或pause状态转变为工作或异常状态
    Q_INVOKABLE void startTask();
    //暂停当前任务，控制板由工作状态转为pause或异常状态
    Q_INVOKABLE void pasueTask();
    //停止任务，控制板由工作或pasue状态转为ready或异常状态
    Q_INVOKABLE void stopTask();
    //设置步进电机方向
    Q_INVOKABLE void setSmotorDirection(int smotor_id, int direction);
    //获取步进电机方向
    Q_INVOKABLE int getSmotorDirection(int smotor_id);
    //设置步进电机前进速度
    Q_INVOKABLE void setSmotorPositiveSpeed(int id, int speed);
    //获取步进电机前进速度
    Q_INVOKABLE int getSmotorPositiveSpeed(int id);
    //设置步进电机后退速度
    Q_INVOKABLE void setSmotorNegtiveSpeed(int id, int speed);
    //获取步进电机后退速度
    Q_INVOKABLE int getSmotorNegtiveSpeed(int id);
    //设置步进电机位置0
    Q_INVOKABLE void setSmotorPrePosition(int id, int pos);
    //获取步进电机位置0
    Q_INVOKABLE int getSmotorPrePosition(int id);
    //设置步进电机位置1
    Q_INVOKABLE void setSmotorStartPosition(int id, int pos);
    //获取步进电机位置1
    Q_INVOKABLE int getSmotorStartPosition(int id);
    //设置步进电机位置2
    Q_INVOKABLE void setSmotorStoPosition(int id, int pos);
    //获取步进电机位置2
    Q_INVOKABLE int getSmotorStoPosition(int id);
    //设置入料时的持续振动时间，后期改用流量相机控制
    Q_INVOKABLE void setVibratorInputTime(int id,int time);
    //获取清料时的持续振动时间
    Q_INVOKABLE int getVibratorInputTime(int id);
    //设置清料时的持续振动时间，后期改用流量相机控制
    Q_INVOKABLE void setVibratorClearTime(int id, int time);
    //获取清料时的持续振动时间
    Q_INVOKABLE int getVibratorClearTime(int id);
    //设置直流电机策略
    Q_INVOKABLE void setDcmotorPolicy(int id, bool policy);
    //获取直流电机策略
    Q_INVOKABLE int getDcmotorPolicy(int id);
    //设置控制板最大触发次数
    Q_INVOKABLE void setMaxTriggerCount(int count);
    //获取控制板最大触发次数
    Q_INVOKABLE int getMaxTriggerVount();
    // 获取拍照延时
    Q_INVOKABLE int getBoardTriggertDlay();
    // 设置拍照延时
    Q_INVOKABLE void setBoardTriggertDlay(int value);
    // 设置震动器中心频率
    Q_INVOKABLE void setZdmotorCenterRate(int id,float value);
    // 设置出料速度
    Q_INVOKABLE void setZdmotorOutRate(int id,int value);
    // 设置震动频率
    Q_INVOKABLE void setZdmotorRate(int id,int value);
    // 设置电压
    Q_INVOKABLE void setZdmotorVoltage(int id,int value);
    Q_INVOKABLE void saveCameraConfig();
    // 设置流量相机灯
    Q_INVOKABLE void flowLightEnable(bool value);
    Q_INVOKABLE int query_recycle();
public:
    void initBoard();
private:
    void readConfig(QString grainType);
    void saveCameraConfig(QString);
private:
    std::shared_ptr<board::board> m_board;
    std::shared_ptr<BoardControlPrivate> m_d;
};
#endif // BOARDPROPERTY_H
