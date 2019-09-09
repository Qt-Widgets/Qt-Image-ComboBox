#ifndef QImgComboBoxItem_H
#define QImgComboBoxItem_H

#include <QWidget>
#include <QPixmap>

class QImagePopup;

class QImageComboBoxItem : public QWidget
{
    Q_OBJECT
public:
    QImageComboBoxItem(QWidget *parent = nullptr);
    QImageComboBoxItem(const QString &text, const QPixmap &pixmap, QWidget *parent = nullptr);
    void setPixmap(const QPixmap &pixmap);

    QPixmap pixmap() const;

    QString text() const
    {
        return mText;
    }

    void setText(const QString text)
    {
        mText = text;
    }
signals:
    void selected(QImageComboBoxItem *item);
protected:
    void mousePressEvent(QMouseEvent *e) override;
    void paintEvent(QPaintEvent *e) override;
private:
    QImagePopup *mLabel;
    QString mText;
    QPixmap mPixmap;
};

#endif // QImgComboBoxItem_H
