#ifndef INTERFACES_TYPES
#define INTERFACES_TYPES

#include <Arduino.h>
#include <vector>

enum Buttons {
    UP,
    CENTER,
    DOWN,
    NONE
};

struct User {
    const String name;
    // UIDs might be 4, 7, or 10 bytes.
    const std::vector<uint8_t> uid;
};

#endif
