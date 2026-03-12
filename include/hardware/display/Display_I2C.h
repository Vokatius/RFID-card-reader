#ifndef DISPLAY_I2C
#define DISPLAY_I2C

#include <LiquidCrystal_I2C.h>
#include "interfaces/display.h"

#define LCD_ROWS 2
#define LCD_COLS 16
#define LCD_ADDR 0x27

struct Display_Row {
    int startCol;
    String text;
};

class Display_I2C : public IDisplay {
    private:
        const int m_rows;
        const int m_cols;
        LiquidCrystal_I2C m_display;
        Display_Row* m_texts;
    public:
        Display_I2C(int maxCols, int maxRows, int i2cAddr);
        void write(int col, int row, String text);
        void overwrite(int col, int row, const char* text);
        void init();
};

#endif
