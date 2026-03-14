#include "utils/rfid_helpers.h"

namespace rfid_helpers {
    std::string uid_to_string(std::vector<uint8_t> uid) {
        std::string uid_str = "";

        uint8_t size = uid.size() > 4 ? 4 : uid.size();
        for(int i = 0; i < size; i++) {
            uid_str.append(std::to_string(uid[i]));
            if(i+1 != size)
                uid_str.append("-");
        }

        return uid_str;
    }
}