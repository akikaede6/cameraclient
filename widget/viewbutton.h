#ifndef VIEWBUTTON_H
#define VIEWBUTTON_H

#include <QRadioButton>

class ViewButton : public QRadioButton
{
    Q_OBJECT
public:
    explicit ViewButton(QWidget *parent = nullptr);
    explicit ViewButton(const QString &text, QWidget *parent = nullptr);
    ~ViewButton();

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
};

#endif // VIEWBUTTON_H
