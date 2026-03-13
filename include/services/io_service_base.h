#ifndef IO_SERVICE_BASE
#define IO_SERVICE_BASE

#include "services\auth_service.h"
#include "hardware\rfid\Rfid_SPI_Reader.h"

template <typename T_INPUT, typename T_OUTPUT>
class IO_Service_Base {
    private:
        Auth_Service m_auth;
        Rfid_SPI_Reader m_reader;
        T_INPUT m_input;
        T_OUTPUT m_output;
    public:
        IO_Service_Base(Rfid_SPI_Reader* reader, T_INPUT* input, T_OUTPUT* output);
        virtual void init() = 0;
};

#endif