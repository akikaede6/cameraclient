#ifndef _DDS_DDSSUBSCRIBER_INCLUDE_QOSUNION_ZEROCOPYSUBSCRIBERQOS_H_
#define _DDS_DDSSUBSCRIBER_INCLUDE_QOSUNION_ZEROCOPYSUBSCRIBERQOS_H_

#include "DdsSubscriber/include/QosUnion/ISubscriberQos.h"

namespace Dds
{
class ZeroCopySubscriberQos : public ISubscriberQos
{
public:
    ZeroCopySubscriberQos() = default;
    ~ZeroCopySubscriberQos() override = default;

    eprosima::fastdds::dds::DomainParticipantQos createParticipantQos() override;
    eprosima::fastdds::dds::TopicQos             createTopicQos()       override;
    eprosima::fastdds::dds::SubscriberQos        createSubscriberQos()  override;
    eprosima::fastdds::dds::DataReaderQos        createDataReaderQos()  override;
};
    
}

#endif