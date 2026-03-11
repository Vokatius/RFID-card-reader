#ifndef INTERFACES
#define INTERFACES

#include <vector>
#include <Arduino.h>

class Display {
    public:
        virtual void Write(int col, int row, String text);
        virtual void Overwrite(int col, int row, const char* text);
        virtual void Init();
};

struct User {
    const String name;

    //Cant be fixed size 
    //UIDs might be 4, 7 or 10 Bytes
    const std::vector<uint8_t> uid;
};

class UserPersistance {
    public:
        virtual void create_user(User user);
        virtual User read_user(std::vector<uint8_t> uid);
        virtual void update_user(std::vector<uint8_t> uid, User user);
        virtual void delete_user(std::vector<uint8_t> uid);
};

#endif
