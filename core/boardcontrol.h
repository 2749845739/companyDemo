#ifndef BOARDCONTROL_H
#define BOARDCONTROL_H

#include <QObject>
#include <iostream>
#include <thread>
#include "board_plugin_api.hpp"
#include <QVariant>
#include <QVariantList>
#include <GlobalParameter.h>
#include "Login.h"
class BoardControlPrivate;

class BoardControl : public QObject {
Q_OBJECT
  Q_PROPERTY(QVariantList lightTime READ lightTime WRITE setLightTime NOTIFY lightTimeChanged)
  Q_PROPERTY(int slDirection READ slDirection WRITE setSlDirection NOTIFY slDirectionChanged)
  Q_PROPERTY(int slPositive_speed READ slPositive_speed WRITE setSlPositive_speed NOTIFY slPositive_speedChanged)
  Q_PROPERTY(int slNegative_speed READ slNegative_speed WRITE setSlNegative_speed NOTIFY slNegative_speedChanged)
  Q_PROPERTY(int slPosition_0 READ slPosition_0 WRITE setSlPosition_0 NOTIFY slPosition_0Changed)
  Q_PROPERTY(int slPosition_1 READ slPosition_1 WRITE setSlPosition_1 NOTIFY slPosition_1Changed)
  Q_PROPERTY(int slPosition_2 READ slPosition_2 WRITE setSlPosition_2 NOTIFY slPosition_2Changed)

  Q_PROPERTY(int cmDirection READ cmDirection WRITE setCmDirection NOTIFY cmDirectionChanged)
  Q_PROPERTY(int cmPositive_speed READ cmPositive_speed WRITE setCmPositive_speed NOTIFY cmPositive_speedChanged)
  Q_PROPERTY(int cmNegative_speed READ cmNegative_speed WRITE setCmNegative_speed NOTIFY cmNegative_speedChanged)
  Q_PROPERTY(int cmPosition_0 READ cmPosition_0 WRITE setCmPosition_0 NOTIFY cmPosition_0Changed)

  Q_PROPERTY(int input_vibrate READ input_vibrate WRITE setInput_vibrate NOTIFY input_vibrateChanged)
  Q_PROPERTY(int clear_vibrate READ clear_vibrate WRITE setClear_vibrate NOTIFY clear_vibrateChanged)

  Q_PROPERTY(bool open_on_vibrate READ open_on_vibrate WRITE setOpen_on_vibrate NOTIFY open_on_vibrateChanged)
  Q_PROPERTY(bool close_on_vibrate READ close_on_vibrate WRITE setClose_on_vibrate NOTIFY close_on_vibrateChanged)

  Q_PROPERTY(int internal_period READ internal_period WRITE setInternal_period NOTIFY internal_periodChanged)
  Q_PROPERTY(int external_period READ external_period WRITE setExternal_period NOTIFY external_periodChanged)
  Q_PROPERTY(int trigger_period READ trigger_period WRITE setTrigger_period NOTIFY trigger_periodChanged)
  Q_PROPERTY(int max_trigger READ max_trigger WRITE setMax_trigger NOTIFY max_triggerChanged)
  Q_PROPERTY(bool isStop READ isStop WRITE setIsStop NOTIFY isStopChanged)
  Q_PROPERTY(bool isPause READ isPause WRITE setIsPause NOTIFY isPauseChanged)

 public:
  explicit BoardControl(QObject *parent = nullptr);
  ~ BoardControl();
  void findPlugin();
  void init();
  void reciveBoardStatus(GBoard::version_info board, GBoard::component_status_t status, void* puser);
  void reciveWeightData(GBoard::version_info board,  GBoard::board_frame frame, void* puser);

  QVariantList lightTime();
  void setLightTime(QVariantList times);

  int slDirection();
  void setSlDirection(int value);

  int slPositive_speed();
  void setSlPositive_speed(int value);

  int slNegative_speed();
  void setSlNegative_speed(int value);

  int slPosition_0();
  void setSlPosition_0(int value);

  int slPosition_1();
  void setSlPosition_1(int value);

  int slPosition_2();
  void setSlPosition_2(int value);

  int cmDirection();
  void setCmDirection(int value);

  int cmPositive_speed();
  void setCmPositive_speed(int value);

  int cmNegative_speed();
  void setCmNegative_speed(int value);

  int cmPosition_0();
  void setCmPosition_0(int value);

  int input_vibrate();
  void setInput_vibrate(int value);

  int clear_vibrate();
  void setClear_vibrate(int value);

  bool open_on_vibrate();
  void setOpen_on_vibrate(bool value);

  bool close_on_vibrate();
  void setClose_on_vibrate(bool value);

  int internal_period();
  void setInternal_period(int value);

  int external_period();
  void setExternal_period(int value);

  int trigger_period();
  void setTrigger_period(int value);

  int max_trigger();
  void setMax_trigger(int value);

  bool isStop();
  void setIsStop(bool value);

  bool isPause();
  void setIsPause(bool value);

  void setConfig();
 signals:
  void lightTimeChanged();
  void slDirectionChanged();
  void slPositive_speedChanged();
  void slNegative_speedChanged();
  void slPosition_0Changed();
  void slPosition_1Changed();
  void slPosition_2Changed();
  void cmDirectionChanged();
  void cmPositive_speedChanged();
  void cmNegative_speedChanged();
  void cmPosition_0Changed();
  void input_vibrateChanged();
  void clear_vibrateChanged();
  void open_on_vibrateChanged();
  void close_on_vibrateChanged();
  void internal_periodChanged();
  void external_periodChanged();
  void trigger_periodChanged();
  void max_triggerChanged();

  void sigWeight(float value);
  void sigAdjust();
  void sigUnsound();
  void sigAiAdjust();

  void isStopChanged();
  void isPauseChanged();
  void finshDetection();

 public slots:
  void getVersion();
  //设置当前控制板任务，成功完成设置后，控制板状态应转为ready
  void setTask(int task);
  //获取当前控制板任务
  void getTask();
  //开始当前任务，控制板由ready或pause状态转变为工作或异常状态
  void startTask(QString sampleid);
  //暂停当前任务，控制板由工作状态转为pause或异常状态
  void pauseTask();
  //停止任务，控制板由工作或pasue状态转为ready或异常状态
  void stopTask();
  //获取光源信息
  void getLightInfo(int);
  //设置光源信息
  void setLightInfo(int id,int time);
  //设置光源OFF/ON
  void setLightStatus(int id,bool flag);
  //获取振动器参数
  void getVibratorInfo();
  //设置震动器参数
  void setVibratorInfo(int id,int key,int value);
  //获取直流电机信息
  void getDCmotorInfo();
  //设置直流电机信息
  void setDCmotorInfo(int id,bool value);
  //获取步进电机信息
  void getSMotorInfo();
  //设置步进电机信息
  void setSMotorInfo(int id,int key,int value);
  //获取相机触发信息
  void getTriggerInfo();
  //设置相机触发信息
  void set_trigger_info(int key,int value);

 public slots:
  void finshedResult();
  void sendGrainCount();
  void setDownLight();
  void closeDownLight();
signals:
  void sigUptrigger(bool falg);
  void sigStoptask();
 private:
  void unknown_status_handle(GBoard::component_status_t::stats_t status);
  void light_status_handle(int id, GBoard::component_status_t::stats_t status);
  void board_status_handle(GBoard::component_status_t::stats_t status);
  void start_grab();

 private:
  boost::shared_ptr<GBoard::board_plugin_api> m_plugin;
  std::vector<void*> m_board;
  BoardControlPrivate* m_boardControlPrivate;
  int m_reciveWightNum { 0 };
};


#endif  // BOARDCONTROL_H
