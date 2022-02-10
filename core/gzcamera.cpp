#include "gzcamera.h"
#include <QCoreApplication>
#include <chrono>
#include <functional>
#include <QImage>
#include <QDebug>
#include <QFile>
#include <memory>
#include <png.h>
#include <condition_variable>
#include <mutex>
#include "../common/CMessageBox.h"

std::mutex frame_timeout_mutex;
std::condition_variable frame_timeout_cond;

int write_png(FILE* fp,
                    unsigned int height,
                    unsigned int width,
                    int bytes_per_pixel,
                    unsigned char* data) {
  png_structp _png_ptr;
  png_infop   _info_ptr;

  _png_ptr = png_create_write_struct(
    png_get_libpng_ver(NULL), NULL, NULL, NULL);
  if (!_png_ptr) {
    printf("png_create_write_struct: failed\n");
    return 2;
  }

  _info_ptr = png_create_info_struct(_png_ptr);
  if (!_info_ptr) {
    png_destroy_write_struct(&_png_ptr, NULL);
    printf("png_create_info_struct: failed\n");
    return 2;
  }

  if (setjmp(png_jmpbuf(_png_ptr))) {
    png_destroy_write_struct(&_png_ptr, &_info_ptr);
    printf("setjmp: failed\n");
    return 3;
  }

  png_init_io(_png_ptr, fp);
  png_set_IHDR(_png_ptr, _info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB,
               PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
               PNG_FILTER_TYPE_DEFAULT);
  // source data format was BGR
  png_set_bgr(_png_ptr);
  png_write_info(_png_ptr, _info_ptr);
  png_set_packing(_png_ptr);

  if (height > PNG_SIZE_MAX / (width * bytes_per_pixel))
    png_error(_png_ptr, "Image data buffer would be too large");

  png_bytep row_pointers[height];  // NOLINT

  if (height > PNG_UINT_32_MAX / (sizeof(png_bytep)))
    png_error(_png_ptr, "Image is to tall to process in memory");

  int k = 0;
  for (k = 0; k < height; ++k)
    row_pointers[k] = data + k * width * bytes_per_pixel;

  png_write_image(_png_ptr, row_pointers);
  png_write_end(_png_ptr, _info_ptr);
  png_destroy_write_struct(&_png_ptr, &_info_ptr);

  return 0;
}

//qml只需在这里拿信息 后面加两个厂家相机改id的意义 和 C++这边业务
class GzCameraInfo{
public:
    GzCameraInfo(){
    }
    QVariantList max_w;
    QVariantList max_h;
    QVariantList mac;
    QVariantList ip;
    QVariantList id;

    QVariantList current_exposure {190,190};
    QVariantList exposure_max;
    QVariantList exposure_min;

    QVariantList r_digitial_max;
    QVariantList r_digitial_min;
    QVariantList r_digitial_current {0,0};

    QVariantList g_digitial_max;
    QVariantList g_digitial_min;
    QVariantList g_digitial_current {0,0};

    QVariantList b_digitial_max;
    QVariantList b_digitial_min;
    QVariantList b_digitial_current {0,0};
    QVariantList triggerMode {0,0};

    QVariantList exposureGain_current {0,0};
    QVariantList exposureGain_max;
    QVariantList exposureGain_min;

    QVariantList trigger_delay_current {0,0};
    QVariantList trigger_delay_max;
    QVariantList trigger_delay_min;
    QVariantList darkExposureTime  {500,500};

    QVariantList vflip{false,false};
    QVariantList hflip{false,false};
};

GzCamera::GzCamera(QObject *parent)
        : QObject(parent),
        m_cameraInfo(new GzCameraInfo),
        m_requireImageOne(new RequireImage(this)),
        m_requireImageTwo(new RequireImage(this)),
        m_managerMath(new ManagerMath),
        m_ua_done(false),
        m_ub_done(false),
        m_da_done(false),
        m_db_done(false),
        m_is_up_light(true) {
    boost::dll::fs::path lib_path(QString(QCoreApplication::applicationDirPath()+"/3td").toStdString());
    std::vector<boost::shared_ptr<GCamera::CameraApi>> Plugins;
    Plugins = GCamera::CameraApi::findPlugins<GCamera::CameraApi>(
                std::vector<boost::dll::fs::path>{lib_path / "do3think_plugin"},
                "create_camera_plugin");
    QCoreApplication::processEvents();
    QVariantList cameraId;
    QVariantList max_w;
    QVariantList max_h;
    QVariantList mac;
    QVariantList ip;
    QVariantList id;
    QVariantList current_exposure;
    QVariantList exposure_max;
    QVariantList exposure_min;

    QVariantList r_digitial_min;
    QVariantList r_digitial_current;
    QVariantList r_digitial_max;

    QVariantList g_digitial_max;
    QVariantList g_digitial_min;
    QVariantList g_digitial_current;

    QVariantList b_digitial_max;
    QVariantList b_digitial_min;
    QVariantList b_digitial_current;
    QVariantList triggerMode{0,0};

    QVariantList exposureGain_current;
    QVariantList exposureGain_max;
    QVariantList exposureGain_min;

    QVariantList trigger_delay_current;
    QVariantList trigger_delay_max;
    QVariantList trigger_delay_min;
    for (const auto& p : Plugins) {
        std::cout << "[main] plugin name: " << p->name() << std::endl;
        std::vector<int> camera_ids;
        while (true) {
            camera_ids = p->findCamera();
            // 相机数量不对
            if (camera_ids.size() != CAMERACOUNT) {
                if (CMessageBox::ShowInfo("没有找到相机，是否继续查找？",
                        nullptr ,CMessageBox::StandardButton::YesNo) == 0) {
                    break;
                }
            } else {
                break;
            }
        }

        for (int id : camera_ids) {
            while (GCamera::CameraError::OK != p->openCamera(id)) {
                if (CMessageBox::ShowInfo("相机打开失败，是否重新打开？",
                        nullptr ,CMessageBox::StandardButton::YesNo) == 0) {
                    break;
                }
            }
            QCoreApplication::processEvents();
            GCamera::CameraInfo info;
            // p->setTriggerMode(id, GCamera::TriggerMode::HARDWARE);
            p->infoCamera(id, &info);
            p->setFrameCB(std::bind(&GzCamera::reviceData, this,
                std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            cameraId.append(id);
            max_w.append(info.max_w);
            max_h.append(info.max_h);
            mac.append(info.mac);
            ip.append(info.ip);
            current_exposure.append(info.exposure.time[0]);
            exposure_max.append(info.exposure.time[2]);
            exposure_min.append(info.exposure.time[1]);

            r_digitial_max.append(info.gains.digital_r[2]);
            r_digitial_min.append(info.gains.digital_r[1]);
            r_digitial_current.append(info.gains.digital_r[0]);

            g_digitial_max.append(info.gains.digital_g[2]);
            g_digitial_min.append(info.gains.digital_g[1]);
            g_digitial_current.append(info.gains.digital_g[0]);

            b_digitial_max.append(info.gains.digital_b[2]);
            b_digitial_min.append(info.gains.digital_b[1]);
            b_digitial_current.append(info.gains.digital_b[0]);
            triggerMode.append(static_cast<int>(info.trigger_mode));
            exposureGain_current.append(info.exposure.gain[0]);
            exposureGain_max.append(info.exposure.gain[2]);
            exposureGain_min.append(info.exposure.gain[1]);

            trigger_delay_current.append(info.trigger_delay[0]);
            trigger_delay_max.append(info.trigger_delay[2]);
            trigger_delay_min.append(info.trigger_delay[1]);
            std::cout << "[main] Camera info - max w: "
                      << info.max_w << ", max h:" << info.max_h
                      << "\n\t exposure time: [" << info.exposure.time[0]
                      << ", " << info.exposure.time[1]
                      << ", " << info.exposure.time[2]
                      << "]\n\t exposure gain: [" << info.exposure.gain[0]
                      << ", " << info.exposure.gain[1]
                      << ", " << info.exposure.gain[2]
                      << "]\n\t digital gain[R,G,B]: [(" << info.gains.digital_r[0]
                      << ", " << info.gains.digital_r[1]
                      << ", " << info.gains.digital_r[2]
                      << "), (" << info.gains.digital_g[0]
                      << ", " << info.gains.digital_g[1]
                      << ", " << info.gains.digital_g[2]
                      << "), (" << info.gains.digital_b[0]
                      << ", " << info.gains.digital_b[1]
                      << ", " << info.gains.digital_b[2] << ")]" << std::endl;
            p->startCamera(id);
            m_Cameraplugins.push_back(p);
            m_cameraMap[QString(info.ip)] = id;
        }
    }

    getCamerIpInfo();
    setListCameraId(cameraId);
    setListIp(ip);
    setListMac(mac);
    setListMax_h(max_h);
    setListMax_w(max_w);

    setListExposureMax(exposure_max);
    setListExposureMin(exposure_min);
    setListR_digitial_max(r_digitial_max);
    setListR_digitial_min(r_digitial_min);
    //setListR_digitial_current(r_digitial_current);

    setListG_digitial_min(g_digitial_min);
    setListG_digitial_max(g_digitial_max);
    //setListG_digitial_current(g_digitial_current);

    setListB_digitial_min(b_digitial_min);
    setListB_digitial_max(b_digitial_max);
    //setListB_digitial_current(b_digitial_current);
    //setTriggetMode(triggerMode);
    setExposureGain_min(exposureGain_min);
    setExposureGain_max(exposureGain_max);
    //setExposureGain_current(exposureGain_current);
    setTrigger_delay_max(trigger_delay_max);
    setTrigger_delay_min(trigger_delay_min);
    //setTrigger_delay_current(trigger_delay_current);

    for(int i=0;i<cameraId.size();i++){
        //
        if(i==0){
            m_idImages[cameraId[i].toInt()]=m_requireImageOne;
        }else if(i==1){
           m_idImages[cameraId[i].toInt()]= m_requireImageTwo;
        }else {
            m_idImages[cameraId[i].toInt()]=new RequireImage(this);
        }
    }
    GlobalObject::g_cameraInfo = m_cameraMap;
    //m_imgData.resize(4);
}

GzCamera::~GzCamera()
{
    //setConfig();
    for (int i=0;i<m_Cameraplugins.size();i++){
        m_Cameraplugins[i]->stopCamera(m_cameraInfo->id[i].toInt());
        m_Cameraplugins[i]->closeCamera(m_cameraInfo->id[i].toInt());
    }
}

QVariantList GzCamera::listCameraId()
{
    return m_cameraInfo->id;
}

void GzCamera::setListCameraId(QVariantList id)
{
    m_cameraInfo->id=id;
    emit listCameraIdChanged();
}

QVariantList GzCamera::listR_digitial_max()
{
    return m_cameraInfo->r_digitial_max;
}

void GzCamera::setListR_digitial_max(QVariantList r)
{
    m_cameraInfo->r_digitial_max=r;
    emit listR_digitial_max();
}

QVariantList GzCamera::listMac()
{
    return m_cameraInfo->mac;
}

void GzCamera::setListMac(QVariantList mac)
{
    m_cameraInfo->mac=mac;
    emit listMacChanged();
}

QVariantList GzCamera::listIp()
{
    return m_cameraInfo->ip;
}

void GzCamera::setListIp(QVariantList ip)
{
    m_cameraInfo->ip=ip;
    emit listIpChanged();
}

QVariantList GzCamera::listMax_w()
{
    return m_cameraInfo->max_w;
}

void GzCamera::setListMax_w(QVariantList w)
{
    m_cameraInfo->max_w=w;
    emit listMax_wChanged();
}

QVariantList GzCamera::listMax_h()
{
    return m_cameraInfo->max_h;
}

void GzCamera::setListMax_h(QVariantList h)
{
    m_cameraInfo->max_h=h;
    emit listMax_hChanged();
}

QVariantList GzCamera::listCurrentExposure()
{
    return  m_cameraInfo->current_exposure;
}

void GzCamera::setListCurrentExposure(QVariantList e)
{
    m_cameraInfo->current_exposure=e;
    emit listCurrentExposureChanged();
}

QVariantList GzCamera::listExposureMax()
{
    return  m_cameraInfo->exposure_max;
}

void GzCamera::setListExposureMax(QVariantList e)
{
    m_cameraInfo->exposure_max=e;
    emit listExposureMaxChanged();
}

QVariantList GzCamera::listExposureMin()
{
    return m_cameraInfo->exposure_min;
}

void GzCamera::setListExposureMin(QVariantList e)
{
    m_cameraInfo->exposure_min=e;
    emit listExposureMinChanged();
}

QVariantList GzCamera::listR_digitial_min()
{
    return m_cameraInfo->r_digitial_min;
}

void GzCamera::setListR_digitial_min(QVariantList r)
{
    m_cameraInfo->r_digitial_min=r;
    emit listR_digitial_minChanged();
}

QVariantList GzCamera::listR_digitial_current()
{
    return  m_cameraInfo->r_digitial_current;
}

void GzCamera::setListR_digitial_current(QVariantList r)
{
    m_cameraInfo->r_digitial_current=r;
    emit listR_digitial_current();
}

QVariantList GzCamera::listG_digitial_max()
{
    return m_cameraInfo->g_digitial_max;
}

void GzCamera::setListG_digitial_max(QVariantList g)
{
    m_cameraInfo->g_digitial_max=g;
    emit listG_digitial_maxChanged();
}

QVariantList GzCamera::listG_digitial_min()
{
    return  m_cameraInfo->g_digitial_min;
}

void GzCamera::setListG_digitial_min(QVariantList g)
{
    m_cameraInfo->g_digitial_min=g;
    emit listG_digitial_minChanged();
}

QVariantList GzCamera::listG_digitial_current()
{
    return m_cameraInfo->g_digitial_current;
}

void GzCamera::setListG_digitial_current(QVariantList g)
{
    m_cameraInfo->g_digitial_current=g;
    emit listG_digitial_currentChanged();
}

QVariantList GzCamera::listB_digitial_max()
{
    return  m_cameraInfo->b_digitial_max;
}

void GzCamera::setListB_digitial_max(QVariantList b)
{
    m_cameraInfo->b_digitial_max=b;
    emit listB_digitial_maxChanged();
}

QVariantList GzCamera::listB_digitial_min()
{
    return  m_cameraInfo->b_digitial_min;
}

void GzCamera::setListB_digitial_min(QVariantList b)
{
    m_cameraInfo->b_digitial_min=b;
    emit listB_digitial_minChanged();
}

QVariantList GzCamera::listB_digitial_current()
{
    return m_cameraInfo->b_digitial_current;
}

void GzCamera::setListB_digitial_current(QVariantList b)
{
    m_cameraInfo->b_digitial_current=b;
    emit listB_digitial_currentChanged();
}

QVariantList GzCamera::triggetMode()
{
    return m_cameraInfo->triggerMode;
}

void GzCamera::setTriggetMode(QVariantList mode)
{
    m_cameraInfo->triggerMode=mode;
    emit triggetModeChanged();
}

QVariantList GzCamera::exposureGain_current()
{
    return m_cameraInfo->exposureGain_current;
}

void GzCamera::setExposureGain_current(QVariantList e)
{
    m_cameraInfo->exposureGain_current=e;
    emit exposureGain_currentChanged();
}

QVariantList GzCamera::exposureGain_max()
{
    return m_cameraInfo->exposureGain_max;
}

void GzCamera::setExposureGain_max(QVariantList e)
{
    m_cameraInfo->exposureGain_max=e;
    emit exposureGain_maxChanged();
}

QVariantList GzCamera::exposureGain_min()
{
    return m_cameraInfo->exposure_min;
}

void GzCamera::setExposureGain_min(QVariantList e)
{
    m_cameraInfo->exposure_min=e;
    emit exposureGain_minChanged();
}

QVariantList GzCamera::trigger_delay_current()
{
    return m_cameraInfo->trigger_delay_current;
}

void GzCamera::setTrigger_delay_current(QVariantList d)
{
    m_cameraInfo->trigger_delay_current=d;
    emit trigger_delay_currentChanged();
}

QVariantList GzCamera::trigger_delay_min()
{
    return m_cameraInfo->trigger_delay_min;
}

void GzCamera::setTrigger_delay_min(QVariantList d)
{
    m_cameraInfo->trigger_delay_min=d;
    emit trigger_delay_minChanged();
}

QVariantList GzCamera::trigger_delay_max()
{
    return m_cameraInfo->trigger_delay_max;
}

void GzCamera::setTrigger_delay_max(QVariantList d)
{
    m_cameraInfo->trigger_delay_max=d;
    return trigger_delay_maxChanged();
}

QVariantList GzCamera::darkExposureTime()
{
    return m_cameraInfo->darkExposureTime;
}

void GzCamera::setDarkExposureTime(QVariantList d)
{
    m_cameraInfo->darkExposureTime=d;
    emit darkExposureTimeChanged();
}

QVariantList GzCamera::vflip()
{
    return m_cameraInfo->vflip;
}

void GzCamera::setVflip(QVariantList d)
{
    m_cameraInfo->vflip=d;
    emit vflipChanged();
}

QVariantList GzCamera::hflip()
{
    return m_cameraInfo->hflip;
}

void GzCamera::setHflip(QVariantList d)
{
    m_cameraInfo->hflip=d;
    emit hflipChanged();
}

std::atomic<int> g_imgindex(0);
std::mutex m_mutex;
QString g_grainType = "";
QString g_abnormalType = "";
std::uint32_t ua_lost = 0;
std::uint32_t db_lost = 0;
std::uint32_t da_lost = 0;
std::uint32_t ub_lost = 0;

void GzCamera::reviceData(int cameraId, GCamera::FrameInfo info, void *) {
    std::lock_guard<std::mutex> l(m_mutex);
    int up_camera_id = m_cameraMap.value(m_UpCmaeraIp);
    int dn_camera_id = m_cameraMap.value(m_DownCmaeraIp);
    // 上灯亮时上相机有帧数据丢失：UA
    if (cameraId == -1) {
        // 重置相机曝光时间
        m_isDarkExposure[up_camera_id] = false;
        setExpouseTime(up_camera_id, listCurrentExposure().at(up_camera_id).toInt());
        ua_lost++;
        qDebug() << "[CAMERA-ERROR] \tUUUUUUUU AAAAAAAA frame lost" << ua_lost;
        return;
    }

    // 上灯亮时下相机有帧数据丢失：DB
    if (cameraId == -2) {
        m_isDarkExposure[dn_camera_id] = true;
        setdarkTime(dn_camera_id, darkExposureTime().at(dn_camera_id).toInt());
        db_lost++;
        qDebug() << "[CAMERA-ERROR] \tDDDDDDDD BBBBBBBB frame lost" << db_lost;
        return;
    }

    // 下灯亮时上相机有帧数据丢失：DA
    if (cameraId == -3) {
        // 重置相机曝光时间
        m_isDarkExposure[up_camera_id] = true;
        setdarkTime(up_camera_id, darkExposureTime().at(up_camera_id).toInt());
        da_lost++;
        qDebug() << "[CAMERA-ERROR] \tDDDDDDDD AAAAAAAA frame lost" << da_lost;
        return;
    }

    // 下灯亮时下相机有帧数据丢失：UB
    if (cameraId == -4) {
        m_isDarkExposure[dn_camera_id] = false;
        setExpouseTime(dn_camera_id, listCurrentExposure().at(dn_camera_id).toInt());
        ub_lost++;
        qDebug() << "[CAMERA-ERROR] \tUUUUUUUU BBBBBBBB frame lost" << ub_lost;
        return;
    }

     qDebug() << "[CAMERA-INFO] *************** frame lost info, UA:" << ua_lost
              << ", DB:" << db_lost << ", DA:" << da_lost << ", UB:" << ub_lost;

    QString im_name;
    // 这里有三份数据需要准备（给算法的，给存储的，给界面显示的）
    // 存储数据
    std::shared_ptr<cv::Mat> psv = std::make_shared<cv::Mat>(
            cv::Mat(info.h, info.w, CV_8UC3, info.data.get()).clone());

    if (m_period == 0) {
        m_picTime = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
    }

    // 上光源点亮
    if (m_is_up_light) {
        frame_timeout_cond.notify_all();
        // 上光源亮时，下数据不应该OK
        if (m_da_done || m_ub_done) return;
        // UA 0
        if (GlobalObject::g_cameraInfo.key(cameraId) == GlobalObject::g_upCamerIp) {
            // 图像存储名字
            im_name = QString(QApplication::applicationDirPath() +
                "/result/21-UW-G1000-0000_6_%1_%2_%3_%4_UA_%5.png")
                .arg(m_picTime).arg(g_imgindex).arg(g_grainType).arg(g_abnormalType);
            // 更新数据
            if (m_ua_done) {
                m_AU = std::make_shared<cv::Mat>(psv->clone());
                for (auto &it : g_temp) {
                    if (it.imgName == im_name) it.ImgData = psv;
                }
                qDebug() << "[CAMERA-INFO] UUUUUUUUUU AAAAAAAAAA image updated";
                return;
            }
            m_ua_done = true;
            m_AU = std::make_shared<cv::Mat>(psv->clone());
            g_temp.push_back({psv, im_name});
            qDebug() << "[CAMERA-INFO] UUUUUUUUUU AAAAAAAAAA image received";
        }
        // DB 3
        if (GlobalObject::g_cameraInfo.key(cameraId) == GlobalObject::g_downCamerIp) {
            // DB数据进来时UA必定OK
            if (!m_ua_done) return;
            im_name = QString(QApplication::applicationDirPath() +
                "/result/21-UW-G1000-0000_6_%1_%2_%3_%4_DB_%5.png")
                .arg(m_picTime).arg(g_imgindex).arg(g_grainType).arg(g_abnormalType);
            // 更新数据
            if (m_db_done) {
                m_BD = std::make_shared<cv::Mat>(psv->clone());
                for (auto &it : g_temp) {
                    if (it.imgName == im_name) it.ImgData = psv;
                }
                qDebug() << "[CAMERA-INFO] DDDDDDDDDD BBBBBBBBBB image updated";
                return;
            }
            m_db_done = true;
            m_BD = std::make_shared<cv::Mat>(psv->clone());
            g_temp.push_back({psv, im_name});
            qDebug() << "[CAMERA-INFO] DDDDDDDDDD BBBBBBBBBB image received";
        }
    } else {  // 下光源点亮
        frame_timeout_cond.notify_all();
        // 下光源亮时，上数据必须OK
        if (!m_ua_done || !m_db_done) return;
        // DA 2
        if (GlobalObject::g_cameraInfo.key(cameraId) == GlobalObject::g_upCamerIp) {
            im_name = QString(QApplication::applicationDirPath() +
                "/result/21-UW-G1000-0000_6_%1_%2_%3_%4_DA_%5.png")
                .arg(m_picTime).arg(g_imgindex).arg(g_grainType).arg(g_abnormalType);
            // 更新数据
            if (m_da_done) {
                m_AD = std::make_shared<cv::Mat>(psv->clone());
                for (auto &it : g_temp) {
                    if (it.imgName == im_name) it.ImgData = psv;
                }
                qDebug() << "[CAMERA-INFO] DDDDDDDDDD AAAAAAAAAA image updated";
                return;
            }
            m_da_done = true;
            m_AD = std::make_shared<cv::Mat>(psv->clone());
            g_temp.push_back({psv, im_name});
            qDebug() << "[CAMERA-INFO] DDDDDDDDDD AAAAAAAAAA image received";
        }
        // UB 1
        if (GlobalObject::g_cameraInfo.key(cameraId) == GlobalObject::g_downCamerIp) {
            if (!m_da_done) return;
            im_name = QString(QApplication::applicationDirPath() +
                "/result/21-UW-G1000-0000_6_%1_%2_%3_%4_UB_%5.png")
                .arg(m_picTime).arg(g_imgindex).arg(g_grainType).arg(g_abnormalType);
            // 更新数据
            if (m_ub_done) {
                m_BU = std::make_shared<cv::Mat>(psv->clone());
                for (auto &it : g_temp) {
                    if (it.imgName == im_name) it.ImgData = psv;
                }
                qDebug() << "[CAMERA-INFO] UUUUUUUUUU BBBBBBBBBB image updated";
                return;
            }
            m_ub_done = true;
            m_BU = std::make_shared<cv::Mat>(psv->clone());
            g_temp.push_back({psv, im_name});
            qDebug() << "[CAMERA-INFO] UUUUUUUUUU BBBBBBBBBB image received";
        }
    }
    ++m_period;
    if (m_period == 2) {
        // frame_timeout_cond.notify_one();
        // 上光源点亮拍照结束
        emit sigSetlightInfo();
    }

    if (m_period == 4) {
        // frame_timeout_cond.notify_one();
        m_period = 0;
        GlobalObject::g_instance()->m_saveImgData.push(g_temp);
        // 推入存图队列
        if (!Login::SuperAdmin) {
            GZ_SetImageName(m_managerMath->m_MathBaseModel->m_base->handler,
                QApplication::applicationDirPath().toStdString()+"/result/"
                ,QString("21-UW-G1000-0000_6_%1_%2_%3_%4_UB_%5.png")
                .arg(m_picTime).arg(g_imgindex).arg(g_grainType).arg(g_abnormalType).arg("0.000").toStdString());
            // 如果不是管理员登录，则调用算法
            m_managerMath->processData({m_AU, m_BU, m_AD, m_BD});
        }
        g_temp.clear();
        g_imgindex++;
        // 此轮拍照结束（图像样本采集结束）
        emit sigCloseDownLight();
    }
    if (m_isDarkExposure[cameraId]) {
#ifdef INFO_LOG
        qDebug() << "[CAMERA-INFO] camera[" << cameraId << "] set reflection exposure time: "
                 << listCurrentExposure().at(cameraId).toInt();
#endif  // INFO_LOG
        setExpouseTime(cameraId, listCurrentExposure().at(cameraId).toInt());
    } else {
#ifdef INFO_LOG
        qDebug() <<"[CAMERA-INFO] camera[" << cameraId << "] set transmission exposure time: "
                 << darkExposureTime().at(cameraId).toInt();
#endif  // INFO_LOG
        setdarkTime(cameraId, darkExposureTime().at(cameraId).toInt());
    }
    m_isDarkExposure[cameraId] = !m_isDarkExposure[cameraId];

    BGR2RGB(info.data.get(), info.w, info.h);
    QImage ui_im = QImage(info.data.get(), info.w, info.h, info.w * 3, QImage::Format_RGB888, 0, 0).copy();
    m_idImages[cameraId]->getCameraImage(ui_im);
}

void GzCamera::getCamerIpInfo()
{
    if(m_Cameraplugins.size()>1){
        QJsonObject rootObj = getConfig();
        if(rootObj.contains("Camera"))
        {
            QJsonObject obj = rootObj.value("Camera").toObject();
            if(obj.contains("upCamerIp")){
                m_UpCmaeraIp=obj.value("upCamerIp").toString();
                GlobalObject::g_upCamerIp=m_UpCmaeraIp;
            }
            if(obj.contains("downCamerIp")){
                m_DownCmaeraIp=obj.value("downCamerIp").toString();
                GlobalObject::g_downCamerIp=m_DownCmaeraIp;
            }
            if(obj.contains("cameraOne")){
                QJsonObject tmp=obj.value("cameraOne").toObject();
                if(tmp.contains("TriggerMode")){
                   tmp.value("TriggerMode").toString()=="SoftTrigger"?
                               setTriggerMode(0,1):setTriggerMode(0,0);
                }
                if(tmp.contains("DownExposureTime")){
                    setdarkTime(m_cameraMap[m_UpCmaeraIp],
                                tmp.value("DownExposureTime").toInt());
                }
                if(tmp.contains("UPExposureTime")){
                   setExpouseTime(m_cameraMap[m_UpCmaeraIp],
                                  tmp.value("UPExposureTime").toInt());
                }
                if(tmp.contains("ExposureGain")){
                    setExposureGain(m_cameraMap[m_UpCmaeraIp],
                                            tmp.value("ExposureGain").toInt());
                }
                if(tmp.contains("TriggerDelay")){
                   setTrigger_delay(0,tmp.value("TriggerDelay").toInt());
                }
                if(tmp.contains("RGain")){
                   setR_digitial(0,tmp.value("RGain").toInt());
                }
                if(tmp.contains("GGain")){
                   setG_digitial(0,tmp.value("GGain").toInt());
                }
                if(tmp.contains("BGain")){
                   setB_digitial(0,tmp.value("BGain").toInt());
                }
                if(tmp.contains("vFlip")){
                   setvFlip(0,tmp.value("vFlip").toBool());
                }
                if(tmp.contains("hFlip")){
                   sethFlip(0,tmp.value("hFlip").toBool());
                }
            }
            if(obj.contains("cameraTwo")){
                QJsonObject tmp=obj.value("cameraTwo").toObject();
                if(tmp.contains("TriggerMode")){
                   tmp.value("TriggerMode").toString()=="SoftTrigger"?
                               setTriggerMode(1,1):setTriggerMode(1,0);
                }
                if(tmp.contains("DownExposureTime")){
                    setExpouseTime(m_cameraMap[m_DownCmaeraIp],
                                tmp.value("DownExposureTime").toInt());
                }
                if(tmp.contains("ExposureGain")){
                    setExposureGain(m_cameraMap[m_DownCmaeraIp],
                                            tmp.value("ExposureGain").toInt());
                }
                if(tmp.contains("UPExposureTime")){
                   setdarkTime(m_cameraMap[m_DownCmaeraIp],
                                  tmp.value("UPExposureTime").toInt());
                }
                if(tmp.contains("TriggerDelay")){
                   setTrigger_delay(1,tmp.value("TriggerDelay").toInt());
                }
                if(tmp.contains("RGain")){
                   setR_digitial(1,tmp.value("RGain").toInt());
                }
                if(tmp.contains("GGain")){
                   setG_digitial(1,tmp.value("GGain").toInt());
                }
                if(tmp.contains("BGain")){
                   setB_digitial(1,tmp.value("BGain").toInt());
                }
                if(tmp.contains("vFlip")){
                   setvFlip(1,tmp.value("vFlip").toBool());
                }
                if(tmp.contains("hFlip")){
                   sethFlip(1,tmp.value("hFlip").toBool());
                }
            }
        }
        if(rootObj.contains("grainType"))
        {
            g_grainType = rootObj.value("grainType").toString();
        }
        if(rootObj.contains("abnormalType"))
        {
            g_abnormalType = rootObj.value("abnormalType").toString();
        }

        // if(m_cameraMap.value(m_UpCmaeraIp)==0){
        //     m_isDarkExposure.push_back(false);
        //     m_isDarkExposure.push_back(true);
        // }else{
        //     m_isDarkExposure.push_back(true);
        //     m_isDarkExposure.push_back(false);
        // }
        m_isDarkExposure[m_cameraMap.value(m_UpCmaeraIp)] = false;
        m_isDarkExposure[m_cameraMap.value(m_DownCmaeraIp)] = true;
    }
}

void GzCamera::setTriggerMode(int id, int mode)
{
    if(mode==0)
    {
        m_Cameraplugins[0]->setTriggerMode(id,GCamera::TriggerMode::HARDWARE);
    }else if(mode==1){
        m_Cameraplugins[0]->setTriggerMode(id,GCamera::TriggerMode::SOFTWARE);
    }
    QVariantList tmp= triggetMode();
    tmp.replace(id,mode);
    setTriggetMode(tmp);
}

void GzCamera::softTrigger(int id)
{
    GCamera::CameraError status;
    status = m_Cameraplugins[0]->softTrigger(id);
#ifdef INFO_LOG
    qDebug() << "[CAMERA-INFO] set softTrigger[" << id << "] ret: " << int(status);
#endif  // INFO_LOG
}

void GzCamera::setExpouseTime(int id, int time)
{
    QVariantList tmp= listCurrentExposure();
    GCamera::CameraError status;
    status=m_Cameraplugins[0]->setCameraExposure(id,time);
#ifdef INFO_LOG
    qDebug() << "[CAMERA-INFO] setCameraExposure[" << id
        << "] ret:"<< int(status) << ", value:" << time;
#endif  // INFO_LOG
    tmp.replace(id, time);
    setListCurrentExposure(tmp);
}

void GzCamera::setR_digitial(int id, int value)
{
    QVariantList tmp= listR_digitial_current();
    GCamera::CameraError status;
    status=m_Cameraplugins[0]->setCameraGainR(id,value);
    tmp.replace(id,value);
    setListR_digitial_current(tmp);
#ifdef INFO_LOG
    qDebug() << "[CAMERA-INFO] set R-Gain[" << id
        << "] ret:" << int(status) << ", value: " << value;
#endif  // INFO_LOG
}

void GzCamera::setG_digitial(int id, int value)
{
    QVariantList tmp= listG_digitial_current();
    GCamera::CameraError status;
    status=m_Cameraplugins[0]->setCameraGainG(id,value);
    tmp.replace(id,value);
    setListG_digitial_current(tmp);
#ifdef INFO_LOG
    qDebug() << "[CAMERA-INFO] set G-Gain[" << id
        << "] ret:" << int(status) << ", value: " << value;
#endif  // INFO_LOG
}

void GzCamera::setB_digitial(int id, int value)
{
    QVariantList tmp= listB_digitial_current();
    GCamera::CameraError status;
    status=m_Cameraplugins[0]->setCameraGainB(id,value);
    tmp.replace(id,value);
    setListB_digitial_current(tmp);
#ifdef INFO_LOG
    qDebug() << "[CAMERA-INFO] set B-Gain[" << id
        << "] ret:" << int(status) << ", value: " << value;
#endif  // INFO_LOG
}

void GzCamera::setExposureGain(int id, int value)
{
    QVariantList tmp=exposureGain_current();
    GCamera::CameraError status;
    status=m_Cameraplugins[0]->setCameraGainExposure(id,value);
    tmp.replace(id,value);
    setExposureGain_current(tmp);
#ifdef INFO_LOG
    qDebug() << "[CAMERA-INFO] set Exposure-Gain[" << id
        << "] ret:" << int(status) << ", value: " << value;
#endif  // INFO_LOG
}

void GzCamera::setTrigger_delay(int id, int value)
{
    QVariantList tmp=trigger_delay_current();
    GCamera::CameraError status;
    status=m_Cameraplugins[0]->setTriggerDelay(id,value);
    tmp.replace(id,value);
    setTrigger_delay_current(tmp);
#ifdef INFO_LOG
    qDebug() << "[CAMERA-INFO] set Trigger delay[" << id
        << "] ret:" << int(status) << ", value: " << value;
#endif  // INFO_LOG
}

void GzCamera::setdarkTime(int id, int value)
{
    QVariantList tmp=darkExposureTime();
    GCamera::CameraError status;
    status=m_Cameraplugins[0]->setCameraExposure(id, value);
#ifdef INFO_LOG
    qDebug() << "[CAMERA-INFO] setCameraExposure[" << id
        << "] ret:" << int(status) << ", value: " << value;
#endif  // INFO_LOG
    tmp.replace(id,value);
    setDarkExposureTime(tmp);
}

void GzCamera::setvFlip(int id, bool value)
{
    QVariantList tmp=vflip();
    GCamera::CameraError status;
    status=m_Cameraplugins[0]->setVerticalFlip(id, value);
#ifdef INFO_LOG
    qDebug() << "[CAMERA-INFO] set vertical flip[" << id
        << "] ret:" << int(status) << ", value: " << value;
#endif  // INFO_LOG
    tmp.replace(id,value);
    setVflip(tmp);
}

void GzCamera::sethFlip(int id, bool value)
{
    QVariantList tmp=hflip();
    GCamera::CameraError status;
    status=m_Cameraplugins[0]->setHorizontalFlip(id, value);
#ifdef INFO_LOG
    qDebug() << "[CAMERA-INFO] set horizontal flip[" << id
        << "] ret:" << int(status) << ", value: " << value;
#endif  // INFO_LOG
    tmp.replace(id,value);
    setHflip(tmp);
}

void GzCamera::setStartExposureTime()
{
    if(m_Cameraplugins.size()>1){
        // 设置上相机反射曝光时间
        setExpouseTime(m_cameraMap[m_UpCmaeraIp],
            listCurrentExposure().at(m_cameraMap[m_UpCmaeraIp]).toInt());
        m_isDarkExposure[m_cameraMap.value(m_UpCmaeraIp)] = false;

        // 设置下相机透射曝光时间
        setdarkTime(m_cameraMap[m_DownCmaeraIp],
            darkExposureTime().at(m_cameraMap[m_DownCmaeraIp]).toInt());
        m_isDarkExposure[m_cameraMap.value(m_DownCmaeraIp)] = true;
    }
}

void GzCamera::slotGetWeight(float weight)
{
    m_managerMath->m_MathBaseModel->m_base->m_result.common_result.weights.push_back(weight);
}

void GzCamera::clearWeight()
{
    m_managerMath->m_MathBaseModel->m_base->m_result.common_result.weights.clear();
}

void GzCamera::slotUnsound()
{
    m_adjusting=false;
    m_isCaptureClieked=false;
}

void GzCamera::slotAdjust()
{
    m_adjusting=true;
    m_isCaptureClieked=false;
}

void GzCamera::slotAiAdjust()
{

}

void GzCamera::captureImg()
{
    m_adjusting=false;
    m_isCaptureClieked=true;
}

constexpr int C_FRAME_TIMEOUT = 5000;

void GzCamera::startCapture(bool flag)
{
    if (m_Cameraplugins.size() == 0) return;
    // 上灯亮
    if(flag){
        qDebug() << "[CAMERA-INFO] startCapture: up light on";
        m_is_up_light = true;
        m_ua_done = false;
        m_db_done = false;
        m_da_done = false;
        m_ub_done = false;
        std::thread th([this] {
            // 采集A相机反射图像
            while (!m_ua_done) {
                m_Cameraplugins[0]->softTrigger(m_cameraMap[m_UpCmaeraIp]);
                std::unique_lock<std::mutex> lock_timer(frame_timeout_mutex);
                if (std::cv_status::timeout == frame_timeout_cond.wait_for(
                        lock_timer, std::chrono::milliseconds(C_FRAME_TIMEOUT))) {
                    reviceData(-1, {}, nullptr);
                    continue;
                }
                // m_ua_done = true;
                break;
            }
            // 采集B相机投射图像
            while (!m_db_done) {
                m_Cameraplugins[0]->softTrigger(m_cameraMap[m_DownCmaeraIp]);
                std::unique_lock<std::mutex> lock_timer(frame_timeout_mutex);
                if (std::cv_status::timeout == frame_timeout_cond.wait_for(
                        lock_timer, std::chrono::milliseconds(C_FRAME_TIMEOUT))) {
                    reviceData(-2, {}, nullptr);
                    continue;
                }
                // m_db_done = true;
                break;
            }
        });
        th.detach();
    } else {  // 下灯亮
        qDebug() << "[CAMERA-INFO] startCapture: down light on";
        m_is_up_light = false;
        std::thread th([this] {
            // 采集A相机投射图像
            while (!m_da_done) {
                m_Cameraplugins[0]->softTrigger(m_cameraMap[m_UpCmaeraIp]);
                std::unique_lock<std::mutex> lock_timer(frame_timeout_mutex);
                if (std::cv_status::timeout == frame_timeout_cond.wait_for(
                        lock_timer, std::chrono::milliseconds(C_FRAME_TIMEOUT))) {
                    reviceData(-3, {}, nullptr);
                    continue;
                }
                // m_da_done = true;
                break;
            }
            // 采集B相机反射图像
            while (!m_ub_done) {
                m_Cameraplugins[0]->softTrigger(m_cameraMap[m_DownCmaeraIp]);
                std::unique_lock<std::mutex> lock_timer(frame_timeout_mutex);
                if (std::cv_status::timeout == frame_timeout_cond.wait_for(
                        lock_timer, std::chrono::milliseconds(C_FRAME_TIMEOUT))) {
                    reviceData(-4, {}, nullptr);
                    continue;
                }
                // m_ub_done = true;
                break;
            }
        });
        th.detach();
    }
}

void GzCamera::clearImDate()
{
    m_imgData.clear();
    g_temp.clear();
    //m_cameraId.clear();
    m_period=0;
}

// QString GzCamera::imgName(int cameraId)
// {

// }

void GzCamera::setConfig()
{
    QJsonObject rootObj= getConfig();
    QJsonObject cameraObj = rootObj.find("Camera").value().toObject();
    QJsonObject cameraOneObj = cameraObj.find("cameraOne").value().toObject();
    QString striggetMode;
    if(triggetMode().at(0).toInt()==0){
        striggetMode="HardTrigget";
    }else if(triggetMode().at(0).toInt()==1){
       striggetMode="SoftTrigger";
    }
    cameraOneObj.find("TriggerMode").value()=striggetMode;
    cameraOneObj.find("UPExposureTime").value()=listCurrentExposure().at(0).toInt();
    cameraOneObj.find("DownExposureTime").value()=darkExposureTime().at(0).toInt();
    cameraOneObj.find("ExposureGain").value()=exposureGain_current().at(0).toInt();
    cameraOneObj.find("TriggerDelay").value()=trigger_delay_current().at(0).toInt();
    cameraOneObj.find("RGain").value()=listR_digitial_current().at(0).toInt();
    cameraOneObj.find("GGain").value()=listG_digitial_current().at(0).toInt();
    cameraOneObj.find("BGain").value()=listB_digitial_current().at(0).toInt();
    cameraOneObj.find("vFlip").value()=vflip().at(0).toInt();
    cameraOneObj.find("hFlip").value()=hflip().at(0).toInt();

    QJsonObject cameraTwoObj = cameraObj.find("cameraTwo").value().toObject();
    if(triggetMode().at(1).toInt()==0){
        striggetMode="HardTrigget";
    }else if(triggetMode().at(1).toInt()==1){
       striggetMode="SoftTrigger";
    }
    cameraTwoObj.find("TriggerMode").value()=striggetMode;
    cameraTwoObj.find("UPExposureTime").value()=listCurrentExposure().at(1).toInt();
    cameraTwoObj.find("DownExposureTime").value()=darkExposureTime().at(1).toInt();
    cameraTwoObj.find("ExposureGain").value()=exposureGain_current().at(1).toInt();
    cameraTwoObj.find("TriggerDelay").value()=trigger_delay_current().at(1).toInt();
    cameraTwoObj.find("RGain").value()=listR_digitial_current().at(1).toInt();
    cameraTwoObj.find("GGain").value()=listG_digitial_current().at(1).toInt();
    cameraTwoObj.find("BGain").value()=listB_digitial_current().at(1).toInt();
    cameraTwoObj.find("vFlip").value()=vflip().at(1).toInt();
    cameraTwoObj.find("hFlip").value()=hflip().at(1).toInt();

    QFile File(QApplication::applicationDirPath()+"/config.json");
    QJsonDocument doc;
    doc.setObject(rootObj);
    File.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    File.write(doc.toJson());
    File.close();
}
