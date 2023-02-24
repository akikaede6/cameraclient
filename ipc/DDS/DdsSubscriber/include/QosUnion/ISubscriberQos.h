#ifndef _DDS_DDSSUBSCRIBER_INCLUDE_QOSUNION_ISUBSCRIBERQOS_H_
#define _DDS_DDSSUBSCRIBER_INCLUDE_QOSUNION_ISUBSCRIBERQOS_H_

#include <fastdds/dds/subscriber/qos/SubscriberQos.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/domain/qos/DomainParticipantQos.hpp>
#include <fastdds/dds/topic/qos/TopicQos.hpp>

namespace Dds
{
class ISubscriberQos 
{
public:
    ISubscriberQos() = default;
    virtual ~ISubscriberQos() = default;

    virtual eprosima::fastdds::dds::DomainParticipantQos createParticipantQos() = 0;
    virtual eprosima::fastdds::dds::TopicQos             createTopicQos()       = 0;
    virtual eprosima::fastdds::dds::SubscriberQos        createSubscriberQos()   = 0;
    virtual eprosima::fastdds::dds::DataReaderQos        createDataReaderQos()  = 0;
};
    
}

#endif