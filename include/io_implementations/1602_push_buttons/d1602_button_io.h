#ifndef D1602_BUTTON_IO
#define D1602_BUTTON_IO

#include "hardware\display\Display_I2C.h"
#include "hardware\input\Push_Button_Input.h"
#include "services\io_service_base.h"

class D1602_Button_IO : IO_Service_Base<Push_Button_Input, Display_I2C> {

};

#endif