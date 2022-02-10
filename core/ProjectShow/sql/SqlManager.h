#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtCore/QString>
#include <QtCore/QDebug>
#include <GlobalParameter.h>
class SqlManager{
public:
    static SqlManager* singleInstance();
    ~SqlManager();
    //**********增、删、改***********************************
    bool sqlQuery(const QString& sql, const QStringList& list);
    //**********查询记录************************************
    bool sqlSelectQuery(const QString& sql, const QStringList& info, QVector<QStringList>& dst);
private:
    SqlManager();
private:
    QSqlDatabase mDatabase;
    QSqlQuery mQuery;
};
