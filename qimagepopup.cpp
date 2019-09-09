#include "qimagepopup.h"
#include <QTimer>
#include <QEvent>
#include <QDebug>

QImagePopup::QImagePopup(QWidget *parent)
    : QLabel { parent }
{
    setFrameShape(QLabel::Box);
    setWindowFlags(Qt::Popup);
    setFocusPolicy(Qt::WheelFocus);
    mTimer = new QTimer(this);
    mTimer->setSingleShot(true);

    connect(mTimer, &QTimer::timeout, this, [&]()
    {
        hide();
    });
}

void QImagePopup::show(int msecs)
{
    QLabel::show();
    mTimer->start(msecs);
}

void QImagePopup::mousePressEvent(QMouseEvent *e)
{
    emit clicked();
    hide();
    QLabel::mousePressEvent(e);
}
