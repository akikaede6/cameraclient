#include "mcusubscriberlistener.h"
#include "Data/BstDemo397Tx.h"
#include "../model/cameramodel.h"

#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>

McuSubscriberListener::McuSubscriberListener(CameraModel *model, QObject *parent) : m_model(model)
{

}

void McuSubscriberListener::on_data_available(eprosima::fastdds::dds::DataReader *reader)
{
    BstDemo397Tx data;
    eprosima::fastdds::dds::SampleInfo info;
    if (reader->take_next_sample(&data, &info) == ReturnCode_t::RETCODE_OK)
    {
        if (info.valid_data)
        {
            m_model->setHighBeamStatus((HighBeam)((uint16_t)data.HighBeamSt()));
            m_model->setFrontWiperStatus((FrontWiper)((uint16_t)data.FrontWiperSt()));
            m_model->setDriverDoorAjarStatus((DriverDoorAjar)((uint16_t)data.DriverDoorAjarSt()));
            m_model->setFlWinStatus((FLWin)((uint16_t)data.FLWinSt_G()));
            emit mcuSignalChanged();
            std::cout << "HighBeam: " << (uint16_t)data.HighBeamSt() << std::endl;
            std::cout << "FrontWiperSt: " << (uint16_t)data.FrontWiperSt() << std::endl;
            std::cout << "DriverDoorAjarSt: " << (uint16_t)data.DriverDoorAjarSt() << std::endl;
            std::cout << "FLWinSt_G: " << (uint16_t)data.FLWinSt_G() << std::endl;

        }
    }
}

void McuSubscriberListener::on_subscription_matched(eprosima::fastdds::dds::DataReader *reader, const eprosima::fastdds::dds::SubscriptionMatchedStatus &info)
{
    if (info.current_count_change == 1)
    {
        matched = info.total_count;
        std::cout << "Mcu Subscriber matched." << std::endl;
    }
    else if (info.current_count_change == -1)
    {
        matched = info.total_count;
        std::cout << "Mcu Subscriber unmatched." << std::endl;
    }
    else
    {
        std::cout << info.current_count_change
                  << " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
    }
}
