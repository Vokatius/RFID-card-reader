#include "io_implementations\1602_push_buttons\d1602_button_io.h"

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

void D1602_Button_IO::init() { }