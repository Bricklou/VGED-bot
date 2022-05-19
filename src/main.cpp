#include <iostream>

#include "core/logger/logger.hpp"

int main() {
  logger::create_logger("VGED-bot");
  SPDLOG_DEBUG("Hello world!");
}