#pragma once

#include <nlohmann/json-schema.hpp>

namespace config_validation {
  void validate(nlohmann::json &config);
};