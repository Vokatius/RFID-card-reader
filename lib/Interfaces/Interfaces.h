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

enum Buttons {
    UP,
    CENTER,
    DOWN,
    NONE
};

class Input {
    public:
        virtual Buttons block_until_button_press();
        virtual Buttons get_button();
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

class UserAuthentication {
    public:
        virtual std::vector<uint8_t> block_until_auth();
        virtual bool block_until_is_verified(std::vector<uint8_t> expected_uid);
        virtual std::vector<uint8_t> get_auth();
};

#endif
