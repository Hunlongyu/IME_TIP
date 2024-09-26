#include "cursor_tracker.h"

CursorTracker::CursorTracker() : m_cursorPos{ 0, 0 }, m_focusedWindow(nullptr) {}

CursorTracker::~CursorTracker() {}

void CursorTracker::UpdateCursorPosition() {
	GetCursorPos(&m_cursorPos);
	m_focusedWindow = GetForegroundWindow();

	HWND childWindow = ChildWindowFromPoint(m_focusedWindow, m_cursorPos);
	if (childWindow != nullptr) {
		m_focusedWindow = childWindow;
	}

	RECT windowRect;
	GetWindowRect(m_focusedWindow, &windowRect);
	m_cursorPos.x -= windowRect.left;
	m_cursorPos.y -= windowRect.top;
}

POINT CursorTracker::GetCursorPosition() const {
	return m_cursorPos;
}

HWND CursorTracker::GetFocusedWindow() const {
	return m_focusedWindow;
}