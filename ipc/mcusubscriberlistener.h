#ifndef MCUSUBSCRIBERLISTENER_H
#define MCUSUBSCRIBERLISTENER_H

#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <QObject>

class CameraModel;
class McuSubscriberListener : public QObject, public eprosima::fastdds::dds::DataReaderListener
{
    Q_OBJECT
public:
    explicit McuSubscriberListener(CameraModel *model, QObject *parent = nullptr);

    void on_data_available(
            eprosima::fastdds::dds::DataReader* reader) override;

    void on_subscription_matched(
            eprosima::fastdds::dds::DataReader* reader,
            const eprosima::fastdds::dds::SubscriptionMatchedStatus& info) override;

signals:
    void mcuSignalChanged();

private:
    CameraModel *m_model;
    int matched = 0;
};

#endif // MCUSUBSCRIBERLISTENER_H
