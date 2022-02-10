/**
 * @file Logger.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Logger.h"
#include <QTextEncoder>

struct log_lvl {
  const char* key;
  Log4Qt::Level::Value val;
};

const log_lvl lvl_def[] = {
  {"FATAL", Log4Qt::Level::Value::FATAL_INT},
  {"MAJOR", Log4Qt::Level::Value::ERROR_INT},
  {"MINOR", Log4Qt::Level::Value::WARN_INT},
  {"INFO", Log4Qt::Level::Value::INFO_INT},
  {"CALL", Log4Qt::Level::Value::DEBUG_INT},
  {"DATA", Log4Qt::Level::Value::TRACE_INT},
  {"CMD", Log4Qt::Level::Value::ALL_INT},
  {"HEX", Log4Qt::Level::Value::NULL_INT},
  {"IMG", Log4Qt::Level::Value::OFF_INT},
  {NULL}
};

Logger::Logger() {
  // 使用 rootLogger 打印日志
  logger = Log4Qt::Logger::rootLogger();

  // 创建一个 TTCCLayout（输出时间、线程、Logger 以及消息内容）
  Log4Qt::TTCCLayout *layout = new Log4Qt::TTCCLayout();
  layout->setName("My Layout");
  layout->setCategoryPrefixing(false);    // 禁用 logger 名称
  layout->setContextPrinting(false);      // 禁用嵌套的上下文信息
  layout->setThreadPrinting(false);       // 禁用线程名
  layout->setDateFormat("yyyy-MM-dd hh:mm:ss");
  layout->activateOptions();

  // 日志等级设置
  char* lvl = getenv("LOG_LVL");
  const log_lvl *p = lvl_def;
  Log4Qt::Level::Value l = Log4Qt::Level::Value::DEBUG_INT;
  if (lvl) {
    while (p && p->key) {
      if (0 == strcasecmp(lvl, p->key)) {
        l = p->val;
        break;
      }
      ++p;
    }
  }

  bool log_terminal = false;
  char* logt = getenv("LOG_TERMINAL");
  if (logt && 0 == strcasecmp(logt, "ON")) log_terminal = true;

  // 创建一个 ConsoleAppender（将日志内容输出到控制台上）
  if (log_terminal) {
    Log4Qt::ConsoleAppender *appenderConsole = new Log4Qt::ConsoleAppender();
    appenderConsole->setName("My Appender");
    appenderConsole->setLayout(layout);
    appenderConsole->setEncoding(QTextCodec::codecForName("UTF-8"));      // 设置编码
    appenderConsole->setTarget(Log4Qt::ConsoleAppender::STDOUT_TARGET);   // 输出到 stdout
    appenderConsole->setImmediateFlush(true);  // 立即刷新
    appenderConsole->setThreshold(l);
    appenderConsole->activateOptions();
    logger->addAppender(appenderConsole);
  }

  // 创建一个 RollingFileAppender（滚动多个文件）
  Log4Qt::RollingFileAppender *appender = new Log4Qt::RollingFileAppender();
  appender->setName("My Appender");
  appender->setLayout(layout);
  appender->setFile(QApplication::applicationDirPath() + "/logs/log.out");
  appender->setImmediateFlush(true);  // 立即刷新
  appender->setThreshold(l);
  appender->setAppendFile(true);      // 追加的方式
  appender->setMaxFileSize("10mb");   // 在滚动之前设置文件的最大大小
  appender->setMaxBackupIndex(5);     // 设置备份索引
  appender->activateOptions();

  // 在 logger 上添加 appender
  logger->addAppender(appender);

  logger->setLevel(l);
}

Logger::~Logger() {
  // 关闭 logger
  // logger->removeAllAppenders();
  // logger->loggerRepository()->shutdown();
}

void Logger::LogData(
    IFLY_LOG_LEVEL logLevel,
    const char* function,
    const char* file,
    int line, const char *format, ...) {
  char buf[LOG_BUF_MAX_LEN] = { 0x0 };
  va_list arg_ptr;
  // memset(buf, 0x0, sizeof(buf));

  va_start(arg_ptr, format);
  int ret = vsnprintf(buf, sizeof(buf), format, arg_ptr);
  va_end(arg_ptr);

  if ((ret < 0) || (ret >= LOG_BUF_MAX_LEN)) {
      exit(-1);
      return;
    }

  int nArgsLen = strlen(buf);
#ifdef _WIN32
  _snprintf(buf + nArgsLen, sizeof(buf) - nArgsLen - 1, " [%s()] [%s:%d]", function, file, line);
#else
  snprintf(buf + nArgsLen, sizeof(buf) - nArgsLen - 1, " [%s()] [%s:%d]", function, file, line);
#endif
  if (Logger::GetInstance()!= nullptr) {
      switch (logLevel) {
        case LOG_LEVEL_DEBUG:
          Logger::GetInstance()->logger->debug(buf);
          break;
        case LOG_LEVEL_INFO:
          Logger::GetInstance()->logger->info(buf);
          break;
        case LOG_LEVEL_WARN:
          Logger::GetInstance()->logger->warn(buf);
          break;
        case LOG_LEVEL_ERROR:
          Logger::GetInstance()->logger->error(buf);
          break;
        case LOG_LEVEL_FATAL:
          Logger::GetInstance()->logger->fatal(buf);
          break;
        default:
          break;
        }
    }
}

Log4Qt::Logger * Logger::getLogger() {
  return logger;
}

void Logger::d(QVariant msg) {
  Logger::GetInstance()->logger->debug(msg.toString());
}

Logger * Logger::m_pInstance = NULL;
