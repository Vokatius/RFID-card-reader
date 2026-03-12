#ifndef IO_SERVICE_BASE
#define IO_SERVICE_BASE

#include "services\auth_service.h"
#include "hardware\rfid\Rfid_SPI_Reader.h"

class IO_Service_Base {
    private:
        Auth_Service m_auth;
        Rfid_SPI_Reader m_reader;
    public:
        IO_Service_Base(Rfid_SPI_Reader* reader);
        virtual void init();
};

#endif