#ifndef RECORDWHEATMODEL_H
#define RECORDWHEATMODEL_H

#include <QObject>
#include <QStorageInfo>
#include <QStandardPaths>
#include "RecordBaseModel.hpp"
#include "WheatItem.h"
#include "xlsxdocument.h"
#include "xlsxformat.h"
#include "xlsxcellrange.h"
#include "xlsxworksheet.h"
#include <QtConcurrent>
QTXLSX_USE_NAMESPACE
class RecordWheatModel:public RecordBaseModel<WheatItem>
{
    Q_OBJECT
    Q_ENUMS(Roles)
    Q_PROPERTY(QVariantList headRoles READ headRoles WRITE setHeadRoles NOTIFY headRolesChanged)
    Q_PROPERTY(int rows READ rows WRITE setRows NOTIFY rowsChanged)
public:
    QVariantList headRoles();
    void setHeadRoles(QVariantList value);

    int rows();
    void setRows(int value);
signals:
    void headRolesChanged();
    void rowsChanged();
    void emptySelect(bool);
    void exportFinsh(bool);
public:
    explicit RecordWheatModel(QObject* parent=nullptr);
    enum Roles{CellDataRole = Qt::UserRole+1, CellTypeRole};
    QHash<int,QByteArray> roleNames() const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;
public slots:
    virtual void initModel(QList<QStringList> value,QList<QStringList> valuetwo);
    virtual void selectData();
    virtual bool printResult();
    virtual QString checkUsbDisk();
    virtual void exportExcel(QString path);
public:
    Q_INVOKABLE void updateData();
private:
    bool indexInRange(const QModelIndex &index) const;
private:
    QVariantList m_headRoles;
    int m_rows;
};

#endif // RECORDWHEATMODEL_H
