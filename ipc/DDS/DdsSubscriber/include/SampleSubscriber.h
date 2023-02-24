#ifndef _DDS_DDSSUBSCRIBER_INCLUDE_SAMPLESUBSCRIBER_SAMPLESUBSCRIBER_H_
#define _DDS_DDSSUBSCRIBER_INCLUDE_SAMPLESUBSCRIBER_SAMPLESUBSCRIBER_H_

#include "DdsSubscriber/include/SubscriberTopicer.h"
#include "DdsSubscriber/include/QosUnion/RQosProducer.h"
#include <fastdds/dds/subscriber/qos/SubscriberQos.hpp>
#include <memory>
#include <map>

namespace Dds
{
    
using TopicName = std::string;
class SampleSubscriber
{
public:
    SampleSubscriber(std::unique_ptr<ISubscriberQos> qos, const std::string& participantName);
    ~SampleSubscriber();

    bool init();
    bool createTopic(const std::string& topicName, eprosima::fastdds::dds::TopicDataType* type, 
                     std::unique_ptr<eprosima::fastdds::dds::DataReaderListener> listener, 
                     const eprosima::fastdds::dds::TopicQos& topicQos = eprosima::fastdds::dds::TOPIC_QOS_DEFAULT, 
                     const eprosima::fastdds::dds::DataReaderQos& readQos = eprosima::fastdds::dds::DATAREADER_QOS_DEFAULT);
    bool deleteTopic(const std::string& topicName);

    std::unique_ptr<eprosima::fastdds::dds::DataReaderListener>& getListener(const std::string& topicName);
private:

    eprosima::fastdds::dds::DomainParticipant*               itsParticipant;
    eprosima::fastdds::dds::Subscriber*                      itsSubscriber;
    std::map<TopicName, std::unique_ptr<SubscriberTopicer>>  itsTopics; 
    RQosProducer                                             itsQosProducer;
};

} // namespace Dds







#endif
