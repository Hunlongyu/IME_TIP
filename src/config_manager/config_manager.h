#pragma once

#include "../marker_renderer/marker_renderer.h"
#include <string>
#include <windows.h>

class ConfigManager
{
  public:
    ConfigManager();
    ~ConfigManager();

    bool LoadConfig(const std::string &filename);
    bool SaveConfig(const std::string &filename);
    MarkerProperties GetMarkerProperties() const;
    void SetMarkerProperties(const MarkerProperties &properties);

  private:
    MarkerProperties m_markerProperties;
};