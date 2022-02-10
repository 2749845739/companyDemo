/**
 * @file log.h
 * @author junjun dong (dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-10-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef LOGGING_LOG_H_
#define LOGGING_LOG_H_

#include <string>

#include <boost/locale/generator.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>

namespace logging {

enum severity_level {
    FATAL,
    MAJOR,
    MINOR,
    INFO,
    CALL,
    DATA,
    CMD,
    HEX,
    IMG,
};


typedef boost::log::sinks::synchronous_sink<
    boost::log::sinks::text_ostream_backend> text_stream_sink_t;

typedef boost::log::sinks::synchronous_sink<
    boost::log::sinks::text_file_backend> text_file_sink_t;

class logger {
 private:
    logger() {}

 public:
    static bool init(std::string log_path = ".");
};

// void init_log();

}  // namespace logging

#define log_fatal(lg) BOOST_LOG_SEV(lg, logging::FATAL)
#define log_major(lg) BOOST_LOG_SEV(lg, logging::MAJOR)
#define log_minor(lg) BOOST_LOG_SEV(lg, logging::MINOR)
#define log_info(lg) BOOST_LOG_SEV(lg, logging::INFO)
#define log_call(lg) BOOST_LOG_SEV(lg, logging::CALL)
#define log_data(lg) BOOST_LOG_SEV(lg, logging::DATA)
#define log_cmd(lg) BOOST_LOG_SEV(lg, logging::CMD)
#define log_hex(lg) BOOST_LOG_SEV(lg, logging::HEX)
#define log_img(lg) BOOST_LOG_SEV(lg, logging::IMG)

#endif  // LOGGING_LOG_H_
