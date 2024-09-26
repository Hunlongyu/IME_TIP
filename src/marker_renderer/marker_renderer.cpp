#include "marker_renderer.h"

MarkerRenderer::MarkerRenderer() {
	// Default properties
	m_properties.colorEnglish = RGB(255, 0, 0);  // Red
	m_properties.colorChinese = RGB(0, 255, 0);  // Green
	m_properties.size = 10;
	m_properties.offsetX = 5;
	m_properties.offsetY = -15;
}

MarkerRenderer::~MarkerRenderer() {}

void MarkerRenderer::RenderMarker(HDC hdc, const POINT& position, bool isChineseInput) {
	HBRUSH hBrush = CreateSolidBrush(isChineseInput ? m_properties.colorChinese : m_properties.colorEnglish);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	int x = position.x + m_properties.offsetX;
	int y = position.y + m_properties.offsetY;

	if (isChineseInput) {
		Rectangle(hdc, x, y, x + m_properties.size, y + m_properties.size);
	}
	else {
		Ellipse(hdc, x, y, x + m_properties.size, y + m_properties.size);
	}

	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
}

void MarkerRenderer::SetMarkerProperties(const MarkerProperties& properties) {
	m_properties = properties;
}