#pragma once

#include <windows.h>

class WindowManager {
public:
	WindowManager(HINSTANCE hInstance);
	~WindowManager();

	bool Initialize();
	void Run();

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE m_hInstance;
	HWND m_hwnd;
	static WindowManager* s_pWindowManager;

	bool RegisterWindowClass();
	bool CreateMainWindow();
};