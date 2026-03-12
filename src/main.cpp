#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <vector>
#include "ListMenu.h"
#include "Push_Button_Input.h"
#include "Base64.h"
#include "Display_I2C.h"

#define LED_PIN 2
#define BTN_LEFT_PIN 17
#define BTN_MIDDLE_PIN 16
#define BTN_RIGHT_PIN 4
#define LCD_ROWS 2

Display_I2C lcd(16,LCD_ROWS,0x27);

void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);

    lcd.Init();
    const std::vector<uint8_t> test = { 0x02, 0xA1, 0x05, 0xC0, 0xAB };
    String res = Base64::to_base64(test, true);

    auto test_reparsed = Base64::from_base64(res);

    Serial.print("Return Array: ");
    for(uint8_t i = 0; i < test_reparsed.size(); i++) {
        Serial.print(i);
        Serial.print(" -> ");
        Serial.print(test_reparsed[i]);
        Serial.print(", ");
    }
    Serial.println("");

    lcd.Write(0,0, res);
}

void loop() { }