#ifndef CAMERAPROPERTY_H
#define CAMERAPROPERTY_H
#include <QObject>
#include <QHash>
#include <QVariantList>
#include "GlobalParameter.h"
#include "module/camera/camera.h"
#include "Gzlogger.h"
class CameraInfo;
class CameraProperty:public QObject{
    Q_OBJECT
    Q_PROPERTY(QVariantList maxW READ maxW WRITE setMaxW NOTIFY maxWChanged)
    Q_PROPERTY(QVariantList maxH READ maxH WRITE setMaxH NOTIFY maxHChanged)
    Q_PROPERTY(QVariantList mac READ mac WRITE setMac NOTIFY macChanged)
    Q_PROPERTY(QVariantList ip READ ip WRITE setIp NOTIFY ipChanged)
    Q_PROPERTY(QVariantList exposureTimeMax READ exposureTimeMax WRITE setExposureTimeMax NOTIFY exposureTimeMaxChanged)
    Q_PROPERTY(QVariantList exposureTimeMin READ exposureTimeMin WRITE setExposureTimeMin NOTIFY exposureTimeMinChanged)
    Q_PROPERTY(QVariantList upExposureTime READ upExposureTime WRITE setUpExposureTime NOTIFY upExposureTimeChanged)
    Q_PROPERTY(QVariantList downExposureTime READ downExposureTime WRITE setDownExposureTime NOTIFY downExposureTimeChanged)
    Q_PROPERTY(QVariantList rDigitialMax READ rDigitialMax WRITE setRDigitialMax NOTIFY rDigitialMaxChanged)
    Q_PROPERTY(QVariantList rDigitialMin READ rDigitialMin WRITE setRDigitialMin NOTIFY rDigitialMinChanged)
    Q_PROPERTY(QVariantList rDigitialCurrent READ rDigitialCurrent WRITE setRDigitialCurrent NOTIFY rDigitialCurrentChanged)
    Q_PROPERTY(QVariantList gDigitialMax READ gDigitialMax WRITE setGDigitialMax NOTIFY gDigitialMaxChanged)
    Q_PROPERTY(QVariantList gDigitialMin READ gDigitialMin WRITE setGDigitialMin NOTIFY gDigitialMinChanged)
    Q_PROPERTY(QVariantList gDigitialCurrent READ gDigitialCurrent WRITE setGDigitialCurrent NOTIFY gDigitialCurrentChanged)
    Q_PROPERTY(QVariantList bDigitialMax READ bDigitialMax WRITE setBDigitialMax NOTIFY bDigitialMaxChanged)
    Q_PROPERTY(QVariantList bDigitialMin READ bDigitialMin WRITE setBDigitialMin NOTIFY bDigitialMinChanged)
    Q_PROPERTY(QVariantList bDigitialCurrent READ bDigitialCurrent WRITE setBDigitialCurrent NOTIFY bDigitialCurrentChanged)
    Q_PROPERTY(QVariantList triggerMode READ triggerMode WRITE setTriggerMode NOTIFY triggerModeChanged)
    Q_PROPERTY(QVariantList exposureGainCurrent READ exposureGainCurrent WRITE setExposureGainCurrent NOTIFY exposureGainCurrentChanged)
    Q_PROPERTY(QVariantList exposureGainMax READ exposureGainMax WRITE setExposureGainMax NOTIFY exposureGainMaxChanged)
    Q_PROPERTY(QVariantList exposureGainMin READ exposureGainMin WRITE setExposureGainMin NOTIFY exposureGainMinChanged)
    Q_PROPERTY(QVariantList triggerDelayCurrent READ triggerDelayCurrent WRITE setTriggerDelayCurrent NOTIFY triggerDelayCurrentChanged)
    Q_PROPERTY(QVariantList triggerDelayMax READ triggerDelayMax WRITE setTriggerDelayMax NOTIFY triggerDelayMaxChanged)
    Q_PROPERTY(QVariantList triggerDelayMin READ triggerDelayMin WRITE setTriggerDelayMin NOTIFY triggerDelayMinChanged)
    Q_PROPERTY(QVariantList vflip READ vflip WRITE setVflip NOTIFY vflipChanged)
    Q_PROPERTY(QVariantList hflip READ hflip WRITE setHflip NOTIFY hflipChanged)
public:
    QVariantList maxW();
    void setMaxW(QVariantList value);

    QVariantList maxH();
    void setMaxH(QVariantList value);

    QVariantList mac();
    void setMac(QVariantList value);

    QVariantList ip();
    void setIp(QVariantList value);

    QVariantList exposureTimeMax();
    void setExposureTimeMax(QVariantList value);

    QVariantList exposureTimeMin();
    void setExposureTimeMin(QVariantList vaule);

    QVariantList upExposureTime();
    void setUpExposureTime(QVariantList vaule);

    QVariantList downExposureTime();
    void setDownExposureTime(QVariantList vaule);

    QVariantList rDigitialMax();
    void setRDigitialMax(QVariantList value);

    QVariantList rDigitialMin();
    void setRDigitialMin(QVariantList value);

    QVariantList rDigitialCurrent();
    void setRDigitialCurrent(QVariantList value);

    QVariantList gDigitialMax();
    void setGDigitialMax(QVariantList value);

    QVariantList gDigitialMin();
    void setGDigitialMin(QVariantList value);

    QVariantList gDigitialCurrent();
    void setGDigitialCurrent(QVariantList value);

    QVariantList bDigitialMax();
    void setBDigitialMax(QVariantList value);

    QVariantList bDigitialMin();
    void setBDigitialMin(QVariantList value);

    QVariantList bDigitialCurrent();
    void setBDigitialCurrent(QVariantList value);

    QVariantList triggerMode();
    void setTriggerMode(QVariantList value);

    QVariantList exposureGainCurrent();
    void setExposureGainCurrent(QVariantList value);

    QVariantList exposureGainMax();
    void setExposureGainMax(QVariantList value);

    QVariantList exposureGainMin();
    void setExposureGainMin(QVariantList value);

    QVariantList triggerDelayCurrent();
    void setTriggerDelayCurrent(QVariantList value);

    QVariantList triggerDelayMax();
    void setTriggerDelayMax(QVariantList value);

    QVariantList triggerDelayMin();
    void setTriggerDelayMin(QVariantList value);

    QVariantList vflip();
    void setVflip(QVariantList value);

    QVariantList hflip();
    void setHflip(QVariantList value);
signals:
    void maxWChanged();
    void maxHChanged();
    void ipChanged();
    void exposureTimeMaxChanged();
    void exposureTimeMinChanged();
    void rDigitialMaxChanged();
    void rDigitialMinChanged();
    void rDigitialCurrentChanged();
    void gDigitialMaxChanged();
    void gDigitialMinChanged();
    void gDigitialCurrentChanged();
    void triggerModeChanged();
    void exposureGainCurrentChanged();
    void exposureGainMaxChanged();
    void exposureGainMinChanged();
    void triggerDelayCurrentChanged();
    void triggerDelayMaxChanged();
    void triggerDelayMinChanged();
    void vflipChanged();
    void hflipChanged();
    void bDigitialMaxChanged();
    void bDigitialMinChanged();
    void bDigitialCurrentChanged();
    void macChanged();
    void upExposureTimeChanged();
    void downExposureTimeChanged();
signals:
    void sigCameraBrightTime(QString,int);
    void sigCameraDarkTime(QString,int);
public:
    explicit CameraProperty(std::shared_ptr<camera::camera> one,
                            std::shared_ptr<camera::camera> two,
                            std::shared_ptr<camera::camera> three);
    // 设置触发模式
    Q_INVOKABLE void setTriggerMode(int id,int mode);
    // 设置R通道增益
    Q_INVOKABLE void setR_digitial(int id,int value);
    // 设置G通道增益
    Q_INVOKABLE void setG_digitial(int id,int value);
    // 设置B通道增益
    Q_INVOKABLE void setB_digitial(int id,int value);
    // 设置曝光增益
    Q_INVOKABLE void setExposureGain(int id,int value);
    // 设置触发延迟
    Q_INVOKABLE void setTriggerDelay(int id,int value);
    // 设置垂直翻转
    Q_INVOKABLE void setvFlip(int id,bool value);
    // 设置水平翻转
    Q_INVOKABLE void sethFlip(int id,bool value);
    //设置曝光时间 针对流量相机
    Q_INVOKABLE void setExposuse(int id,int value);
    // 设置明场曝光时间
    Q_INVOKABLE void setUpExposuse(int id,int value);
    // 设置暗场曝光时间
    Q_INVOKABLE void setDownpExposuse(int id,int value);
    Q_INVOKABLE void saveCameraConfig();
private:
    void initParam();
    void readConfig(QString grainType);
    void saveCameraConfig(QString);
public:
    void setCameraInfo();
private:
    //std::map<int,std::shared_ptr<camera::camera>> m_cameras;//相机序号-相机
    QMap<int,std::shared_ptr<camera::camera>> m_cameras;//相机序号-相机
    std::shared_ptr<CameraInfo> m_d;
};

#endif // CAMERAPROPERTY_H
