#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

#include <shellapi.h>

#include <functional>
#include <string>
#include <vector>

class WindowManager
{
  public:
    WindowManager(HINSTANCE hInstance, const std::wstring &appName, const std::wstring &trayTooltip);
    ~WindowManager();

    void initialize();
    static void run(const std::function<void()> &callback);
    void set_show_callback(const std::function<void()> &callback);
    void set_exit_callback(const std::function<void()> &callback);
    void set_icon(HICON hIcon);

    HINSTANCE get_hinstance() const;

    HWND get_hwnd() const;

  private:
    struct MenuItem
    {
        UINT id;
        std::wstring text;
        std::function<void()> callback;
    };

    static LRESULT CALLBACK wnd_proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
    LRESULT handle_message(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param) const;
    void initialize_tray();
    void show_tray_menu() const;

    HINSTANCE m_hInstance;
    HWND m_hwnd;
    std::wstring m_appName;
    std::wstring m_trayTooltip;
    NOTIFYICONDATAW m_nid;
    HMENU m_hPopMenu;
    std::vector<MenuItem> m_menuItems;
    std::function<void()> m_showCallback;
    std::function<void()> m_exitCallback;

    static const UINT WM_TRAYICON = WM_USER + 1;
};