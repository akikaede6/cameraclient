#include "mcudemo.h"
#include "DdsSubscriber/include/QosUnion/DefaultSubscriberQos.h"
#include "../model/cameramodel.h"
#include "../ipc/mcusubscriberlistener.h"
#include "../ipc/Data/BstDemo397TxPubSubTypes.h"
#include "../widget/viewbutton.h"

#include <QHBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QLabel>
#include <QButtonGroup>
#include <QPushButton>
#include <QDebug>

McuDemo::McuDemo(CameraModel *model, QWidget *parent)
    : QWidget{parent}
    , m_model(model)
    , m_subscriber(std::make_unique<Dds::DefaultSubscriberQos>(), "Mcu_Subscriber")
    , m_highBeamBtnGroup(new QButtonGroup)
    , m_frontWiperBtnGroup(new QButtonGroup)
    , m_doorBtnGroup(new QButtonGroup)
    , m_flWinBtnGroup(new QButtonGroup)
    , m_connectBtn(new QPushButton(tr("connect"), this))
    , m_disconnectBtn(new QPushButton(tr("disconnect"), this))
{
    init();
    initConnection();
}

void McuDemo::init()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // High Beam model
    QLabel *highBeamLabel = new QLabel(tr("High Beam Status"), this);
    QGroupBox *highBeamGroup = new QGroupBox(this);
    QVBoxLayout *highBeamLayout = new QVBoxLayout(this);
    ViewButton *highBeamOnBtn = new ViewButton(tr("On"), this);
    ViewButton *highBeamOffBtn = new ViewButton(tr("Off"), this);

    highBeamGroup->setLayout(highBeamLayout);
    highBeamGroup->setFixedSize(280, 360);

    m_highBeamBtnGroup->addButton(highBeamOnBtn, 0);
    m_highBeamBtnGroup->addButton(highBeamOffBtn, 1);

    highBeamLayout->addWidget(highBeamLabel);
    highBeamLayout->addWidget(highBeamOnBtn);
    highBeamLayout->addWidget(highBeamOffBtn);
    highBeamLayout->addStretch();

    // Wiper model
    QLabel *wiperLabel = new QLabel(tr("Front Wiper Status"), this);
    QGroupBox *wiperGroup = new QGroupBox(this);
    QVBoxLayout *wiperLayout = new QVBoxLayout(this);
    ViewButton *wiperOffBtn = new ViewButton(tr("Off"), this);
    ViewButton *wiperErrBtn = new ViewButton(tr("Error"), this);
    ViewButton *wiperSlowBtn = new ViewButton(tr("Continuous slow"), this);
    ViewButton *wiperFastBtn = new ViewButton(tr("Continuous fast"), this);

    wiperGroup->setLayout(wiperLayout);
    wiperGroup->setFixedSize(280, 360);

    m_frontWiperBtnGroup->addButton(wiperOffBtn, 0);
    m_frontWiperBtnGroup->addButton(wiperErrBtn, 1);
    m_frontWiperBtnGroup->addButton(wiperSlowBtn, 2);
    m_frontWiperBtnGroup->addButton(wiperFastBtn, 3);

    wiperLayout->addWidget(wiperLabel);
    wiperLayout->addWidget(wiperOffBtn);
    wiperLayout->addWidget(wiperErrBtn);
    wiperLayout->addWidget(wiperSlowBtn);
    wiperLayout->addWidget(wiperFastBtn);
    wiperLayout->addStretch();

    // Driver Door model
    QLabel *DoorLabel = new QLabel(tr("Driver Door Ajar status"), this);
    QGroupBox *DoorGroup = new QGroupBox(this);
    QVBoxLayout *DoorLayout = new QVBoxLayout(this);
    ViewButton *DoorClosedBtn = new ViewButton(tr("Closed"), this);
    ViewButton *DoorOpenBtn = new ViewButton(tr("Open"), this);

    DoorGroup->setLayout(DoorLayout);
    DoorGroup->setFixedSize(280, 360);

    m_doorBtnGroup->addButton(DoorClosedBtn, 0);
    m_doorBtnGroup->addButton(DoorOpenBtn, 1);

    DoorLayout->addWidget(DoorLabel);
    DoorLayout->addWidget(DoorClosedBtn);
    DoorLayout->addWidget(DoorOpenBtn);
    DoorLayout->addStretch();

    // FLWin model
    QLabel *FLWinLabel = new QLabel(tr("FL Window Status"), this);
    QGroupBox *FLWinGroup = new QGroupBox(this);
    QVBoxLayout *FLWinLayout = new QVBoxLayout(this);
    ViewButton *FLWinUndefBtn = new ViewButton(tr("Undefined window position"), this);
    ViewButton *FLWinClosedBtn = new ViewButton(tr("Window fully closed"), this);
    ViewButton *FLWinMiddleBtn = new ViewButton(tr("Between fullyclosed and fullyopened"), this);
    ViewButton *FLWinOpenedBtn = new ViewButton(tr("Window fully opened"), this);

    FLWinGroup->setLayout(FLWinLayout);
    FLWinGroup->setFixedSize(280, 360);

    m_flWinBtnGroup->addButton(FLWinUndefBtn, 0);
    m_flWinBtnGroup->addButton(FLWinClosedBtn, 1);
    m_flWinBtnGroup->addButton(FLWinMiddleBtn, 2);
    m_flWinBtnGroup->addButton(FLWinOpenedBtn, 3);

    FLWinLayout->addWidget(FLWinLabel);
    FLWinLayout->addWidget(FLWinUndefBtn);
    FLWinLayout->addWidget(FLWinClosedBtn);
    FLWinLayout->addWidget(FLWinMiddleBtn);
    FLWinLayout->addWidget(FLWinOpenedBtn);
    FLWinLayout->addStretch();

    m_connectBtn->setFixedWidth(80);
    m_disconnectBtn->setFixedWidth(80);
    m_disconnectBtn->setEnabled(false);

    QHBoxLayout *subLayout = new QHBoxLayout(this);
    subLayout->addWidget(highBeamGroup, 0, Qt::AlignCenter);
    subLayout->addWidget(wiperGroup, 0, Qt::AlignCenter);
    subLayout->addWidget(DoorGroup, 0, Qt::AlignCenter);
    subLayout->addWidget(FLWinGroup, 0, Qt::AlignCenter);

    QHBoxLayout *btnLayout = new QHBoxLayout(this);
    btnLayout->addWidget(m_connectBtn);
    btnLayout->addWidget(m_disconnectBtn);

    mainLayout->addLayout(subLayout);
    mainLayout->addLayout(btnLayout);
}

void McuDemo::initConnection()
{
    connect(m_connectBtn, &QPushButton::clicked, this, &McuDemo::createTopic);
    connect(m_disconnectBtn, &QPushButton::clicked, this, &McuDemo::deleteTopic);
}

void McuDemo::createTopic()
{
    std::cout << "Create Mcu Topic" << std::endl;
    auto txPtr = new McuSubscriberListener(m_model);
    connect(txPtr, &McuSubscriberListener::mcuSignalChanged, this, &McuDemo::onMcuSignalChanged);
    BstDemo397TxPubSubType* txType = new BstDemo397TxPubSubType;
    m_subscriber.createTopic("BstDemo397Tx_Topic", txType, std::unique_ptr<eprosima::fastdds::dds::DataReaderListener>{txPtr});
    m_connectBtn->setEnabled(false);
    m_disconnectBtn->setEnabled(true);
}

void McuDemo::deleteTopic()
{
    std::cout << "Delete Mcu Topic" << std::endl;
    m_subscriber.deleteTopic("BstDemo397Tx_Topic");
    m_connectBtn->setEnabled(true);
    m_disconnectBtn->setEnabled(false);
    if (m_highBeamBtnGroup->checkedButton())
        m_highBeamBtnGroup->checkedButton()->setChecked(false);
    else if (m_frontWiperBtnGroup->checkedButton())
        m_frontWiperBtnGroup->checkedButton()->setChecked(false);
    else if (m_doorBtnGroup->checkedButton())
        m_doorBtnGroup->checkedButton()->setChecked(false);
    else if (m_flWinBtnGroup->checkedButton())
        m_flWinBtnGroup->checkedButton()->setChecked(false);
}

void McuDemo::onMcuSignalChanged()
{
    if (m_highBeamBtnGroup->button(m_model->getHighBeamStatus()))
        m_highBeamBtnGroup->button(m_model->getHighBeamStatus())->setChecked(true);
    if (m_frontWiperBtnGroup->button(m_model->getFrontWiperStatus()))
        m_frontWiperBtnGroup->button(m_model->getFrontWiperStatus())->setChecked(true);
    if (m_doorBtnGroup->button(m_model->getDriverDoorAjarStatus()))
        m_doorBtnGroup->button(m_model->getDriverDoorAjarStatus())->setChecked(true);
    if (m_flWinBtnGroup->button(m_model->getFlWinStatus()))
        m_flWinBtnGroup->button(m_model->getFlWinStatus())->setChecked(true);
}
