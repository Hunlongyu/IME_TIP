#pragma once

class InputMethod
{
  public:
    static InputMethod &get_instance();

    InputMethod(const InputMethod &) = delete;
    InputMethod &operator=(const InputMethod &) = delete;

    void update_input_method_status();

    static void get_text_cursor_position();

    bool is_chinese_input() const;

  private:
    bool m_is_chinese_;

    InputMethod();
    ~InputMethod();
};
