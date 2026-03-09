#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "ListMenu.h"
#include "Input.h"

#define LED_PIN 2
#define BTN_LEFT_PIN 17
#define BTN_MIDDLE_PIN 16
#define BTN_RIGHT_PIN 4
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(0x27,16,LCD_ROWS);
ListMenu menu(LCD_ROWS, {"Scan", "Register", "Request","Delete"});
Input input({BTN_LEFT_PIN, BTN_MIDDLE_PIN, BTN_RIGHT_PIN});

int calc_pointer(int cursor_pos);

void setup() {
    pinMode(LED_PIN, OUTPUT);

    lcd.init();
    lcd.backlight();
}

void loop() {
    lcd.clear();

    auto items = menu.get_display_items();
    for(int i = 0; i < LCD_ROWS; i++){
        lcd.setCursor(2, i);
        lcd.print(items[i]);
    }

    lcd.setCursor(0, calc_pointer(menu.get_cursor_pos()));
    lcd.print("*");

    int pressed_btn = input.get_button();

    if(pressed_btn == BTN_LEFT_PIN)
        menu.move_up();
    else if(pressed_btn == BTN_MIDDLE_PIN) {
        digitalWrite(LED_PIN, HIGH);
        while (digitalRead(BTN_MIDDLE_PIN) == LOW)
        { }        
        digitalWrite(LED_PIN, LOW);
    }
    else if(pressed_btn == BTN_RIGHT_PIN) 
        menu.move_down();

    delay(200);
}

int calc_pointer(int cursor_pos) {
    if(cursor_pos < LCD_ROWS)
        return cursor_pos;

    return cursor_pos - LCD_ROWS;
}