#include "overlay_window.h"
#include <stdexcept>

OverlayWindow::OverlayWindow() : m_hwnd(nullptr) {}

OverlayWindow::~OverlayWindow() {
	if (m_hwnd) {
		DestroyWindow(m_hwnd);
	}
}

bool OverlayWindow::Create(HINSTANCE hInstance) {
	WNDCLASSEX wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.lpszClassName = "CursorMarkerOverlayClass";

	if (!RegisterClassEx(&wcex)) {
		throw std::runtime_error("Failed to register overlay window class");
	}

	m_hwnd = CreateWindowEx(
		WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED,
		"CursorMarkerOverlayClass", "",
		WS_POPUP,
		0, 0, 1, 1,
		nullptr, nullptr, hInstance, nullptr);

	if (!m_hwnd) {
		throw std::runtime_error("Failed to create overlay window");
	}

	SetLayeredWindowAttributes(m_hwnd, RGB(255, 255, 255), 0, LWA_COLORKEY);

	return true;
}

void OverlayWindow::Show() {
	ShowWindow(m_hwnd, SW_SHOW);
}

void OverlayWindow::Hide() {
	ShowWindow(m_hwnd, SW_HIDE);
}

void OverlayWindow::UpdatePosition(const POINT& cursorPos) {
	SetWindowPos(m_hwnd, HWND_TOPMOST, cursorPos.x, cursorPos.y, 20, 20, SWP_NOACTIVATE);
}

void OverlayWindow::Render() {
	InvalidateRect(m_hwnd, nullptr, TRUE);
	UpdateWindow(m_hwnd);
}

HDC OverlayWindow::GetDC() {
	return ::GetDC(m_hwnd);
}

void OverlayWindow::ReleaseDC(HDC hdc) {
	::ReleaseDC(m_hwnd, hdc);
}

LRESULT CALLBACK OverlayWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
	}
	return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}