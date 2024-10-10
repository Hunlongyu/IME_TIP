#pragma once

#include "webview/webview.h"

class SettingViewer
{
  public:
    static SettingViewer &get_instance();

    SettingViewer(const SettingViewer &) = delete;
    SettingViewer &operator=(const SettingViewer &) = delete;

    void show();

  private:
    webview::webview *m_wv{nullptr};

    SettingViewer();
    ~SettingViewer();
};