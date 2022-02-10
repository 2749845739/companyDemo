#pragma once
#include <QAbstractListModel>
#include <QList>
#include <QDateTime>
template<class T>
class RecordBaseModel : public QAbstractTableModel
{
public:
    explicit RecordBaseModel(QObject *parent = nullptr);
public:
    //[begin] query data
    int rowCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void resetData(const QList<T> &datas);
protected:
    QList<T> mDatas;
};

template<class T>
RecordBaseModel<T>::RecordBaseModel(QObject *parent) : QAbstractTableModel(parent)
{

}

template<class T>
int RecordBaseModel<T>::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mDatas.count();
}


template <class T>
QVariant RecordBaseModel<T>::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mDatas.size()) {
        return {};
    }
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        auto data = mDatas.at(index.row());
        return QVariant::fromValue(data);
    }
    return {};
}

template<class T>
void RecordBaseModel<T>::resetData(const QList<T> &datas)
{
    auto oldObjs = mDatas;
    beginResetModel();
    mDatas = datas;
    endResetModel();
    //qDeleteAll(oldObjs);
}

