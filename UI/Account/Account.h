#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "GlobalParameter.h"
class SqlManager;
class Account:public QObject
{
    Q_OBJECT
public:
    explicit Account(QObject* parent);
    QString queryPassword(QString username);
private:
    SqlManager* m_p {nullptr};
};

#endif // ACCOUNT_H
