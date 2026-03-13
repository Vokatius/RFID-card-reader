#include "services\io_service_base.h"

IO_Service_Base::IO_Service_Base(IRfid_Reader& reader, Auth_Service& auth, uint8_t max_name_len)
: m_reader(reader), m_auth(auth), m_max_name_length(max_name_len) { };
