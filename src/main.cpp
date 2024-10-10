﻿#include "../resource.h"
#include "config_manager/config_manager.h"
#include "setting_viewer/setting_viewer.h"
#include "window_manager/window_manager.h"

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
#else
int main()
{
#endif
    HANDLE hMutex;
    try
    {
        hMutex = OpenMutexW(MUTEX_ALL_ACCESS, FALSE, L"IME_Tips.exe");
        if (hMutex != nullptr)
        {
            MessageBoxW(nullptr, L"应用程序已经在运行!", L"提示", MB_OK);
            return 0;
        }
        hMutex = CreateMutexW(nullptr, FALSE, L"IME_Tips.exe");
    }
    catch (...)
    {
        return 0;
    }

    ConfigManager::get_instance().load_config();

    WindowManager windowManager(hInst, L"IME_Tips", L"输入法中英文状态提示");

    windowManager.initialize();

    HICON hIcon = LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_APP_ICON));
    windowManager.set_icon(hIcon);

    windowManager.set_show_callback([] { SettingViewer::get_instance().show(); });

    windowManager.set_exit_callback([] { SettingViewer::get_instance().close(); });

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (hMutex)
    {
        CloseHandle(hMutex);
        hMutex = nullptr;
    }
    return 0;
}