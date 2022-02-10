#ifndef RECORDWHEATMODEL_H
#define RECORDWHEATMODEL_H
#include "RecordBaseModel.hpp"
#include "ItemWheat.h"
#include "xlsxdocument.h"
#include "xlsxformat.h"
#include "xlsxcellrange.h"
#include "xlsxworksheet.h"
QTXLSX_USE_NAMESPACE
class RecordWheatModel:public RecordBaseModel<ItemWheat>
{
    Q_OBJECT
    Q_PROPERTY(QVariantList headerRoles READ headerRoles WRITE setHeaderRoles NOTIFY headerRolesChanged)
public:
    RecordWheatModel();
    QVariantList headerRoles();
    void setHeaderRoles(QVariantList value);
    int columnCount(const QModelIndex &parent) const override;
    QVariant  data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_ENUMS(Roles);
    enum  Roles {CellDataRole=Qt::UserRole+1,DelegateTypeRole};
    QHash<int, QByteArray>  roleNames() const override;
signals:
    void headerRolesChanged();
public:
    bool exportExecl();
public slots:
    void getRecordWheat(QVector<QStringList> data);
private:
    QVariantList mHeaderRoles;
};

#endif // RECORDWHEATMODEL_H
