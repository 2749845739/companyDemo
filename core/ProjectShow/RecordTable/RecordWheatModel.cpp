#include "RecordWheatModel.h"
#include <QDebug>
//const static QVariantList sHeaderRoles = { "sampleId", "gainName", "volumeweight"
//                                         ,"unsound","impurities","moisture","smell"
//                                         ,"yzwheat","qlweight","jjwheat"};
const static QVariantList sHeaderRoles = { "检测时间", "样品编号"
      ,"不完善粒","虫蚀","生霉","生芽","破损","病斑(黑胚+赤霉)","赤霉","黑胚"};
RecordWheatModel::RecordWheatModel()
{
    setHeaderRoles(sHeaderRoles);
}

void RecordWheatModel::getRecordWheat(QVector<QStringList>data)
{
    QList<ItemWheat> value  {};
//    if(data.size()<=0){
//        return;
//    }
    for(auto& it : data){
       if(it.length()!=10){
           qDebug()<<"wheatRecord num error";
           return;
       }else{
           qDebug()<<it;
           ItemWheat item=ItemWheat(it);
           value<<item;
       }
    }
    resetData(value);
}

QVariantList RecordWheatModel::headerRoles()
{
    return mHeaderRoles;
}

void RecordWheatModel::setHeaderRoles(QVariantList value)
{
    mHeaderRoles=value;
    emit headerRolesChanged();
}

int RecordWheatModel::columnCount(const QModelIndex &parent) const
{
    return sHeaderRoles.length();
}

QVariant RecordWheatModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    if (!index.isValid()) return result;
    auto property = mDatas.at(index.row());
    switch (role) {
    case CellDataRole:
        switch (index.column()) {
        case 0 : result=property.createTime(); break;
        case 1 : result=property.sampleId(); break;
        case 2 : result=property.unsound(); break;
        case 3 : result=property.eaten(); break;
        case 4 : result=property.mildew(); break;
        case 5 : result=property.budding(); break;
        case 6 : result=property.broken(); break;
        case 7 : result=property.scab(); break;
        case 8 : result=property.gibberellic(); break;
        case 9 : result=property.blackEmbryo(); break;
//        case 3 : result=property.whitewhite(); break;
//        case 4 : result=property.qlweight(); break;
//        case 5 : result=property.jjwheat(); break;
        default:
            break;
        }
        break;
     case DelegateTypeRole: result = property.delegateType();
        break;

    default:
        break;
    }
    //property.setResultValue(result.toString());
    return result;
}

QHash<int, QByteArray> RecordWheatModel::roleNames() const
{
    return {
        {CellDataRole,"CellData"},
        {DelegateTypeRole,"DelegateType"}
    };
}

bool RecordWheatModel::exportExecl()
{
    Document xlsx;
    xlsx.addSheet("Grouping");
    for(int i=1;i<sHeaderRoles.length()+1;i++){
        xlsx.write(1, i, sHeaderRoles.at(i-1).toString());
    }
    for (int row = 2; row < mDatas.length()+2; ++row) {
        //for (int col = 1; col < sHeaderRoles.length(); ++col)
            xlsx.write(row, 1, mDatas[row-2].createTime());
            xlsx.write(row, 2, mDatas[row-2].sampleId());
            xlsx.write(row, 3, mDatas[row-2].unsound());
            xlsx.write(row, 4, mDatas[row-2].eaten());
            xlsx.write(row, 5, mDatas[row-2].mildew());
            xlsx.write(row, 6, mDatas[row-2].budding());
            xlsx.write(row, 7, mDatas[row-2].broken());
            xlsx.write(row, 8, mDatas[row-2].scab());
            xlsx.write(row, 9, mDatas[row-2].gibberellic());
            xlsx.write(row, 10, mDatas[row-2].blackEmbryo());
    }
    bool res = xlsx.saveAs(QString("%1.xlsx").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
    qDebug()<<"export execl:"<<res;
    return res;
}
