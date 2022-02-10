/**
 * @file boardcontrol.cpp
 * @author chenghao.pan (panchenghao@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-08-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "boardcontrol.h"
#include <QCoreApplication>
#include <QThread>
#include "../common/CMessageBox.h"
class BoardControlPrivate{
 public:
  explicit BoardControlPrivate() {}

  QVariantList m_lightTime {0, 0};
  ///< 送料电机方向，1：正向，2：反向
  int m_slDirection;
  ///< 送料电机前进速度 min max
  int m_slPositive_speed;
  ///< 送料电机后退速度 min max
  int m_slNegative_speed;
  ///< 送料电机预震时电机位置 min max
  int m_slPosition_0;
  ///< 送料电机开始震动时电机位置 min max
  int m_slPosition_1;
  ///< 送料电机停止震动时电机位置 min max
  int m_slPosition_2;
  ///< 仓门电机方向，1：正向，2：反向
  int m_cmDirection;
  ///< 仓门电机前进速度 min max
  int m_cmPositive_speed;
  ///< 仓门电机后退速度 min max
  int m_cmNegative_speed;
  ///< 仓门电机预震时电机位置 min max
  int m_cmPosition_0;
  ///< 开始进料时震动 min max
  int m_input_vibrate;
  ///< 最后清料时震动 min max
  int m_clear_vibrate;
  ///< 针对仓门电机，震动器入料时保持打开
  bool m_open_on_vibrate;
  ///< 针对仓门电机，震动器入料时保持关闭
  bool m_close_on_vibrate;
  ///< 针对相机，给其触发信号的间隔时间 min max
  int m_internal_period;
  ///< 针对两台不同相机，给其触发信号的间隔时间 min max
  int m_external_period;
  ///< 每次触发之间的间隔时间（针对图像校准） min max
  int m_trigger_period;
  ///< 最大触发次数
  int m_max_trigger;
  bool m_isStop {false};
  bool m_isPause {false};
};

BoardControl::BoardControl(QObject *parent)
    : QObject(parent), m_boardControlPrivate(new BoardControlPrivate) {
  findPlugin();
  init();
}

BoardControl::~BoardControl()
{
    //setConfig();
}

void BoardControl::findPlugin() {
    boost::dll::fs::path lib_path
            (QString(QCoreApplication::applicationDirPath()+"/3td").toStdString());
    auto plugins = GBoard::board_plugin_api::find_plugins<GBoard::board_plugin_api>(
                std::vector<boost::dll::fs::path>{lib_path / "board_plugin"},
                "create_board_plugin");
    for (const auto &plugin : plugins) {
        /// @todo: 这里m_plugin会被最后找到的plugin替换掉，如果有多个plugin的情况
        m_plugin = plugin;
        std::shared_ptr<std::vector<void*>> boards(new std::vector<void*>);
        plugin->enum_board(boards);
        QCoreApplication::processEvents();
        qDebug() << "[BOARD-INFO] " << plugin->name().c_str()
            << ": " << boards->size() << "boards found";
        while (true) {
            for (auto pboard : (*boards)) {
                GBoard::board_error_t ret = plugin->connect_board(pboard);
                QCoreApplication::processEvents();
                if (ret == GBoard::board_error_t::success) {
                    m_board.push_back(pboard);
                    // 设置状态回调函数
                    plugin->set_status_callback(std::bind(
                                                    &BoardControl::reciveBoardStatus,
                                                    this,
                                                    std::placeholders::_1,
                                                    std::placeholders::_2,
                                                    std::placeholders::_3));
                    // 设置数据回调函数
                    plugin->set_data_callback(std::bind(
                                                  &BoardControl::reciveWeightData,
                                                  this,
                                                  std::placeholders::_1,
                                                  std::placeholders::_2,
                                                  std::placeholders::_3));
                    //isfindPlugin=true;
                    /// @todo: 这里成功找到控制板后，直接break，不会继续寻找其他控制板
                    //break;
                    return;
                }else {
                    if(CMessageBox::ShowInfo("没有找到控制器，是否继续查找？", nullptr ,CMessageBox::StandardButton::YesNo)==0){
                        return;
                    }else {
                        continue;
                      }
                }
            }
        }
    }
}

void BoardControl::init() {
  // 读取配置文件
  QJsonObject rootObj = getConfig();
  // 光源配置
  if (rootObj.contains("light")) {
    QJsonObject obj = rootObj.value("light").toObject();
    // 光源0
    if (obj.contains("lightOne")) {
      setLightInfo(0, obj.value("lightOne").toInt());
      QThread::msleep(5);
    }
    // 光源1
    if (obj.contains("lightTwo")) {
      setLightInfo(1, obj.value("lightTwo").toInt());
      QThread::msleep(5);
    }
  }
  // 电机配置
  if (rootObj.contains("Motor")) {
    QJsonObject Motorobj = rootObj.value("Motor").toObject();
    // 送料电机(1号步进电机)
    if (Motorobj.contains("slMotor")) {
      QJsonObject slobj = Motorobj.value("slMotor").toObject();
      // 方向
      if (slobj.contains("direction")) {
        setSMotorInfo(1, 0, slobj.value("direction").toInt());
        QThread::msleep(5);
      }
      // 进速度
      if (slobj.contains("positive_speed")) {
        setSMotorInfo(1, 1, slobj.value("positive_speed").toInt());
        QThread::msleep(5);
      }
      // 回速度
      if (slobj.contains("negative_speed")) {
        setSMotorInfo(1, 2, slobj.value("negative_speed").toInt());
        QThread::msleep(5);
      }
      // 位置0: 预震送料电机位置
      if (slobj.contains("position_0")) {
        setSMotorInfo(1, 3, slobj.value("position_0").toInt());
        QThread::msleep(5);
      }
      // 位置1: 开始震动送料电机位置
      if (slobj.contains("position_1")) {
        setSMotorInfo(1, 4, slobj.value("position_1").toInt());
        QThread::msleep(5);
      }
      // 位置2: 结束震动送料电机位置
      if (slobj.contains("position_2")) {
        setSMotorInfo(1, 5, slobj.value("position_2").toInt());
        QThread::msleep(5);
      }
    }
    // 仓门电机(0号步进电机)
    if (Motorobj.contains("cmMotor")) {
      QJsonObject slobj = Motorobj.value("cmMotor").toObject();
      // 方向
      if (slobj.contains("direction")) {
        setSMotorInfo(0, 0, slobj.value("direction").toInt());
        QThread::msleep(5);
      }
      // 进速度
      if (slobj.contains("positive_speed")) {
        setSMotorInfo(0, 1, slobj.value("positive_speed").toInt());
        QThread::msleep(5);
      }
      // 回速度
      if (slobj.contains("negative_speed")) {
        setSMotorInfo(0, 2, slobj.value("negative_speed").toInt());
        QThread::msleep(5);
      }
      // 位置0: 仓门打开高度
      if (slobj.contains("position_0")) {
        setSMotorInfo(0, 3, slobj.value("position_0").toInt());
        QThread::msleep(5);
      }
    }
    // 0号震动器
    if (Motorobj.contains("zdMotor")) {
      QJsonObject slobj = Motorobj.value("zdMotor").toObject();
      // 进料时预震时长（后面改用料仓相机监控）
      if (slobj.contains("input_vibrate")) {
        setVibratorInfo(0, 0, slobj.value("input_vibrate").toInt());
        QThread::msleep(5);
      }
      // 清料时震动时长（后面改用料仓相机监控）
      if (slobj.contains("clear_vibrate")) {
        setVibratorInfo(0, 1, slobj.value("clear_vibrate").toInt());
        QThread::msleep(5);
      }
    }
    // 刮料电机(0号直流电机)
    if (Motorobj.contains("zlMotor")) {
      QJsonObject slobj=Motorobj.value("zlMotor").toObject();
      if (slobj.contains("open_on_vibrate")) {
        setDCmotorInfo(0, slobj.value("open_on_vibrate").toBool());
        QThread::msleep(5);
      }
    }
  }
  // 触发器设置
  if (rootObj.contains("Camera")) {
    QJsonObject obj = rootObj.value("Camera").toObject();
    // 板子给到同一个相机触发信号之间的时间间隔
    if (obj.contains("internal_period")) {
      set_trigger_info(0, obj.value("internal_period").toInt());
      QThread::msleep(5);
    }
    // 板子给到两个不同相机触发信号之间的时间间隔
    if (obj.contains("external_period")) {
      set_trigger_info(1, obj.value("external_period").toInt());
      QThread::msleep(5);
    }
    // 每次触发之间的间隔时间（针对图像校准）
    if (obj.contains("trigger_period")) {
      set_trigger_info(2, obj.value("trigger_period").toInt());
      QThread::msleep(5);
    }
    // 最大触发次数
    if (obj.contains("max_trigger")) {
      set_trigger_info(3, obj.value("max_trigger").toInt());
      QThread::msleep(5);
    }
  }

  // 设置任务
  /// @todo: 任务也应该由配置文件读取
  setTask(1);
  QThread::msleep(5);
}

/**
 * @brief 控制板状态回调函数
 * 
 * @param board 
 * @param status 
 * @param puser 
 */
void BoardControl::reciveBoardStatus(GBoard::version_info board,
    GBoard::component_status_t status, void *puser) {
  switch (status.name) {
    case GBoard::component_status_t::unknown:
      unknown_status_handle(status.status);
    break;
    case GBoard::component_status_t::light0:
      light_status_handle(0, status.status);
    break;
    case GBoard::component_status_t::light1:
      light_status_handle(1, status.status);
    break;
    case GBoard::component_status_t::board:
      board_status_handle(status.status);
    break;
    default: break;
  }
  // switch (status.status) {
  //   // 整机ready
  //   case GBoard::component_status_t::ready:
  //     if (!Login::SuperAdmin) {
  //         qDebug() << "detection finshed";
  //         emit finshDetection();
  //     }
  //   break;
  //   // 
  //   default: break;
  // }
}

/**
 * @brief 控制板数据回调函数
 * 
 * @param board 
 * @param frame 数据帧
 * @param puser 
 */
void BoardControl::reciveWeightData(GBoard::version_info board,
    GBoard::board_frame frame, void *puser) {
  std::lock_guard<std::mutex> l(GlobalObject::g_instance()->m_picMutex);
  switch (frame.name) {
  // 电子秤读数，上一批次样本重量
  case GBoard::board_frame::weightor:
  {
      m_reciveWightNum++;
      float weight = *(float*)&frame.value / 1000;
      //sigWeight(weight);
      GlobalObject::g_instance()->m_weights.push_back(weight);
      qDebug() << "[BOARD-INFO] weight data[" << m_reciveWightNum << "]: " << weight;
       emit sigWeight(weight);
      break;
  }
  // 未知数据返回，控制板异常？
  case GBoard::board_frame::unknown:
    qDebug() << "[BOARD-WARNING] board_frame::unknown received";
  break;
  default: break;
  }
}

/**
 * @brief 获取光源点亮时间
 * 
 * @return QVariantList 
 */
QVariantList BoardControl::lightTime() {
  return m_boardControlPrivate->m_lightTime;
}

/**
 * @brief 设置光源点亮时间
 * 
 * @param times 
 */
void BoardControl::setLightTime(QVariantList times) {
  m_boardControlPrivate->m_lightTime = times;
  emit lightTimeChanged();
}

/**
 * @brief 获取送料电机（1号步进电机）方向
 * 
 * @return int 
 */
int BoardControl::slDirection() {
  return m_boardControlPrivate->m_slDirection;
}

/**
 * @brief 设置送料电机（1号步进电机）方向
 * 
 * @param value 
 */
void BoardControl::setSlDirection(int value) {
  m_boardControlPrivate->m_slDirection = value;
  emit slDirectionChanged();
}

/**
 * @brief 获取送料电机进速度
 * 
 * @return int 
 */
int BoardControl::slPositive_speed() {
  return m_boardControlPrivate->m_slPositive_speed;
}

/**
 * @brief 设置送料电机进速度
 * 
 * @param value 
 */
void BoardControl::setSlPositive_speed(int value) {
  m_boardControlPrivate->m_slPositive_speed = value;
  emit slPositive_speedChanged();
}

/**
 * @brief 获取送料电机回速度
 * 
 * @return int 
 */
int BoardControl::slNegative_speed() {
  return m_boardControlPrivate->m_slNegative_speed;
}

/**
 * @brief 设置送料电机回速度
 * 
 * @param value 
 */
void BoardControl::setSlNegative_speed(int value) {
  m_boardControlPrivate->m_slNegative_speed = value;
  emit slNegative_speedChanged();
}

/**
 * @brief 获取送料电机位置0: 预震时送料电机位置
 * 
 * @return int 
 */
int BoardControl::slPosition_0() {
  return m_boardControlPrivate->m_slPosition_0;
}

/**
 * @brief 设置送料电机位置0: 预震时送料电机位置
 * 
 * @param value 
 */
void BoardControl::setSlPosition_0(int value) {
  m_boardControlPrivate->m_slPosition_0 = value;
  emit slPosition_0Changed();
}

/**
 * @brief 获取送料电机位置1: 开始震动时送料电机位置
 * 
 * @return int 
 */
int BoardControl::slPosition_1() {
  return m_boardControlPrivate->m_slPosition_1;
}

/**
 * @brief 设置送料电机位置1: 开始震动时送料电机位置
 * 
 * @param value 
 */
void BoardControl::setSlPosition_1(int value) {
  m_boardControlPrivate->m_slPosition_1 = value;
  emit slPosition_1Changed();
}

/**
 * @brief 获取送料电机位置2: 结束震动送料电机位置
 * 
 * @return int 
 */
int BoardControl::slPosition_2() {
  return m_boardControlPrivate->m_slPosition_2;
}

/**
 * @brief 设置送料电机位置2: 结束震动送料电机位置
 * 
 * @param value 
 */
void BoardControl::setSlPosition_2(int value) {
  m_boardControlPrivate->m_slPosition_2 = value;
  emit slPosition_2Changed();
}

/**
 * @brief 获取仓门电机（0号步进电机）方向
 * 
 * @return int 
 */
int BoardControl::cmDirection() {
  return m_boardControlPrivate->m_cmDirection;
}

/**
 * @brief 设置仓门电机方向
 * 
 * @param value 
 */
void BoardControl::setCmDirection(int value) {
  m_boardControlPrivate->m_cmDirection = value;
  emit cmDirectionChanged();
}

/**
 * @brief 获取仓门电机进速度
 * 
 * @return int 
 */
int BoardControl::cmPositive_speed() {
  return m_boardControlPrivate->m_cmPositive_speed;
}

/**
 * @brief 设置仓门电机进速度
 * 
 * @param value 
 */
void BoardControl::setCmPositive_speed(int value) {
  m_boardControlPrivate->m_cmPositive_speed = value;
  emit cmPositive_speedChanged();
}

/**
 * @brief 获取仓门电机回速度
 * 
 * @return int 
 */
int BoardControl::cmNegative_speed() {
  return m_boardControlPrivate->m_cmNegative_speed;
}

/**
 * @brief 设置仓门电机回速度
 * 
 * @param value 
 */
void BoardControl::setCmNegative_speed(int value) {
  m_boardControlPrivate->m_cmNegative_speed = value;
  emit cmNegative_speedChanged();
}

/**
 * @brief 获取仓门电机位置0（打开高度）
 * 
 * @return int 
 */
int BoardControl::cmPosition_0() {
  return m_boardControlPrivate->m_cmPosition_0;
}

/**
 * @brief 设置仓门电机位置0（打开高度）
 * 
 * @param value 
 */
void BoardControl::setCmPosition_0(int value) {
  m_boardControlPrivate->m_cmPosition_0 = value;
  emit cmPosition_0Changed();
}

/**
 * @brief 获取进料时震动时间（预震时间），后面改用入料相机控制
 * 
 * @return int 
 */
int BoardControl::input_vibrate() {
  return m_boardControlPrivate->m_input_vibrate;
}

/**
 * @brief 设置进料时震动时间（预震时间），后面改用入料相机控制
 * 
 * @param value 
 */
void BoardControl::setInput_vibrate(int value) {
  m_boardControlPrivate->m_input_vibrate = value;
  emit input_vibrateChanged();
}

/**
 * @brief 获取清料时震动时间，后面改用入料相机控制
 * 
 * @return int 
 */
int BoardControl::clear_vibrate() {
  return m_boardControlPrivate->m_clear_vibrate;
}

/**
 * @brief 设置清料时震动时间，后面改用入料相机控制
 * 
 * @param value 
 */
void BoardControl::setClear_vibrate(int value) {
  m_boardControlPrivate->m_clear_vibrate = value;
  emit clear_vibrateChanged();
}

///////////////////////// @todo 可以合并成两个函数，不用每次调用2个函数
/**
 * @brief 获取刮料电机策略（入料时打开 or 入料时关闭）
 * 
 * @return true 
 * @return false 
 */
bool BoardControl::open_on_vibrate() {
  return m_boardControlPrivate->m_open_on_vibrate;
}

/**
 * @brief 设置刮料电机策略（入料时打开 or 入料时关闭）
 * 
 * @param value 
 */
void BoardControl::setOpen_on_vibrate(bool value) {
  m_boardControlPrivate->m_open_on_vibrate = value;
  emit open_on_vibrateChanged();
}

bool BoardControl::close_on_vibrate() {
  return m_boardControlPrivate->m_close_on_vibrate;
}

void BoardControl::setClose_on_vibrate(bool value) {
  m_boardControlPrivate->m_close_on_vibrate = value;
  emit close_on_vibrateChanged();
}
//////////////////////// @todo end ///////////////////////////////////

/**
 * @brief 获取同一相机触发信号间隔
 * 
 * @return int 
 */
int BoardControl::internal_period() {
  return m_boardControlPrivate->m_internal_period;
}

/**
 * @brief 设置同一相机触发信号间隔
 * 
 * @param value 
 */
void BoardControl::setInternal_period(int value) {
  m_boardControlPrivate->m_internal_period = value;
  emit internal_periodChanged();
}

/**
 * @brief 获取不同相机触发信号间隔
 * 
 * @return int 
 */
int BoardControl::external_period() {
  return m_boardControlPrivate->m_external_period;
}

/**
 * @brief 设置不同相机触发信号间隔
 * 
 * @param value 
 */
void BoardControl::setExternal_period(int value)
{
  m_boardControlPrivate->m_external_period=value;
  emit external_periodChanged();
}

/**
 * @brief 获取每组触发间隔
 * 
 * @return int 
 */
int BoardControl::trigger_period()
{
  return m_boardControlPrivate->m_trigger_period;
}

/**
 * @brief 设置每组触发间隔时间
 * 
 * @param value 
 */
void BoardControl::setTrigger_period(int value) {
  m_boardControlPrivate->m_trigger_period = value;
  emit trigger_periodChanged();
}

/**
 * @brief 获取最大触发次数
 * 
 * @return int 
 */
int BoardControl::max_trigger() {
  return m_boardControlPrivate->m_max_trigger;
}

/**
 * @brief 设置最大触发次数
 * 
 * @param value 
 */
void BoardControl::setMax_trigger(int value) {
  m_boardControlPrivate->m_max_trigger = value;
  emit max_triggerChanged();
}

void BoardControl::setIsStop(bool value) {
  m_boardControlPrivate->m_isStop = value;
  emit isStopChanged();
}

bool BoardControl::isPause() {
  return m_boardControlPrivate->m_isPause;
}

void BoardControl::setIsPause(bool value) {
  m_boardControlPrivate->m_isPause = value;
  emit isPauseChanged();
}

void BoardControl::setConfig()
{
   QJsonObject rootObj= getConfig();

   QJsonObject lightObj = rootObj.find("light").value().toObject();
   lightObj.find("lightOne").value()=lightTime().at(0).toInt();
   lightObj.find("lightTwo").value()=lightTime().at(1).toInt();

   QJsonObject motorObj = rootObj.find("Motor").value().toObject();
   QJsonObject slObj = motorObj.find("slMotor").value().toObject();
   slObj.find("direction").value()=slDirection();
   slObj.find("positive_speed").value()=slPositive_speed();
   slObj.find("negative_speed").value()=slNegative_speed();
   slObj.find("position_0").value()=slPosition_0();
   slObj.find("position_1").value()=slPosition_1();
   slObj.find("position_2").value()=slPosition_2();

   QJsonObject cmObj = motorObj.find("cmMotor").value().toObject();
   cmObj.find("direction").value()=cmDirection();
   cmObj.find("positive_speed").value()=cmPositive_speed();
   cmObj.find("negative_speed").value()=cmNegative_speed();
   cmObj.find("position_0").value()=cmPosition_0();

   QJsonObject zdObj = motorObj.find("zdMotor").value().toObject();
   zdObj.find("input_vibrate").value()=input_vibrate();
   zdObj.find("clear_vibrate").value()=clear_vibrate();

   QJsonObject zlObj = motorObj.find("zlMotor").value().toObject();
   zlObj.find("open_on_vibrate").value()=open_on_vibrate();
   zlObj.find("close_on_vibrate").value()=close_on_vibrate();

   QJsonObject cameraObj = rootObj.find("Camera").value().toObject();
   cameraObj.find("internal_period").value()=internal_period();
   cameraObj.find("external_period").value()=external_period();
   cameraObj.find("trigger_period").value()=trigger_period();
   cameraObj.find("max_trigger").value()=max_trigger();


   QFile File(QApplication::applicationDirPath()+"/config.json");
   QJsonDocument doc;
   doc.setObject(rootObj);
   File.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
   File.write(doc.toJson());
   File.close();
}


bool BoardControl::isStop() {
  return m_boardControlPrivate->m_isStop;
}

/**
 * @brief 获取控制板版本信息
 * @todo 调用该函数没有意义
 * 
 */
void BoardControl::getVersion() {
  if (m_board.size() > 0) {
    GBoard::version_info version;
    m_plugin->get_version_info(m_board[0], &version);
  }
}

/**
 * @brief 设置控制板任务
 * 
 * @param task 
 */
void BoardControl::setTask(int task) {
  if (m_board.size() > 0) {
    GBoard::board_tasks_t task_type;
    switch (task) {
      case 0:
        task_type = GBoard::board_tasks_t::null;
      break;
      // 设置不完善粒任务
      case 1:
        task_type = GBoard::board_tasks_t::unsound;
        emit sigUnsound();
      break;
      // 设置图像校准任务
      case 2:
        task_type = GBoard::board_tasks_t::im_calibrate;
        emit sigAdjust();
      break;
      // 设置算法校准
      case 3:
        task_type = GBoard::board_tasks_t::ai_calibrate;
        emit sigAiAdjust();
      break;
      /// @todo: 默认设置不完善粒任务
      default:
        task_type = GBoard::board_tasks_t::null;
      break;
    }
    m_plugin->set_task(m_board[0], task_type);
  }
}

/**
 * @brief 获取当前控制板任务
 * @todo 该接口没意义，获取到的任务只是在函数内部
 * 
 */
void BoardControl::getTask() {
  if (m_board.size() > 0) {
    std::shared_ptr<GBoard::board_tasks_t> task = std::make_shared<GBoard::board_tasks_t>();
    m_plugin->get_task(m_board[0], task.get());
  }
}

/**
 * @brief 开始任务
 * 
 */
void BoardControl::startTask(QString sampleid) {
  GlobalObject::g_instance()->g_smapleid=sampleid;
  if (m_board.size() > 0) {
    m_plugin->start_task(m_board[0]);
    setIsStop(false);
    /// @todo isPause = ture ???
    setIsPause(true);
  }
}

/**
 * @brief 暂停任务
 * 
 */
void BoardControl::pauseTask() {
  if (m_board.size() > 0) {
    m_plugin->pause_task(m_board[0]);
    /// @todo isPause = false ???
    setIsPause(false);
  }
}

/**
 * @brief 停止任务
 * 
 */
void BoardControl::stopTask() {
  if (m_board.size() > 0) {
    // qDebug() << "[BOARD-INFO] stopTask";
    m_plugin->stop_task(m_board[0]);
    emit sigStoptask();
    m_reciveWightNum = 0;
  }
}

/**
 * @brief 获取光源信息
 * 
 * @param id 
 */
void BoardControl::getLightInfo(int id) {
  if (m_board.size() > 0) {
    std::shared_ptr<GBoard::light_info> l = std::make_shared<GBoard::light_info>();
    l->id = id;
    m_plugin->get_light_info(m_board[0], l.get());
    m_boardControlPrivate->m_lightTime.replace(id, l->on_time);
    setLightTime(m_boardControlPrivate->m_lightTime);
  }
}

/**
 * @brief 设置光源信息
 * 
 * @param id 
 * @param time 
 */
void BoardControl::setLightInfo(int id, int time) {
  if (m_board.size() > 0) {
    qDebug() << "[BOARD-INFO] set light-on_time[" << id << "]: " << time;
    GBoard::light_info l{(std::uint8_t)id, GBoard::light_info::on_time,(std::uint16_t)time};
    m_plugin->set_light_info(m_board[0], l);
    m_boardControlPrivate->m_lightTime.replace(id, time);
    setLightTime(m_boardControlPrivate->m_lightTime);
  }
}

void BoardControl::setLightStatus(int id, bool flag)
{
    if (m_board.size() > 0) {
      GBoard::light_info l;
      l.id=(std::uint8_t)id;
      l.value=(std::uint16_t)0;
      flag?l.key=GBoard::light_info::on:l.key=GBoard::light_info::off;
      m_plugin->set_light_info(m_board[0], l);
    }
}

/**
 * @brief 获取振动器信息
 * @todo 调用该接口没意义
 */
void BoardControl::getVibratorInfo() {
  if (m_board.size() > 0) {
    std::shared_ptr<GBoard::vibrator_info> v = std::make_shared<GBoard::vibrator_info>();
    m_plugin->get_vibrator_info(m_board[0], v.get());
  }
}

/**
 * @brief 设置振动器信息
 * 
 * @param id 
 * @param key 
 * @param value 
 */
void BoardControl::setVibratorInfo(int id, int key, int value) {
  if(m_board.size()>0){
    GBoard::vibrator_info v;
    v.id = id;
    switch (key) {
      // 入料时震动时间
      case 0:
        v.key = GBoard::vibrator_info::input_vibrate;
        setInput_vibrate(value);
      break;
      // 清料时震动时间
      case 1:
        v.key = GBoard::vibrator_info::clear_vibrate;
        setClear_vibrate(value);
      break;
      default:
      break;
    }
    v.value = value;
    m_plugin->set_vibrator_info(m_board[0], v);
  }
}

/**
 * @brief 获取直流电机信息
 * @todo 调用该接口没有意义
 */
void BoardControl::getDCmotorInfo() {
  if (m_board.size() > 0) {
    std::shared_ptr<GBoard::dcmotor_info> m = std::make_shared<GBoard::dcmotor_info>();
    m_plugin->get_dcmotor_info(m_board[0], m.get());
  }
}

/**
 * @brief 设置直流电机（刮料电机）：进料时开启 or 进料时关闭
 * 
 * @param id 
 * @param value 
 */
void BoardControl::setDCmotorInfo(int id, bool value) {
  if (m_board.size() > 0) {
    GBoard::dcmotor_info m;
    m.id=id;
    value == 1 ? m.value = GBoard::dcmotor_info::open_on_vibrate :
                 m.value = GBoard::dcmotor_info::close_on_vibrate;
    value == 1 ? setOpen_on_vibrate(true) : setOpen_on_vibrate(false);
    //value==2?setOpen_on_vibrate(false):setOpen_on_vibrate(false);
    m_plugin->set_dcmotor_info(m_board[0], m);
  }
}

/**
 * @brief 获取步进电机信息
 * @todo 调用接口没有意义
 * @todo 没有区分电机序号，获取所有电机信息？
 */
void BoardControl::getSMotorInfo() {
  if (m_board.size() > 0) {
    std::shared_ptr<GBoard::smotor_info> m = std::make_shared<GBoard::smotor_info>();
    m_plugin->get_smotor_info(m_board[0], m.get());
  }
}

/**
 * @brief 设置步进电机
 * 
 * @param id 
 * @param key 
 * @param value 
 */
void BoardControl::setSMotorInfo(int id, int key, int value) {
  if (m_board.size() > 0) {
    GBoard::smotor_info m;
    m.id = id;
    switch (key) {
      // 方向
      case 0:
        m.key = GBoard::smotor_info::direction;
        id == 1 ? setSlDirection(value) : setCmDirection(value);
      break;
      // 进速度
      case 1:
        m.key = GBoard::smotor_info::positive_speed;
        id == 1 ? setSlPositive_speed(value) : setCmPositive_speed(value);
      break;
      // 回速度
      case 2:
        m.key = GBoard::smotor_info::negative_speed;
        id == 1 ? setSlNegative_speed(value) : setCmNegative_speed(value);
      break;
      // 位置0
      case 3:
        m.key = GBoard::smotor_info::position_0;
        id == 1 ? setSlPosition_0(value) : setCmPosition_0(value);
      break;
      // 位置1
      case 4:
        m.key = GBoard::smotor_info::position_1;
        setSlPosition_1(value);
      break;
      // 位置2
      case 5:
        m.key = GBoard::smotor_info::position_2;
        setSlPosition_2(value);
      break;
      default:
      break;
    }
    m.value = value;
    m_plugin->set_smotor_info(m_board[0], m);
  }
}

/**
 * @brief 获取触发器信息
 * @todo 调用该接口没有意义
 */
void BoardControl::getTriggerInfo() {
  if (m_board.size() > 0) {
    std::shared_ptr<GBoard::trigger_info> t = std::make_shared<GBoard::trigger_info>();
    m_plugin->get_trigger_info(m_board[0], t.get());
  }
}

/**
 * @brief 设置触发器信息
 * 
 * @param key 
 * @param value 
 */
void BoardControl::set_trigger_info(int key, int value) {
  if (m_board.size() > 0) {
    GBoard::trigger_info t;
    switch (key) {
      case 0:
        t.key = GBoard::trigger_info::internal_period;
        setInternal_period(value);
      break;
      case 1:
        t.key = GBoard::trigger_info::external_period;
        setExternal_period(value);
      break;
      case 2:
        t.key = GBoard::trigger_info::trigger_period;
        setTrigger_period(value);
      break;
      case 3:
        t.key = GBoard::trigger_info::max_trigger;
        setMax_trigger(value);
      break;
      default:
      break;
    }
    t.value=value;
    m_plugin->set_trigger_info(m_board[0], t);
  }
}

void BoardControl::finshedResult() {
    setIsStop(true);
}

void BoardControl::sendGrainCount()
{
    if (m_board.size() > 0) {
        GBoard::weightor_info  weightInfo;
        weightInfo.key= GBoard::weightor_info::shift;
        weightInfo.value=0;
        m_plugin->set_weightor_info(m_board[0],weightInfo);
    }
}
#include <QThread>
void BoardControl::setDownLight()
{
    setLightStatus(0,false);
    QThread::msleep(50);
    setLightStatus(1,true);
    GlobalObject::GrapReady=false;
    emit sigUptrigger(false);
}

void BoardControl::closeDownLight()
{
    setLightStatus(1,false);
}

void BoardControl::unknown_status_handle(GBoard::component_status_t::stats_t status) {
  switch(status) {
    case GBoard::component_status_t::invalid:
    break;
    case GBoard::component_status_t::ready:
    break;
    case GBoard::component_status_t::running:
    break;
    case GBoard::component_status_t::pause:
    break;
    case GBoard::component_status_t::exception:
    break;
    case GBoard::component_status_t::grab_ready:
    break;
    case GBoard::component_status_t::query:
    break;
    default: break;
  }
}

void BoardControl::light_status_handle(int id, GBoard::component_status_t::stats_t status) {
  switch(status) {
    case GBoard::component_status_t::invalid:
    break;
    case GBoard::component_status_t::ready:
    break;
    case GBoard::component_status_t::running:
    break;
    case GBoard::component_status_t::pause:
    break;
    case GBoard::component_status_t::exception:
    break;
    case GBoard::component_status_t::grab_ready:
    break;
    case GBoard::component_status_t::query:
    break;
    default: break;
  }
}

void BoardControl::board_status_handle(GBoard::component_status_t::stats_t status) {
    switch(status) {
    case GBoard::component_status_t::invalid:
        break;
    case GBoard::component_status_t::ready:
    {
        qDebug() << "[BOARD-INFO] READY status from board, finished";
        std::lock_guard<std::mutex> l(GlobalObject::g_instance()->m_picMutex);
        while(!GlobalObject::g_instance()->m_saveImgData.empty()){
            qDebug() << "[BOARD-ERROR] weight data count not match";
            GlobalObject::g_instance()->m_saveImgData.pop();
        }
        if (!Login::SuperAdmin) {
            emit finshDetection();
        }
    }
        break;
    case GBoard::component_status_t::running:
    break;
    case GBoard::component_status_t::pause:
    break;
    case GBoard::component_status_t::exception:
    break;
    case GBoard::component_status_t::grab_ready:
#ifdef SOFTERTRIGER
    start_grab();
#endif
    break;
    case GBoard::component_status_t::query:
    break;
    default: break;
  }
}

void BoardControl::start_grab() {
  QThread::msleep(20);
  GlobalObject::GrapReady=true;
/// @todo: 上光源点亮（0号光源）
  setLightStatus(0,true);
  QThread::msleep(10);
/// @todo: 软触发0号1号相机
  emit sigUptrigger(true);
/// @todo: 上光源关闭，下光源点亮
/// @todo: 软触发0号1号相机
/// @todo: 下光源关闭
}
