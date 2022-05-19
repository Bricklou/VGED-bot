#pragma once

#include <string>

#include <spdlog/spdlog.h>

namespace logger {
  void create_logger(const std::string &name);
}