#pragma once

#include "webview/webview.h"

class SettingViewer
{
  public:
    static SettingViewer &get_instance();

    SettingViewer(const SettingViewer &) = delete;
    SettingViewer &operator=(const SettingViewer &) = delete;

    void show();

    void close();

    void get_config() const;

    void save_config() const;

  private:
    webview::webview *m_wv{nullptr};

    SettingViewer();
    ~SettingViewer();
};