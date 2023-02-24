#include "DdsSubscriber/include/SampleSubscriber.h"

namespace Dds
{

SampleSubscriber::SampleSubscriber(std::unique_ptr<ISubscriberQos> qos, const std::string& participantName)
    : itsParticipant(nullptr), itsSubscriber(nullptr), itsTopics()
    , itsQosProducer(std::move(qos), participantName)
{
    init();
}

SampleSubscriber::~SampleSubscriber()
{
    if (itsSubscriber != nullptr)
    {
        itsParticipant->delete_subscriber(itsSubscriber);
    }
    
    itsTopics.clear();

    eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->delete_participant(itsParticipant);
}

bool SampleSubscriber::init()
{
    itsParticipant = eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->create_participant(0, itsQosProducer.getParticipantQos());
    if(itsParticipant)
    {
        itsSubscriber = itsParticipant->create_subscriber(itsQosProducer.getSubscriberQos(), nullptr, eprosima::fastdds::dds::StatusMask::all());
        if(itsSubscriber)
        {
            return true;
        }
    }
    return false;
}

bool SampleSubscriber::createTopic(const std::string& topicName, eprosima::fastdds::dds::TopicDataType* type, 
                                    std::unique_ptr<eprosima::fastdds::dds::DataReaderListener> listener, 
                                    const eprosima::fastdds::dds::TopicQos& topicQos, 
                                    const eprosima::fastdds::dds::DataReaderQos& readQos)

{
    if(!type || !itsParticipant || !itsSubscriber || !listener)
    {
        return false;
    }

    itsTopics.emplace(topicName, std::make_unique<SubscriberTopicer>(topicName, itsParticipant, itsSubscriber, type, itsQosProducer.getTopicQos()));
    auto& topic = itsTopics[topicName];
    topic->setListener(std::move(listener));
    return topic->createRader(itsQosProducer.getDataReaderQos());
}

bool SampleSubscriber::deleteTopic(const std::string& topicName)
{
    itsTopics[topicName].reset();
    itsTopics.erase(topicName);
    return true;
}

std::unique_ptr<eprosima::fastdds::dds::DataReaderListener> &SampleSubscriber::getListener(const std::string &topicName)
{
    return itsTopics[topicName]->getListener();//todo if null
}

}
