#include "BoardProperty.h"
class BoardControlPrivate{
public:
    explicit BoardControlPrivate() {}
    ///< 送料电机方向，1：正向，2：反向
    int m_slDirection;
    ///< 送料电机前进速度 min max
    int m_slPositiveSpeed;
    ///< 送料电机后退速度 min max
    int m_slNegativeSpeed;
    ///< 送料电机预震时电机位置 min max
    int m_slPrePosition;
    ///< 送料电机开始震动时电机位置 min max
    int m_slStartPosition;
    ///< 送料电机停止震动时电机位置 min max
    int m_slStopPosition;
    // 拍照延时
    int m_triggerDlay;
    ///< 仓门电机方向，1：正向，2：反向
    int m_cmDirection;
    ///< 仓门电机前进速度 min max
    int m_cmPositiveSpeed;
    ///< 仓门电机后退速度 min max
    int m_cmNegativeSpeed;
    ///< 仓门电机预震时电机位置 仓门打开高度min max
    int m_cmPrePosition;
    ///< 开始进料时震动 min max
    int m_inputVibrate;
    ///< 最后清料时震动 min max
    int m_clearVibrate;
    ///< 针对仓门电机，震动器入料时保持打开
    bool m_openOnVibrate;
    ///< 针对仓门电机，震动器入料时保持关闭
    bool m_closeOnVibrate;
    ///< 最大触发次数
    int m_maxTrigger;
    // 中心频率
    float m_centerRate;
    // 出料速度
    int m_outputRate;
    // 震动频率
    float m_vibrationRate;
    //电压
    int m_voltage;
    //设备状态
    bool m_isStop {false};
    bool m_isPause {false};
};

int BoardProperty::slDirection()
{
    return m_d->m_slDirection;
}

void BoardProperty::setSlDirection(int value)
{
    m_d->m_slDirection=value;
    emit slDirectionChanged();
}

int BoardProperty::slPositiveSpeed()
{
    return m_d->m_slPositiveSpeed;
}

void BoardProperty::setSlPositiveSpeed(int value)
{
    m_d->m_slPositiveSpeed=value;
    emit slPositiveSpeedChanged();
}

int BoardProperty::slNegativeSpeed()
{
    return m_d->m_slNegativeSpeed;
}

void BoardProperty::setSlNegativeSpeed(int value)
{
    m_d->m_slNegativeSpeed=value;
    emit slNegativeSpeedChanged();
}

int BoardProperty::slPrePosition()
{
    return m_d->m_slPrePosition;
}

void BoardProperty::setSlPrePosition(int value)
{
    m_d->m_slPrePosition=value;
    emit slPrePositionChanged();
}

int BoardProperty::slStartPosition()
{
    return m_d->m_slStartPosition;
}

void BoardProperty::setSlStartPosition(int value)
{
    m_d->m_slStartPosition=value;
    emit slStartPositionChanged();
}

int BoardProperty::slStopPosition()
{
    return m_d->m_slStopPosition;
}

void BoardProperty::setSlStopPosition(int value)
{
    m_d->m_slStopPosition=value;
    emit slStopPositionChanged();
}

int BoardProperty::cmDirection()
{
    return m_d->m_cmDirection;
}

void BoardProperty::setCmDirection(int value)
{
    m_d->m_cmDirection=value;
    emit cmDirectionChanged();
}

int BoardProperty::cmPositiveSpeed()
{
    return m_d->m_cmPositiveSpeed;
}

void BoardProperty::setCmPositiveSpeed(int value)
{
    m_d->m_cmPositiveSpeed=value;
    emit cmPositiveSpeedChanged();
}

int BoardProperty::cmNegativeSpeed()
{
    return m_d->m_cmNegativeSpeed;
}

void BoardProperty::setCmNegativeSpeed(int value)
{
    m_d->m_cmNegativeSpeed=value;
    emit cmNegativeSpeedChanged();
}

int BoardProperty::cmPrePosition()
{
    return m_d->m_cmPrePosition;
}

void BoardProperty::setCmPrePosition(int value)
{
    m_d->m_cmPrePosition=value;
    emit cmPrePositionChanged();
}

int BoardProperty::inputVibrate()
{
    return m_d->m_inputVibrate;
}

void BoardProperty::setInputVibrate(int value)
{
    m_d->m_inputVibrate=value;
    emit inputVibrateChanged();
}

int BoardProperty::clearVibrate()
{
    return m_d->m_clearVibrate;
}

void BoardProperty::setClearVibrate(int value)
{
    m_d->m_clearVibrate=value;
    emit clearVibrateChanged();
}

bool BoardProperty::openOnVibrate()
{
    return m_d->m_openOnVibrate;
}

void BoardProperty::setOpenOnVibrate(bool value)
{
    m_d->m_openOnVibrate=value;
    emit openOnVibrateChanged();
}

bool BoardProperty::closeOnVibrate()
{
    return m_d->m_closeOnVibrate;
}

void BoardProperty::setCloseOnVibrate(bool value)
{
    m_d->m_closeOnVibrate=value;
    emit closeOnVibrateChanged();
}

int BoardProperty::maxTrigger()
{
    return m_d->m_maxTrigger;
}

void BoardProperty::setMaxTrigger(int value)
{
    m_d->m_maxTrigger=value;
    emit maxTriggerChanged();
}

int BoardProperty::isStop()
{
    return m_d->m_isStop;
}

void BoardProperty::setIsStop(bool value)
{
    m_d->m_isStop=value;
    emit isStopChanged();
}

int BoardProperty::isPause()
{
    return m_d->m_isPause;
}

void BoardProperty::setIsPause(bool value)
{
    m_d->m_isPause=value;
    emit isPauseChanged();
}

int BoardProperty::triggerDlay()
{
    return m_d->m_triggerDlay;
}

void BoardProperty::setTriggerDlay(int value)
{
    m_d->m_triggerDlay=value;
    emit triggerDlayChanged();
}

float BoardProperty::centerRate()
{
    return m_d->m_centerRate;
}

void BoardProperty::setCenterRate(float value)
{
    m_d->m_centerRate=value;
    emit centerRateChanged();
}

int BoardProperty::outputRate()
{
    return m_d->m_outputRate;
}

void BoardProperty::setOutputRate(int value)
{
    m_d->m_outputRate=value;
    emit outputRateChanged();
}

float BoardProperty::vibrationRate()
{
    return m_d->m_vibrationRate;
}

void BoardProperty::setVibrationRate(float value)
{
    m_d->m_vibrationRate=value;
    emit vibrationRateChanged();
}

int BoardProperty::voltage()
{
    return m_d->m_voltage;
}

void BoardProperty::setVoltage(int value)
{
    m_d->m_voltage=value;
    emit voltageChanged();
}

BoardProperty::BoardProperty(std::shared_ptr<board::board> board):m_board(board)
  ,m_d(std::make_shared<BoardControlPrivate>())
{
    //initBoard();
    Login::MainTainUser ? flowLightEnable(true):flowLightEnable(true);
}
void BoardProperty::setTask(int value)
{
    board::e_task task_type;
    switch (value) {
    case 0:
        task_type = board::e_task::null;
        break;
        // 设置不完善粒任务
    case 1:
        task_type = board::e_task::unsound;
        break;
        // 设置图像校准任务
    case 2:
        task_type =board::e_task::im_calibrate;
        break;
        // 设置算法校准
    case 3:
        task_type =board::e_task::ai_calibrate;
        break;
        /// @todo: 默认设置不完善粒任务
    default:
        task_type =  board::e_task::null;
        break;
    }
    m_board->task(task_type);
}

board::e_task BoardProperty::getTask()
{
    return m_board->task();
}

void BoardProperty::startTask()
{
    m_board->start_task();
    setIsPause(false);
    setIsStop(false);
}

void BoardProperty::pasueTask()
{
    m_board->pasue_task();
    setIsPause(true);
    setIsStop(false);
}

void BoardProperty::stopTask()
{
    m_board->stop_task();
    setIsStop(true);
}

void BoardProperty::setSmotorDirection(int smotor_id, int direction)
{
    m_board->smotor_direction(smotor_id,direction);
    if(smotor_id==SLMOTOR){
        setSlDirection(direction);
    }else if(smotor_id==CMMOTOR){
        setCmDirection(direction);
    }
}

int BoardProperty::getSmotorDirection(int smotor_id)
{
    return m_board->smotor_direction(smotor_id);
}

void BoardProperty::setSmotorPositiveSpeed(int id, int speed)
{
    LOGGER_DEBUG("修改送料电机前进速度:%d",speed);
    m_board->smotor_positive_speed(id,speed);
    if(id==SLMOTOR){
        setSlPositiveSpeed(speed);
    }else if(id==CMMOTOR){
        setCmPositiveSpeed(speed);
    }
}

int BoardProperty::getSmotorPositiveSpeed(int id)
{
    return m_board->smotor_positive_speed(id);
}

void BoardProperty::setSmotorNegtiveSpeed(int id, int speed)
{
    LOGGER_DEBUG("修改送料电机回退速度:%d",speed);
    m_board->smotor_negtive_speed(id,speed);
    if(id==SLMOTOR){
        setSlNegativeSpeed(speed);
    }else if(id==CMMOTOR){
        setCmNegativeSpeed(speed);
    }
}

int BoardProperty::getSmotorNegtiveSpeed(int id)
{
    return m_board->smotor_negtive_speed(id);
}

void BoardProperty::setSmotorPrePosition(int id, int pos)
{

    m_board->smotor_pre_position(id,pos);
    if(id==SLMOTOR){
        LOGGER_DEBUG("修改送料电机预震位置:%d",pos);
        setSlPrePosition(pos);
    }else if(id==CMMOTOR){
        LOGGER_DEBUG("修改仓门电机仓门打开位置:%d",pos);
        setCmPrePosition(pos);
    }
}

int BoardProperty::getSmotorPrePosition(int id)
{
    return m_board->smotor_pre_position(id);
}

void BoardProperty::setSmotorStartPosition(int id, int pos)
{
    LOGGER_DEBUG("修改送料电机开始位置:%d",pos);
    m_board->smotor_start_position(id,pos);
    if(id==SLMOTOR){
        setSlStartPosition(pos);
    }else if(id==CMMOTOR){

    }
}

int BoardProperty::getSmotorStartPosition(int id)
{
    return m_board->smotor_start_position(id);
}

void BoardProperty::setSmotorStoPosition(int id, int pos)
{
    LOGGER_DEBUG("修改送料电机停止位置:%d",pos);
    m_board->smotor_stop_position(id,pos);
    if(id==SLMOTOR){
        setSlStopPosition(pos);
    }else if(id==CMMOTOR){

    }
}

int BoardProperty::getSmotorStoPosition(int id)
{
    return m_board->smotor_stop_position(id);
}

void BoardProperty::setVibratorInputTime(int id, int time)
{
    m_board->vibrator_input_time(id,time);
    setInputVibrate(time);
}

int BoardProperty::getVibratorInputTime(int id)
{
    return m_board->vibrator_input_time(id);
}

void BoardProperty::setVibratorClearTime(int id, int time)
{
    m_board->vibrator_clear_time(id,time);
    setClearVibrate(time);
}

int BoardProperty::getVibratorClearTime(int id)
{
    return m_board->vibrator_clear_time(id);
}

void BoardProperty::setDcmotorPolicy(int id, bool policy)
{
    LOGGER_DEBUG("修改刮料电机:%d",policy);
    policy?m_board->dcmotor_policy(id,1):m_board->dcmotor_policy(id,2);
    setOpenOnVibrate(policy);
}

int BoardProperty::getDcmotorPolicy(int id)
{
    return m_board->dcmotor_policy(id);
}

void BoardProperty::setMaxTriggerCount(int count)
{
    m_board->max_trigger_count(count);
    setMaxTrigger(count);
}

int BoardProperty::getMaxTriggerVount()
{
    return m_board->max_trigger_count();
}

int BoardProperty::getBoardTriggertDlay()
{
    return 0;
}

void BoardProperty::setBoardTriggertDlay(int value)
{
    LOGGER_DEBUG("拍照延时:%d",value);
    m_board->capture_delay(value);
    setTriggerDlay(value);
}

void BoardProperty::setZdmotorOutRate(int id,int value)
{
    LOGGER_DEBUG("修改震动器出料速度:%d",value);
    m_board->vibrator_discharge_speed(id,value);
    setOutputRate(value);
}

void BoardProperty::setZdmotorRate(int id ,int value)
{
    LOGGER_DEBUG("修改震动器出震动频率:%d",value);
    m_board->vibrator_vibration_frequency(id,value);
    setVibrationRate(value);
}

void BoardProperty::setZdmotorVoltage(int id,int value)
{
    LOGGER_DEBUG("修改震动器电压:%d",value);
    m_board->vibrator_voltage(id,value);
    setVoltage(value);
}

void BoardProperty::saveCameraConfig()
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

void BoardProperty::flowLightEnable(bool value)
{
    value?m_board->light_on(2):m_board->light_off(2);
}

int BoardProperty::query_recycle()
{
    LOGGER_DEBUG("query_recycle");
    return m_board->query_recycle();
}

void BoardProperty::setZdmotorCenterRate(int id,float value)
{
    LOGGER_DEBUG("修改震动器中心频率:%d",value);
    m_board->vibrator_center_frequency(id,value);
    setCenterRate(value);
}

void BoardProperty::initBoard()
{
    switch (GlobalObject::g_grainType) {
    case GrainType::WHEAT: readConfig("wheat");
        break;
    case GrainType::RICE: readConfig("wheat");
        break;
    case GrainType::CRON: readConfig("wheat");
        break;
    case GrainType::SORGHUM: readConfig("wheat");
        break;
    default:readConfig("wheat");
        break;
    }
}

void BoardProperty::readConfig(QString grainType)
{
    // 读取配置文件
    QJsonObject rootObj = getConfig();
    if(rootObj.contains(grainType)){
        QJsonObject objNode = rootObj.value(grainType).toObject();
        //最大次数
//        if(objNode.contains("max_trigger")){
//        setMaxTriggerCount(objNode.value("max_trigger").toInt());
//        }
        // 电机配置
        if (objNode.contains("Motor")) {
            QJsonObject Motorobj = objNode.value("Motor").toObject();
            // 送料电机(1号步进电机)
            if (Motorobj.contains("slMotor")) {
                QJsonObject slobj = Motorobj.value("slMotor").toObject();
                // 方向
//                if (slobj.contains("direction")) {
//                    setSmotorDirection(SLMOTOR,slobj.value("direction").toInt());
//                    QThread::msleep(5);
//                }
                // 进速度
                if (slobj.contains("forward_speed")) {
                    setSmotorPositiveSpeed(SLMOTOR,slobj.value("forward_speed").toInt());
                    QThread::msleep(5);
                }
                // 回速度
                if (slobj.contains("back_speed")) {
                    setSmotorNegtiveSpeed(SLMOTOR,slobj.value("back_speed").toInt());
                    QThread::msleep(5);
                }
                // 位置0: 预震送料电机位置
                if (slobj.contains("pre_position")) {
                    setSmotorPrePosition(SLMOTOR,slobj.value("pre_position").toInt());
                    QThread::msleep(5);
                }
                // 位置1: 开始震动送料电机位置
                if (slobj.contains("start_position")) {
                    setSmotorStartPosition(SLMOTOR,slobj.value("start_position").toInt());
                    QThread::msleep(5);
                }
                // 位置2: 结束震动送料电机位置
                if (slobj.contains("end_position")) {
                    setSmotorStoPosition(SLMOTOR,slobj.value("end_position").toInt());
                    QThread::msleep(5);
                }
                //拍照延时
                if (slobj.contains("trigger_delay")) {
                    //setSmotorStoPosition(SLMOTOR,slobj.value("end_position").toInt());
                    setBoardTriggertDlay(slobj.value("trigger_delay").toInt());
                    QThread::msleep(5);
                }
            }
            // 仓门电机(0号步进电机)
            if (Motorobj.contains("cmMotor")) {
                QJsonObject slobj = Motorobj.value("cmMotor").toObject();
                // 方向
//                if (slobj.contains("direction")) {
//                    setSmotorDirection(CMMOTOR,slobj.value("direction").toInt());
//                    QThread::msleep(5);
//                }
//                // 进速度
//                if (slobj.contains("positive_speed")) {
//                    setSmotorPositiveSpeed(CMMOTOR,slobj.value("positive_speed").toInt());
//                    QThread::msleep(5);
//                }
//                // 回速度
//                if (slobj.contains("negative_speed")) {
//                    setSmotorNegtiveSpeed(CMMOTOR,slobj.value("negative_speed").toInt());
//                    QThread::msleep(5);
//                }
                // 位置0: 仓门打开高度
                if (slobj.contains("open_height")) {
                    setSmotorPrePosition(CMMOTOR,slobj.value("open_height").toInt());
                    QThread::msleep(5);
                }
            }
            // 0号震动器
            if (Motorobj.contains("zdMotor")) {
                QJsonObject slobj = Motorobj.value("zdMotor").toObject();
                // 中心频率
                if (slobj.contains("center_rate")) {
                    //setDcmotorPolicy(0,slobj.value("input_vibrate").toInt());
                    //setInputVibrate(slobj.value("input_vibrate").toInt());
                    setZdmotorCenterRate(0,slobj.value("center_rate").toInt());
                    QThread::msleep(5);
                }
                // 出料速度
                if (slobj.contains("output_speed")) {
                    //setDcmotorPolicy(0,slobj.value("clear_vibrate").toInt());
                    setZdmotorOutRate(0,slobj.value("output_speed").toInt());
                    QThread::msleep(5);
                }
                // 震动频率
                if (slobj.contains("vibration_rate")) {
                    //setDcmotorPolicy(0,slobj.value("clear_vibrate").toInt());
                    setZdmotorRate(0,slobj.value("vibration_rate").toInt());
                    QThread::msleep(5);
                }
                // 电压
                if (slobj.contains("voltage")) {
                    //setDcmotorPolicy(0,slobj.value("clear_vibrate").toInt());
                    setZdmotorVoltage(0,slobj.value("voltage").toInt());
                    QThread::msleep(5);
                }
            }
            // 刮料电机(0号直流电机)
            if (Motorobj.contains("glMotor")) {
                QJsonObject slobj=Motorobj.value("glMotor").toObject();
                if (slobj.contains("open_on_vibrate")) {
                    setDcmotorPolicy(0,slobj.value("open_on_vibrate").toBool());
                    QThread::msleep(5);
                }
            }
        }
    }
}

void BoardProperty::saveCameraConfig(QString grainType)
{
    QJsonObject rootObj = getConfig();
    if(rootObj.contains(grainType)){
        QJsonObject objNode = rootObj.find(grainType).value().toObject();
        if(objNode.contains("Motor"))
        {
            QJsonObject obj = objNode.find("Motor").value().toObject();
            if(obj.contains("slMotor")){
                QJsonObject tmp=obj.find("slMotor").value().toObject();
                if(tmp.contains("forward_speed")){
                    tmp.find("forward_speed").value()=slPositiveSpeed();
                    LOGGER_DEBUG("修改送料电机前进速度:%d",slPositiveSpeed());
                }
                if(tmp.contains("back_speed")){
                    tmp.find("back_speed").value()=slNegativeSpeed();
                    LOGGER_DEBUG("修改送料电机回退速度:%d",slNegativeSpeed());
                }
                if(tmp.contains("pre_position")){
                    tmp.find("pre_position").value()=slPrePosition();
                    LOGGER_DEBUG("修改送料电机预震位置:%d",slPrePosition());
                }
//                if(tmp.contains("TriggerDelay")){
//                    tmp.find("TriggerDelay").value()=triggerDelayCurrent().at(0).toInt();
//                    LOGGER_DEBUG("上相机触发延迟:%d",triggerDelayCurrent().at(0).toInt());
//                }
                if(tmp.contains("start_position")){
                    tmp.find("start_position").value()=slStartPosition();
                    LOGGER_DEBUG("修改送料电机开始位置:%d",slStartPosition());
                }
                if(tmp.contains("end_position")){
                    tmp.find("end_position").value()=slStopPosition();
                    LOGGER_DEBUG("修改送料电机停止位置:%d",slStopPosition());
                }
                if(tmp.contains("trigger_delay")){
                    tmp.find("trigger_delay").value()=triggerDlay();
                    LOGGER_DEBUG("拍照延时:%d",triggerDlay());
                }
                obj.find("slMotor").value()=tmp;
            }
            if(obj.contains("cmMotor")){
                QJsonObject tmp=obj.find("cmMotor").value().toObject();
                if(tmp.contains("open_height")){
                    tmp.find("open_height").value()=cmPrePosition();
                    LOGGER_DEBUG("修改仓门电机仓门打开位置:%d",cmPrePosition());
                }
                obj.find("cmMotor").value()=tmp;
            }
            if(obj.contains("zdMotor")){
                QJsonObject tmp=obj.find("zdMotor").value().toObject();
                if(tmp.contains("center_rate")){
                    tmp.find("center_rate").value()=centerRate();
                    LOGGER_DEBUG("修改震动器中心频率:%d",centerRate());
                }
                if(tmp.contains("output_speed")){
                    tmp.find("output_speed").value()=outputRate();
                    LOGGER_DEBUG("修改震动器出料速度:%d",outputRate());
                }
//                if(tmp.contains("TriggerDelay")){
//                    tmp.find("TriggerDelay").value()=triggerDelayCurrent().at(2).toInt();
//                    LOGGER_DEBUG("流量相机触发延迟:%d",triggerDelayCurrent().at(0).toInt());
//                }
                if(tmp.contains("vibration_rate")){
                    tmp.find("vibration_rate").value()=vibrationRate();
                    LOGGER_DEBUG("修改震动器出震动频率:%d",vibrationRate());
                }
                if(tmp.contains("voltage")){
                    tmp.find("voltage").value()=voltage();
                    LOGGER_DEBUG("修改震动器电压:%d",voltage());
                }

                obj.find("zdMotor").value()=tmp;
            }
            if(obj.contains("glMotor")){
                QJsonObject tmp=obj.find("glMotor").value().toObject();
                if(tmp.contains("open_on_vibrate")){
                    tmp.find("open_on_vibrate").value()=openOnVibrate();
                    LOGGER_DEBUG("修改刮料电机:%d",openOnVibrate());
                }
                obj.find("glMotor").value()=tmp;
            }
            objNode.find("Motor").value()=obj;
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
