#pragma once

#include <string>
#include <vector>
#include <windows.h>

// Position结构体
struct Position
{
    int x;
    int y;
};

// Marker子结构体
struct Marker
{
    int width;
    std::string color;
    std::string shape;
};

// Image子结构体
struct Image
{
    std::string path;
    int width;
};

// MarkerProperties结构体
struct MarkerProperties
{
    bool auto_start = false;
    int update_interval = 0;
    std::string type;
    Position position;
    struct
    {
        Marker en;
        Marker zh;
    } marker;
    struct
    {
        Image en;
        Image zh;
    } image;
    std::vector<std::string> exclude;
};

class MarkerRenderer
{
  public:
    MarkerRenderer();
    ~MarkerRenderer();

    void RenderMarker(HDC hdc, const POINT &position, bool isChineseInput);
    void SetMarkerProperties(const MarkerProperties &properties);

  private:
    MarkerProperties m_properties;

    COLORREF ParseColor(const std::string &colorStr);
};