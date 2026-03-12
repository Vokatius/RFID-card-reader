#include "services\io_service_base.h"

IO_Service_Base::IO_Service_Base(Rfid_SPI_Reader* reader)
: m_reader(*reader), m_auth({}) { };
