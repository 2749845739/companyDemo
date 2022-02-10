#ifndef SQLSAMPLEID_H
#define SQLSAMPLEID_H
#include "SqlManager.h"
#include "GlobalParameter.h"
#include "../TableModel/WheatItem.h"
#include "../TableModel/RecordWheatModel.h"
class SqlSampleId:public QObject
{
    Q_OBJECT
public:
    explicit SqlSampleId(QObject* parent=nullptr);
    virtual Q_INVOKABLE void querySamplid(QString)=0;
    virtual Q_INVOKABLE void queryRecord(QVariantList,int)=0;
    virtual Q_INVOKABLE int queryRecordCount(QVariantList);
    virtual Q_INVOKABLE void sqlQuery(QVariantList list)=0;
    SqlManager* m_p {nullptr};
    bool m_isRepeatId {false};
};

class SqlWheatSampleId:public SqlSampleId{
    Q_OBJECT
public:
    explicit SqlWheatSampleId(QObject* parent=nullptr);
    Q_INVOKABLE void querySamplid(QString) override;
    Q_INVOKABLE void sqlQuery(QVariantList list) override;
    Q_INVOKABLE void queryRecord(QVariantList,int) override;
signals:
    void sigRepeatId(bool);
public:
    RecordWheatModel* m_recoedWheatModel  {nullptr};
};
#endif // SQLSAMPLEID_H
