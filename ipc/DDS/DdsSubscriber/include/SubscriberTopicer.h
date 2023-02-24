#ifndef _DDS_DDSSUBSCRIBER_INCLUDE_SAMPLESUBSCRIBER_SUBSCRIBERTOPICER_H_
#define _DDS_DDSSUBSCRIBER_INCLUDE_SAMPLESUBSCRIBER_SUBSCRIBERTOPICER_H_

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>

#include <memory>

namespace Dds
{
    
class SubscriberTopicer
{
public:
    SubscriberTopicer(const std::string& topicName, eprosima::fastdds::dds::DomainParticipant* itsParticipant, 
                eprosima::fastdds::dds::Subscriber* subscriber, 
                eprosima::fastdds::dds::TopicDataType* type, 
                const eprosima::fastdds::dds::TopicQos& topicQos = eprosima::fastdds::dds::TOPIC_QOS_DEFAULT);
    ~SubscriberTopicer();

    SubscriberTopicer(const SubscriberTopicer& other) = delete;
    SubscriberTopicer& operator=(const SubscriberTopicer& other) = delete;

    eprosima::fastdds::dds::TypeSupport& getTypeSupport();
    eprosima::fastdds::dds::Topic* getTopic();
    std::unique_ptr<eprosima::fastdds::dds::DataReaderListener>& getListener();
    eprosima::fastdds::dds::DataReader* getReader();

    void setListener(std::unique_ptr<eprosima::fastdds::dds::DataReaderListener> listener);
    bool createRader(const eprosima::fastdds::dds::DataReaderQos& raderQos);

    static eprosima::fastdds::dds::DataReaderQos CreateReadQos();

private:
    std::string                                                  itsName;
    eprosima::fastdds::dds::DomainParticipant*                   itsParticipant;
    eprosima::fastdds::dds::Subscriber*                          itsSubscriber;
    eprosima::fastdds::dds::TypeSupport                          itsType;
    eprosima::fastdds::dds::Topic*                               itsTopic;
    std::unique_ptr<eprosima::fastdds::dds::DataReaderListener>  itsListener;    
    eprosima::fastdds::dds::DataReader*                          itsReader;
};

} // namespace Dds







#endif