#include "config_manager.h"
#include "../utils/utils.h"
#include <fstream>
#include <iostream>

ConfigManager::ConfigManager()
{
    m_marker_properties_.auto_start = false;
    m_marker_properties_.update_interval = 100;
    m_marker_properties_.type = "marker";

    m_marker_properties_.position = {4, 4};

    m_marker_properties_.marker.en = {10, "#FF0000", "circle"};
    m_marker_properties_.marker.zh = {10, "#00FF00", "circle"};

    m_marker_properties_.image.en = {"image/en/marker.png", 4};
    m_marker_properties_.image.zh = {"image/zh/marker.png", 4};

    m_marker_properties_.exclude = {};

    auto dir = get_executable_path();
    if (!dir.empty())
    {
        m_filename_ = dir + "/config.json";
    }
}

ConfigManager::~ConfigManager()
{
}

ConfigManager &ConfigManager::get_instance()
{
    static ConfigManager instance;
    return instance;
}

MarkerProperties ConfigManager::from_json(json j)
{
    MarkerProperties maker;
    maker.auto_start = j["auto_start"].get<bool>();
    maker.update_interval = j["update_interval"].get<int>();
    maker.type = j["type"].get<std::string>();

    maker.position.x = j["position"]["x"].get<int>();
    maker.position.y = j["position"]["y"].get<int>();

    maker.marker.en.width = j["marker"]["en"]["width"].get<int>();
    maker.marker.en.color = j["marker"]["en"]["color"].get<std::string>();
    maker.marker.en.shape = j["marker"]["en"]["shape"].get<std::string>();

    maker.marker.zh.width = j["marker"]["zh"]["width"].get<int>();
    maker.marker.zh.color = j["marker"]["zh"]["color"].get<std::string>();
    maker.marker.zh.shape = j["marker"]["zh"]["shape"].get<std::string>();

    maker.image.en.path = j["image"]["en"]["path"].get<std::string>();
    maker.image.en.width = j["image"]["en"]["width"].get<int>();

    maker.image.zh.path = j["image"]["zh"]["path"].get<std::string>();
    maker.image.zh.width = j["image"]["zh"]["width"].get<int>();

    maker.exclude = j["exclude"].get<std::vector<std::string>>();
    return maker;
}

json ConfigManager::to_json(MarkerProperties marker)
{
    json j;
    j["auto_start"] = marker.auto_start;
    j["update_interval"] = marker.update_interval;
    j["type"] = marker.type;

    j["position"]["x"] = marker.position.x;
    j["position"]["y"] = marker.position.y;

    j["marker"]["en"]["width"] = marker.marker.en.width;
    j["marker"]["en"]["color"] = marker.marker.en.color;
    j["marker"]["en"]["shape"] = marker.marker.en.shape;

    j["marker"]["zh"]["width"] = marker.marker.zh.width;
    j["marker"]["zh"]["color"] = marker.marker.zh.color;
    j["marker"]["zh"]["shape"] = marker.marker.zh.shape;

    j["image"]["en"]["path"] = marker.image.en.path;
    j["image"]["en"]["width"] = marker.image.en.width;

    j["image"]["zh"]["path"] = marker.image.zh.path;
    j["image"]["zh"]["width"] = marker.image.zh.width;

    j["exclude"] = marker.exclude;
    return j;
}

std::string ConfigManager::json_to_string(json j)
{
    std::string json_string = j.dump();
    return json_string;
}

std::string ConfigManager::struct_to_string(const MarkerProperties &marker)
{
    json j = to_json(marker);
    std::string json_string = j.dump();
    return json_string;
}

std::string ConfigManager::get_config_json_string() const
{
    return struct_to_string(m_marker_properties_);
}

void ConfigManager::set_config_from_json_string(std::string str)
{
    json j = json::parse(str);
    m_marker_properties_ = from_json(j);
    save_config();
}

void ConfigManager::load_config()
{
    try
    {
        std::ifstream file(m_filename_);
        if (!file.is_open())
        {
            save_config();
            return;
        }

        json j;
        file >> j;

        m_marker_properties_ = from_json(j);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to load configuration: " << e.what() << std::endl;
    }
}

void ConfigManager::save_config() const
{
    try
    {
        auto json_config = to_json(m_marker_properties_);
        std::ofstream file(m_filename_);
        if (!file.is_open())
        {
            std::cerr << "Unable to open file for writing: " << m_filename_ << std::endl;
            return;
        }

        file << json_config.dump(4);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to save configuration: " << e.what() << std::endl;
    }
}

MarkerProperties ConfigManager::get_marker_properties() const
{
    return m_marker_properties_;
}

void ConfigManager::set_marker_properties(const MarkerProperties &properties)
{
    m_marker_properties_ = properties;
}