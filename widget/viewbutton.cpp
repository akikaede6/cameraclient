#include "viewbutton.h"

ViewButton::ViewButton(QWidget *parent) : QRadioButton{parent}
{

}

ViewButton::ViewButton(const QString &text, QWidget *parent) : QRadioButton{parent}
{
    this->setText(text);
}

ViewButton::~ViewButton()
{

}

void ViewButton::keyPressEvent(QKeyEvent *e)
{

}

void ViewButton::keyReleaseEvent(QKeyEvent *e)
{

}

void ViewButton::mousePressEvent(QMouseEvent *e)
{

}

void ViewButton::mouseReleaseEvent(QMouseEvent *e)
{

}
