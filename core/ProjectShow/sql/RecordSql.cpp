#include "RecordSql.h"
#include <QDateTime>
class RecordSqlPrivateData{
public:
    RecordSqlPrivateData():mSqlManager(SqlManager::singleInstance()){
    }
public:
    SqlManager* mSqlManager;
};

RecordSql::RecordSql(QObject *parent) : QObject(parent),m_p(new RecordSqlPrivateData)
{

}

bool RecordSql::selectStaticRecord(RecordStaticParmeter &data,QStringList &dst)
{
    return m_p->mSqlManager->sqlSelectQuery(data,dst);
}

bool RecordSql::selectRecordToAi()
{
    QString sql="SELECT a.sampleid, a.totalNumber, a.normal, a.scab,a.mildew, a.germination, a.eaten, a.broken, a.blackfoetus, a.totalunsound, a.unsound ,b.totalNumber, b.normal, b.scab,b.mildew, b.germination, b.eaten, b.broken, b.blackfoetus, b.totalunsound,b.unsound FROM wheat_count_one a,wheat_weight_one b WHERE a.sampleid=b.sampleid";
    QVector<QStringList> dst;
    //QVector<QStringList> dstTwo;
    m_p->mSqlManager->sqlSelectQuery(sql,QStringList(),dst);
//    sql="SELECT sampleid, totalNumber, normal, scab, mildew, germination, eaten, broken, blackfoetus, totalunsound, unsound FROM wheat_weight_one";
//    m_p->mSqlManager->sqlSelectQuery(sql,QStringList(),dstTwo);

    Document xlsx;
    xlsx.addSheet("Math");
    Format format;
    format.setHorizontalAlignment(Format::AlignHCenter);
    format.setVerticalAlignment(Format::AlignVCenter);
    //xlsx.setColumnWidth(1,12,200);
    xlsx.write("A1", "G1000人工样本");
    xlsx.mergeCells("A1:L1", format);
    xlsx.write(2, 1, "样本编号");
    xlsx.write(2, 2, "评价类型");
    xlsx.write(2, 3, "总数（重量）");
    xlsx.write(2, 4, "正常");
    xlsx.write(2, 5, "病斑");
    xlsx.write(2, 6, "生芽");
    xlsx.write(2, 7, "生霉");
    xlsx.write(2, 8, "虫蚀");
    xlsx.write(2, 9, "破碎");
    xlsx.write(2, 10, "黑胚");
    xlsx.write(2, 11, "不完善粒总数(重量)");
    xlsx.write(2, 12, "不完善粒率");
   for(int row=3;row<dst.size()+3;row++){
       //xlsx.write(row)
       QString cellstart=QString("A%1").arg(2*(row-2)+1);
       xlsx.write(cellstart,dst.at(row-3).at(0));
       QString cellend=QString(cellstart+":A%1").arg(2*(row-1));
       xlsx.mergeCells(cellend, format);
       //xlsx.write(row, 2, );
       xlsx.write(2*(row-2)+1, 2, "数量");
       xlsx.write(2*(row-1), 2, "重量");
       for(int column=3;column<13;column++){
           xlsx.write(2*(row-2)+1, column, dst.at(row-3).at(column-2));
           xlsx.write(2*(row-1), column, dst.at(row-3).at(10+column-2));

       }
   }
   bool res = xlsx.saveAs(QString("%1.xlsx").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
   qDebug()<<"export execl:"<<res;
   return res;
}

void RecordSql::getSqlparmeter(QString startTime, QString endTime)
{
    QString sql;
    sql = "SELECT createtime,sampleid,unsound"
",eaten,mildew,budding,broken,scab,gibberellic,blackEmbryo FROM wheat WHERE ";

    if(startTime==""||endTime==""){
         //startTime=QDateTime::currentDateTime().toString("yyyy-MM-dd")+" 00:00:00";
        startTime="2020-01-01 00:00:00";
         endTime=QDateTime::currentDateTime().toString("yyyy-MM-dd")+" 23:59:59";
    }
    //LIMIT ?,10
    sql+="createtime BETWEEN ? ANd ? ORDER BY  createtime DESC";
    qDebug()<<"sql"<<sql;
    QStringList info;
    info<<startTime<<endTime;
    QVector<QStringList> dest;
     m_p->mSqlManager->sqlSelectQuery(sql,info,dest);
     qDebug()<<dest;
     if(dest.size()==0) emit emptyRecord();
     emit getWheatRecordData(dest);
}

void RecordSql::addRecordData(QStringList normal,QStringList count,QStringList weight,QString grainName)
{
    if(count.size()!=8||weight.size()!=9||normal.size()!=7){
        qDebug()<<count.size()<<weight.size()<<normal.size()
               <<"count or weight record error";
    }else{
         QString createTime=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QString sampleid=GlobalObject::g_instance()->g_smapleid;
        if(sampleid=="") sampleid=createTime;
        //不完善率 正常 病斑粒 生芽粒 生霉粒 虫蚀粒 破损粒 黑胚粒
        QString sql;
        sql="INSERT INTO wheat_count_one (sampleid,totalNumber,normal,scab,mildew,"
    "germination,eaten,broken,blackfoetus,totalunsound,unsound,createtime) VALUES(?,?,?,?,?,?,?,?,?,?,?,?)";
        int normalCount=count.at(0).toInt();
        int scab=count.at(1).toInt();
        int mildew=count.at(2).toInt();
        int germination=count.at(3).toInt();
        int eaten=count.at(4).toInt();
        int broken=count.at(5).toInt();
        int blackfoetus=count.at(6).toInt();
        int totalNumberCount=normalCount+scab+mildew
                +germination+eaten+broken+blackfoetus;
        int totalunsound=scab+mildew
                +germination+eaten+broken+blackfoetus;
        QStringList info;
        info<<sampleid<<
              QString::number(totalNumberCount)<<QString::number(normalCount)<<
              QString::number(scab)<<QString::number(mildew)<<QString::number(germination)<<
              QString::number(eaten)<<QString::number(broken)<<QString::number(blackfoetus)<<
               QString::number(totalunsound)<<count.at(7)<<createTime;
         qDebug()<<"save wheat record cout" <<m_p->mSqlManager->sqlQuery(sql,info);

         sql="INSERT INTO wheat_weight_one (sampleid,totalNumber,normal,scab,mildew,"
    "germination,eaten,broken,blackfoetus,totalunsound,unsound,createtime) VALUES(?,?,?,?,?,?,?,?,?,?,?,?)";
         float normalWeight=weight.at(0).toFloat();
         float scabWeight=weight.at(1).toFloat();
         float mildewWeight=weight.at(2).toFloat();
         float germinationWeight=weight.at(3).toFloat();
         float eatenWeight=weight.at(4).toFloat();
         float brokenWeight=weight.at(5).toFloat();
         float blackfoetusWeight=weight.at(6).toFloat();
         float totalNumberWeight=weight.at(8).toFloat();
         float totalunsoundWeight=scab+mildew
                 +germination+eaten+broken+blackfoetus;
         info.clear();
         info<<sampleid<<QString::number(totalNumberWeight,'f',3)<<
               QString::number(normalWeight,'f',3)<<
               QString::number(scabWeight,'f',3)<<
                QString::number(mildewWeight,'f',3)<<
                QString::number(germinationWeight,'f',3)<<
                QString::number(eatenWeight,'f',3)<<
                QString::number(brokenWeight,'f',3)<<
                QString::number(blackfoetusWeight,'f',3)<<
                QString::number(totalunsoundWeight,'f',3)<<weight.at(7)<<createTime;
               ;
         qDebug()<<"save wheat record wheat" <<m_p->mSqlManager->sqlQuery(sql,info);

         sql="INSERT INTO wheat (createtime,sampleid,unsound,eaten,mildew,"
"budding,broken,scab,gibberellic,blackEmbryo) VALUES(?,?,?,?,?,?,?,?,?,?)";
         QString n_gibberellic=normal.at(0);
         QString n_budding=normal.at(1);
         QString n_mildew=normal.at(2);
         QString n_eaten=normal.at(3);
         QString n_broken=normal.at(4);
         QString n_blackEmbryo=normal.at(5);
         QString n_unsound=normal.at(6);
         QString n_scab=QString::number(n_gibberellic.toFloat()+n_blackEmbryo.toFloat(),'f',1);
         //
         info.clear();
         info<<createTime<<sampleid<<n_unsound<<n_eaten<<n_mildew
            <<n_budding<<n_broken<<n_scab<<n_gibberellic<<n_blackEmbryo;
         qDebug()<<"save wheat record wheat" <<m_p->mSqlManager->sqlQuery(sql,info);
    }

}

