#include "Push_Button_Input.h"
#include <Arduino.h>

Push_Button_Input::Push_Button_Input(uint8_t up_btn, uint8_t middle_btn, uint8_t down_btn) 
: m_buttons({ up_btn, middle_btn, down_btn}) { };

void Push_Button_Input::init() {
    for(int btn : m_buttons)
        pinMode(btn, INPUT_PULLUP);
}

Buttons Push_Button_Input::int_to_button(uint8_t btn) {
    if(btn == -1)
        return Buttons::NONE;

    if(btn == m_buttons[0])
        return Buttons::UP;

    if(btn == m_buttons[1])
        return Buttons::UP;

    if(btn == m_buttons[2])
        return Buttons::UP;

    //TODO: Error handling
    throw 1;
};

Buttons Push_Button_Input::get_button() {
    int press = -1;   
    for(int btn : m_buttons) {
        if(digitalRead(btn) == LOW){
            press = btn;
        }
    }

    return int_to_button(press);
};

Buttons Push_Button_Input::block_until_button_press() {
    int press = -1;
    while (press == -1) {
        for(int btn : m_buttons) {
            if(digitalRead(btn) == LOW){
                press = btn;
            }
        }
    }

    return int_to_button(press);
};