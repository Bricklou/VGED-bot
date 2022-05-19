#pragma once

#include <cstdint>
#include <dpp/dpp.h>
#include <memory>

/**
 * @brief Wrapper for D++ cluster, it simplify the usage of the cluster itself
 * while running all the code
 */
class Bot {
  public:
    /**
     * @brief Builder to populate the dpp::cluster instance inside of the Bot.
     */
    struct Builder {
      public:
        Builder();

        /**
         * @brief Set the bot token
         *
         * @param token bot token
         * @return Builder& Builder object
         */
        Builder &set_token(const std::string &token);

        /**
         * @brief Set the cluster shards and cluster counts
         *
         * @param max_shards maximum shards per cluster
         * @param cluster_id current cluster id
         * @param max_clusters total clusters count
         * @return Builder& Builder object
         */
        Builder &set_cluster(std::uint8_t max_shards, std::uint8_t cluster_id,
                             std::uint8_t max_clusters);

        /**
         * @brief Set the bot intents
         *
         * @param intents intents the bot can to use
         * @return Builder& Builder object
         */
        Builder &set_intents(dpp::intents intents);

        /**
         * @brief Build the bot instance
         *
         * @return Bot bot instance
         */
        Bot build();

      private:
        /// Cluster instance
        std::unique_ptr<dpp::cluster> _cluster;
    };

    /**
     * @brief Access the bot cluster instance
     *
     * @return dpp::cluster& cluster instance
     */
    dpp::cluster &operator()();

    /**
     * @brief Start the bot
     */
    void start();

    /**
     * @brief Get the bot user id
     *
     * @return dpp::snowflake bot id
     */
    dpp::snowflake get_id() const;

  private:
    Bot(std::unique_ptr<dpp::cluster> cluster);
    Bot(const Bot &) = delete;
    Bot &operator=(const Bot &) = delete;

    ~Bot();

    dpp::user _user;
    std::unique_ptr<dpp::cluster> _cluster;
    /// The bot shard count
    uint32_t _shard_init_count = 0;

    bool _started = false;

    void on_log(const dpp::log_t &log);
    void on_ready(const dpp::ready_t &ready);
};