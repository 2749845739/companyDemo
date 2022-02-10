#pragma once
#include <QAbstractListModel>
#include <QList>
#include <QDateTime>
#include <QMetaType>
#include <GlobalParameter.h>
template<class T>
class RecordBaseModel : public QAbstractTableModel
{
public:
    explicit RecordBaseModel(QObject *parent = nullptr);
public:
    //[begin] query data
    int rowCount(const QModelIndex &parent=QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void resetData(const QList<T> &datas);
protected:
    QList<T> mDatas;
    QList<T> mAllDatas;
    int m_itemCount;
    T* m_currentItem {nullptr};
    T* m_oldtItem {nullptr};
    QModelIndex m_oldIndex;
};

template<class T>
RecordBaseModel<T>::RecordBaseModel(QObject *parent) : QAbstractTableModel(parent),m_itemCount(0)
{

}
#include <QDebug>
template<class T>
int RecordBaseModel<T>::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    //fecth more
    //return m_itemCount;
    return mDatas.size();
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
