#include "logger.hpp"
#include "spdlog/common.h"
#include "spdlog/sinks/sink.h"
#include <vector>

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include <memory>
#include <spdlog/async.h>
#include <spdlog/async_logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

void logger::create_logger(const std::string &name) {

  // Create console logger sink
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

  // Create a new logger
  spdlog::init_thread_pool(1024, 1);
  auto logger = std::make_shared<spdlog::async_logger>(
      name, console_sink, spdlog::thread_pool(),
      spdlog::async_overflow_policy::block);

  // Set the default log level
  logger->set_level(spdlog::level::trace);

  // Set the pattern for the logger (like the default one but with more colors)
  logger->set_pattern(
      "\u001b[90m[%Y-%m-%d %T.%e] [thread %t]\u001b[39m "
      "[\u001b[33m%n\u001b[39m] [%^%l%$] \u001b[90m[%@]\u001b[39m %v");

  // Set our new logger as the default one
  spdlog::set_default_logger(logger);
  spdlog::set_level(spdlog::level::trace);
}