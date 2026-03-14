#include "io_implementations/1602_push_buttons/ui-components/ui_helpers.h"

namespace ui_helpers {
    Buttons toggle_row(Display_I2C& display, 
                    Push_Button_Input& inp, 
                    uint8_t row, 
                    uint16_t switch_time, 
                    const char* first_text, 
                    const char* second_text
    ) {
        display.write(0,row, first_text);

        int16_t timer = 0;
        bool has_written = false;
        Buttons input = NONE;
        while(input == NONE) {
            if(timer > switch_time && !has_written) {
                display.write(0,row, second_text);            
                has_written = true;
            } else if(timer > switch_time * 2) {
                display.write(0,row, first_text);
                timer = 0;
                has_written = false;
            }
            delay(50);
            timer += 50;
            
            input = inp.get_button();
        }

        return input;
    }
}
