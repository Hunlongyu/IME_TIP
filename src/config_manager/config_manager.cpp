#include "config_manager.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

ConfigManager::ConfigManager()
{
    // Set default properties
    m_markerProperties.auto_start = false;
    m_markerProperties.update_interval = 100;
    m_markerProperties.type = "marker";

    m_markerProperties.position = {4, 4}; // Default position (x: 4, y: 4)

    // Set default marker properties
    m_markerProperties.marker.en = {10, "#FF0000", "circle"}; // English marker
    m_markerProperties.marker.zh = {10, "#00FF00", "circle"}; // Chinese marker

    // Set default image properties
    m_markerProperties.image.en = {"image/en/marker.png", 4};
    m_markerProperties.image.zh = {"image/zh/marker.png", 4};

    m_markerProperties.exclude = {};
}

ConfigManager::~ConfigManager()
{
}

bool ConfigManager::LoadConfig(const std::string &filename)
{
    try
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Unable to open config file: " << filename << std::endl;
            return false;
        }

        json j;
        file >> j;

        m_markerProperties.auto_start = j["auto_start"].get<bool>();
        m_markerProperties.update_interval = j["update_interval"].get<int>();
        m_markerProperties.type = j["type"].get<std::string>();

        m_markerProperties.position.x = j["position"]["x"].get<int>();
        m_markerProperties.position.y = j["position"]["y"].get<int>();

        m_markerProperties.marker.en.width = j["marker"]["en"]["width"].get<int>();
        m_markerProperties.marker.en.color = j["marker"]["en"]["color"].get<std::string>();
        m_markerProperties.marker.en.shape = j["marker"]["en"]["shape"].get<std::string>();

        m_markerProperties.marker.zh.width = j["marker"]["zh"]["width"].get<int>();
        m_markerProperties.marker.zh.color = j["marker"]["zh"]["color"].get<std::string>();
        m_markerProperties.marker.zh.shape = j["marker"]["zh"]["shape"].get<std::string>();

        m_markerProperties.image.en.path = j["image"]["en"]["path"].get<std::string>();
        m_markerProperties.image.en.width = j["image"]["en"]["width"].get<int>();

        m_markerProperties.image.zh.path = j["image"]["zh"]["path"].get<std::string>();
        m_markerProperties.image.zh.width = j["image"]["zh"]["width"].get<int>();

        // 如果 exclude 是一个空数组，直接解析为空的 vector
        m_markerProperties.exclude = j["exclude"].get<std::vector<std::string>>();

        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to load configuration: " << e.what() << std::endl;
        return false;
    }
}

bool ConfigManager::SaveConfig(const std::string &filename)
{
    try
    {
        json j;
        j["auto_start"] = m_markerProperties.auto_start;
        j["update_interval"] = m_markerProperties.update_interval;
        j["type"] = m_markerProperties.type;

        j["position"]["x"] = m_markerProperties.position.x;
        j["position"]["y"] = m_markerProperties.position.y;

        j["marker"]["en"]["width"] = m_markerProperties.marker.en.width;
        j["marker"]["en"]["color"] = m_markerProperties.marker.en.color;
        j["marker"]["en"]["shape"] = m_markerProperties.marker.en.shape;

        j["marker"]["zh"]["width"] = m_markerProperties.marker.zh.width;
        j["marker"]["zh"]["color"] = m_markerProperties.marker.zh.color;
        j["marker"]["zh"]["shape"] = m_markerProperties.marker.zh.shape;

        j["image"]["en"]["path"] = m_markerProperties.image.en.path;
        j["image"]["en"]["width"] = m_markerProperties.image.en.width;

        j["image"]["zh"]["path"] = m_markerProperties.image.zh.path;
        j["image"]["zh"]["width"] = m_markerProperties.image.zh.width;

        j["exclude"] = m_markerProperties.exclude;

        std::ofstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Unable to open file for writing: " << filename << std::endl;
            return false;
        }

        file << j.dump(4); // Use 4 spaces for indentation
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to save configuration: " << e.what() << std::endl;
        return false;
    }
}

MarkerProperties ConfigManager::GetMarkerProperties() const
{
    return m_markerProperties;
}

void ConfigManager::SetMarkerProperties(const MarkerProperties &properties)
{
    m_markerProperties = properties;
}