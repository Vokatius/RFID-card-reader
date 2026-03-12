#ifndef PUSH_INPUT_H
#define PUSH_INPUT_H

#include <array>
#include "Interfaces.h"

class Push_Button_Input : Input  {
    private:
        const std::array<uint8_t, 3> m_buttons;
        Buttons int_to_button(uint8_t btn);

    public:
        Push_Button_Input(uint8_t up_btn, uint8_t middle_btn, uint8_t down_btn);
        void init();
        Buttons block_until_button_press();
        Buttons get_button();
};

#endif
