#ifndef RFID_AUTH
#define RFID_AUTH

#include <vector>
#include <MFRC522.h>

class Rfid_SPI_Reader {
    private:
        MFRC522 m_rfid;

    public: 
        Rfid_SPI_Reader(uint8_t rstPin = 0, uint8_t ssPin = 5);
        void init();
        std::vector<uint8_t> block_until_auth();
        bool block_until_verified(std::vector<uint8_t> expectedUid);
        std::vector<uint8_t> get_auth();
};

#endif
