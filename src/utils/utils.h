#pragma once

#include <filesystem>
#include <string>

inline std::string get_executable_path()
{
    const auto path = std::filesystem::current_path().string();
    return path;
}

inline std::string get_appdata_path()
{
    char* appDataRoaming = nullptr;
    std::string appDataPath;
    errno_t err = _dupenv_s(&appDataRoaming, nullptr, "APPDATA");
    if (err == 0 && appDataRoaming != nullptr) {
        appDataPath = appDataRoaming;
        free(appDataRoaming);
    } else {
        throw std::runtime_error("Could not retrieve APPDATA environment variable.");
    }
    return appDataPath;
}