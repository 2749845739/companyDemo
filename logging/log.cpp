/**
 * @file log.cpp
 * @author junjun dong (dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-10-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <fstream>
#include <locale>
#include <string>
#include <chrono>
#include <cstdlib>

#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/current_thread_id.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/expressions/attr.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>
#include <boost/log/expressions/keyword.hpp>
#include <boost/log/expressions/message.hpp>
#include <boost/log/expressions/predicates/has_attr.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/core/null_deleter.hpp>

#include "logging/log.h"
#include "logging/terminal.h"

namespace logging {

struct lvl_def {
  const char* key;
  severity_level val;
};

const lvl_def def[] = {
  {"FATAL", FATAL},
  {"MAJOR", MAJOR},
  {"MINOR", MINOR},
  {"INFO", INFO},
  {"CALL", CALL},
  {"DATA", DATA},
  {"CMD", CMD},
  {"HEX", HEX},
  {"IMG", IMG},
  {NULL}
};

template<typename CharT, typename TraitsT>
inline std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& strm, severity_level lvl) {
    static const char* const str[] = {
        GzRedBold "[F] " GzReset,
        GzYellowBold "[M] " GzReset,
        GzPurpleBold "[m] " GzReset,
        GzCyan "{I} " GzReset,
        GzLime"{C} " GzReset,
        GzBlue "{D} " GzReset,
        GzTeal"(e) " GzReset,
        GzNavy "(x) " GzReset,
        GzGreen "(i) " GzReset
    };
    if (static_cast<std::size_t>(lvl) < (sizeof(str) / sizeof(*str))) {
        strm << str[lvl];
    } else {
        strm << static_cast<int>(lvl);
    }
    return strm;
}

BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level)
BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime)
BOOST_LOG_ATTRIBUTE_KEYWORD(module, "Module", std::string)

bool logger::init(std::string log_path) {
  if (log_path.empty()) log_path = ".";
  boost::log::add_common_attributes();
  boost::shared_ptr<boost::log::core> lg_core = boost::log::core::get();
  lg_core->add_global_attribute("Scope", boost::log::attributes::named_scope());

  char* log_lvl = getenv("LOG_LVL");
  const lvl_def *p = def;
  severity_level l = DATA;
  if (log_lvl) {
    while (p && p->key) {
      if (0 == strcasecmp(log_lvl, p->key)) {
        l = p->val;
        break;
      }
      ++p;
    }
  }

  bool log_terminal = true;
  char* logt = getenv("LOG_TERM");
  if (logt && 0 == strcasecmp(logt, "OFF")) log_terminal = false;

  if (log_terminal) {
    // text ostream sink backend
    boost::shared_ptr<boost::log::sinks::text_ostream_backend> sbackend =
      boost::make_shared<boost::log::sinks::text_ostream_backend>();
    sbackend->add_stream(boost::shared_ptr<std::ostream>(&std::clog, boost::null_deleter()));

    std::time_t tcur = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char time_str[24] = {0};
    std::strftime(time_str, sizeof(time_str), "%Y-%m-%dT%H:%M:%S", std::localtime(&tcur));
    std::string log_file = log_path + "/" + std::string(time_str) + ".log";
    sbackend->add_stream(boost::shared_ptr<std::ostream>(new std::ofstream(log_file)));

    sbackend->auto_flush(true);
    boost::shared_ptr<text_stream_sink_t> ssink(new text_stream_sink_t(sbackend));

    ssink->imbue(boost::locale::generator()("en_US.UTF-8"));
    ssink->set_formatter(boost::log::expressions::stream
      << "" GzViolet << boost::log::expressions::format_date_time<
        boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f ")
#ifdef LOG_TID
      << "[" << boost::log::expressions::attr<
        boost::log::attributes::current_thread_id::value_type>("ThreadID") << "] "
#endif  // LOG_TID
      << severity.or_default(MAJOR)

      << boost::log::expressions::if_(boost::log::expressions::has_attr(module))
      [
          boost::log::expressions::stream << GzLimeBold "" << std::setw(8) << module
      ]
#ifdef LOG_SCOPE
      .else_
      [
        boost::log::expressions::stream << "" GzOrange
          << boost::log::expressions::format_named_scope(
            "Scope", boost::log::keywords::format = "%n (%f:%l) ", boost::log::keywords::depth = 1)
      ]
#endif  // LOG_SCOPE

      << GzReset " " << boost::log::expressions::smessage);

    ssink->set_filter(boost::log::expressions::attr<severity_level>("Severity") <= l);
    lg_core->add_sink(ssink);
  } else {
    // test file sink backend
    boost::shared_ptr<boost::log::sinks::text_file_backend> fbackend =
      boost::make_shared<boost::log::sinks::text_file_backend>(
        boost::log::keywords::target = log_path,
        boost::log::keywords::min_free_space = 200 * 1024 * 1024,
        boost::log::keywords::file_name = "p600.log",
        boost::log::keywords::target_file_name = log_path + "/p600_%Y-%m-%d_%3N.log",
        boost::log::keywords::rotation_size = 5 * 1024 * 1024);
    boost::shared_ptr<text_file_sink_t> fsink(new text_file_sink_t(fbackend));

    fsink->set_formatter(boost::log::expressions::stream
      << boost::log::expressions::format_date_time<
        boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f ")
      << "[" << boost::log::expressions::attr<
        boost::log::attributes::current_thread_id::value_type>("ThreadID") << "] "
      << severity.or_default(MAJOR)
      << boost::log::expressions::format_named_scope(
        "Scope", boost::log::keywords::format = "%n (%f:%l) ", boost::log::keywords::depth = 1)
      << boost::log::expressions::smessage);
    fsink->set_filter(boost::log::expressions::attr<severity_level>("Severity") <= l);
    lg_core->add_sink(fsink);
  }
  return true;
}

}  // namespace logging
