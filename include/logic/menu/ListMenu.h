#ifndef LIST_MENU_H
#define LIST_MENU_H

#include <vector>
#include <memory>
#include <unordered_map>

class ListMenu
{
    private:
        std::vector<const char*> m_menuTexts{};
        int m_cursorPos{};
        int m_displayRows{};
    
    public:
        ListMenu(int displayRows, std::vector<const char*> texts);
        int get_cursor_pos();
        void move_up();
        void move_down();
        int select();
        std::unique_ptr<const char*[]> get_display_items();
};
#endif
