#include "marker_renderer.h"
#include <iomanip>
#include <sstream>

MarkerRenderer::MarkerRenderer()
{
    // 默认属性设置
    m_properties.auto_start = false;
    m_properties.update_interval = 100;
    m_properties.type = "marker";
    m_properties.position = {0, 0};
    m_properties.marker.en = {10, "#FF0000", "circle"};
    m_properties.marker.zh = {10, "#00FF00", "square"};
    m_properties.image.en = {"", 0};
    m_properties.image.zh = {"", 0};
}

MarkerRenderer::~MarkerRenderer()
{
}

void MarkerRenderer::RenderMarker(HDC hdc, const POINT &position, bool isChineseInput)
{
    const Marker &marker = isChineseInput ? m_properties.marker.zh : m_properties.marker.en;
    const Image &image = isChineseInput ? m_properties.image.zh : m_properties.image.en;

    int x = position.x + m_properties.position.x;
    int y = position.y + m_properties.position.y;

    // 渲染图像（如果有）
    if (!image.path.empty())
    {
        // 这里应该添加加载和绘制图像的代码
        // 由于Windows API的限制，这里只是一个占位符
        // 实际实现可能需要使用GDI+或其他图像处理库
        // DrawImage(hdc, image.path, x, y, image.width, image.width);
    }
    else
    {
        // 如果没有图像，则渲染形状标记
        COLORREF color = ParseColor(marker.color);
        HBRUSH hBrush = CreateSolidBrush(color);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

        if (marker.shape == "square")
        {
            Rectangle(hdc, x, y, x + marker.width, y + marker.width);
        }
        else
        { // 默认为圆形
            Ellipse(hdc, x, y, x + marker.width, y + marker.width);
        }

        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
    }
}

void MarkerRenderer::SetMarkerProperties(const MarkerProperties &properties)
{
    m_properties = properties;
}

COLORREF MarkerRenderer::ParseColor(const std::string &colorStr)
{

    if (colorStr[0] == '#' && colorStr.length() == 7)
    {
        int r, g, b;
        std::istringstream(colorStr.substr(1, 2)) >> std::hex >> r;
        std::istringstream(colorStr.substr(3, 2)) >> std::hex >> g;
        std::istringstream(colorStr.substr(5, 2)) >> std::hex >> b;
        return RGB(r, g, b);
    }
    return RGB(0, 0, 0); // 默认黑色
}