#ifndef INTERFACES_RFID_READER
#define INTERFACES_RFID_READER

#include <stdint.h>
#include <vector>

class IRfid_Reader {
    public:
        virtual void init() = 0;
        virtual bool try_get_auth(std::vector<uint8_t>* out_result) = 0;
};

#endif