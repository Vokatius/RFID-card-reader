#include "services\io_service_base.h"

template <typename T_INPUT, typename T_OUTPUT>
IO_Service_Base<T_INPUT, T_OUTPUT>::IO_Service_Base(Rfid_SPI_Reader* reader, T_INPUT* input, T_OUTPUT* output)
: m_reader(*reader), m_input(*input), m_output(*output), m_auth({}) { };
