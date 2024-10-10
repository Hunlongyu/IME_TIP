#include "window_manager.h"
#include "../../resource.h"
#include <iostream>

WindowManager::WindowManager(HINSTANCE hInstance, const std::wstring &appName, const std::wstring &trayTooltip)
    : m_hInstance(hInstance), m_appName(appName), m_trayTooltip(trayTooltip), m_hwnd(nullptr), m_hPopMenu(nullptr)
{
}

WindowManager::~WindowManager()
{
    if (m_hPopMenu)
    {
        DestroyMenu(m_hPopMenu);
    }
    Shell_NotifyIconW(NIM_DELETE, &m_nid);
}

void WindowManager::initialize()
{
    WNDCLASSEXW wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = wnd_proc;
    wc.hInstance = m_hInstance;
    wc.lpszClassName = m_appName.c_str();
    RegisterClassExW(&wc);

    m_hwnd = CreateWindowExW(0, m_appName.c_str(), m_appName.c_str(), 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, m_hInstance,
                             this);
    initialize_tray();
}

void WindowManager::initialize_tray()
{
    m_nid = {0};
    m_nid.cbSize = sizeof(NOTIFYICONDATAW);
    m_nid.hWnd = m_hwnd;
    m_nid.uID = 1;
    m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    m_nid.uCallbackMessage = WM_TRAYICON;
    m_nid.hIcon = LoadIcon(nullptr, MAKEINTRESOURCE(IDI_APP_ICON));
    wcsncpy_s(m_nid.szTip, L"IME_Tips\n输入法中英文状态提示", ARRAYSIZE(m_nid.szTip) - 1);
    m_nid.szTip[ARRAYSIZE(m_nid.szTip) - 1] = L'\0';

    Shell_NotifyIconW(NIM_ADD, &m_nid);

    m_hPopMenu = CreatePopupMenu();
    m_menuItems.push_back({1, L"设置", [this]() {
                               if (m_showCallback)
                               {
                                   m_showCallback();
                               }
                           }});
    m_menuItems.push_back({2, L"退出", [this]() {
                               if (m_exitCallback)
                               {
                                   m_exitCallback();
                               }
                               PostQuitMessage(0);
                               ExitProcess(0);
                           }});

    for (const auto &item : m_menuItems)
    {
        AppendMenuW(m_hPopMenu, MF_STRING, item.id, item.text.c_str());
    }
}

void WindowManager::run(const std::function<void()> &callback)
{
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        callback();
    }
}

void WindowManager::set_show_callback(const std::function<void()> &callback)
{
    m_showCallback = callback;
}

void WindowManager::set_exit_callback(const std::function<void()> &callback)
{
    m_exitCallback = callback;
}

void WindowManager::set_icon(HICON hIcon)
{
    m_nid.hIcon = hIcon;
    Shell_NotifyIconW(NIM_MODIFY, &m_nid);
}

HINSTANCE WindowManager::get_hinstance() const
{
    return m_hInstance;
}

HWND WindowManager::get_hwnd() const
{
    return m_hwnd;
}

LRESULT CALLBACK WindowManager::wnd_proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    WindowManager *pThis;
    if (message == WM_NCCREATE)
    {
        pThis = static_cast<WindowManager *>(reinterpret_cast<CREATESTRUCT *>(lParam)->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    else
    {
        pThis = reinterpret_cast<WindowManager *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (pThis)
    {
        return pThis->handle_message(hwnd, message, wParam, lParam);
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT WindowManager::handle_message(const HWND hwnd, const UINT message, const WPARAM w_param,
                                      const LPARAM l_param) const
{
    switch (message)
    {
    case WM_TRAYICON: {
        if (l_param == WM_RBUTTONUP)
        {
            show_tray_menu();
        }
        else if (l_param == WM_LBUTTONDBLCLK)
        {
            if (m_showCallback)
            {
                m_showCallback();
            }
        }
        break;
    }
    case WM_COMMAND: {
        UINT id = LOWORD(w_param);
        for (const auto &item : m_menuItems)
        {
            if (item.id == id)
            {
                item.callback();
                break;
            }
        }
        break;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
        break;
    }
    case WM_CLOSE: {
        std::cout << "lala";
        break;
    }
    default:
        return DefWindowProc(hwnd, message, w_param, l_param);
    }
    return 0;
}

void WindowManager::show_tray_menu() const
{
    POINT pt;
    GetCursorPos(&pt);
    SetForegroundWindow(m_hwnd);
    TrackPopupMenu(m_hPopMenu, TPM_RIGHTALIGN | TPM_BOTTOMALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, 0, m_hwnd, nullptr);
    PostMessage(m_hwnd, WM_NULL, 0, 0);
}