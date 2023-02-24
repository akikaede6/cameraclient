#include "ConfigClient.h"
#include <QString>
#include <string>
#include <sys/time.h>

#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <QMessageBox>
#include "../model/cameramodel.h"

void printTimeStamp()
{
    std::string sTimestamp;
        char acTimestamp[256];

        struct timeval tv;
        struct tm *tm;

        gettimeofday(&tv, NULL);

        tm = localtime(&tv.tv_sec);

        sprintf(acTimestamp, "%04d-%02d-%02d %02d:%02d:%02d.%03d\n",
                tm->tm_year + 1900,
                tm->tm_mon + 1,
                tm->tm_mday,
                tm->tm_hour,
                tm->tm_min,
                tm->tm_sec,
                (int) (tv.tv_usec / 1000)
            );

        sTimestamp = acTimestamp;

        std::cout << sTimestamp << std::endl;
}

ConfigClient::ConfigClient(CameraModel *model, QWidget *parent)
    : itsFrameRate(FrameRate::Rate_15), m_clarity(15), itsTcpClient(nullptr), m_model(model)
{
    itsTcpClient = new QTcpSocket();
    itsTcpClient->abort();	//取消原有连接
    connect(itsTcpClient, &QTcpSocket::readyRead,this, &ConfigClient::ReadData);	//获取数据
//    void (QAbstractSocket::*p)(QAbstractSocket::SocketError) =&QAbstractSocket::errorOccurred;	//函数指针
//    connect(itsTcpClient, p, this, &ConfigClient::ReadError);	//检测异常
//    connect(itsTcpClient, static_cast<void (QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::errorOccurred), this, &ConfigClient::ReadError);	//检测异常
    connect(itsTcpClient, &QTcpSocket::stateChanged, this, &ConfigClient::stateChanged);
}

ConfigClient::~ConfigClient()
{
    delete itsTcpClient;
}

void ConfigClient::sendRequest()
{
    static constexpr auto SIZE = 8;
    char data[SIZE] = {0};
    data[0] = static_cast<uint8_t>(itsFrameRate);
    data[1] = m_clarity;
    itsTcpClient->write(data, 8);
}

bool ConfigClient::connectToService()
{
    itsTcpClient->connectToHost(m_model->getServerAddress(), 8888);
    if(itsTcpClient->waitForConnected(1000))
    {
        qDebug()<<"connect success";
        return true;
    }
    else
    {
        qDebug()<<"connect fail";
        return false;
    }

}

void ConfigClient::ReadData()
{
    QByteArray buffer=itsTcpClient->readAll();
    if(!buffer.isEmpty())
    {
        emit configFinished(buffer.at(0), buffer.at(1));
    }
    else
    {
        emit configFinished(-1, -1);
        std::cout << "read fail" << std::endl;
    }
}

void ConfigClient::disconnect()
{
    itsTcpClient->disconnectFromHost();
    qDebug()<<"disconnect";
}

QAbstractSocket::SocketState ConfigClient::getSocketState()
{
    return itsTcpClient->state();
}

void ConfigClient::ReadError(QAbstractSocket::SocketError e)
{
    itsTcpClient->disconnectFromHost();
    qDebug()<<"socket error: "<<e;
    qDebug()<<itsTcpClient->errorString();
}

void ConfigClient::setFrameRate(int index)
{
    std::cout << index << std::endl;
    switch (index)
    {
    case 0:
        itsFrameRate = FrameRate::Rate_15;
        break;
    case 1:
        itsFrameRate = FrameRate::Rate_30;
        /* code */
        break;

    default:
        abort();
        break;
    }
}

void ConfigClient::setCameraClarity(int index)
{
    if (index  >= 1 && index <= 51)
        m_clarity = index;
}
