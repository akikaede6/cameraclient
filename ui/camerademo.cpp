#include "camerademo.h"
#include "DdsSubscriber/include/QosUnion/BigdataSubscriberQos.h"
#include "../ipc/cameraSubscriberListener.h"
#include "../model/cameramodel.h"
#include "../ipc/Data/CameraStreamPubSubTypes.h"
#include "../decode/decode.h"
#include "../FileManagement/FileManager.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QMessageBox>
#include <QDebug>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QSlider>
#include <QToolTip>


CameraDemo::CameraDemo(CameraModel *model, QWidget *parent)
    : QWidget{parent}
    , m_model(model)
    , m_connectBtn(new QPushButton(tr("connect"), this))
    , m_sendBtn(new QPushButton(tr("Send"), this))
    , m_startBtn(new QPushButton(tr("Start"), this))
    , m_stopBtn(new QPushButton(tr("Stop"), this))
    , m_frontCheck(new QCheckBox(tr("Front"), this))
    , m_backCheck(new QCheckBox(tr("Back"), this))
    , m_rightCheck(new QCheckBox(tr("Right"), this))
    , m_leftCheck(new QCheckBox(tr("Left"), this))
    , m_claritySlider(new QSlider(Qt::Horizontal, this))
    , m_frontCamera(new VideoPlayer(this))
    , m_backCamera(new VideoPlayer(this))
    , m_leftCamera(new VideoPlayer(this))
    , m_rightCamera(new VideoPlayer(this))
    , m_subscriber1(std::make_unique<Dds::BigdataSubscriberQos>(Dds::Transport::TCP, m_model->getServerAddress().toStdString(), 7890), "Camera_Subscriber1")
    , m_subscriber2(std::make_unique<Dds::BigdataSubscriberQos>(Dds::Transport::TCP, m_model->getServerAddress().toStdString(), 7891), "Camera_Subscriber2")
    , m_frontDecoder(new Decode())
    , m_backDecoder(new Decode())
    , m_leftDecoder(new Decode())
    , m_rightDecoder(new Decode())
    , m_frontFps(new QLabel(this))
    , m_backFps(new QLabel(this))
    , m_leftFps(new QLabel(this))
    , m_rightFps(new QLabel(this))
    , m_ConfigClient(new ConfigClient(m_model, this))
    , m_frontFile(new FileManager(m_model->getLogDir().toStdString(), "Front", 5))
    , m_backFile(new FileManager(m_model->getLogDir().toStdString(), "Back", 5))
    , m_leftFile(new FileManager(m_model->getLogDir().toStdString(), "Left", 5))
    , m_rightFile(new FileManager(m_model->getLogDir().toStdString(), "Right", 5))
{
    init();
    initConnect();
    if (m_ConfigClient->connectToService())
        m_connectBtn->setHidden(true);
}

CameraDemo::~CameraDemo()
{
    disconnect(m_ConfigClient, &ConfigClient::stateChanged, this, &CameraDemo::onSocketStateChanged);
    m_ConfigClient->disconnect();
}

void CameraDemo::init()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // config part
    QLabel *clarityLabel = new QLabel(tr("Clarity"), this);

    m_claritySlider->setRange(m_model->getMinClarity(), m_model->getMaxClarity());
    m_claritySlider->setValue(15);

    m_connectBtn->setFixedWidth(60);
    m_sendBtn->setFixedWidth(60);

    QHBoxLayout *configBtnLayout = new QHBoxLayout(this);
    configBtnLayout->addWidget(m_connectBtn);
    configBtnLayout->addWidget(m_sendBtn);

    QGridLayout *configLayout = new QGridLayout(this);
    configLayout->addWidget(clarityLabel, 0, 0, Qt::AlignRight);
    configLayout->addWidget(m_claritySlider, 0, 1, 1, 2);
    configLayout->addLayout(configBtnLayout, 0, 3, Qt::AlignRight);
    configLayout->addWidget(new QLabel(tr("Clear")), 1, 1, Qt::AlignLeft);
    configLayout->addWidget(new QLabel(tr("Vague")), 1, 2, Qt::AlignRight);

    QGroupBox *configGroup = new QGroupBox(tr("Config"), this);
    configGroup->setLayout(configLayout);
    configGroup->setFixedHeight(100);

    // video part
    QGridLayout *videoLayout = new QGridLayout(this);
    videoLayout->addWidget(new QLabel(this), 0, 0);
    videoLayout->addWidget(m_frontCheck, 0, 1, Qt::AlignHCenter);
    videoLayout->addWidget(m_frontFps, 0, 2, Qt::AlignHCenter);
    videoLayout->addWidget(m_frontCamera, 1, 0, 1, 3, Qt::AlignHCenter);

    videoLayout->addWidget(new QLabel(this), 0, 3);
    videoLayout->addWidget(m_backCheck, 0, 4, Qt::AlignHCenter);
    videoLayout->addWidget(m_backFps, 0, 5, Qt::AlignHCenter);
    videoLayout->addWidget(m_backCamera, 1, 3, 1, 3, Qt::AlignHCenter);

    videoLayout->addWidget(new QLabel(this), 2, 0);
    videoLayout->addWidget(m_leftCheck, 2, 1, Qt::AlignHCenter);
    videoLayout->addWidget(m_leftFps, 2, 2, Qt::AlignHCenter);
    videoLayout->addWidget(m_leftCamera, 3, 0, 1, 3);

    videoLayout->addWidget(new QLabel(this), 2, 3);
    videoLayout->addWidget(m_rightCheck, 2, 4, Qt::AlignHCenter);
    videoLayout->addWidget(m_rightFps, 2, 5, Qt::AlignHCenter);
    videoLayout->addWidget(m_rightCamera, 3, 3, 1, 3);

    // button part
    m_startBtn->setFixedWidth(60);
    m_stopBtn->setFixedWidth(60);
    m_stopBtn->setEnabled(false);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(m_startBtn);
    btnLayout->addWidget(m_stopBtn);

    mainLayout->addWidget(configGroup);
    mainLayout->addLayout(videoLayout);
    mainLayout->addLayout(btnLayout);
}

void CameraDemo::initConnect()
{
    connect(m_startBtn, &QPushButton::clicked, this, &CameraDemo::onStartClicked);
    connect(m_stopBtn, &QPushButton::clicked, this, &CameraDemo::onStopClicked);
    connect(m_sendBtn, &QPushButton::clicked, this, &CameraDemo::onSendClicked);
    connect(m_ConfigClient, &ConfigClient::configFinished, this, &CameraDemo::onConfigFinished);
    connect(m_frontDecoder, &Decode::dataAvaliable, m_frontCamera, &VideoPlayer::onDataAvaliable);
    connect(m_backDecoder, &Decode::dataAvaliable, m_backCamera, &VideoPlayer::onDataAvaliable);
    connect(m_leftDecoder, &Decode::dataAvaliable, m_leftCamera, &VideoPlayer::onDataAvaliable);
    connect(m_rightDecoder, &Decode::dataAvaliable, m_rightCamera, &VideoPlayer::onDataAvaliable);
    connect(m_stopBtn, &QPushButton::clicked, m_frontFps, &QLabel::clear);
    connect(m_stopBtn, &QPushButton::clicked, m_backFps, &QLabel::clear);
    connect(m_stopBtn, &QPushButton::clicked, m_leftFps, &QLabel::clear);
    connect(m_stopBtn, &QPushButton::clicked, m_rightFps, &QLabel::clear);
    connect(m_claritySlider, &QSlider::sliderMoved, [&](int value){QToolTip::showText(QCursor::pos(), QString("%1").arg(value), nullptr);});
    connect(m_ConfigClient, &ConfigClient::stateChanged, this, &CameraDemo::onSocketStateChanged);
    connect(m_connectBtn, &QPushButton::clicked, this, &CameraDemo::onConnectClicked);
}

void CameraDemo::enableBtn(bool enable)
{
    m_frontCheck->setEnabled(enable);
    m_backCheck->setEnabled(enable);
    m_leftCheck->setEnabled(enable);
    m_rightCheck->setEnabled(enable);
    m_claritySlider->setEnabled(enable);
}

bool CameraDemo::startCamera(bool frontFlag, bool backFlag, bool leftFlag, bool rightFlag)
{
    bool status = true;
    if (frontFlag)
    {
        std::cout << "Create Topic" << std::endl;
        m_frontCamera->startSpinner();
        auto ptr = new CameraSubscriberListener(m_frontDecoder, m_frontFile);
        connect(ptr, &CameraSubscriberListener::fpsChanged, m_frontFps, &QLabel::setText);
        connect(ptr, &CameraSubscriberListener::dataAvailable, [this](bool flag){m_stopBtn->setEnabled(flag);});
        CameraStreamPubSubType* type = new CameraStreamPubSubType;
        status &= m_subscriber1.createTopic("Camera_Front", type, std::unique_ptr<eprosima::fastdds::dds::DataReaderListener>{ptr});
    }
    if (backFlag)
    {
        std::cout << "Create Topic" << std::endl;
        m_backCamera->startSpinner();
        auto ptr = new CameraSubscriberListener(m_backDecoder, m_backFile);
        connect(ptr, &CameraSubscriberListener::fpsChanged, m_backFps, &QLabel::setText);
        connect(ptr, &CameraSubscriberListener::dataAvailable, [this](bool flag){m_stopBtn->setEnabled(flag);});
        CameraStreamPubSubType* type = new CameraStreamPubSubType;
        status &= m_subscriber1.createTopic("Camera_Back", type, std::unique_ptr<eprosima::fastdds::dds::DataReaderListener>{ptr});
    }
    if (leftFlag)
    {
        std::cout << "Create Topic" << std::endl;
        m_leftCamera->startSpinner();
        auto ptr = new CameraSubscriberListener(m_leftDecoder, m_leftFile);
        connect(ptr, &CameraSubscriberListener::fpsChanged, m_leftFps, &QLabel::setText);
        connect(ptr, &CameraSubscriberListener::dataAvailable, [this](bool flag){m_stopBtn->setEnabled(flag);});
        CameraStreamPubSubType* type = new CameraStreamPubSubType;
        status &= m_subscriber2.createTopic("Camera_Left", type, std::unique_ptr<eprosima::fastdds::dds::DataReaderListener>{ptr});
    }
    if (rightFlag)
    {
        std::cout << "Create Topic" << std::endl;
        m_rightCamera->startSpinner();
        auto ptr = new CameraSubscriberListener(m_rightDecoder, m_rightFile);
        connect(ptr, &CameraSubscriberListener::fpsChanged, m_rightFps, &QLabel::setText);
        connect(ptr, &CameraSubscriberListener::dataAvailable, [this](bool flag){m_stopBtn->setEnabled(flag);});
        CameraStreamPubSubType* type = new CameraStreamPubSubType;
        status &= m_subscriber2.createTopic("Camera_Right", type, std::unique_ptr<eprosima::fastdds::dds::DataReaderListener>{ptr});
    }
    return status;
}

void CameraDemo::stopCamera(bool frontFlag, bool backFlag, bool leftFlag, bool rightFlag)
{
    if (frontFlag)
    {
        qDebug() << "Delete Topic";
        m_frontCamera->stopSpinner();
        m_subscriber1.deleteTopic("Camera_Front");
        m_frontCamera->clear();
    }
    if (backFlag)
    {
        qDebug() << "Delete Topic";
        m_backCamera->stopSpinner();
        m_subscriber1.deleteTopic("Camera_Back");
        m_backCamera->clear();
    }
    if (leftFlag)
    {
        qDebug() << "Delete Topic";
        m_leftCamera->stopSpinner();
        m_subscriber2.deleteTopic("Camera_Left");
        m_leftCamera->clear();
    }
    if (rightFlag)
    {
        qDebug() << "Delete Topic";
        m_rightCamera->stopSpinner();
        m_subscriber2.deleteTopic("Camera_Right");
        m_rightCamera->clear();
    }
}

void CameraDemo::onStartClicked()
{
    if (startCamera(m_frontCheck->isChecked(), m_backCheck->isChecked(), m_leftCheck->isChecked(), m_rightCheck->isChecked()))
    {
        m_startBtn->setEnabled(false);
        m_stopBtn->setEnabled(false);
        m_sendBtn->setEnabled(false);
        m_connectBtn->setHidden(true);
        enableBtn(false);
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Start Camera Failed!"));
    }
}

void CameraDemo::onStopClicked()
{
    m_startBtn->setEnabled(true);
    m_stopBtn->setEnabled(false);
    if (m_ConfigClient && m_ConfigClient->getSocketState() == QAbstractSocket::ConnectedState)
    {
        m_sendBtn->setEnabled(true);
        m_connectBtn->setHidden(true);
    }
    else
    {
        m_sendBtn->setEnabled(false);
        m_connectBtn->setHidden(false);
    }
    enableBtn(true);
    stopCamera(m_frontCheck->isChecked(), m_backCheck->isChecked(), m_leftCheck->isChecked(), m_rightCheck->isChecked());
    m_frontCamera->clear();
    m_backCamera->clear();
    m_leftCamera->clear();
    m_rightCamera->clear();
}

void CameraDemo::onSendClicked()
{
    m_startBtn->setEnabled(false);
    m_stopBtn->setEnabled(false);
    m_sendBtn->setEnabled(false);
    enableBtn(false);

    m_ConfigClient->setCameraClarity(m_claritySlider->value());

    m_ConfigClient->sendRequest();
}

void CameraDemo::onConfigFinished(int8_t frameRateRet, int8_t clarityRet)
{
    std::cout << "----------------------" << std::endl;
    m_startBtn->setEnabled(true);
    m_stopBtn->setEnabled(false);
    m_sendBtn->setEnabled(true);
    enableBtn(true);
    if (frameRateRet == -1 && clarityRet == -1)
    {
        QMessageBox::warning(this, tr("Disconnected"), tr("Connection failed!"), QMessageBox::Ok);
    }
    else if (frameRateRet == 0 && clarityRet == 0)
    {
        QMessageBox::information(this, tr("Success"), tr("Camera Config Set Success!"));
    }
    else
    {
        switch(frameRateRet)
        {
        case 1:
            QMessageBox::critical(this, tr("Frame Rate"), tr("Unknown Error! Please retry."));
            break;
        case 2:
            QMessageBox::critical(this, tr("Frame Rate"), tr("Argument didn't changed! Please retry."));
            break;
        case 3:
            QMessageBox::critical(this, tr("Frame Rate"), tr("Device is busy! Please retry."));
            break;
        case 4:
            QMessageBox::critical(this, tr("Frame Rate"), tr("Invalid Argument! Please retry."));
            break;
        }
        switch(clarityRet)
        {
        case 1:
            QMessageBox::critical(this, tr("Clarity"), tr("Unknown Error! Please retry."));
            break;
        case 2:
            QMessageBox::critical(this, tr("Clarity"), tr("Argument didn't changed! Please retry."));
            break;
        case 3:
            QMessageBox::critical(this, tr("Clarity"), tr("Device is busy! Please retry."));
            break;
        case 4:
            QMessageBox::critical(this, tr("Clarity"), tr("Invalid Argument! Please retry."));
            break;
        }
    }
}

void CameraDemo::onSocketStateChanged(QAbstractSocket::SocketState state)
{
    std::cout << __func__ << state << std::endl;
    if (state == QAbstractSocket::UnconnectedState)
    {
        QMessageBox::warning(this, tr("Disconnected"), tr("Config Socket Disconnected!"), QMessageBox::Ok);
        m_connectBtn->setHidden(false);
        m_sendBtn->setEnabled(false);
    }
    else if (state == QAbstractSocket::ConnectedState)
    {
        m_connectBtn->setHidden(true);
        m_sendBtn->setEnabled(true);
    }
}

void CameraDemo::onConnectClicked()
{
    disconnect(m_ConfigClient, &ConfigClient::configFinished, this, &CameraDemo::onConfigFinished);
    disconnect(m_ConfigClient, &ConfigClient::stateChanged, this, &CameraDemo::onSocketStateChanged);
    m_ConfigClient->disconnect();
    delete m_ConfigClient;
    m_ConfigClient = new ConfigClient(m_model, this);
    connect(m_ConfigClient, &ConfigClient::configFinished, this, &CameraDemo::onConfigFinished);
    connect(m_ConfigClient, &ConfigClient::stateChanged, this, &CameraDemo::onSocketStateChanged);
    if (m_ConfigClient->connectToService())
    {
        QMessageBox::information(this, tr("Connect Success"), tr("Connect Success!"), QMessageBox::Ok);
        m_connectBtn->setHidden(true);
    }
    else
    {
        m_connectBtn->setHidden(false);
    }
}
