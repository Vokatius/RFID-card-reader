#ifndef INTERFACES
#define INTERFACES

class Display {
    public:
        virtual void Write(int col, int row, String text);
        virtual void Overwrite(int col, int row, const char* text);
        virtual void Init();
};

#endif