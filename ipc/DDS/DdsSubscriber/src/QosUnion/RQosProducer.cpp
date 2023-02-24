#include "DdsSubscriber/include/QosUnion/RQosProducer.h"

namespace Dds
{

RQosProducer::RQosProducer(std::unique_ptr<ISubscriberQos> qos, const std::string& participantName)
    : itsQosCreator(std::move(qos)), itsParticipantName(participantName)
{
    
}
eprosima::fastdds::dds::DomainParticipantQos RQosProducer::getParticipantQos()
{
    auto qos = itsQosCreator->createParticipantQos();
    qos.name(itsParticipantName);
    return qos;
}

eprosima::fastdds::dds::TopicQos RQosProducer::getTopicQos()
{
    return itsQosCreator->createTopicQos();
}

eprosima::fastdds::dds::SubscriberQos RQosProducer::getSubscriberQos()
{
    return itsQosCreator->createSubscriberQos();
}

eprosima::fastdds::dds::DataReaderQos RQosProducer::getDataReaderQos()
{
    return itsQosCreator->createDataReaderQos();
}
  
}