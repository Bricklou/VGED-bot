#include "schema.hpp"
#include "nlohmann/json-schema.hpp"
#include "nlohmann/json_fwd.hpp"
#include <cstdlib>

using nlohmann::json_schema::json_validator;

static nlohmann::json config_schema = R"(
{
  "$schema": "https://json-schema.org/draft-07/schema#",
  "type": "object",
  "title": "VGED-bot configuration",
  "properties": {
      "token": {
        "type": "string",
        "description": "The token to use for the bot."
      }
  }
}
)"_json;

void config_validation::validate(nlohmann::json &config) {
  // Initialize the validator
  json_validator validator;

  // Ignore the token requirement if it has been provided from environment
  // variables
  // The environment variable will override the config file value
  const char *token = getenv("BOT_TOKEN");
  if (token != nullptr) {
    config["token"] = token;
  }

  // Load the schema
  validator.set_root_schema(config_schema);

  // Validate the configuration
  validator.validate(config);
}