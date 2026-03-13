#ifndef IO_SERVICE_BASE
#define IO_SERVICE_BASE

#include "services/auth_service.h"
#include "interfaces/rfid_reader.h"

class IO_Service_Base {
    protected:
        const uint8_t m_max_name_length;
        Auth_Service& m_auth;
        IRfid_Reader& m_reader;
    public:
        IO_Service_Base(IRfid_Reader& reader, Auth_Service& auth, uint8_t max_name_len);
        virtual void init() = 0;
};

#endif