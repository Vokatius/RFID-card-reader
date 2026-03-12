#include "Rfid_SPI_Authentication.h"

Rfid_SPI_Authentication::Rfid_SPI_Authentication(uint8_t rst_pin, uint8_t ss_pin)
: m_rfid(ss_pin, rst_pin) { }

void Rfid_SPI_Authentication::init() {
    m_rfid.PCD_Init();
};

std::vector<uint8_t> Rfid_SPI_Authentication::get_auth() {
    if(!m_rfid.PICC_IsNewCardPresent()) // return if same card has been scanned
        return {};

    if(!m_rfid.PICC_ReadCardSerial())  // return if card couldnt be read
        return {};

    std::vector<uint8_t> result = {};
    for(int i = 0; i < m_rfid.uid.size; i++) 
        result.push_back(m_rfid.uid.uidByte[i]);

    m_rfid.PICC_HaltA();
    m_rfid.PCD_StopCrypto1();
    return result;
};

std::vector<uint8_t> Rfid_SPI_Authentication::block_until_auth() {
    std::vector<uint8_t> result = {};

    while (result.size() == 0)
        result = get_auth();

    return result;
}

bool Rfid_SPI_Authentication::block_until_is_verified(std::vector<uint8_t> expected_uid) {
    std::vector<uint8_t> result = {};
    
    while (result.size() == 0)
        result = get_auth();

    return result == expected_uid;
}