#ifndef GLOBALPARAMETER_H
#define GLOBALPARAMETER_H
#include <QJsonObject>
#include <QRunnable>
#include <QThreadPool>
#include <QFile>
#include <QImage>
#include <QDir>
#include <QApplication>
#include <QJsonParseError>
#include <QDebug>
#include <queue>
#include <mutex>
#include <memory>
#include <opencv2/opencv.hpp>
#include "module/camera/common.h"
#include "module/camera/camera.h"
#include "module/board/board.h"
#include "Gzlogger.h"
#include "../../algorithm/graineval/dcdf.h"
#include <QSemaphore>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <QObject>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtCore/QTextStream>
#include <QTextCodec>
#define THREAD_COUNT 3
enum class GrainType:unsigned int {
      WHEAT,
      RICE,
      CRON,
      SORGHUM
};
struct RecordStaticParmeter{
    int grainType;
    QString startTime;
    QString endTime;
    int page;
    RecordStaticParmeter(){
        grainType=-1;
        startTime="";
        endTime="";
        page=0;
    }
};
struct SaveImgData{
    std::shared_ptr<cv::Mat> ImgData;
    QString imgName;
};

static QJsonObject getConfig(){
    QFile file(QApplication::applicationDirPath()+"/config.json");
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error";
    } else {
        QByteArray allData = file.readAll();
        QJsonParseError jsonError;
        QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &jsonError));
        if(jsonError.error != QJsonParseError::NoError)
        {
            qDebug() << "json error!" << jsonError.errorString();
        }else{
            QJsonObject rootObj = jsonDoc.object();
            return  rootObj;
            file.close();
        }
    }
    return QJsonObject();
}
static bool BGR2RGB(unsigned char* pRgbData, unsigned int nWidth, unsigned int nHeight)
{
    if (NULL == pRgbData)
    {
        return false;
    }

    for (unsigned int j = 0; j < nHeight; j++)
    {
        for (unsigned int i = 0; i < nWidth; i++)
        {
            unsigned char red = pRgbData[j * (nWidth * 3) + i * 3];
            pRgbData[j * (nWidth * 3) + i * 3] = pRgbData[j * (nWidth * 3) + i * 3 + 2];
            pRgbData[j * (nWidth * 3) + i * 3 + 2] = red;
        }
    }
    return true;
}
static QVector<QString> get_all_files(const char* dir) {
    struct stat s;
    QVector<QString> files;
    stat(dir, &s);
    if (!S_ISDIR(s.st_mode)) {
        return files;
    }
    DIR* open_dir = opendir(dir);
    if (NULL == open_dir) {
        std::exit(EXIT_FAILURE);
    }
    dirent* p = nullptr;
    while( (p = readdir(open_dir)) != nullptr) {
        if (p->d_name[0] != '.') {
            files.push_back(QString::fromStdString(p->d_name));
        }
    }
    closedir(open_dir);
    return files;
}
static QString printDev(){
    QString priDev="";
    QVector<QString> files = get_all_files("/dev/usb");
    for(int i = 0; i < files.size(); ++i)
    {
        if(files[i].left(2) == "lp")
        {
            priDev = files[i];
            break;
        }
    }
    return priDev;
}
static bool printVal(const QByteArray& val){
    QTextCodec* utf8Codec= QTextCodec::codecForName("utf-8");
    QTextCodec* gb2312Codec = QTextCodec::codecForName("gb2312");

    QString strUnicode= utf8Codec->toUnicode(val);
    QByteArray ByteGb2312= gb2312Codec->fromUnicode(strUnicode);

    return system(ByteGb2312.data());
}

class GlobalObject:public QObject{
    Q_OBJECT
public:
    GlobalObject(QObject* parent=nullptr);
    static GlobalObject* g_instance(){
        static GlobalObject* g_globObject=new GlobalObject();
        return g_globObject;
//        if(g_globObject==nullptr){
//            return g_globObject= new GlobalObject();
//        }else{
//            return g_globObject;
//        }
    }
    void readConfig();
    Q_INVOKABLE QString getSampleid();
    Q_INVOKABLE void setSampleid();
    void saveImgEnable(bool);
signals:
    void sigSaveImg(bool);
public slots:
public:
    static GrainType g_grainType;
    static QString g_deviceName;
    static bool g_saveOriginalImg;
    static QString g_sampleId;
    static QString g_grainTyoe;
    static QString g_childType;
    std::queue<QStringList> m_picName;
    std::vector<float> m_weights;
    using mSaveImgData = std::queue<std::vector<SaveImgData>>;
    mSaveImgData m_saveImgData;
    QString g_smapleid;
public:
    Q_INVOKABLE void setGrainType(int type);
    Q_INVOKABLE void closeSystem();
public:
    std::queue<algorithm::result> m_res;//
    std::mutex m_mutex;
    QSemaphore m_sm {0};
    QMap<int, std::queue<algorithm::result>> m_mulitRes;
    QSemaphore m_saveSema[THREAD_COUNT+1];
};

class BoardStatus:public QObject,public board::board_observer
{
    Q_OBJECT
public:
    explicit BoardStatus(QObject* parent=nullptr);
    void handle_frame(std::string uid, board::frame frame) override;
    void handle_status(std::string uid, std::uint32_t status) override;
signals:
    void sigResetStatus();
    void sigGrapFinsh();
    void sigGrapStart();
    void sigKeypressed();
    void sigRecyleStatus(bool);
};
class SavePng:public QObject,public QRunnable {
    Q_OBJECT
public:
    explicit SavePng(QList<QImage> img,QObject* parent=nullptr);
    void run();
signals:
    void sigfinshed(bool flag);
private:
    QList<QImage> m_img;
};

#endif // GLOBALPARAMETER_H
