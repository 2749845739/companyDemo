#pragma once
#include <log4qt/logger.h>
#include <log4qt/ttcclayout.h>
#include <log4qt/rollingfileappender.h>
#include <log4qt/loggerrepository.h>
#include "log4qt/logger.h"
#include <log4qt/consoleappender.h>
#include <QApplication>
#define LOG_BUF_MAX_LEN 1024

typedef enum IFLY_LOG_LEVEL_enum
{
  LOG_LEVEL_DEBUG,
  LOG_LEVEL_INFO,
  LOG_LEVEL_WARN,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_FATAL
}IFLY_LOG_LEVEL;

class Logger:public QObject
{
    Q_OBJECT
public:

  Logger();
  ~Logger();
  static void LogData(IFLY_LOG_LEVEL logLevel,const char* function, const char* file, int line,const char* format, ...);
  static Logger* GetInstance()
  {
    if (m_pInstance == nullptr)
      m_pInstance = new Logger();
    return m_pInstance;
  }

  Log4Qt::Logger * getLogger();
  Q_INVOKABLE void d(QVariant);
private:
  static Logger *m_pInstance;
  Log4Qt::Logger *logger;
};


