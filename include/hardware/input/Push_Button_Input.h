#ifndef PUSH_INPUT_H
#define PUSH_INPUT_H

#include <array>
#include "interfaces/input.h"

class Push_Button_Input : public IInput  {
    private:
        const std::array<uint8_t, 3> m_buttons;
        Buttons int_to_button(uint8_t btn);

    public:
        Push_Button_Input(uint8_t upBtn, uint8_t middleBtn, uint8_t downBtn);
        void init();
        Buttons block_until_button_press();
        Buttons get_button();
};

#endif
