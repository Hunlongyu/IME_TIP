#pragma once

#include "../marker_renderer/marker_renderer.h"
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class ConfigManager
{
  public:
    static ConfigManager &get_instance();

    ConfigManager(const ConfigManager &) = delete;
    ConfigManager &operator=(const ConfigManager &) = delete;

    static MarkerProperties from_json(json j);
    static json to_json(MarkerProperties marker);

    static std::string json_to_string(json j);
    static std::string struct_to_string(const MarkerProperties &marker);

    std::string get_config_json_string() const;
    void set_config_from_json_string(std::string str);

    void load_config();
    void save_config() const;

    MarkerProperties get_marker_properties() const;
    void set_marker_properties(const MarkerProperties &properties);

  private:
    MarkerProperties m_marker_properties_;
    std::string m_filename_;

    ConfigManager();
    ~ConfigManager();
};