#ifndef GZ_LOGGER_H
#define GZ_LOGGER_H
#include "Logger.h"
#include <string.h>
namespace GZ_LOGGER {

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define LOGGER_DEBUG(format, ...) Logger::LogData(LOG_LEVEL_DEBUG,__FUNCTION__, __FILENAME__, __LINE__,format, ##__VA_ARGS__)
#define LOGGER_INFO(format, ...)  Logger::LogData(LOG_LEVEL_INFO, __FUNCTION__, __FILENAME__, __LINE__,format, ##__VA_ARGS__)
#define LOGGER_WARN(format, ...)  Logger::LogData(LOG_LEVEL_WARN, __FUNCTION__, __FILENAME__, __LINE__,format, ##__VA_ARGS__)
#define LOGGER_ERROR(format, ...) Logger::LogData(LOG_LEVEL_ERROR,__FUNCTION__, __FILENAME__, __LINE__,format, ##__VA_ARGS__)
#define LOGGER_FATAL(format, ...) Logger::LogData(LOG_LEVEL_FATAL, __FUNCTION__, __FILENAME__, __LINE__,format, ##__VA_ARGS__)
}

#endif // GZ_LOGGER_H
