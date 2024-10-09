#pragma once

#include "webview/webview.h"

class SettingViewer
{
  public:
    SettingViewer();
    ~SettingViewer();

    void show();

  private:
    webview::webview *m_wv{nullptr};
};