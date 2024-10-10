#include "input_method.h"
#include <Windows.h>
#include <imm.h>
#include <iostream>

#pragma comment(lib, "imm32.lib")

InputMethod &InputMethod::get_instance()
{
    static InputMethod instance;
    return instance;
}

InputMethod::InputMethod()
{
}

InputMethod::~InputMethod()
{
}

void InputMethod::update_input_method_status()
{
    const HWND win = GetForegroundWindow();
    if (!win)
    {
        return;
    }

    const DWORD thread_id = GetWindowThreadProcessId(win, nullptr);
    std::cout << "thread_id: " << thread_id << std::endl;
    if (!thread_id)
    {
        return;
    }

    const HIMC im = ImmGetContext(win);
    if (!im)
    {
        return;
    }

    DWORD conversion, sentence;
    if (ImmGetConversionStatus(im, &conversion, &sentence))
    {
        if (conversion & IME_CMODE_NATIVE)
        {
            m_is_chinese_ = true;
        }
        else
        {
            m_is_chinese_ = false;
        }

        std::cout << "m_is_chinese: " << m_is_chinese_ << std::endl;
    }
    ImmReleaseContext(win, im);
}

void InputMethod::get_text_cursor_position()
{
    const HWND win = GetForegroundWindow();
    if (!win)
    {
        return;
    }

    POINT caretPos;
    if (GetCaretPos(&caretPos))
    {
        auto x = caretPos.x;
        auto y = caretPos.y;
        std::cout << "文本光标位置: (" << caretPos.x << ", " << caretPos.y << ")" << std::endl;
    }
}

bool InputMethod::is_chinese_input() const
{
    return m_is_chinese_;
}
