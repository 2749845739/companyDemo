#include "RecordManager.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtCore/QTextStream>
#include <QTextCodec>
QVector<QString> get_all_files(const char* dir) {
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
void printVal(const QByteArray& val)
{
    QTextCodec* utf8Codec= QTextCodec::codecForName("utf-8");
    QTextCodec* gb2312Codec = QTextCodec::codecForName("gb2312");

    QString strUnicode= utf8Codec->toUnicode(val);
    QByteArray ByteGb2312= gb2312Codec->fromUnicode(strUnicode);

    system(ByteGb2312.data());
}
RecordManager::RecordManager(QObject *parent) : QObject(parent),m_recordWheatModel(new RecordWheatModel),m_recordSql(new RecordSql)
{
    connect(m_recordSql,&RecordSql::getWheatRecordData,
            m_recordWheatModel,&RecordWheatModel::getRecordWheat);
    connect(m_recordSql,&RecordSql::emptyRecord,
            this,&RecordManager::emptyRecordResult);
}

void RecordManager::getRocoedData(QString startTime, QString endtime,QString grainName)
{
    // 根据grainName来实例哪个表格
    QDateTime dateS=QDateTime::fromString(startTime, "yyyy-MM-dd hh:mm:ss");
    QDateTime dateE=QDateTime::fromString(endtime, "yyyy-MM-dd hh:mm:ss");
    if(dateE.toSecsSinceEpoch()<dateS.toSecsSinceEpoch())
    {
        emit timeRangeError();
        return;
    }
    m_recordSql->getSqlparmeter(startTime,endtime);

}

bool RecordManager::exportExcel(QString grainName)
{
    // 根据grainName来导出哪个表格
    return m_recordWheatModel->exportExecl();
    //m_recordSql->selectRecordToAi();
}

QString RecordManager::printDev()
{
    QString priDev;
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

void RecordManager::addRecord(QStringList normal, QStringList count, QStringList weight, QString grainName)
{
    // 根据grainName来存入哪个种类
    m_recordSql->addRecordData(normal,count,weight,grainName);
    mBatchWeightResults=normal;
}

void RecordManager::printResult()
{
    if(mBatchWeightResults.size()==7){
        QString pTitle = QString("   小麦不完善粒分析结果   ");
        QString pTime =  QString("   %1   ").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd  hh:mm:ss"));
        QString pLine = QString("\n_____________________________");
        QString pMassRatio="";
        QJsonObject rootObj = getConfig();
        int type=1;
         if (rootObj.contains("wheatUnsoundType")) {
             type=rootObj.value("wheatUnsoundType").toInt();
         }
        if(type==1){
            pMassRatio = QString("\n不完善粒质量比    %1%\n    赤霉粒  %2%\n    生芽粒  %4%\n  "
                                              "  生霉粒  %5%\n    虫蚀粒  %6%\n    破损粒  %7%\n    黑胚粒  %8%\n").
                    arg(mBatchWeightResults.at(6)).
                    arg(mBatchWeightResults.at(0)).
                    arg(mBatchWeightResults.at(1)).
                    arg(mBatchWeightResults.at(2)).
                    arg(mBatchWeightResults.at(3)).
                    arg(mBatchWeightResults.at(4)).
                    arg(mBatchWeightResults.at(5));
        }else if(type==2){
            pMassRatio = QString("\n不完善粒质量比    %1%\n    病斑粒  %2%\n    生芽粒  %4%\n  "
                                              "  生霉粒  %5%\n    虫蚀粒  %6%\n    破损粒  %7%\n").
                    arg(mBatchWeightResults.at(6)).
                    arg(mBatchWeightResults.at(0)).
                    arg(mBatchWeightResults.at(1)).
                    arg(mBatchWeightResults.at(2)).
                    arg(mBatchWeightResults.at(3)).
                    arg(mBatchWeightResults.at(4));
        }

        QString pLogo = QString("\n        高哲AI快检仪       ");
            QString dev = printDev();
            QString pSplitLine = QString("\n------------------------------");
            if(!dev.isEmpty())
            {
              QString printV = QString("echo \" %1 \" > /dev/usb/%2").arg(pTitle).arg(dev);
              printVal(printV.toUtf8());

              printV = QString("echo \" %1 \" > /dev/usb/%2").arg(pTime).arg(dev);
              printVal(printV.toUtf8());

              printV = QString("echo \" %1 \" > /dev/usb/%2").arg(pLine).arg(dev);
              printVal(printV.toUtf8());

              printV = QString("echo \" %1 \" > /dev/usb/%2").arg(pMassRatio).arg(dev);
              printVal(printV.toUtf8());

              printV = QString("echo \" %1\n \" > /dev/usb/%2").arg(pLogo).arg(dev);
              printVal(printV.toUtf8());

              printV = QString("echo \" %1\n \" > /dev/usb/%2").arg(pSplitLine).arg(dev);
              printVal(printV.toUtf8());
            }
    }
}


