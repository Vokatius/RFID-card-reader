#ifndef INTERFACES_DISPLAY
#define INTERFACES_DISPLAY

#include <Arduino.h>

class IDisplay {
    public:
        virtual void write(int col, int row, String text);
        virtual void overwrite(int col, int row, const char* text);
        virtual void init();
};

#endif
