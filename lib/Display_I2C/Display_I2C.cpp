#include "Display_I2C.h"
#include <sstream>

Display_I2C::Display_I2C(int max_cols, int max_rows, int i2c_addr) 
: m_rows(max_rows), m_cols(max_cols), m_texts(new Display_Row[max_rows]) , m_display(i2c_addr, max_cols, max_rows) {
    for(int i = 0; i < m_rows; i++)
        m_texts[i] = {0, ""};
}

void Display_I2C::Write(int col, int row, String text) {
    if(text.length() + col > m_cols) {
        Write(0, 0, "Text too long!");
        Write(0, 1, text.c_str());

        throw 1;
    }

    if(col > m_cols || row > m_rows) {
        std::ostringstream err_stream;
        err_stream << "R: " << row << " C: " << col;

        Write(0, 0, "Invalid Pos");
        Write(0, 1, err_stream.str().c_str());
        
        throw 1;
    }
    
    m_texts[row] = {col, text};

    m_display.clear();

    Display_Row data;
    for(int row_itr = 0; row_itr < m_rows; row_itr++) {
        data = m_texts[row_itr];
        m_display.setCursor(data.start_col, row_itr);
        m_display.print(data.text);
    }
}

void Display_I2C::Overwrite(int col, int row, const char* text) {
    m_display.setCursor(col, row);
    m_display.print(text);
}

void Display_I2C::Init() {
    m_display.init();
    m_display.backlight();
}