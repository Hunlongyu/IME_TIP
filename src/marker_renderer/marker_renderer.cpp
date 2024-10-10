#include "marker_renderer.h"
#include <iomanip>
#include <sstream>

MarkerRenderer::MarkerRenderer()
{
    // 默认属性设置
    m_properties_.auto_start = false;
    m_properties_.update_interval = 100;
    m_properties_.type = "marker";
    m_properties_.position = {0, 0};
    m_properties_.marker.en = {10, "#FF0000", "circle"};
    m_properties_.marker.zh = {10, "#00FF00", "square"};
    m_properties_.image.en = {"", 0};
    m_properties_.image.zh = {"", 0};
}

MarkerRenderer::~MarkerRenderer()
{
}

void MarkerRenderer::render_marker(HDC hdc, const POINT &position, bool is_chinese_input)
{
    const Marker &marker = is_chinese_input ? m_properties_.marker.zh : m_properties_.marker.en;
    const Image &image = is_chinese_input ? m_properties_.image.zh : m_properties_.image.en;

    int x = position.x + m_properties_.position.x;
    int y = position.y + m_properties_.position.y;

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
        COLORREF color = parse_color(marker.color);
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

void MarkerRenderer::set_marker_properties(const MarkerProperties &properties)
{
    m_properties_ = properties;
}

COLORREF MarkerRenderer::parse_color(const std::string &color_str)
{

    if (color_str[0] == '#' && color_str.length() == 7)
    {
        int r, g, b;
        std::istringstream(color_str.substr(1, 2)) >> std::hex >> r;
        std::istringstream(color_str.substr(3, 2)) >> std::hex >> g;
        std::istringstream(color_str.substr(5, 2)) >> std::hex >> b;
        return RGB(r, g, b);
    }
    return RGB(0, 0, 0); // 默认黑色
}