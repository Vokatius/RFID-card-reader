#ifndef UI_HELPERS
#define UI_HELPERS

#include "hardware/display/Display_I2C.h"
#include "hardware/input/Push_Button_Input.h"

namespace ui_helpers {
    Buttons toggle_row(Display_I2C& display, 
                    Push_Button_Input& inp, 
                    uint8_t row, 
                    uint16_t switch_time, 
                    const char* first_text, 
                    const char* second_text
    );
}

#endif