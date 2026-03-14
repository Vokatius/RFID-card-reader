#ifndef INPUT_MENU
#define INPUT_MENU

#include "hardware\display\Display_I2C.h"
#include "hardware\input\Push_Button_Input.h"
#include <string>
#include <array>

enum input_mode {
    MENU,
    EDIT,
    NAVIGATION,
    CHANGE_LETTERS,
};

enum exit_state {
    CONFIRM,
    ABORT
};

class input_menu {
    private:
        Display_I2C& m_display;
        Push_Button_Input& m_buttons;
        uint8_t m_input_length;
        std::string m_input_text;
        uint8_t m_cursor_pos = 0;
        input_mode m_cur_state;
        std::string m_lower_output = "";
        void toggle_mode();
        void go_left();
        void go_right();
        void letter_up();
        void letter_down();
        void toggle_lettering();
        void delete_char();
        std::array<std::string, 2> format_input();
        void sanitize_input(bool append_spaces = true);
    public:
        input_menu(uint8_t input_length, Display_I2C& display, Push_Button_Input& buttons)
        : m_input_length(input_length), m_display(display), m_buttons(buttons), m_cur_state(MENU) { };
        exit_state open_editor(const char* start_text);
        std::string get_text();
};

#endif