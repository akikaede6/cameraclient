#include "DdsSubscriber/include/SubscriberTopicer.h"

namespace Dds
{
    
SubscriberTopicer::SubscriberTopicer(const std::string& topicName, eprosima::fastdds::dds::DomainParticipant* itsParticipant, 
                                    eprosima::fastdds::dds::Subscriber* subscriber, 
                                    eprosima::fastdds::dds::TopicDataType* type, 
                                    const eprosima::fastdds::dds::TopicQos& topicQos)
    : itsName(topicName), itsParticipant(itsParticipant), itsSubscriber(subscriber), itsType(type)
    , itsTopic(nullptr), itsListener(nullptr), itsReader(nullptr)
{
    itsType.register_type(itsParticipant);
    itsTopic = itsParticipant->create_topic(topicName, itsType.get_type_name(), topicQos);
    if (itsTopic == nullptr)
    {
        //print error
    }
}

SubscriberTopicer::~SubscriberTopicer()
{
    if(itsReader)
    {
        std::cout << "delete reader" << std::endl;
        itsSubscriber->delete_datareader(itsReader);
    }

    if(itsTopic)
    {
        itsParticipant->delete_topic(itsTopic);
    }
}

eprosima::fastdds::dds::TypeSupport& SubscriberTopicer::getTypeSupport()
{
    return itsType;
}

eprosima::fastdds::dds::Topic* SubscriberTopicer::getTopic()
{
    return itsTopic;
}

std::unique_ptr<eprosima::fastdds::dds::DataReaderListener>& SubscriberTopicer::getListener()
{
    return itsListener;
}

eprosima::fastdds::dds::DataReader* SubscriberTopicer::getReader()
{
    return itsReader;
}

void SubscriberTopicer::setListener(std::unique_ptr<eprosima::fastdds::dds::DataReaderListener> listener)
{
    itsListener = std::move(listener);
}

bool SubscriberTopicer::createRader(const eprosima::fastdds::dds::DataReaderQos& RaderQos)
{
    itsReader = itsSubscriber->create_datareader(itsTopic, RaderQos, itsListener.get());
    return itsReader != nullptr;
}

eprosima::fastdds::dds::DataReaderQos SubscriberTopicer::CreateReadQos()
{
    eprosima::fastdds::dds::DataReaderQos rqos = eprosima::fastdds::dds::DATAREADER_QOS_DEFAULT;
    rqos.reliability().kind = eprosima::fastdds::dds::RELIABLE_RELIABILITY_QOS;
    // rqos.history().kind = eprosima::fastdds::dds::KEEP_ALL_HISTORY_QOS;
    // rqos.reliable_reader_qos().times.heartbeatPeriod.seconds = 0;
    // rqos.reliable_reader_qos().times.heartbeatPeriod.nanosec = 500000000; //500 ms
    // rqos.properties().properties().emplace_back("fastdds.push_mode", "true");
    return rqos;
}

} // namespace Dds



