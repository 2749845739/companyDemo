#include "systemusagerate.h"
#include <QDebug>
double m_cpu_total = 0;
double m_cpu_use = 0;
int getCpuRate(QProcess *process) {
  process->start(QString("cat /proc/stat"));
  process->waitForFinished();
  QString str = process->readLine();
  str.replace("\n", "");
  str.replace(QRegExp("( ){1,}"), " ");
  auto sInfo = str.split(" ");
  if (sInfo.size() > 3) {
    double use =
        sInfo[1].toDouble() + sInfo[2].toDouble() + sInfo[3].toDouble();
    double total = 0;
    for (int i = 1; i < sInfo.size(); ++i)
      total += sInfo[i].toDouble();
    if (total - m_cpu_total > 0) {
      int cpurate = (use - m_cpu_use) / (total - m_cpu_total) * 100.0;
      m_cpu_total = total;
      m_cpu_use = use;
      return cpurate;
    }
  }
  return 0;
}
SystemUsageRate::SystemUsageRate(QObject* parent):QObject(parent)
{
  mProcess=new QProcess(this);
  mPid = getpid();
  mRefreshTimer.setSingleShot(false);
  mRefreshTimer.setInterval(1500);
  connect(&mRefreshTimer, SIGNAL(timeout()), this, SLOT(getCpuUsage()));
}

QVariantList SystemUsageRate::listRate()
{
    return m_listRate;
}

void SystemUsageRate::setlistRate(QVariantList listRate)
{
    m_listRate=listRate;
    //set完要emit
    emit listRateChanged(m_listRate);
}

void SystemUsageRate::getCpuUsage()
{
    m_listRate.clear();
    QStringList arg;
    // arg << QString("u %1").arg(mPid);
    // mProcess->start(QString("ps"), arg);
    QString strCatCpu = QString("ps u %1").arg(mPid);
    mProcess->start(strCatCpu);
    mProcess->waitForFinished();
    QByteArray info = mProcess->readAllStandardOutput();
    mProcess->close();
    int index = info.indexOf('\n');
    int len = info.length();
    QByteArray cpuInfo = info.right(len - index - 1);
    QByteArray simCpuInfo = cpuInfo.simplified();
    QList<QByteArray> list = simCpuInfo.split(' ');
    int cpurate = getCpuRate(mProcess);
    int memrate = list.at(3).toFloat();
    m_listRate.append(QVariant(cpurate));
    m_listRate.append(QVariant(memrate));
    emit listRateChanged(m_listRate);
}

void SystemUsageRate::stop()
{
    mRefreshTimer.stop();
}

void SystemUsageRate::start()
{
    mRefreshTimer.start();
}
