#include "DdsSubscriber/include/QosUnion/ZeroCopySubscriberQos.h"

namespace Dds
{

eprosima::fastdds::dds::DomainParticipantQos ZeroCopySubscriberQos::createParticipantQos() 
{
    eprosima::fastdds::dds::DomainParticipantQos pqos;
    return pqos;
}

eprosima::fastdds::dds::TopicQos ZeroCopySubscriberQos::createTopicQos()       
{
    return eprosima::fastdds::dds::TOPIC_QOS_DEFAULT;
}

eprosima::fastdds::dds::SubscriberQos ZeroCopySubscriberQos::createSubscriberQos()   
{
    return eprosima::fastdds::dds::SUBSCRIBER_QOS_DEFAULT;
}

eprosima::fastdds::dds::DataReaderQos ZeroCopySubscriberQos::createDataReaderQos()  
{
    eprosima::fastdds::dds::DataReaderQos rqos = eprosima::fastdds::dds::DATAREADER_QOS_DEFAULT;
    rqos.history().depth = 10;
    rqos.reliability().kind = eprosima::fastdds::dds::RELIABLE_RELIABILITY_QOS;
    rqos.durability().kind = eprosima::fastdds::dds::TRANSIENT_LOCAL_DURABILITY_QOS;
    rqos.data_sharing().on("/dev/shm");
    return rqos;
}

    
}
