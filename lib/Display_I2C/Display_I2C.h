#ifndef DISPLAY_I2C
#define DISPLAY_I2C

#include <LiquidCrystal_I2C.h>
#include "Interfaces.h"

#define LCD_ROWS 2
#define LCD_COLS 16
#define LCD_ADDR 0x27

struct Display_Row {
    int start_col;
    String text;
};

class Display_I2C : Display {
    private:
        const int m_rows;
        const int m_cols;
        LiquidCrystal_I2C m_display;
        Display_Row* m_texts;
    public:
        Display_I2C(int max_cols, int max_rows, int i2c_addr);
        void Write(int col, int row, String text);    
        void Overwrite(int col, int row, const char* text);
        void Init();    
};

#endif