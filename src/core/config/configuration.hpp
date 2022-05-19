#pragma once

#include "nlohmann/json_fwd.hpp"
#include <filesystem>
#include <nlohmann/json.hpp>

class Configuration {
  public:
    static void init();
    static Configuration *instance();

    static nlohmann::json &JSON() { return _instance->_config; }

  private:
    Configuration();
    Configuration(const Configuration &) = delete;
    Configuration &operator=(const Configuration &) = delete;

    static Configuration *_instance;

    nlohmann::json _config;
    std::filesystem::path _config_path{};

    void load_from_file();
    void save_to_file();
};