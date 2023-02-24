#include "cameramodel.h"

CameraModel::CameraModel(QObject *parent) : QObject(parent)
{

}

QStringList CameraModel::getFrameRateList() const
{
    return FrameRateList;
}

int CameraModel::getMinClarity() const
{
    return MinClarity;
}

int CameraModel::getMaxClarity() const
{
    return MaxClarity;
}

QString CameraModel::getLogDir() const
{
    return logDir;
}

QString CameraModel::getServerAddress() const
{
    return serverAddress;
}

void CameraModel::setServerAddress(const QString &newServerAddress)
{
    serverAddress = newServerAddress;
}

HighBeam CameraModel::getHighBeamStatus() const
{
    return highBeamStatus;
}

void CameraModel::setHighBeamStatus(HighBeam newHighBeamStatus)
{
    highBeamStatus = newHighBeamStatus;
}

FrontWiper CameraModel::getFrontWiperStatus() const
{
    return frontWiperStatus;
}

void CameraModel::setFrontWiperStatus(FrontWiper newFrontWiperStatus)
{
    frontWiperStatus = newFrontWiperStatus;
}

DriverDoorAjar CameraModel::getDriverDoorAjarStatus() const
{
    return driverDoorAjarStatus;
}

void CameraModel::setDriverDoorAjarStatus(DriverDoorAjar newDriverDoorAjarStatus)
{
    driverDoorAjarStatus = newDriverDoorAjarStatus;
}

FLWin CameraModel::getFlWinStatus() const
{
    return flWinStatus;
}

void CameraModel::setFlWinStatus(FLWin newFlWinStatus)
{
    flWinStatus = newFlWinStatus;
}
