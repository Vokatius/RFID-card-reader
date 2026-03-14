#include <Arduino.h>

#include "SPI.h"

#include "services/auth_service.h"
#include "services/io_service_base.h"

#include "storage/NVS_User_Storage.h"

#include "interfaces/rfid_reader.h"
#include "interfaces/user_persistence.h"

#include "hardware/display/Display_I2C.h"
#include "hardware/rfid/Rfid_SPI_Reader.h"
#include "hardware/input/Push_Button_Input.h"

#include "io_implementations/1602_push_buttons/d1602_button_io.h"

#define BTN_UP_PIN 17
#define BTN_MIDDLE_PIN 16
#define BTN_DOWN_PIN 4

#define LCD_ROWS 2
#define LCD_COLS 16
#define LCD_I2C_Addr 0x27

#define RFID_SPI_RST_PIN 0
#define RFID_SPI_SS_PIN 5

#define MAX_NAME_LEN 8

Display_I2C lcd(LCD_COLS, LCD_ROWS, LCD_I2C_Addr);
Push_Button_Input input(BTN_UP_PIN, BTN_MIDDLE_PIN, BTN_DOWN_PIN);

NVS_User_Storage storage(MAX_NAME_LEN);
Rfid_SPI_Reader rfid(RFID_SPI_RST_PIN, RFID_SPI_SS_PIN);

Auth_Service auth_service(storage);
D1602_Button_IO io_service(rfid, lcd, auth_service, input, MAX_NAME_LEN);

void setup() {
    Serial.begin(9600);
    SPI.begin();

    lcd.init();
    storage.init();
    input.init();
    rfid.init();

    io_service.init();
}

void loop() { }
