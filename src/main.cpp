#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <vector>
#include "ListMenu.h"
#include "Input.h"
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
    const std::vector<uint8_t> test = { 0x02, 0xA1, 0x02, 0xA2, 0x12, 0xA1, 0x02 };
    String res = Base64::to_base64(test);

    lcd.Write(0,0, res);
}

void loop() { }