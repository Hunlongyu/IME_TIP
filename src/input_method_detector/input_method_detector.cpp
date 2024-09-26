#include "input_method_detector.h"
#include <imm.h>

#pragma comment(lib, "imm32.lib")

InputMethodDetector::InputMethodDetector() : m_isChineseInput(false) {}

InputMethodDetector::~InputMethodDetector() {}

bool InputMethodDetector::IsChineseInputMethod(HWND hwnd) {
	HIMC hIMC = ImmGetContext(hwnd);
	if (hIMC) {
		HKL hKL = GetKeyboardLayout(GetWindowThreadProcessId(hwnd, nullptr));
		DWORD dwConversion = 0, dwSentence = 0;

		if (ImmGetConversionStatus(hIMC, &dwConversion, &dwSentence)) {
			ImmReleaseContext(hwnd, hIMC);
			return (PRIMARYLANGID(LOWORD(hKL)) == LANG_CHINESE) && (dwConversion & IME_CMODE_NATIVE);
		}

		ImmReleaseContext(hwnd, hIMC);
	}
	return false;
}

void InputMethodDetector::UpdateInputMethodStatus(HWND hwnd) {
	m_isChineseInput = IsChineseInputMethod(hwnd);
}

bool InputMethodDetector::IsChineseInput() const {
	return m_isChineseInput;
}