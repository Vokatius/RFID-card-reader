#include "hardware/rfid/Rfid_SPI_Reader.h"

Rfid_SPI_Reader::Rfid_SPI_Reader(uint8_t rstPin, uint8_t ssPin)
: m_rfid(ssPin, rstPin) { }

void Rfid_SPI_Reader::init() {
    m_rfid.PCD_Init();
};

bool Rfid_SPI_Reader::try_get_auth(std::vector<uint8_t>* out_result) {
    if(out_result == nullptr)
        return false;

    if(!m_rfid.PICC_IsNewCardPresent()) // return if same card has been scanned
        return false;

    if(!m_rfid.PICC_ReadCardSerial())  // return if card couldnt be read
        return false;

    out_result->resize(0);
    for(int i = 0; i < m_rfid.uid.size; i++) 
        out_result->push_back(m_rfid.uid.uidByte[i]);

    m_rfid.PICC_HaltA();
    m_rfid.PCD_StopCrypto1();

    return true;
};
