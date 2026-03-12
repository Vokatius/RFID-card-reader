#include "hardware/display/Display_I2C.h"
#include <sstream>

Display_I2C::Display_I2C(int maxCols, int maxRows, int i2cAddr)
: m_rows(maxRows), m_cols(maxCols), m_texts(new Display_Row[maxRows]), m_display(i2cAddr, maxCols, maxRows) {
    for(int i = 0; i < m_rows; i++)
        m_texts[i] = {0, ""};
}

void Display_I2C::write(int col, int row, String text) {
    if(text.length() + col > m_cols) {
        write(0, 0, "Text too long!");
        write(0, 1, text.c_str());

        throw 1;
    }

    if(col > m_cols || row > m_rows) {
        std::ostringstream errStream;
        errStream << "R: " << row << " C: " << col;

        write(0, 0, "Invalid Pos");
        write(0, 1, errStream.str().c_str());
        
        throw 1;
    }
    
    m_texts[row] = {col, text};

    m_display.clear();

    Display_Row data;
    for(int rowItr = 0; rowItr < m_rows; rowItr++) {
        data = m_texts[rowItr];
        m_display.setCursor(data.startCol, rowItr);
        m_display.print(data.text);
    }
}

void Display_I2C::overwrite(int col, int row, const char* text) {
    m_display.setCursor(col, row);
    m_display.print(text);
}

void Display_I2C::init() {
    m_display.init();
    m_display.backlight();
}
