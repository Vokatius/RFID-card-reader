#include "io_implementations\1602_push_buttons\d1602_button_io.h"

#include "Arduino.h"

#define DISPLAY_ROWS 2

D1602_Button_IO::D1602_Button_IO(
    IRfid_Reader& reader, 
    Display_I2C& display, 
    Auth_Service& auth,
    Push_Button_Input& buttons, 
    uint8_t max_name_len
) : IO_Service_Base(reader, auth, max_name_len), 
    m_display(display),
    m_buttons(buttons) 
{ }

void D1602_Button_IO::init() { 
    show_main_menu();
}

void D1602_Button_IO::show_main_menu() { 
    auto debug = [this]() {
        m_display.write(0,0, "");
        m_display.write(0, 1, "Click to return");

        String uid_str = "";
        std::vector<uint8_t> uid = {};
        while(m_buttons.get_button() == NONE) {
            if(m_reader.try_get_auth(&uid)) {
                uid_str = "";
                for(int i = 0; i < uid.size(); i++) {
                    uid_str.concat(uid[i]);
                    if(i+1 != uid.size())
                        uid_str.concat("-");
                }
                m_display.write(0,0, uid_str);
            }
        }            
    };

    std::vector<Menu_Item> main_menu_items = {
        Menu_Item{"auth.. user", [this]() { this->authenticate_user_menu(); }},
        Menu_Item{"find by chip", [this]() { this->find_user_menu(); }},
        Menu_Item{"register user", [this]() { this->register_user_menu(); }},
        Menu_Item{"change user", [this]() { this->change_user_menu(); }},
        Menu_Item{"delete user", [this]() { this->delete_user_menu(); }},
        Menu_Item{"debug", debug }
    };
    auto menu = ListMenu(DISPLAY_ROWS, main_menu_items);

    const char* texts[DISPLAY_ROWS];
    Buttons pressed_btn;

    menu.get_displayed_texts(texts);
    while(true) {
        for(int i = 0; i < DISPLAY_ROWS; i++) {
            m_display.write(0, i, texts[i]);
        }
        
        pressed_btn = m_buttons.block_until_button_press();
        
        switch (pressed_btn)
        {
            case UP:
                menu.move_up(texts);
                break;
            case DOWN:
                menu.move_down(texts);
                break;
            case CENTER:
                menu.select();
                break;

            default:
                throw 1;
        }        
    }
};

void D1602_Button_IO::authenticate_user_menu() {

}

void D1602_Button_IO::find_user_menu() {

}

void D1602_Button_IO::register_user_menu() {

}

void D1602_Button_IO::change_user_menu() {

}

void D1602_Button_IO::delete_user_menu() {

}