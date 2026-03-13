#ifndef LIST_MENU_H
#define LIST_MENU_H

#include <vector>
#include <memory>
#include <string>
#include <functional>

struct Menu_Item {
    std::string text;
    std::function<void()> action;
};

class ListMenu
{
    private:
        std::vector<Menu_Item> m_menu_actions;
        uint8_t m_cursorPos;
        uint8_t m_displayRows;
        void set_selector(uint8_t from, uint8_t to);
    
    public:
        ListMenu(uint8_t displayRows, std::vector<Menu_Item> menu_actions);
        void move_up(const char** out_displayed_rows);
        void move_down(const char** out_displayed_rows);
        void get_displayed_texts(const char** out_displayed_rows);
        uint8_t get_cursor_pos();
        void select();
};
#endif
