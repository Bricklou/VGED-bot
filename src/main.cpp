#include <csignal>
#include <exception>
#include <iostream>
#include <spdlog/spdlog.h>

#include "core/config/configuration.hpp"
#include "core/logger/logger.hpp"

/**
 * @brief Exit signal handler
 *
 * @param signum exit code
 */
void signal_handler(int signum) {
  SPDLOG_INFO("Stopping discord bot...");

  // Cleanup all registered loggers and flush all logs before shutdown
  spdlog::drop_all();
  spdlog::shutdown();

  exit(signum);
}

void register_signals() {
  std::signal(SIGINT, signal_handler);
  std::signal(SIGTERM, signal_handler);
  std::signal(SIGABRT, signal_handler);
  std::signal(SIGHUP, signal_handler);
}

int main() {
  logger::create_logger("VGED-bot");

  try {
    // Initialize configuration
    Configuration::init();
  } catch (const std::exception &e) {
    SPDLOG_CRITICAL("Failed to initialize configuration: {}", e.what());
    return 1;
  }

  SPDLOG_DEBUG("Hello world!");
}