#ifndef _DDS_DDSSUBSCRIBER_INCLUDE_QOSUNION_DEFAULTSUBSCRIBERQOS_H_
#define _DDS_DDSSUBSCRIBER_INCLUDE_QOSUNION_DEFAULTSUBSCRIBERQOS_H_

#include "DdsSubscriber/include/QosUnion/ISubscriberQos.h"

namespace Dds
{
class DefaultSubscriberQos : public ISubscriberQos
{
public:
    DefaultSubscriberQos() = default;
    ~DefaultSubscriberQos() override = default;

    eprosima::fastdds::dds::DomainParticipantQos createParticipantQos() override;
    eprosima::fastdds::dds::TopicQos             createTopicQos()       override;
    eprosima::fastdds::dds::SubscriberQos        createSubscriberQos()  override;
    eprosima::fastdds::dds::DataReaderQos        createDataReaderQos()  override;
};
    
}

#endif