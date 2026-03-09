#include "Input.h"
#include <Arduino.h>

Input::Input(std::vector<int> buttons) {
    this->buttons = buttons;

    for(int btn : buttons)
        pinMode(btn, INPUT_PULLUP);
};

int Input::get_button() {
    int press = -1;   
    for(int btn : buttons) {
        if(digitalRead(btn) == LOW){
            press = btn;
        }
    }

    return press;
};