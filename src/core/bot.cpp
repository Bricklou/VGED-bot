#include "bot.hpp"

#include "spdlog/spdlog.h"
#include <fmt/format.h>
#include <functional>
#include <memory>

Bot::Builder::Builder() { _cluster = std::make_unique<dpp::cluster>(""); }

Bot::Builder &Bot::Builder::set_token(const std::string &token) {
  _cluster->token = token;

  _cluster->numshards = 1;
  _cluster->cluster_id = 0;
  _cluster->maxclusters = 1;

  _cluster->intents = dpp::intents::i_default_intents;
  return *this;
}

Bot::Builder &Bot::Builder::set_cluster(std::uint8_t max_shards,
                                        std::uint8_t cluster_id,
                                        std::uint8_t max_clusters) {
  _cluster->numshards = max_shards;
  _cluster->cluster_id = cluster_id;
  _cluster->maxclusters = max_clusters;
  return *this;
}

Bot::Builder &Bot::Builder::set_intents(dpp::intents intents) {
  _cluster->intents = dpp::intents::i_default_intents | intents;
  return *this;
}

Bot Bot::Builder::build() { return Bot(std::move(_cluster)); }

Bot::Bot(std::unique_ptr<dpp::cluster> cluster) : _cluster(std::move(cluster)) {
  // Links some events to the dispatcher
  _cluster->on_log(std::bind(&Bot::on_log, this, std::placeholders::_1));
  _cluster->on_ready(std::bind(&Bot::on_ready, this, std::placeholders::_1));
}

void Bot::on_log(const dpp::log_t &event) {
  switch (event.severity) {
  case dpp::ll_trace:
    SPDLOG_TRACE("{}", event.message);
    break;
  case dpp::ll_debug:
    SPDLOG_DEBUG("{}", event.message);
    break;
  case dpp::ll_info:
    SPDLOG_INFO("{}", event.message);
    break;
  case dpp::ll_warning:
    SPDLOG_WARN("{}", event.message);
    break;
  case dpp::ll_error:
    SPDLOG_ERROR("{}", event.message);
    break;
  case dpp::ll_critical:
  default:
    SPDLOG_CRITICAL("{}", event.message);
    break;
  }
}

void Bot::on_ready(const dpp::ready_t &ready) {
  _user = _cluster->me;
  // Increase the shard init counter
  _shard_init_count++;

  _cluster->log(
      dpp::ll_debug,
      fmt::format("on_ready({}/{})", _shard_init_count,
                  _cluster->numshards /
                      (_cluster->maxclusters ? _cluster->maxclusters : 1)));
}

dpp::snowflake Bot::get_id() const { return _user.id; }

void Bot::start() { _cluster->start(false); }