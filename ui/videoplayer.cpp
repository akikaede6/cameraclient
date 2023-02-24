#include "videoplayer.h"
#include "../widget/waitingspinnerwidget.h"

#include <QHBoxLayout>
#include <QImage>
#include <QLabel>
#include <QPixmap>

VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget{parent}, m_height(720), m_width(1280), m_label(new QLabel(this)), m_spinner(new WaitingSpinnerWidget(m_label))
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    m_label->setFixedSize(m_width / 2, m_height / 2);
    m_label->setFrameStyle(QFrame::Box);

    layout->addWidget(m_label);
}

VideoPlayer::~VideoPlayer()
{
}

void VideoPlayer::setResolution(int width, int height)
{
    m_height = height;
    m_width = width;
    m_label->setFixedSize(m_width / 2, m_height / 2);
}

void VideoPlayer::clear()
{
    m_label->clear();
}

void VideoPlayer::startSpinner()
{
    m_spinner->start();
}

void VideoPlayer::stopSpinner()
{
    m_spinner->stop();
}

void VideoPlayer::onDataAvaliable(const QImage &image)
{
    if (m_spinner->isSpinning())
        m_spinner->stop();
    if (!image.isNull())
        m_label->setPixmap(QPixmap::fromImage(image));
}
