#ifndef D1602_BUTTON_IO
#define D1602_BUTTON_IO

#include "hardware\display\Display_I2C.h"
#include "hardware\input\Push_Button_Input.h"
#include "services\io_service_base.h"

class D1602_Button_IO : public IO_Service_Base {
    private:
        Display_I2C& m_display;
        Push_Button_Input& m_buttons;

    public:
        D1602_Button_IO(IRfid_Reader& reader, Display_I2C& display, Auth_Service& auth, Push_Button_Input& buttons, uint8_t max_name_len);
        void init();
};

#endif