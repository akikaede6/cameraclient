#ifndef CONFIGCLIENT_H
#define CONFIGCLIENT_H

#include <QTcpSocket>
#include <iostream>
#include <QMainWindow>
#include <QObject>
#include <thread>

enum class FrameRate:uint8_t
{
    Rate_15 = 0x01U,
    Rate_30 = 0x02U,
    Rate_60 = 0x03U
};
enum class CameraMode:uint8_t
{
    ConfigDayTimeMode = 0x11U,
    ConfigRainyMode = 0x12U,
    ConfigDuskMode = 0x13U,
    ConfigNightMode = 0x14U
};

class CameraModel;
class ConfigClient : public QObject
{
    Q_OBJECT
public:
    explicit ConfigClient(CameraModel* model, QWidget *parent = nullptr);
    ~ConfigClient();

    void setFrameRate(int index);
    void setCameraClarity(int index);
    void sendRequest();
    bool connectToService();
    void disconnect();
    QAbstractSocket::SocketState getSocketState();

signals:
    void configFinished(int8_t frameRateRet, int8_t clarityRet);
    void stateChanged(QAbstractSocket::SocketState);

private slots:
    void ReadData();
    void ReadError(QAbstractSocket::SocketError e);

private:
    void onReadMessage();

    FrameRate   itsFrameRate;
    int         m_clarity;
    QTcpSocket* itsTcpClient;
    CameraModel *m_model;
};

#endif
