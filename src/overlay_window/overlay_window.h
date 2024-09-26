#pragma once

#include <windows.h>

class OverlayWindow {
public:
	OverlayWindow();
	~OverlayWindow();

	bool Create(HINSTANCE hInstance);
	void Show();
	void Hide();
	void UpdatePosition(const POINT& cursorPos);
	void Render();
	HDC GetDC();
	void ReleaseDC(HDC hdc);

private:
	HWND m_hwnd;
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};