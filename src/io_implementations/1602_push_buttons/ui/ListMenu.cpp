#include "io_implementations\1602_push_buttons\ui\ListMenu.h"
#include <memory>

ListMenu::ListMenu(int displayRows, std::vector<const char*> texts) {
    m_cursorPos = 0;
    m_displayRows = displayRows;
    m_menuTexts = texts;
}

int ListMenu::get_cursor_pos() {
    return m_cursorPos;
}

void ListMenu::move_up() {
    if(m_cursorPos + 1 <= m_menuTexts.size() - 1)
        m_cursorPos++;
    else
        m_cursorPos = 0;
}

void ListMenu::move_down() {
    if(m_cursorPos - 1 >= 0)
        m_cursorPos--;
    else
        m_cursorPos = m_menuTexts.size() - 1;
}

int ListMenu::select() {
    for(int i = 0; i < m_menuTexts.size(); i++)
        if(m_menuTexts[i] == m_menuTexts[m_cursorPos])
            return i;

    throw 1;
}

std::unique_ptr<const char*[]> ListMenu::get_display_items() {
    int page = m_cursorPos / m_displayRows;
    int firstEntry = page * m_displayRows;

     std::unique_ptr<const char*[]> values(new const char*[m_displayRows]);

    for(int i = firstEntry, cnt = 0; cnt < m_displayRows; i++, cnt++)
        values[cnt] = m_menuTexts[i];
    
    return values;
}
