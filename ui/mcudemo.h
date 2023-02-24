#ifndef MCUDEMO_H
#define MCUDEMO_H

#include <QWidget>

#include "../ipc/DDS/DdsSubscriber/include/SampleSubscriber.h"

class CameraModel;
class QButtonGroup;
class QPushButton;
class McuDemo : public QWidget
{
    Q_OBJECT
public:
    explicit McuDemo(CameraModel *model, QWidget *parent = nullptr);

private:
    void init();
    void initConnection();

private slots:
    void createTopic();
    void deleteTopic();

public slots:
    void onMcuSignalChanged();

private:
    CameraModel *m_model;
    Dds::SampleSubscriber m_subscriber;
    QButtonGroup *m_highBeamBtnGroup;
    QButtonGroup *m_frontWiperBtnGroup;
    QButtonGroup *m_doorBtnGroup;
    QButtonGroup *m_flWinBtnGroup;
    QPushButton *m_connectBtn;
    QPushButton *m_disconnectBtn;
};

#endif // MCUDEMO_H
