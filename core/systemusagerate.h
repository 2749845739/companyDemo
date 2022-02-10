#ifndef SYSTEMUSAGERATE_H
#define SYSTEMUSAGERATE_H

#include <QObject>
#include <QProcess>
#include <QTimer>
#include <unistd.h>
#include <QVariant>
class SystemUsageRate:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList listRate READ listRate WRITE setlistRate NOTIFY listRateChanged)
public:
    explicit SystemUsageRate(QObject* parent=nullptr);
    QVariantList listRate();
    void setlistRate(QVariantList listRate);
public slots:
    void getCpuUsage();
    void stop();
    void start();
signals:
    void listRateChanged(QVariantList listRate);
private:
    QVariantList m_listRate{0,0};
    QTimer mRefreshTimer;
    pid_t mPid;
    QProcess *mProcess;
};
#endif // SYSTEMUSAGERATE_H
