#include "../resource.h"
#include "webview/webview.h"
#include "window_manager/window_manager.h"
#include <filesystem>

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

    WindowManager windowManager(hInst, L"IME_Tips", L"输入法中英文状态提示");

    windowManager.initialize();

    HICON hIcon = LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_APP_ICON));
    windowManager.set_icon(hIcon);

    windowManager.set_show_callback([] {
        webview::webview w(false, nullptr);
        w.set_title("Basic Example");
        w.set_size(1080, 720, WEBVIEW_HINT_NONE);

        /*wchar_t rawPathName[MAX_PATH] = { 0 };
        GetModuleFileNameW(NULL, rawPathName, MAX_PATH);
        std::string executablePath = std::filesystem::path(rawPathName).parent_path().string();
        w.navigate("file://" + executablePath + "/srv/index.html");*/

        w.navigate("file:///H:/Temp/so/html/index.html");
        w.run();
    });

    windowManager.set_exit_callback([]() {});

    windowManager.run();

    if (hMutex)
    {
        CloseHandle(hMutex);
        hMutex = nullptr;
    }
    return 0;
}