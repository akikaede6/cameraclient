#ifndef _DDS_DDSSUBSCRIBER_INCLUDE_QOSUNION_BIGDATASUBSCRIBERQOS_H_
#define _DDS_DDSSUBSCRIBER_INCLUDE_QOSUNION_BIGDATASUBSCRIBERQOS_H_

#include "DdsSubscriber/include/QosUnion/ISubscriberQos.h"
#include "DdsCommon/include/Defs.h"

#include <string>

namespace Dds
{
class BigdataSubscriberQos : public ISubscriberQos
{

public:
    BigdataSubscriberQos(Transport proto, const std::string& addr, const int &port, const uint32_t& dataSize = MAX_BUFF_SIZE);
    ~BigdataSubscriberQos() override = default;

    eprosima::fastdds::dds::DomainParticipantQos createParticipantQos() override;
    eprosima::fastdds::dds::TopicQos             createTopicQos()       override;
    eprosima::fastdds::dds::SubscriberQos        createSubscriberQos()  override;
    eprosima::fastdds::dds::DataReaderQos        createDataReaderQos()  override;

private:
    Transport   itsProto;
    uint32_t    itsSocketSize;
    std::string itsIpAddr;
    int         itsPort;

    static constexpr auto MAX_BUFF_SIZE = 8912896;
};
    
}

#endif
