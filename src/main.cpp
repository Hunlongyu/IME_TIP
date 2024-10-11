#include "../resource.h"
#include "config_manager/config_manager.h"
#include "input_method/input_method.h"
#include "setting_viewer/setting_viewer.h"
#include "window_manager/window_manager.h"

#ifdef _WIN32
int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpCmdLine, int nCmdShow)
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
            MessageBoxW(nullptr, L"应用程序 IME_Tips 已经在运行!", L"提示", MB_OK);
            return 0;
        }
        hMutex = CreateMutexW(nullptr, FALSE, L"IME_Tips.exe");
    }
    catch (...)
    {
        return 0;
    }

    {
        // AllocConsole();
        // FILE *fp;
        // freopen_s(&fp, "CONOUT$", "w", stdout); // 重定向 stdout 到控制台
        // freopen_s(&fp, "CONOUT$", "w", stderr); // 重定向 stderr 到控制台
        // freopen_s(&fp, "CONIN$", "r", stdin);   // 重定向 stdin 到控制台
        // HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        // HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
        // SetConsoleMode(hOut, ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);
        // SetConsoleMode(hIn, ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT);
        // SetConsoleOutputCP(CP_UTF8);
        // SetConsoleCP(CP_UTF8);
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

    // MSG msg;
    // while (true)
    //{
    //     while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    //     {
    //         TranslateMessage(&msg);
    //         DispatchMessage(&msg);
    //         if (msg.message == WM_QUIT)
    //         {
    //             if (hMutex)
    //             {
    //                 CloseHandle(hMutex);
    //                 hMutex = nullptr;
    //             }
    //             return 0;
    //         }
    //     }

    //    /*InputMethod::get_instance().update_input_method_status();
    //    InputMethod::get_instance().get_text_cursor_position();
    //    Sleep(interval);*/
    //}
}