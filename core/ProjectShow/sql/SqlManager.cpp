#include"SqlManager.h"
#include <QDateTime>
SqlManager *SqlManager::singleInstance()
{
    static SqlManager* instance = new SqlManager();
    return instance;
}

SqlManager::~SqlManager(){}

bool SqlManager::sqlQuery(const QString &sql, const QStringList &list)
{
    mQuery.clear();
    mQuery.prepare(sql);
    for (int i = 0; i < list.size(); i++)
    {
        QString str = list.at(i);
        mQuery.bindValue(i, str);
    }
    bool result = mQuery.exec();
    return result;
}

bool SqlManager::sqlSelectQuery(const QString &sql, const QStringList &info, QVector<QStringList> &dst)
{
    mQuery.clear();

    mQuery.prepare(sql);
    for (int i = 0; i < info.size(); i++)
    {
        QString str = info.at(i);
        mQuery.addBindValue(str);
    }
    mQuery.exec();
    bool result = false;
    while (mQuery.next())
    {
        int index = 0;
        QStringList it;
        while (mQuery.value(index).toString() != NULL)
        {
            it << mQuery.value(index).toString();
            index++;
        }
        dst.append(it);
        result = true;
    }
    return result;
}

SqlManager::SqlManager()
{
    mDatabase = QSqlDatabase::addDatabase("QSQLITE");
    mDatabase.setDatabaseName(QApplication::applicationDirPath()+"/database/G1000.db");
    mQuery = QSqlQuery(mDatabase);

    if (!mDatabase.open())
    {
        qDebug() << "Error: Failed to connect database." << mDatabase.lastError();
    }
}
