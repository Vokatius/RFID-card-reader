#include "io_implementations\1602_push_buttons\ui-components\ListMenu.h"
#include <memory>
#include <cmath>
#include <array>
#include "Arduino.h"

#define SELECTOR '*'
#define SPACE ' '

ListMenu::ListMenu(uint8_t displayRows, std::vector<Menu_Item> menu_actions) 
: m_cursorPos(0), m_displayRows(displayRows) { 
    m_menu_actions = {};

    std::string temp_str;
    for(auto item : menu_actions) {
        temp_str = "  ";
        item.text =  temp_str.append(item.text);
        m_menu_actions.push_back(item);
    }

    m_menu_actions[0].text.begin()[0] = SELECTOR;
}

void ListMenu::get_displayed_texts(const char** out_displayed_rows) {
    uint8_t start_pos = (std::ceil(double(m_cursorPos + 1) / m_displayRows) - 1) * m_displayRows;

    for(int i = 0, j = start_pos; i < m_displayRows; i++, j++) {
        if(j < m_menu_actions.size())
            out_displayed_rows[i] = m_menu_actions[j].text.c_str();
        else 
            out_displayed_rows[i] = "";
    }    
}

void ListMenu::move_up(const char** out_displayed_rows) {
    if(m_cursorPos + 1 <= m_menu_actions.size() - 1) {
        set_selector(m_cursorPos, m_cursorPos + 1);
        m_cursorPos++;
    }
    else {
        set_selector(m_cursorPos, 0);
        m_cursorPos = 0;
    }

    if(out_displayed_rows != nullptr)
        get_displayed_texts(out_displayed_rows);
}

void ListMenu::move_down(const char** out_displayed_rows) {
    if(m_cursorPos - 1 >= 0) {
        set_selector(m_cursorPos, m_cursorPos - 1);
        m_cursorPos--;
    }
    else {
        set_selector(m_cursorPos, m_menu_actions.size() - 1);
        m_cursorPos = m_menu_actions.size() - 1;
    }

    if(out_displayed_rows != nullptr)
        get_displayed_texts(out_displayed_rows);
}

void ListMenu::select() {
    m_menu_actions[m_cursorPos].action();
}

uint8_t ListMenu::get_cursor_pos() {
    return m_cursorPos;
}

void ListMenu::set_selector(uint8_t from, uint8_t to) {
    m_menu_actions[from].text.begin()[0] = SPACE;
    m_menu_actions[to].text.begin()[0] = SELECTOR;
}