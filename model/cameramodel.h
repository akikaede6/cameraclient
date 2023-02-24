#ifndef CAMERAMODEL_H
#define CAMERAMODEL_H

#include <QObject>
#include <QMap>

static const QStringList FrameRateList = {"15FPS", "30FPS"};
static const int MinClarity = 15;
static const int MaxClarity = 51;
static constexpr auto docker_addr = "192.168.111.10";
static constexpr auto a1000_addr = "172.16.28.248";
static const QString logDir = "/tmp/CameraLog";

enum HighBeam
{
    NotACTIVE,
    ACTIVE
};

enum FrontWiper
{
    Off,
    Error,
    ContinuoutSlow,
    ContinuousFast
};

enum DriverDoorAjar
{
    Closed,
    Open
};

enum FLWin
{
    UndefinedWindowPosition,
    WindowFullylosed,
    BetweenFullyclosedAndFullyOpened,
    WindowFullyOpened
};

class CameraModel : public QObject
{
    Q_OBJECT
public:
    explicit CameraModel(QObject *parent = nullptr);

    QStringList getFrameRateList() const;
    int getMinClarity() const;
    int getMaxClarity() const;
    QString getLogDir() const;

    QString getServerAddress() const;
    void setServerAddress(const QString &newServerAddress);

    HighBeam getHighBeamStatus() const;
    void setHighBeamStatus(HighBeam newHighBeamStatus);

    FrontWiper getFrontWiperStatus() const;
    void setFrontWiperStatus(FrontWiper newFrontWiperStatus);

    DriverDoorAjar getDriverDoorAjarStatus() const;
    void setDriverDoorAjarStatus(DriverDoorAjar newDriverDoorAjarStatus);

    FLWin getFlWinStatus() const;
    void setFlWinStatus(FLWin newFlWinStatus);

private:
    QString serverAddress = a1000_addr;
    HighBeam highBeamStatus;
    FrontWiper frontWiperStatus;
    DriverDoorAjar driverDoorAjarStatus;
    FLWin flWinStatus;
};

#endif // CAMERAMODEL_H
