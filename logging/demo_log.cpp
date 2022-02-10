/**
 * @file demo_log.cpp
 * @author junjun dong (dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-10-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "logging/log.h"
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/severity_logger.hpp>

void test_narrow_char_logging() {
    boost::log::sources::logger lg;
    BOOST_LOG(lg) << "Hello, World! This is a narrow character message";
}

void test_lvl_logging() {
    boost::log::sources::severity_channel_logger_mt<logging::severity_level> slg;
    // slg.add_attribute("Scope", boost::log::attributes::named_scope());
    BOOST_LOG_SCOPED_LOGGER_TAG(slg, "Module", " slog");
    // BOOST_LOG_SCOPED_THREAD_TAG("Module", "+++IMPORTANT_MESSAGE+++");
    // BOOST_LOG_NAMED_SCOPE("module");
    BOOST_LOG_FUNCTION();
    BOOST_LOG_SEV(slg, logging::FATAL) << "Fatal";
    BOOST_LOG_SEV(slg, logging::MAJOR) << "MAJOR";
    BOOST_LOG_SEV(slg, logging::MINOR) << "MINOR";
    BOOST_LOG_SEV(slg, logging::INFO) << "INFO";
    BOOST_LOG_SEV(slg, logging::CALL) << "CALL";
    BOOST_LOG_SEV(slg, logging::DATA) << "DATA";
    BOOST_LOG_SEV(slg, logging::CMD) << "CMD";
    BOOST_LOG_SEV(slg, logging::HEX) << "HEX";
    BOOST_LOG_SEV(slg, logging::IMG) << "IMG";
}

int main() {
    logging::logger::init();
    // test_narrow_char_logging();
    // BOOST_LOG_NAMED_SCOPE("module");
    // BOOST_LOG_SCOPED_LOGGER_TAG(slg, "Module", " slog");
    // BOOST_LOG_SCOPED_THREAD_TAG("Module", "***IMPORTANT_MESSAGE***");
    BOOST_LOG_FUNCTION();
    test_lvl_logging();
    return 0;
}
