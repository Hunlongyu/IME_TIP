#pragma once

#include <windows.h>

class CursorTracker {
public:
	CursorTracker();
	~CursorTracker();

	void UpdateCursorPosition();
	POINT GetCursorPosition() const;
	HWND GetFocusedWindow() const;

private:
	POINT m_cursorPos;
	HWND m_focusedWindow;
};