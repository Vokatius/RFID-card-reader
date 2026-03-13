#ifndef RFID_AUTH
#define RFID_AUTH

#include <vector>
#include <MFRC522.h>

#include "interfaces/rfid_reader.h"

class Rfid_SPI_Reader : public IRfid_Reader {
    private:
        MFRC522 m_rfid;

    public: 
        Rfid_SPI_Reader(uint8_t rstPin = 0, uint8_t ssPin = 5);
        void init();
        bool try_get_auth(std::vector<uint8_t>* out_result);
};

#endif
