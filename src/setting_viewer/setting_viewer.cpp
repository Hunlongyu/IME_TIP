#include "setting_viewer.h"

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