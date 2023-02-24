#ifndef SUBSCRIBERLISTENER_H
#define SUBSCRIBERLISTENER_H

#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <QObject>

class QImage;
class Decode;
class FileManager;
class CameraSubscriberListener : public QObject, public eprosima::fastdds::dds::DataReaderListener
{
    Q_OBJECT
public:
    explicit CameraSubscriberListener(Decode *decoder, FileManager *fileManager, QObject *parent = nullptr);
    ~CameraSubscriberListener() override;

    void on_data_available(
            eprosima::fastdds::dds::DataReader* reader) override;

    void on_subscription_matched(
            eprosima::fastdds::dds::DataReader* reader,
            const eprosima::fastdds::dds::SubscriptionMatchedStatus& info) override;

signals:
    void fpsChanged(QString);
    void dataAvailable(bool);

private:
    int matched = 0;
    Decode *m_decoder;
    FileManager *m_file;
};

#endif // SUBSCRIBERLISTENER_H
