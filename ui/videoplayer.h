#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>

class QLabel;
class WaitingSpinnerWidget;
class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit VideoPlayer(QWidget *parent = nullptr);
    ~VideoPlayer();

    void setResolution(int width, int height);
    void clear();
    void startSpinner();
    void stopSpinner();

public slots:
    void onDataAvaliable(const QImage &image);

private:
    int m_height;
    int m_width;
    QLabel *m_label;
    WaitingSpinnerWidget* m_spinner;
};


#endif // VIDEOPLAYER_H
