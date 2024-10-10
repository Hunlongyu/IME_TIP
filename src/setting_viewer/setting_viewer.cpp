#include "setting_viewer.h"
#include "../config_manager/config_manager.h"
#include <iostream>

SettingViewer::SettingViewer()
{
}

SettingViewer::~SettingViewer()
{
    if (m_wv)
    {
        delete m_wv;
        m_wv = nullptr;
    }
}

SettingViewer &SettingViewer::get_instance()
{
    static SettingViewer instance;
    return instance;
}

void SettingViewer::show()
{
    if (m_wv)
    {
        return;
    }
    m_wv = new webview::webview(true, nullptr);
    m_wv->set_title("IME_Tips 设置");
    m_wv->set_size(1280, 720, WEBVIEW_HINT_NONE);
    m_wv->navigate("https://baidu.com");
    m_wv->run();
    delete m_wv;
    m_wv = nullptr;
}

void SettingViewer::get_config() const
{
    if (!m_wv)
    {
        return;
    }
    m_wv->bind("get_config", [&](const std::string &req) -> std::string {
        auto str = ConfigManager::get_instance().get_config_json_string();
        return str;
    });
}

void SettingViewer::save_config() const
{
    if (!m_wv)
    {
        return;
    }
    m_wv->bind("save_config", [&](const std::string &req) -> std::string {
        ConfigManager::get_instance().set_config_from_json_string(req);
        return "true";
    });
}