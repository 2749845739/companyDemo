#include "RecordWheatModel.h"
#include <QDebug>
QVariantList RecordWheatModel::headRoles()
{
    return m_headRoles;
}

void RecordWheatModel::setHeadRoles(QVariantList value)
{
    m_headRoles=value;
    emit headRolesChanged();
}

int RecordWheatModel::rows()
{
    return m_rows;
}

void RecordWheatModel::setRows(int value)
{
    m_rows=value;
    emit rowsChanged();
}

RecordWheatModel::RecordWheatModel(QObject* parent):
    RecordBaseModel<WheatItem>(parent)
{
    setHeadRoles({"打印选择",
                  "样本号",
                  "检测时间",
                  "不完善粒",
                  "虫蚀粒",
                  "破损粒",
                  "生芽粒",
                  "生霉粒",
                  "病斑粒",
                  "赤霉粒",
                  "黑胚粒"});
//    QVector<QStringList> data;
//    for(int i=0;i<100;i++){
//        data.append(QStringList()<<QString::number(i)<<QString::number(i));
//    }
//    initModel(data);
//    qDebug()<<"init finsh";
}

QHash<int, QByteArray> RecordWheatModel::roleNames() const
{
    return {
        {Roles::CellDataRole,"cellData"},
        {Roles::CellTypeRole,"cellType"}
    };
}

int RecordWheatModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_headRoles.size();
}

QVariant RecordWheatModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    if (!index.isValid() || !indexInRange(index)) return result;
    WheatItem item(std::move(mDatas.at(index.row())));
    bool isNameColumn (index.column() == 0);
    switch (role) {
        case Roles::CellDataRole: result = item.indexData(index.column());
            break;
        case Roles::CellTypeRole: result = isNameColumn ? WheatItem::DelegateType::CheckboxEditor : item.delegateType();
            break;
        default:
            break;
    }
    return result;

}

QVariant RecordWheatModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant result;
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal)   result=m_headRoles.at(section);
        //if (orientation == Qt::Vertical)     result=m_columnNames.at(section);
    }
    return result;
}

bool RecordWheatModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || !indexInRange(index)) return false;
    switch (role) {
        case Roles::CellDataRole:
            if (index.column()== 0){
                if(m_oldtItem&&m_oldIndex!=index)
                {
                    m_oldtItem->setChecked("false");
                    if(m_oldIndex.isValid()) emit dataChanged(m_oldIndex,m_oldIndex,{role});
                }
                 m_oldIndex=index;
                 mDatas[index.row()].setChecked(value.toString());
                 m_currentItem=&mDatas[index.row()];
                 m_oldtItem=m_currentItem;
            }
            break;
        default:
            return false;
    }
    emit dataChanged(index,index,{role});
    return true;
}

Qt::ItemFlags RecordWheatModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsEditable;
}

bool RecordWheatModel::canFetchMore(const QModelIndex &parent) const
{
    return false;
}

void RecordWheatModel::fetchMore(const QModelIndex &parent)
{
    if (parent.isValid()) return;
    int remainder = mDatas.size() - m_itemCount;
    int itemsToFetch = qMin(100, remainder);
    if (itemsToFetch <= 0) return;
    beginInsertRows(QModelIndex(), m_itemCount, m_itemCount + itemsToFetch - 1);
    m_itemCount += itemsToFetch;
    endInsertRows();
    setRows(rowCount());
}


void RecordWheatModel::initModel(QList<QStringList> value,QList<QStringList> valuetwo)
{
    mAllDatas.clear();
    mDatas.clear();
    beginResetModel();
    for(auto& it:value){
        mDatas.append(WheatItem(it));
    }
    for(auto& it:valuetwo){
        mAllDatas.append(WheatItem(it));
    }
    m_currentItem=nullptr;
    m_oldtItem=nullptr;
    m_oldIndex=QModelIndex();
    endResetModel();
    setRows(rowCount());
    //fetchMore({});
}

void RecordWheatModel::selectData()
{
    if(m_currentItem&&m_currentItem->checked()=="true"){
        emit emptySelect(false);
    }else{
        emit emptySelect(true);
    }
}

bool RecordWheatModel::printResult()
{
    if(m_currentItem){
        QString pLogo = QString("\n        高哲AI快检仪       ");
        QString dev = printDev();
        QString pSplitLine = QString("\n------------------------------");
        QString smapleId=QString("样品编号:%1").arg(m_currentItem->sampleid());
        QString grainame=QString("谷物种类:%1").arg("小麦");
        QString detectionTime=QString("检测时间:%1").arg(m_currentItem->createTime());
        QString quato=QString("        指标   质量比\n         不完善粒  %1%\n         生芽粒  %2%\n         虫蚀粒  %3%\n  "
                              "       破损粒  %4%\n         生霉粒  %5%\n         病斑粒  %6%\n         赤霉粒  %7%\n         黑胚粒  %8%\n")
                .arg(m_currentItem->mass()).arg(m_currentItem->sy())
                .arg(m_currentItem->cs()).arg(m_currentItem->ps())
                .arg(m_currentItem->sm()).arg(m_currentItem->bb())
                .arg(m_currentItem->cm()).arg(m_currentItem->hp());
        if(!dev.isEmpty())
        {
            QString printV;
            printV = QString("echo \" %1\n \" > /dev/usb/%2").arg(pLogo).arg(dev);
            printVal(printV.toUtf8());
            printV = QString("echo \" %1\n \" > /dev/usb/%2").arg(smapleId).arg(dev);
            printVal(printV.toUtf8());
            printV = QString("echo \" %1\n \" > /dev/usb/%2").arg(grainame).arg(dev);
            printVal(printV.toUtf8());
            printV = QString("echo \" %1\n \" > /dev/usb/%2").arg(detectionTime).arg(dev);
            printVal(printV.toUtf8());
            printV = QString("echo \" %1\n \" > /dev/usb/%2").arg(quato).arg(dev);
            printVal(printV.toUtf8());
            printV = QString("echo \" %1\n \" > /dev/usb/%2").arg(pSplitLine).arg(dev);
            printVal(printV.toUtf8());
            return true;
        }else {
            return false;
        }
    }
    return false;
}

QString RecordWheatModel::checkUsbDisk()
{
    QString userPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString userName = userPath.section("/", -1, -1);
    foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes()) {
        if(storage.rootPath().contains("/media/"+userName)){
            return "/media/"+userName+"/";
        }
//       qDebug() << storage.rootPath();
//       if (storage.isReadOnly())
//           qDebug() << "isReadOnly:" << storage.isReadOnly();
//       qDebug() << "name:" << storage.name();
//       qDebug() << "fileSystemType:" << storage.fileSystemType();
//       qDebug() << "size:" << storage.bytesTotal()/1000/1000 << "MB";
//       qDebug() << "availableSize:" << storage.bytesAvailable()/1000/1000 << "MB";
    }
    return "";
}

void RecordWheatModel::exportExcel(QString path)
{

    QtConcurrent::run([&]{
    QString rootPath=path;
    Document xlsx;
    rootPath=rootPath.mid(7)+"/";
    xlsx.addSheet("Grouping");
    for(int i=1;i<headRoles().length();i++){
        xlsx.write(1, i, headRoles().at(i).toString());
    }
    for (int row = 2; row < mAllDatas.length()+2; ++row) {
        xlsx.write(row, 1, mAllDatas[row-2].sampleid());
        xlsx.write(row, 2, mAllDatas[row-2].createTime());
        xlsx.write(row, 3, mAllDatas[row-2].mass());
        xlsx.write(row, 4, mAllDatas[row-2].cs());
        xlsx.write(row, 5, mAllDatas[row-2].ps());
        xlsx.write(row, 6, mAllDatas[row-2].sy());
        xlsx.write(row, 7, mAllDatas[row-2].sm());
        xlsx.write(row, 8, mAllDatas[row-2].bb());
        xlsx.write(row, 9, mAllDatas[row-2].cm());
        xlsx.write(row, 10, mAllDatas[row-2].hp());
    }
    bool res = xlsx.saveAs(QString("%1.xlsx").arg(rootPath+QDateTime::currentDateTime().toString("yyyyMMddhhmmss")));
    LOGGER_DEBUG("export execl:%d",res);
    emit exportFinsh(res);
    });
//    QtConcurrent::run([&]{
//        path=path.mid(7)+"/";
//        xlsx.addSheet("Grouping");
//        for(int i=1;i<headRoles().length();i++){
//            xlsx.write(1, i, headRoles().at(i).toString());
//        }
//        for (int row = 2; row < mAllDatas.length()+2; ++row) {
//                xlsx.write(row, 1, mAllDatas[row-2].sampleid());
//                xlsx.write(row, 2, mAllDatas[row-2].createTime());
//                xlsx.write(row, 3, mAllDatas[row-2].mass());
//                xlsx.write(row, 4, mAllDatas[row-2].cs());
//                xlsx.write(row, 5, mAllDatas[row-2].ps());
//                xlsx.write(row, 6, mAllDatas[row-2].sy());
//                xlsx.write(row, 7, mAllDatas[row-2].sm());
//                xlsx.write(row, 8, mAllDatas[row-2].bb());
//                xlsx.write(row, 9, mAllDatas[row-2].cm());
//                xlsx.write(row, 10, mAllDatas[row-2].hp());
//        }
//        bool res = xlsx.saveAs(QString("%1.xlsx").arg(path+QDateTime::currentDateTime().toString("yyyyMMddhhmmss")));
//        LOGGER_DEBUG("export execl:%d",res);
//        return res;
//    });
//   return false;
}

void RecordWheatModel::updateData()
{
    //fetchMore({});
}

bool RecordWheatModel::indexInRange(const QModelIndex &index) const
{
   return index.row()>=0 && index.row()< rowCount() && index.column()>=0 && index.column()<columnCount();
}
