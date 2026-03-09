// #include <Arduino.h>
// #include <LiquidCrystal_I2C.h>
// #include "Menu.h"

// #define LED_PIN 2
// #define BTN_LEFT_PIN 17
// #define BTN_MIDDLE_PIN 16
// #define BTN_RIGHT_PIN 4
// #define LCD_ROWS 2

// int prev_btn = -1;

// LiquidCrystal_I2C lcd(0x27,16,LCD_ROWS);
// Menu menu(LCD_ROWS);

// int calc_pointer(int cursor_pos);

// void setup2() {
//     pinMode(LED_PIN, OUTPUT);
//     pinMode(BTN_LEFT_PIN, INPUT_PULLUP);
//     pinMode(BTN_MIDDLE_PIN, INPUT_PULLUP);
//     pinMode(BTN_RIGHT_PIN, INPUT_PULLUP);

//     lcd.init();
//     lcd.backlight();
// }

// void loop2() {
//     lcd.clear();

//     auto items = menu.get_display_items();
//     for(int i = 0; i < LCD_ROWS; i++){
//         lcd.setCursor(2, i);
//         lcd.print(items[i]);
//     }

//     lcd.setCursor(0, calc_pointer(menu.get_cursor_pos()));
//     lcd.print("*");

//     if(digitalRead(BTN_LEFT_PIN) == LOW && prev_btn != BTN_LEFT_PIN) {
//         menu.move_up();
//         prev_btn = BTN_LEFT_PIN;
//     }
//     else if(digitalRead(BTN_MIDDLE_PIN) == LOW && prev_btn != BTN_MIDDLE_PIN) {
//         digitalWrite(LED_PIN, HIGH);
//         prev_btn = BTN_MIDDLE_PIN;
//     }
//     else if(digitalRead(BTN_RIGHT_PIN) == LOW && prev_btn != BTN_RIGHT_PIN) {
//         menu.move_down();
//         prev_btn = BTN_RIGHT_PIN;
//     }
//     else if(digitalRead(BTN_LEFT_PIN) == HIGH && digitalRead(BTN_MIDDLE_PIN) == HIGH && digitalRead(BTN_RIGHT_PIN) == HIGH) {
//         prev_btn = -1;
//     }
//     else {
//         digitalWrite(LED_PIN, LOW);
//     }

//     delay(200);
// }

// int calc_pointer(int cursor_pos) {
//     if(cursor_pos < LCD_ROWS)
//         return cursor_pos;

//     return cursor_pos - LCD_ROWS;
// }