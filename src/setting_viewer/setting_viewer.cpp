#include "setting_viewer.h"

// ˽�й��캯��
SettingViewer::SettingViewer()
{
    m_wv = new webview::webview(true, nullptr);
    m_wv->set_title("IME_Tips ����");
    m_wv->set_size(1080, 720, WEBVIEW_HINT_NONE);
}

// ˽����������
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