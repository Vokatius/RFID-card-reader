#include "ListMenu.h"
#include <memory>

ListMenu::ListMenu(int display_rows, std::vector<const char*> texts) {
    m_cur_cursor_pos = 0;
    m_display_rows = display_rows;
    m_menu_texts = texts;
}

int ListMenu::get_cursor_pos() {
    return m_cur_cursor_pos;
}

void ListMenu::move_up() {
    if(m_cur_cursor_pos + 1 <= m_menu_texts.size() - 1)
        m_cur_cursor_pos++;
    else
        m_cur_cursor_pos = 0;
}

void ListMenu::move_down() {
    if(m_cur_cursor_pos - 1 >= 0)
        m_cur_cursor_pos--;
    else
        m_cur_cursor_pos = m_menu_texts.size() - 1;
}

int ListMenu::select() {
    for(int i = 0; i < m_menu_texts.size(); i++)
        if(m_menu_texts[i] == m_menu_texts[m_cur_cursor_pos])
            return i;
}

std::unique_ptr<const char*[]> ListMenu::get_display_items() {
    int page = m_cur_cursor_pos / m_display_rows;
    int first_entry = page * m_display_rows;

     std::unique_ptr<const char*[]> values(new const char*[m_display_rows]);

    for(int i = first_entry, cnt = 0; cnt < m_display_rows; i++, cnt++)
        values[cnt] = m_menu_texts[i];
    
    return values;
}