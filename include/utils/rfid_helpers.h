#ifndef RFID_HELPERS
#define RFID_HELPERS

#include <vector>
#include <stdint.h>
#include <string>

namespace rfid_helpers {
    std::string uid_to_string(std::vector<uint8_t> uid);
}

#endif