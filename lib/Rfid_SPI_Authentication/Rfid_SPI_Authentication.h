#ifndef RFID_AUTH
#define RFID_AUTH

#include <SPI.h>
#include <MFRC522.h>
#include "Interfaces.h"

class Rfid_SPI_Authentication : UserAuthentication {
    private:
        MFRC522 m_rfid;

    public: 
        Rfid_SPI_Authentication(uint8_t rst_pin = 0, uint8_t ss_pin = 5);
        void init();
        std::vector<uint8_t> block_until_auth();
        bool block_until_is_verified(std::vector<uint8_t> expected_uid);
        std::vector<uint8_t> get_auth();
};

#endif