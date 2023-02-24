#ifndef _DDS_DDSCOMMON_INCLUDE_DEFS_
#define _DDS_DDSCOMMON_INCLUDE_DEFS_

namespace Dds
{
    
enum class Transport : uint8_t
{
    UDP   = 0x01,
    TCP   = 0x02,
    UDPv6 = 0x03,
    TCPv6 = 0x04
};
    

} // namespace Dds


#endif