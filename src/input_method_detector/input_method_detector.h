#pragma once

#include <windows.h>

class InputMethodDetector {
public:
	InputMethodDetector();
	~InputMethodDetector();

	bool IsChineseInputMethod(HWND hwnd);
	void UpdateInputMethodStatus(HWND hwnd);
	bool IsChineseInput() const;

private:
	bool m_isChineseInput;
};