#ifndef INTERFACES
#define INTERFACES

class Display {
    public:
        virtual void Write(int col, int row, String text);
};

#endif