#include "DdsSubscriber/include/QosUnion/DefaultSubscriberQos.h"

namespace Dds
{

eprosima::fastdds::dds::DomainParticipantQos DefaultSubscriberQos::createParticipantQos() 
{
    return eprosima::fastdds::dds::PARTICIPANT_QOS_DEFAULT;
}

eprosima::fastdds::dds::TopicQos DefaultSubscriberQos::createTopicQos()       
{
    return eprosima::fastdds::dds::TOPIC_QOS_DEFAULT;
}

eprosima::fastdds::dds::SubscriberQos DefaultSubscriberQos::createSubscriberQos()   
{
    return eprosima::fastdds::dds::SUBSCRIBER_QOS_DEFAULT;
}

eprosima::fastdds::dds::DataReaderQos DefaultSubscriberQos::createDataReaderQos()  
{
    eprosima::fastdds::dds::DataReaderQos qos = eprosima::fastdds::dds::DATAREADER_QOS_DEFAULT;
    //using reliable connection
    qos.reliability().kind = eprosima::fastdds::dds::RELIABLE_RELIABILITY_QOS;
    //keep all data until all subscriber receive then
    qos.history().kind = eprosima::fastdds::dds::KEEP_LAST_HISTORY_QOS;
    return qos;
}

    
}
