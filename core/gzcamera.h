#ifndef GZCAMERA_H
#define GZCAMERA_H
#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <QObject>
#include <iostream>
#include <thread>  // NOLINT
#include <chrono>  // NOLINT
#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/dll/shared_library_load_mode.hpp>
#include <boost/dll/import.hpp>
#include <boost/function.hpp>
#include <boost/dll/shared_library.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <vector>
#include <array>
#include <GlobalParameter.h>
#include "include/camera_api.hpp"
#include <QThreadPool>
#include <QTimer>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "ManagerMath.h"
#include "RequireImage.h"
#include "Login.h"
#define CAMERACOUNT 2

//class TaskConversion:public QObject,public QRunnable{
//    Q_OBJECT
//public:
//    TaskConversion(unsigned char *,unsigned char *,int,int);
//    void run() override;
//signals:
//    void converFinshed();
//private:
//};


class GzCameraInfo;
class GzCamera:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList listCameraId READ listCameraId WRITE setListCameraId NOTIFY listCameraIdChanged)
    Q_PROPERTY(QVariantList listMac READ listMac WRITE setListMac NOTIFY listMacChanged)
    Q_PROPERTY(QVariantList listIp READ listIp WRITE setListIp NOTIFY listIpChanged)
    Q_PROPERTY(QVariantList listMax_w READ listMax_w WRITE setListMax_w NOTIFY listMax_wChanged)
    Q_PROPERTY(QVariantList listMax_h READ listMax_h WRITE setListMax_h NOTIFY listMax_hChanged)
    Q_PROPERTY(QVariantList listCurrentExposure READ listCurrentExposure WRITE setListCurrentExposure NOTIFY listCurrentExposureChanged)
    Q_PROPERTY(QVariantList listExposureMax READ listExposureMax WRITE setListExposureMax NOTIFY listExposureMaxChanged)
    Q_PROPERTY(QVariantList listExposureMin READ listExposureMin WRITE setListExposureMin NOTIFY listExposureMinChanged)

    Q_PROPERTY(QVariantList listR_digitial_max READ listR_digitial_max WRITE setListR_digitial_max NOTIFY listR_digitial_maxChanged)
    Q_PROPERTY(QVariantList listR_digitial_min READ listR_digitial_min WRITE setListR_digitial_min NOTIFY listR_digitial_minChanged)
    Q_PROPERTY(QVariantList listR_digitial_current READ listR_digitial_current WRITE setListR_digitial_current NOTIFY listR_digitial_currentChanged)

    Q_PROPERTY(QVariantList listG_digitial_max READ listG_digitial_max WRITE setListG_digitial_max NOTIFY listG_digitial_maxChanged)
    Q_PROPERTY(QVariantList listG_digitial_min READ listG_digitial_min WRITE setListG_digitial_min NOTIFY listG_digitial_minChanged)
    Q_PROPERTY(QVariantList listG_digitial_current READ listG_digitial_current WRITE setListG_digitial_current NOTIFY listG_digitial_currentChanged)

    Q_PROPERTY(QVariantList listB_digitial_max READ listB_digitial_max WRITE setListB_digitial_max NOTIFY listB_digitial_maxChanged)
    Q_PROPERTY(QVariantList listB_digitial_min READ listB_digitial_min WRITE setListB_digitial_min NOTIFY listB_digitial_minChanged)
    Q_PROPERTY(QVariantList listB_digitial_current READ listB_digitial_current WRITE setListB_digitial_current NOTIFY listB_digitial_currentChanged)

    Q_PROPERTY(QVariantList triggetMode READ triggetMode WRITE setTriggetMode NOTIFY triggetModeChanged)

    Q_PROPERTY(QVariantList exposureGain_current READ exposureGain_current WRITE setExposureGain_current NOTIFY exposureGain_currentChanged)
    Q_PROPERTY(QVariantList exposureGain_max READ exposureGain_max WRITE setExposureGain_max NOTIFY exposureGain_maxChanged)
    Q_PROPERTY(QVariantList exposureGain_min READ exposureGain_min WRITE setExposureGain_min NOTIFY exposureGain_minChanged)

    Q_PROPERTY(QVariantList trigger_delay_current READ trigger_delay_current WRITE setTrigger_delay_current NOTIFY trigger_delay_currentChanged)
    Q_PROPERTY(QVariantList trigger_delay_max READ trigger_delay_max WRITE setTrigger_delay_max NOTIFY trigger_delay_maxChanged)
    Q_PROPERTY(QVariantList trigger_delay_min READ trigger_delay_min WRITE setTrigger_delay_min NOTIFY trigger_delay_minChanged)

    Q_PROPERTY(QVariantList darkExposureTime READ darkExposureTime WRITE setDarkExposureTime NOTIFY darkExposureTimeChanged)

    Q_PROPERTY(QVariantList vflip READ vflip WRITE setVflip NOTIFY vflipChanged)
    Q_PROPERTY(QVariantList hflip READ hflip WRITE setHflip NOTIFY hflipChanged)
public:
    explicit GzCamera(QObject* parent=nullptr);
    ~GzCamera();
    QVariantList listCameraId();
    void setListCameraId(QVariantList id);
    QVariantList listR_digitial_max();
    void setListR_digitial_max(QVariantList r);

    QVariantList listMac();
    void setListMac(QVariantList mac);

    QVariantList listIp();
    void setListIp(QVariantList ip);

    QVariantList listMax_w();
    void setListMax_w(QVariantList w);

    QVariantList listMax_h();
    void setListMax_h(QVariantList h);

    QVariantList listCurrentExposure();
    void setListCurrentExposure(QVariantList e);

    QVariantList listExposureMax();
    void setListExposureMax(QVariantList e);

    QVariantList listExposureMin();
    void setListExposureMin(QVariantList e);

    QVariantList listR_digitial_min();
    void setListR_digitial_min(QVariantList r);

    QVariantList listR_digitial_current();
    void setListR_digitial_current(QVariantList r);

    QVariantList listG_digitial_max();
    void setListG_digitial_max(QVariantList g);

    QVariantList listG_digitial_min();
    void setListG_digitial_min(QVariantList g);

    QVariantList listG_digitial_current();
    void setListG_digitial_current(QVariantList g);

    QVariantList listB_digitial_max();
    void setListB_digitial_max(QVariantList b);

    QVariantList listB_digitial_min();
    void setListB_digitial_min(QVariantList b);

    QVariantList listB_digitial_current();
    void setListB_digitial_current(QVariantList b);

    QVariantList triggetMode();
    void setTriggetMode(QVariantList mode);

    QVariantList exposureGain_current();
    void setExposureGain_current(QVariantList e);

    QVariantList exposureGain_max();
    void setExposureGain_max(QVariantList e);

    QVariantList exposureGain_min();
    void setExposureGain_min(QVariantList e);

    QVariantList trigger_delay_current();
    void setTrigger_delay_current(QVariantList d);

    QVariantList trigger_delay_min();
    void setTrigger_delay_min(QVariantList d);

    QVariantList trigger_delay_max();
    void setTrigger_delay_max(QVariantList d);

    QVariantList darkExposureTime();
    void setDarkExposureTime(QVariantList d);

    QVariantList vflip();
    void setVflip(QVariantList d);

    QVariantList hflip();
    void setHflip(QVariantList d);
private:
    void reviceData(int,GCamera::FrameInfo info,void *);
    void getCamerIpInfo();
    void clearImDate();
    // QString imgName(int);
    void setConfig();

public slots:
    void setTriggerMode(int id,int mode);
    void softTrigger(int id);
    void setExpouseTime(int id,int);
    void setR_digitial(int id,int value);
    void setG_digitial(int id,int value);
    void setB_digitial(int id,int value);
    void setExposureGain(int id,int value);
    void setTrigger_delay(int id,int value);
    void setdarkTime(int id,int value);
    void setvFlip(int id,bool value);
    void sethFlip(int id,bool value);

    void setStartExposureTime();


    void slotGetWeight(float weight);
    void clearWeight();

    void slotUnsound();
    void slotAdjust();
    void slotAiAdjust();
    void captureImg();

    void startCapture(bool flag);
signals:
    void listMax_wChanged();
    void listMax_hChanged();
    void listMacChanged();
    void listIpChanged();
    void listCameraIdChanged();
    void listR_digitial_maxChanged();
    void listCurrentExposureChanged();
    void listExposureMaxChanged();
    void listExposureMinChanged();
    void listR_digitial_minChanged();
    void listR_digitial_currentChanged();

    void listG_digitial_maxChanged();
    void listG_digitial_minChanged();
    void listG_digitial_currentChanged();

    void listB_digitial_maxChanged();
    void listB_digitial_minChanged();
    void listB_digitial_currentChanged();
    void triggetModeChanged();
    void exposureGain_currentChanged();
    void exposureGain_maxChanged();
    void exposureGain_minChanged();
    void trigger_delay_currentChanged();
    void trigger_delay_maxChanged();
    void trigger_delay_minChanged();
    void darkExposureTimeChanged();
    void vflipChanged();
    void hflipChanged();

    void sigSetlightInfo();
    void sigCloseDownLight();
private:
    std::vector<boost::shared_ptr<GCamera::CameraApi>> m_Cameraplugins;
    QMap<int, bool> m_isDarkExposure;
    QMap<QString,int> m_cameraMap;
    QString m_UpCmaeraIp;
    QString m_DownCmaeraIp;
public:
    RequireImage* m_requireImageOne;
    RequireImage* m_requireImageTwo;
    QMap<int ,RequireImage*> m_idImages;
    GzCameraInfo* m_cameraInfo;
    ManagerMath* m_managerMath     {nullptr};
    std::vector<im_data> m_imgData;
    std::atomic<int> m_period      {0};
    std::atomic<bool> m_adjusting      {false};
    std::atomic<bool> m_isCaptureClieked      {false};

    std::vector<SaveImgData> g_temp;
    im_data m_AU;
    im_data m_AD;
    im_data m_BU;
    im_data m_BD;
    QString m_picTime  {""};
    bool m_ua_done;
    bool m_ub_done;
    bool m_da_done;
    bool m_db_done;
    bool m_is_up_light;
};

#endif // GZCAMERA_H
