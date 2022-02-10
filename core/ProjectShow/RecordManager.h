#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H

#include "RecordTable/RecordWheatModel.h"
#include "sql/RecordSql.h"
#include <QObject>

class RecordManager : public QObject
{
    Q_OBJECT
public:
    explicit RecordManager(QObject *parent = nullptr);
    Q_INVOKABLE void getRocoedData(QString,QString,QString grainName="");
    Q_INVOKABLE bool exportExcel(QString grainName);
    QString printDev();
signals:
    void emptyRecordResult();
    void timeRangeError();
public slots:
    void addRecord(QStringList normal,QStringList count,QStringList weight,QString grainName);
    void printResult();
public:
    RecordWheatModel* m_recordWheatModel;
    RecordSql* m_recordSql;
    QStringList mBatchWeightResults;
};

#endif // RECORDMANAGER_H
