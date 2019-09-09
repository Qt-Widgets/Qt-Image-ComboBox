#include "qimagecomboboxitem.h"
#include "qimagepopup.h"
#include <QLabel>
#include <QEvent>
#include <QPaintEvent>
#include <QStylePainter>
#include <QStyleOptionButton>

QImageComboBoxItem::QImageComboBoxItem(QWidget *parent)
    : QWidget { parent }
{
    mLabel = new QImagePopup(this);

    connect(mLabel, &QImagePopup::clicked, this, [&]()
    {
        emit selected(this);
    });
}

QImageComboBoxItem::QImageComboBoxItem(const QString &text, const QPixmap &pixmap, QWidget *parent)
    : QImageComboBoxItem { parent }
{
    setText(text);
    setPixmap(pixmap);
}

void QImageComboBoxItem::setPixmap(const QPixmap &pixmap)
{
    mPixmap = pixmap;
    mLabel->setPixmap(mPixmap.scaled(100, 100));
}

QPixmap QImageComboBoxItem::pixmap() const
{
    return mPixmap;
}

void QImageComboBoxItem::mousePressEvent(QMouseEvent *e)
{
    QPoint p = parentWidget()->parentWidget()->parentWidget()->mapToGlobal(e->pos());
    const int x = p.x();
    const int y = p.y();
    const int w = mLabel->pixmap()->width();
    const int h = mLabel->pixmap()->height();
    mLabel->setGeometry(x, y, w, h);
    mLabel->show();
    QWidget::mousePressEvent(e);
}

void QImageComboBoxItem::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawText(2, rect().center().y() + height()/4, mText);
    QWidget::paintEvent(e);
}
