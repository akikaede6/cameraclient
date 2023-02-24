#ifndef _DDS_DDSSUBSCRIBER_INCLUDE_QOSUNION_RQOSPRODUCER_H_
#define _DDS_DDSSUBSCRIBER_INCLUDE_QOSUNION_RQOSPRODUCER_H_

#include "DdsSubscriber/include/QosUnion/ISubscriberQos.h"

namespace Dds
{
class RQosProducer 
{
public:
    RQosProducer(std::unique_ptr<ISubscriberQos> qos, const std::string& participantName);
    ~RQosProducer() = default;

    eprosima::fastdds::dds::DomainParticipantQos getParticipantQos();
    eprosima::fastdds::dds::TopicQos             getTopicQos();
    eprosima::fastdds::dds::SubscriberQos        getSubscriberQos();
    eprosima::fastdds::dds::DataReaderQos        getDataReaderQos();

private:
    std::unique_ptr<ISubscriberQos> itsQosCreator;
    std::string                     itsParticipantName;
};
    
}

#endif