#include "SqlSampleId.h"

SqlSampleId::SqlSampleId(QObject* parent):QObject(parent),
    m_p(SqlManager::singleInstance())
{}

//void SqlSampleId::queryRecord(QVariantList list,int start)
//{

//}

int SqlSampleId::queryRecordCount(QVariantList list)
{
    QStringList parmater;
    for(auto& it: list){
        parmater<<it.toString();
    }
    if(parmater.size()==4){
        QString sql="";
        switch (parmater.at(0).toInt()) {
        case 0:{
            if(parmater.at(1)!=""){
                sql+="SELECT COUNT(*) FROM wheat WHERE createtime BETWEEN ? AND ?";
            }else{
                sql+="SELECT COUNT(*) FROM wheat";
                parmater.removeAt(1);
                parmater.removeAt(2);
            }
        }
            break;
        default:
            break;
        }
        parmater.removeFirst();
        if(parmater.at(2)!="") {
            if(parmater.size()<3){
                sql+=" WHERE";
            }else{
                sql+=" AND";
            }
            sql+=" sampleid LIKE ?";
            QString it = parmater.last();
            parmater.replace(2,"%"+it+"%");
        }else{
            parmater.removeLast();
        }
        QList<QStringList> dst {};
        if(sql!=""){
            //sql+=" limited "
            //qDebug()<<sql<<"  "<<parmater;
            m_p->sqlSelectQuery(sql,parmater,dst);
            //res ? LOGGER_DEBUG("查询记录成功"):LOGGER_DEBUG("查询记录失败");

            if(dst.size()>0){
                //qDebug()<<dst.at(0).at(0);
                return dst.at(0).at(0).toInt();
            }
        }
    }
    return 0;
}

SqlWheatSampleId::SqlWheatSampleId(QObject *parent):SqlSampleId(parent),m_recoedWheatModel(new RecordWheatModel(this))
{}

void SqlWheatSampleId::querySamplid(QString sampleid)
{
    if(sampleid=="") sampleid=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    GlobalObject::g_sampleId=sampleid;
    QString sql="SELECT COUNT(*) FROM wheat WHERE sampleid=?";
    QList<QStringList> dst;
    bool res = m_p->sqlSelectQuery(sql,QStringList()<<sampleid,dst);
    if(res&&dst.size()>0){
        if(dst.at(0).at(0)=="0"){
            emit sigRepeatId(false);
            m_isRepeatId=false;
        }else{
            emit sigRepeatId(true);
            m_isRepeatId=true;
        }
    }
}

void SqlWheatSampleId::sqlQuery(QVariantList list)
{
    if(!m_isRepeatId){
        QString sql="INSERT INTO wheat(sampleid,indexid,createtime,mass,"
                    "sy,cs,ps,sm,bb,cm,hp) VALUES(?,?,?,?,?,?,?,?,?,?,?)";
        QStringList parmater;
        parmater<<GlobalObject::g_sampleId<<GlobalObject::g_sampleId<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        for(auto& it: list){
            parmater<<it.toString();
        }
        bool res = m_p->sqlQuery(sql,parmater);
        res ? LOGGER_DEBUG("添加数据成功"):LOGGER_DEBUG("添加数据失败");
    }else{
        QString sql="UPDATE wheat SET indexid=?,createtime=?,mass=?,sy=?,cs=?,ps=?,sm=?,bb=?,cm=?,hp=? WHERE sampleid=?";
        QStringList parmater;
        parmater<<GlobalObject::g_sampleId<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");//indexid
        for(auto& it: list){
            parmater<<it.toString();
        }
        parmater<<GlobalObject::g_sampleId;//sampleid
        bool res = m_p->sqlQuery(sql,parmater);
        res ? LOGGER_DEBUG("覆盖数据成功"):LOGGER_DEBUG("覆盖数据失败");
    }
}

void SqlWheatSampleId::queryRecord(QVariantList list,int start)
{
    QStringList parmater;
    for(auto& it: list){
        parmater<<it.toString();
    }
    if(parmater.size()==4){
        QString sql="";
        switch (parmater.at(0).toInt()) {
        case 0:{
            if(parmater.at(1)!=""){
                sql+="SELECT sampleid,createtime,mass,sy,cs,ps,sm,bb,cm,hp FROM wheat WHERE createtime BETWEEN ? AND ?";
            }else{
                sql+="SELECT sampleid,createtime,mass,sy,cs,ps,sm,bb,cm,hp FROM wheat";
                parmater.removeAt(1);
                parmater.removeAt(2);
            }
        }
            break;
        default:
            break;
        }
        parmater.removeFirst();
        if(parmater.at(2)!="") {
            if(parmater.size()<3){
                sql+=" WHERE";
            }else{
                sql+=" AND";
            }
            sql+=" sampleid LIKE ?";
            QString it = parmater.last();
            parmater.replace(2,"%"+it+"%");
        }else{
            parmater.removeLast();
        }
        QList<QStringList> dstone {};
        QList<QStringList> dsttwo {};
        if(sql!=""){
            QString sqlAll="";
            sqlAll=sql+" ORDER BY createtime DESC";
            sql+=QString(" ORDER BY createtime DESC LIMIT %1 OFFSET %2").arg(QUERYCOUNT).arg(start);
            //qDebug()<<sql<<"  "<<parmater;
            m_p->sqlSelectQuery(sql,parmater,dstone);
            m_p->sqlSelectQuery(sqlAll,parmater,dsttwo);
            //res ? LOGGER_DEBUG("查询记录成功"):LOGGER_DEBUG("查询记录失败");
        }
        m_recoedWheatModel->initModel(dstone,dsttwo);
        LOGGER_DEBUG("%d",dstone.size());
    }
}

