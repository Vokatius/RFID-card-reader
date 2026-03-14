#include "io_implementations/1602_push_buttons/ui-components/InputMenu.h"

#include "io_implementations/1602_push_buttons/ui-components/ui_helpers.h"
#include <Arduino.h>

#define MOVE_CURSOR '|'
#define CHANGE_CURSOR '#'

#define MENU_TEXT "cnfirm|MENU|back"
#define EDIT_TEXT "delete|EDIT|caps"
#define NAVIGATION_TEXT "left |NAV| right"
#define CHANGE_TEXT "up |LETTER| down"

void input_menu::toggle_mode() {
    if(m_cur_state == MENU) {
        m_cur_state = NAVIGATION;
        m_lower_output = NAVIGATION_TEXT;
    } else if(m_cur_state == NAVIGATION) {
        m_cur_state = CHANGE_LETTERS;
        m_lower_output = CHANGE_TEXT;
    } else if(m_cur_state == CHANGE_LETTERS) {
        m_cur_state = EDIT;
        m_lower_output = EDIT_TEXT;
    } else {
        m_cur_state = MENU;
        m_lower_output = MENU_TEXT;
    }
}

void input_menu::go_left() {
    if(m_cursor_pos == 0)
        m_cursor_pos = m_input_length - 1;
    else 
        m_cursor_pos--;
}

void input_menu::go_right() {
    if(m_cursor_pos == m_input_length - 1)
        m_cursor_pos = 0;
    else 
        m_cursor_pos++;
}

void input_menu::letter_down() {
    bool is_capital = m_input_text[m_cursor_pos] < 'a';
    uint8_t max_val = is_capital ? 'Z' : 'z';
    uint8_t min_val = is_capital ? 'A' : 'a';

    if(m_input_text[m_cursor_pos] == ' ') {
        m_input_text.begin()[m_cursor_pos] = char(max_val);
    } else if(m_input_text[m_cursor_pos] == min_val)
        m_input_text.begin()[m_cursor_pos] = char(max_val);
    else {
        m_input_text.begin()[m_cursor_pos] = char(--m_input_text[m_cursor_pos]);
    }
}

void input_menu::letter_up() {
    bool is_capital = m_input_text[m_cursor_pos] < 'a';

    uint8_t max_val = is_capital ? 'Z' : 'z';
    uint8_t min_val = is_capital ? 'A' : 'a';

    if(m_input_text[m_cursor_pos] == ' ') {
        m_input_text.begin()[m_cursor_pos] = char(min_val);
    } else if(m_input_text[m_cursor_pos] == max_val)
        m_input_text.begin()[m_cursor_pos] = char(min_val);
    else {
        m_input_text.begin()[m_cursor_pos] = char(++m_input_text[m_cursor_pos]);
    }
}

void input_menu::toggle_lettering() {
    if(m_input_text[m_cursor_pos] == ' ')
        return;

    bool is_capital = m_input_text[m_cursor_pos] < 'a';

    if(is_capital) {
        m_input_text.begin()[m_cursor_pos] += ('a' - 'A');
    } else {
        m_input_text.begin()[m_cursor_pos] -= ('a' - 'A');
    }
}

void input_menu::delete_char() {
    m_input_text.begin()[m_cursor_pos] = ' ';
}

std::array<std::string, 2> input_menu::format_input() {
    std::string no_cursor_text = std::string(m_input_text.c_str());
    
    auto space_pos = no_cursor_text.find(" ");
    while (space_pos != std::string::npos) {
        no_cursor_text.replace(space_pos, 1, "_");
        space_pos = no_cursor_text.find(" ");
    }    

    std::string cursor_text = std::string(no_cursor_text.c_str());

    cursor_text.begin()[m_cursor_pos] = m_cur_state == CHANGE_LETTERS ? CHANGE_CURSOR : MOVE_CURSOR;

    return std::array<std::string, 2>{ no_cursor_text, cursor_text };  
}

void input_menu::sanitize_input(bool append_spaces) {
    if(m_input_text.length() != 0) {
        auto first_char = m_input_text.find_first_not_of(' ');
        auto last_char = m_input_text.find_last_not_of(' ');
    
        if(first_char != std::string::npos && last_char != std::string::npos) {
            m_input_text = m_input_text.substr(first_char, last_char - first_char + 1);
            m_cursor_pos -= first_char;        
        }
    }    

    if(append_spaces)
        while(m_input_text.length() < m_input_length)
            m_input_text.append(" ");
}

exit_state input_menu::open_editor(const char* start_text) {
    m_input_text = start_text;
    m_lower_output = MENU_TEXT;

    while (true) {        
        m_display.write(0,1, m_lower_output.c_str());

        sanitize_input();
        auto upper_texts = format_input();

        Buttons btn;
        if(m_cur_state == CHANGE_LETTERS || m_cur_state == EDIT)
            btn = ui_helpers::toggle_row(m_display, m_buttons, 0, 1000, upper_texts[0].c_str(), upper_texts[1].c_str());
        else 
            btn = ui_helpers::toggle_row(m_display, m_buttons, 0, 1000, upper_texts[1].c_str(), upper_texts[0].c_str());

        switch(m_cur_state) {
            case MENU:
                if(btn == UP)
                    return CONFIRM;
                else if(btn == DOWN)
                    return ABORT;
                else
                    toggle_mode();
            break;

            case EDIT:
                if(btn == UP)
                    delete_char();
                else if(btn == DOWN)
                    toggle_lettering();
                else 
                    toggle_mode();
            break;

            case NAVIGATION:
                if(btn == UP)
                    go_left();
                else if(btn == DOWN)
                    go_right();
                else 
                    toggle_mode();
            break;

            case CHANGE_LETTERS:
                if(btn == UP)
                    letter_up();
                else if(btn == DOWN)
                    letter_down();
                else 
                    toggle_mode();
            break;
        }
    }
}

std::string input_menu::get_text() {
    sanitize_input(false);
    return std::string(m_input_text);
}