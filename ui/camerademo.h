#ifndef CAMERADEMO_H
#define CAMERADEMO_H

#include <QWidget>

#include "videoplayer.h"
#include "../ipc/DDS/DdsSubscriber/include/SampleSubscriber.h"
#include "ConfigClient.h"

class CameraModel;
class CPlayWidget;
class QComboBox;
class QCheckBox;
class QPushButton;
class Decode;
class QSlider;
class QLabel;
class FileManager;
class CameraDemo : public QWidget
{
    Q_OBJECT
public:
    explicit CameraDemo(CameraModel* model, QWidget *parent = nullptr);
    ~CameraDemo();

private:
    void init();
    void initConnect();
    void enableBtn(bool enable);
    bool startCamera(bool frontFlag, bool backFlag, bool leftFlag, bool rightFlag);
    void stopCamera(bool frontFlag, bool backFlag, bool leftFlag, bool rightFlag);

private slots:
    void onStartClicked();
    void onStopClicked();
    void onSendClicked();
    void onConfigFinished(int8_t frameRateRet, int8_t clarityRet);
    void onSocketStateChanged(QAbstractSocket::SocketState state);
    void onConnectClicked();

private:
    CameraModel *m_model;
    QPushButton *m_connectBtn;
    QPushButton *m_sendBtn;

    QPushButton *m_startBtn;
    QPushButton *m_stopBtn;

    QCheckBox *m_frontCheck;
    QCheckBox *m_backCheck;
    QCheckBox *m_rightCheck;
    QCheckBox *m_leftCheck;

    QComboBox *m_frameRateBox;
    QSlider *m_claritySlider;

    VideoPlayer *m_frontCamera;
    VideoPlayer *m_backCamera;
    VideoPlayer *m_leftCamera;
    VideoPlayer *m_rightCamera;

    Dds::SampleSubscriber m_subscriber1;
    Dds::SampleSubscriber m_subscriber2;

    Decode *m_frontDecoder;
    Decode *m_backDecoder;
    Decode *m_leftDecoder;
    Decode *m_rightDecoder;

    QLabel *m_frontFps;
    QLabel *m_backFps;
    QLabel *m_leftFps;
    QLabel *m_rightFps;

    ConfigClient* m_ConfigClient;

    FileManager *m_frontFile;
    FileManager *m_backFile;
    FileManager *m_leftFile;
    FileManager *m_rightFile;
};

#endif // CAMERADEMO_H
