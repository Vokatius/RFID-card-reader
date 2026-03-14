#ifndef UI_HELPERS
#define UI_HELPERS

#include <vector>
#include "interfaces/rfid_reader.h"
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

    bool try_block_get_uid(Push_Button_Input& inp, IRfid_Reader& reader, std::vector<uint8_t>& out_uid);
}

#endif