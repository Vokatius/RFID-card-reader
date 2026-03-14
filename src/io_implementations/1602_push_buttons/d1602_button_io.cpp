#include "io_implementations\1602_push_buttons\d1602_button_io.h"

#include "utils/rfid_helpers.h"
#include "Arduino.h"
#include "io_implementations/1602_push_buttons/ui-components/ui_helpers.h"
#include "io_implementations/1602_push_buttons/ui-components/InputMenu.h"

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

        std::vector<uint8_t> uid = {};
        while(m_buttons.get_button() == NONE) {
            if(m_reader.try_get_auth(&uid)) {
                m_display.write(0,0, rfid_helpers::uid_to_string(uid).c_str());
            }
        }            
    };

    std::vector<Menu_Item> main_menu_items = {
        Menu_Item{"authenticate", [this]() { this->find_user_menu(); }},
        Menu_Item{"register user", [this]() { this->register_user_menu(); }},
        Menu_Item{"delete user", [this]() { this->delete_user_menu(); }},
        Menu_Item{"change user", [this]() { this->change_user_submenu(); }},
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

void D1602_Button_IO::find_user_menu() {
    m_display.write(0,0, "Scan your chip");
    m_display.write(0,1, "Press to abort");

    std::vector<uint8_t> uid = {};
    Buttons inp = NONE;
    while (inp == NONE && uid.size() == 0)
    {
        inp = m_buttons.get_button();
        m_reader.try_get_auth(&uid);
    }

    if(!m_auth.is_registered(uid)) {
        m_display.write(0,0, "Chip not found");
        m_display.write(0,1, "Press to cntinue");
        m_buttons.block_until_button_press();
        return;
    }

    User u = m_auth.get_user(uid);

    m_display.write(0,0, "Authenticated!");
    
    String temp_str = "Hello, ";
    temp_str.concat(u.name.substr(0,8).c_str());
    ui_helpers::toggle_row(m_display, m_buttons, 1, 1500, temp_str.c_str(), "Press to cntinue");
}

void D1602_Button_IO::register_user_menu() {
    m_display.write(0,0, "Scan a new chip");
    m_display.write(0,1, "Press to abort");

    std::vector<uint8_t> uid = {};
    Buttons inp = NONE;
    while (inp == NONE && uid.size() == 0)
    {
        inp = m_buttons.get_button();
        m_reader.try_get_auth(&uid);
    }

    if(inp != NONE ||uid.size() == 0)
        return;
    
    if(m_auth.is_registered(uid)) {
        m_display.write(0,0, "Chip blocked");
        m_display.write(0,1, "Press to return");
        m_buttons.block_until_button_press();
        return;
    }

    m_display.write(0,0, "Found chip!");
    ui_helpers::toggle_row(m_display, m_buttons, 1, 1500, rfid_helpers::uid_to_string(uid).c_str(), "Press to cntinue");

    input_menu input{m_max_name_length, m_display, m_buttons};
    auto result = input.open_editor("");

    if(result != CONFIRM || input.get_text().size() == 0){
        m_display.write(0,0, "Cancelled the");
        ui_helpers::toggle_row(m_display, m_buttons, 1, 1500, "registration", "Press to cntinue");
        return;
    }

    m_auth.register_user(User{input.get_text(), uid});

    String temp_str = String(input.get_text().substr(0, 8).c_str());
    temp_str.concat(" is now");
    m_display.write(0,0, temp_str);
    ui_helpers::toggle_row(m_display, m_buttons, 1, 1500, "registered", "Press to cntinue");
}

void D1602_Button_IO::delete_user_menu() {
    m_display.write(0,0, "Scan your chip");
    m_display.write(0,1, "Press to abort");

    std::vector<uint8_t> uid = {};
    Buttons inp = NONE;
    while (inp == NONE && uid.size() == 0)
    {
        inp = m_buttons.get_button();
        m_reader.try_get_auth(&uid);
    }

    if(!m_auth.is_registered(uid)) {
        m_display.write(0,0, "Chip not found");
        m_display.write(0,1, "Press to cntinue");
        m_buttons.block_until_button_press();
        return;
    }

    m_auth.delete_user(uid);

    m_display.write(0,0, "Deleted!");
    m_display.write(0,1, "Press to cntinue");
    m_buttons.block_until_button_press();
}


void D1602_Button_IO::change_user_submenu() {
    std::vector<Menu_Item> change_menu_items = {
        Menu_Item{"change name", [this]() { this->change_user_name_menu(); }},
        Menu_Item{"change card", [this]() { this->change_user_chip_menu(); }},
        Menu_Item{"back", [this]() { }},
    };
    auto menu = ListMenu(DISPLAY_ROWS, change_menu_items);

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
                if(menu.get_cursor_pos() != 2)
                    menu.select();
                
                return;                

            default:
                throw 1;
        }        
    }
}

void D1602_Button_IO::change_user_name_menu() {
    m_display.write(0,0, "Scan your chip");
    m_display.write(0,1, "Press to abort");

    std::vector<uint8_t> uid = {};
    Buttons inp = NONE;
    while (inp == NONE && uid.size() == 0)
    {
        inp = m_buttons.get_button();
        m_reader.try_get_auth(&uid);
    }

    if(!m_auth.is_registered(uid)) {
        m_display.write(0,0, "Chip not found");
        m_display.write(0,1, "Press to cntinue");
        m_buttons.block_until_button_press();
        return;
    }

    User u = m_auth.get_user(uid);

    input_menu input{m_max_name_length, m_display, m_buttons};
    auto result = input.open_editor(u.name.c_str());

    if(result != CONFIRM || input.get_text().size() == 0){
        m_display.write(0,0, "Cancelled the");
        ui_helpers::toggle_row(m_display, m_buttons, 1, 1500, "name change", "Press to cntinue");
        return;
    }

    m_auth.update_user(uid, User{input.get_text(), uid});

    String temp_str = String(input.get_text().substr(0, 8).c_str());
    temp_str.concat(" is now");
    m_display.write(0,0, temp_str);
    ui_helpers::toggle_row(m_display, m_buttons, 1, 1500, "your new name", "Press to cntinue");
}

void D1602_Button_IO::change_user_chip_menu() {
    m_display.write(0,0, "Scan old chip");
    m_display.write(0,1, "Press to abort");

    std::vector<uint8_t> old_uid = {};
    Buttons inp = NONE;
    while (inp == NONE && old_uid.size() == 0)
    {
        inp = m_buttons.get_button();
        m_reader.try_get_auth(&old_uid);
    }

    if(inp != NONE ||old_uid.size() == 0)
        return;

    if(!m_auth.is_registered(old_uid)) {
        m_display.write(0,0, "Chip not found");
        m_display.write(0,1, "Press to cntinue");
        m_buttons.block_until_button_press();
        return;
    }

    m_display.write(0,0, "Scan new chip");
    m_display.write(0,1, "Press to abort");

    std::vector<uint8_t> new_uid = {};
    inp = NONE;
    while (inp == NONE && new_uid.size() == 0)
    {
        inp = m_buttons.get_button();
        m_reader.try_get_auth(&new_uid);
    }

    if(inp != NONE ||new_uid.size() == 0)
        return;

    if(m_auth.is_registered(new_uid)) {
        m_display.write(0,0, "Chip blocked");
        m_display.write(0,1, "Press to cntinue");
        m_buttons.block_until_button_press();
        return;
    }

    User u = m_auth.get_user(old_uid);
    m_auth.update_user(old_uid, User{u.name, new_uid});

    m_display.write(0,0, "Changed card");
    m_display.write(0,1, "Press to cntinue");
    m_buttons.block_until_button_press();
}
