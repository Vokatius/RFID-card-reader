#ifndef RFID_AUTH
#define RFID_AUTH

#include <SPI.h>
#include <MFRC522.h>
#include "interfaces/user_authentication.h"

class Rfid_SPI_Authentication : public IUserAuthentication {
    private:
        MFRC522 m_rfid;

    public: 
        Rfid_SPI_Authentication(uint8_t rstPin = 0, uint8_t ssPin = 5);
        void init();
        std::vector<uint8_t> block_until_auth();
        bool block_until_verified(std::vector<uint8_t> expectedUid);
        std::vector<uint8_t> get_auth();
};

#endif
