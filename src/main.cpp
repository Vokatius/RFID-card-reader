#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define LED_PIN 2

#define BTN_LEFT_PIN 17
#define BTN_MIDDLE_PIN 16
#define BTN_RIGHT_PIN 4

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(BTN_LEFT_PIN, INPUT_PULLUP);
    pinMode(BTN_MIDDLE_PIN, INPUT_PULLUP);
    pinMode(BTN_RIGHT_PIN, INPUT_PULLUP);

    lcd.init();                      // initialize the lcd 
    // Print a message to the LCD.
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Hello, world!");
    lcd.setCursor(0,1);
    lcd.print("Ywrobot Arduino!");
    lcd.setCursor(0,2);
    digitalWrite(LED_PIN, LOW);
}

void loop() {
    if(digitalRead(BTN_LEFT_PIN) == LOW) {
        digitalWrite(LED_PIN, HIGH);
        delay(2000);
        digitalWrite(LED_PIN, LOW);
    }
    else if(digitalRead(BTN_MIDDLE_PIN) == LOW) {
        digitalWrite(LED_PIN, HIGH);
        delay(1000);
        digitalWrite(LED_PIN, LOW);
    }
    else if(digitalRead(BTN_RIGHT_PIN) == LOW) {
        digitalWrite(LED_PIN, HIGH);
        delay(500);
        digitalWrite(LED_PIN, LOW);
    }

    delay(500);
}