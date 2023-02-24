#include "DdsSubscriber/include/QosUnion/BigdataSubscriberQos.h"

#include <fastdds/rtps/transport/TCPv4TransportDescriptor.h>
#include <fastdds/rtps/transport/TCPv6TransportDescriptor.h>
#include <fastdds/rtps/common/Time_t.h>
#include <fastrtps/utils/IPLocator.h>

#include <memory>

namespace Dds
{
    
BigdataSubscriberQos::BigdataSubscriberQos(Transport proto, const std::string& addr, const int& port, const uint32_t& dataSize)
    : itsProto(proto), itsSocketSize(dataSize), itsIpAddr(addr), itsPort(port)
{

}

eprosima::fastdds::dds::DomainParticipantQos BigdataSubscriberQos::createParticipantQos() 
{
    eprosima::fastdds::dds::DomainParticipantQos pqos;
    pqos.wire_protocol().builtin.discovery_config.leaseDuration = eprosima::fastrtps::c_TimeInfinite;
    pqos.wire_protocol().builtin.discovery_config.leaseDuration_announcementperiod = eprosima::fastrtps::Duration_t(1, 0);

        switch(itsProto)
    {
        case Transport::UDP:
        {
            pqos.transport().use_builtin_transports = true;
            break;
        }
        case Transport::TCP:
        {
            int32_t kind = LOCATOR_KIND_TCPv4;

            eprosima::fastdds::rtps::Locator initial_peer_locator;
            initial_peer_locator.kind = kind;
            eprosima::fastrtps::rtps::IPLocator::setIPv4(initial_peer_locator, itsIpAddr);
            initial_peer_locator.port = itsPort;
            pqos.wire_protocol().builtin.initialPeersList.push_back(initial_peer_locator); // Publisher's channel

            pqos.transport().use_builtin_transports = false;
            std::shared_ptr<eprosima::fastdds::rtps::TCPv4TransportDescriptor> descriptor = std::make_shared<eprosima::fastdds::rtps::TCPv4TransportDescriptor>();
            descriptor->sendBufferSize = MAX_BUFF_SIZE; // 8.5Mb
            descriptor->receiveBufferSize = MAX_BUFF_SIZE; // 8.5Mb
            pqos.transport().user_transports.push_back(descriptor);
            break;
        }
        case Transport::UDPv6:
        {
            break;
        }
        case Transport::TCPv6:
        {
            uint32_t kind = LOCATOR_KIND_TCPv6;
            pqos.transport().use_builtin_transports = false;

            eprosima::fastdds::rtps::Locator initial_peer_locator;
            initial_peer_locator.kind = kind;
            eprosima::fastrtps::rtps::IPLocator::setIPv6(initial_peer_locator, itsIpAddr);
            initial_peer_locator.port = itsPort;
            pqos.wire_protocol().builtin.initialPeersList.push_back(initial_peer_locator); // Publisher's channel

            pqos.transport().use_builtin_transports = false;
            std::shared_ptr<eprosima::fastdds::rtps::TCPv6TransportDescriptor> descriptor = std::make_shared<eprosima::fastdds::rtps::TCPv6TransportDescriptor>();
            descriptor->sendBufferSize = MAX_BUFF_SIZE; // 8.5Mb
            descriptor->receiveBufferSize = MAX_BUFF_SIZE; // 8.5Mb
            pqos.transport().user_transports.push_back(descriptor);
            break;
        }
        default:
        {
            abort();
        }
    }

    return pqos;
}

eprosima::fastdds::dds::TopicQos BigdataSubscriberQos::createTopicQos()       
{
    return eprosima::fastdds::dds::TOPIC_QOS_DEFAULT;
}

eprosima::fastdds::dds::SubscriberQos BigdataSubscriberQos::createSubscriberQos()  
{
    return eprosima::fastdds::dds::SUBSCRIBER_QOS_DEFAULT;
}

eprosima::fastdds::dds::DataReaderQos BigdataSubscriberQos::createDataReaderQos()  
{
    eprosima::fastdds::dds::DataReaderQos rqos;
    rqos.history().kind = eprosima::fastdds::dds::KEEP_LAST_HISTORY_QOS;
    rqos.history().depth = 30;
    rqos.resource_limits().max_samples = 50;
    rqos.resource_limits().allocated_samples = 20;
    rqos.reliability().kind = eprosima::fastdds::dds::BEST_EFFORT_RELIABILITY_QOS;
    rqos.durability().kind = eprosima::fastdds::dds::TRANSIENT_LOCAL_DURABILITY_QOS;
    rqos.endpoint().history_memory_policy = eprosima::fastrtps::rtps::PREALLOCATED_WITH_REALLOC_MEMORY_MODE;
    return rqos;
}


} // namespace Dds
