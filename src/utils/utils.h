#pragma once

#include <filesystem>
#include <iostream>
#include <string>

inline std::string get_executable_path()
{
    const auto path = std::filesystem::current_path().string();
    return path;
}

inline std::string get_appdata_path()
{
    char *appDataRoaming = nullptr;
    std::string appDataPath;
    errno_t err = _dupenv_s(&appDataRoaming, nullptr, "APPDATA");
    if (err == 0 && appDataRoaming != nullptr)
    {
        appDataPath = appDataRoaming;
        free(appDataRoaming);
    }
    else
    {
        throw std::runtime_error("Could not retrieve APPDATA environment variable.");
    }
    return appDataPath;
}

inline std::string load_html_resource(const int resource_id)
{
    const HRSRC h_res = FindResource(nullptr, MAKEINTRESOURCE(resource_id), RT_HTML);
    if (h_res == nullptr)
        return "";

    const HGLOBAL h_data = LoadResource(nullptr, h_res);
    if (h_data == nullptr)
        return "";

    const DWORD data_size = SizeofResource(nullptr, h_res);
    const char* data = static_cast<const char*>(LockResource(h_data));

    std::string html_content(data, data_size);
    
    return html_content;
}