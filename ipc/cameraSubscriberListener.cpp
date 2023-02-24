#include "cameraSubscriberListener.h"
#include "Data/CameraStream.h"
#include "../decode/decode.h"
#include "../../FileManagement/FileManager.h"

#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <QImage>

CameraSubscriberListener::CameraSubscriberListener(Decode *decoder, FileManager *fileManager, QObject *parent) : QObject(parent), m_decoder(decoder), m_file(fileManager)
{
    if(!m_decoder->init())
    {
        std::cout << "decoder init error" << std::endl;
    }
}

CameraSubscriberListener::~CameraSubscriberListener()
{
    std::cout << "delete SubscriberListener" << std::endl;
}

void CameraSubscriberListener::on_data_available(
        eprosima::fastdds::dds::DataReader* reader)
{
    CameraStream data;
    eprosima::fastdds::dds::SampleInfo info;
    if (reader->take_next_sample(&data, &info) == ReturnCode_t::RETCODE_OK)
    {
        if (info.valid_data)
        {
            std::cout << data.message().size() << std::endl;
            m_decoder->parse(data.message().data(), data.message().size());
            emit fpsChanged(QString::number(data.fps(), 'f', 2));
            emit dataAvailable(true);
            m_file->writeFile(data.message().data(), data.message().size());
        }
    }
}

void CameraSubscriberListener::on_subscription_matched(
        eprosima::fastdds::dds::DataReader*,
        const eprosima::fastdds::dds::SubscriptionMatchedStatus& info)
{
    if (info.current_count_change == 1)
    {
        matched = info.total_count;
        std::cout << "Camera Subscriber matched." << std::endl;
    }
    else if (info.current_count_change == -1)
    {
        matched = info.total_count;
        std::cout << "Camera Subscriber unmatched." << std::endl;
    }
    else
    {
        std::cout << info.current_count_change
                  << " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
    }
}
