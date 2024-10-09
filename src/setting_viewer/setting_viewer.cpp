#include "setting_viewer.h"

// 私有构造函数
SettingViewer::SettingViewer()
{
    m_wv = new webview::webview(true, nullptr);
    m_wv->set_title("IME_Tips 设置");
    m_wv->set_size(1080, 720, WEBVIEW_HINT_NONE);
}

// 私有析构函数
SettingViewer::~SettingViewer()
{
    delete m_wv;
    m_wv = nullptr;
}

void SettingViewer::show()
{
    m_wv->navigate("https://baidu.com");
    m_wv->run();
}