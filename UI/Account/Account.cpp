#include "Account.h"
#include "SqlManager.h"
Account::Account(QObject* parent):QObject(parent),
    m_p(SqlManager::singleInstance())
{}

QString Account::queryPassword(QString username)
{
    QString sql="SELECT password FROM user WHERE username=?";
    QList<QStringList> dst;
    bool res = m_p->sqlSelectQuery(sql,QStringList()<<username,dst);
    if(res&&dst.size()>0){
        return dst.at(0).at(0);
    }else{
        return "";
    }
}
