#include <filesystem>
#include <windows.h>
#include <stdexcept>
#include <memory>
#include "window_manager/window_manager.h"
#include "cursor_tracker/cursor_tracker.h"
#include "overlay_window/overlay_window.h"
#include "input_method_detector/input_method_detector.h"
#include "marker_renderer/marker_renderer.h"
#include "config_manager/config_manager.h"

// 全局变量
std::unique_ptr<WindowManager> g_windowManager;
std::unique_ptr<CursorTracker> g_cursorTracker;
std::unique_ptr<OverlayWindow> g_overlayWindow;
std::unique_ptr<InputMethodDetector> g_inputMethodDetector;
std::unique_ptr<MarkerRenderer> g_markerRenderer;
std::unique_ptr<ConfigManager> g_configManager;

// 函数声明
bool InitializeApplication(HINSTANCE hInstance);
void CleanupApplication();
void UpdateAndRender();

// 主函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	try {
		if (!InitializeApplication(hInstance)) {
			return 1;
		}

		// 主消息循环
		MSG msg = {};
		while (GetMessage(&msg, nullptr, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			UpdateAndRender();
		}

		CleanupApplication();
		return static_cast<int>(msg.wParam);
	}
	catch (const std::exception& e) {
		MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONERROR);
		return 1;
	}
}

// 初始化应用程序
bool InitializeApplication(HINSTANCE hInstance) {
	// 初始化配置管理器
	g_configManager = std::make_unique<ConfigManager>();
	const auto& filename = std::filesystem::current_path().string() + "/config.json";
	if (!g_configManager->LoadConfig(filename)) {
		MessageBoxA(nullptr, "Failed to load configuration.", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	// 初始化窗口管理器
	g_windowManager = std::make_unique<WindowManager>(hInstance);
	if (!g_windowManager->Initialize()) {
		MessageBoxA(nullptr, "Failed to initialize window manager.", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	// 初始化光标跟踪器
	g_cursorTracker = std::make_unique<CursorTracker>();

	// 初始化输入法检测器
	g_inputMethodDetector = std::make_unique<InputMethodDetector>();

	// 初始化标记渲染器
	g_markerRenderer = std::make_unique<MarkerRenderer>();
	g_markerRenderer->SetMarkerProperties(g_configManager->GetMarkerProperties());

	// 初始化覆盖窗口
	g_overlayWindow = std::make_unique<OverlayWindow>();
	if (!g_overlayWindow->Create(hInstance)) {
		MessageBoxA(nullptr, "Failed to create overlay window.", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}

// 清理应用程序资源
void CleanupApplication() {
	g_overlayWindow.reset();
	g_markerRenderer.reset();
	g_inputMethodDetector.reset();
	g_cursorTracker.reset();
	g_windowManager.reset();
	g_configManager.reset();
}

// 更新应用程序状态并渲染
void UpdateAndRender() {
	// 更新光标位置
	g_cursorTracker->UpdateCursorPosition();
	POINT cursorPos = g_cursorTracker->GetCursorPosition();
	HWND focusedWindow = g_cursorTracker->GetFocusedWindow();

	// 更新输入法状态
	g_inputMethodDetector->UpdateInputMethodStatus(focusedWindow);
	bool isChineseInput = g_inputMethodDetector->IsChineseInput();

	// 更新覆盖窗口位置
	g_overlayWindow->UpdatePosition(cursorPos);

	// 渲染标记
	HDC hdc = g_overlayWindow->GetDC();
	g_markerRenderer->RenderMarker(hdc, cursorPos, isChineseInput);
	g_overlayWindow->ReleaseDC(hdc);

	// 刷新覆盖窗口
	g_overlayWindow->Render();
}