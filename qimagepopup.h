#ifndef QImgPopup_H
#define QImgPopup_H

#include <QLabel>

class QTimer;

class QImagePopup : public QLabel
{
    Q_OBJECT
public:
    QImagePopup(QWidget *parent = nullptr);
    void show(int msecs = 1000);
signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent *e) override;
private:
    QTimer *mTimer;
};

#endif // QImgPopup_H
