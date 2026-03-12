#include <Arduino.h>
#include "SPI.h"
#include <LiquidCrystal_I2C.h>
#include <vector>
#include "hardware/input/Push_Button_Input.h"
#include "utils/Base64.h"
#include "hardware/display/Display_I2C.h"
#include "hardware/rfid/Rfid_SPI_Reader.h"

#define LED_PIN 2
#define BTN_LEFT_PIN 17
#define BTN_MIDDLE_PIN 16
#define BTN_RIGHT_PIN 4
#define LCD_ROWS 2

Display_I2C lcd(16, LCD_ROWS, 0x27);
Rfid_SPI_Reader rfid;

void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);

    SPI.begin();
    lcd.init();
    rfid.init();
    // const std::vector<uint8_t> test = { 0x02, 0xA1, 0x05, 0xC0, 0xAB };
    // String res = Base64::toBase64(test, true);

    // auto testReparsed = Base64::fromBase64(res);

    // Serial.print("Return Array: ");
    // for(uint8_t i = 0; i < testReparsed.size(); i++) {
    //     Serial.print(i);
    //     Serial.print(" -> ");
    //     Serial.print(testReparsed[i]);
    //     Serial.print(", ");
    // }
    // Serial.println("");

    // lcd.write(0, 0, res);
}

void loop() { 
    auto res = rfid.block_until_auth();
        
    for(auto num : res) {
        Serial.print(num < 0x10 ? " 0" : " ");
        Serial.print(num, HEX);
    }
}
