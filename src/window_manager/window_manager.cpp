#include "window_manager.h"
#include <stdexcept>

WindowManager* WindowManager::s_pWindowManager = nullptr;

WindowManager::WindowManager(HINSTANCE hInstance)
	: m_hInstance(hInstance), m_hwnd(nullptr) {
	s_pWindowManager = this;
}

WindowManager::~WindowManager() {
	s_pWindowManager = nullptr;
}

bool WindowManager::Initialize() {
	if (!RegisterWindowClass()) {
		return false;
	}

	if (!CreateMainWindow()) {
		return false;
	}

	return true;
}

void WindowManager::Run() {
	ShowWindow(m_hwnd, SW_SHOW);
	UpdateWindow(m_hwnd);

	MSG msg = {};
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK WindowManager::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	WindowManager* pThis = s_pWindowManager;

	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool WindowManager::RegisterWindowClass() {
	WNDCLASSEX wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.hInstance = m_hInstance;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = "CursorMarkerWindowClass";

	if (!RegisterClassEx(&wcex)) {
		throw std::runtime_error("Failed to register window class");
	}

	return true;
}

bool WindowManager::CreateMainWindow() {
	m_hwnd = CreateWindowEx(
		0, "CursorMarkerWindowClass", "Cursor Marker",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
		nullptr, nullptr, m_hInstance, nullptr);

	if (!m_hwnd) {
		throw std::runtime_error("Failed to create main window");
	}

	return true;
}