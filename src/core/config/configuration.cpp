#include "configuration.hpp"

#include "schema.hpp"
#include "spdlog/spdlog.h"
#include <fstream>

nlohmann::json default_config = {
    {"token", ""},
};

Configuration *Configuration::_instance = nullptr;

void Configuration::init() {
  if (_instance == nullptr) {
    _instance = new Configuration();
  }
}

Configuration::Configuration() {
  _config_path = std::filesystem::current_path() / "config.json";

  // If the config file does not exist, create it
  if (!std::filesystem::exists(_config_path)) {
    // Create parent directories
    std::filesystem::create_directories(_config_path.parent_path());
  } else {
    this->load_from_file();
  }

  // If the config is empty, just initialize it with the default one
  if (_config.empty()) {
    _config = default_config;
    this->save_to_file();
  }

  config_validation::validate(_config);
}

Configuration *Configuration::instance() { return _instance; }

void Configuration::load_from_file() {
  std::ifstream i{_config_path};
  _config = nlohmann::json::parse(i, nullptr, true, true);
  i.close();
}

void Configuration::save_to_file() {
  std::ofstream o{_config_path};
  o << _config.dump(2);
  o.close();
}