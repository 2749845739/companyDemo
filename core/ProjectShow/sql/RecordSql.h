#ifndef RECORDSQL_H
#define RECORDSQL_H

#include <QObject>
#include "SqlManager.h"
#include "GlobalParameter.h"
#include "xlsxdocument.h"
#include "xlsxformat.h"
#include "xlsxcellrange.h"
#include "xlsxworksheet.h"
QTXLSX_USE_NAMESPACE
class RecordSqlPrivateData;
class RecordSql : public QObject
{
    Q_OBJECT
public:
    explicit RecordSql(QObject *parent = nullptr);
    bool selectStaticRecord(RecordStaticParmeter &list,QStringList &dst);
    bool selectRecordToAi();
public slots:
    void getSqlparmeter(QString,QString);
    void addRecordData(QStringList ,QStringList ,QStringList ,QString);
signals:
    void getWheatRecordData(QVector<QStringList> data);
    void emptyRecord();
private:
    RecordSqlPrivateData* m_p;
};

#endif // RECORDSQL_H
