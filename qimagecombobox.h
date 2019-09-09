#ifndef QIMGCOMBOBOX_H
#define QIMGCOMBOBOX_H

#include <QWidget>

class QMenu;
class QListWidget;
class QImageComboBoxItem;

class QImageComboBox : public QWidget
{
    Q_OBJECT
public:
    QImageComboBox(QWidget *parent = nullptr);

    QImageComboBoxItem *currentItem() const
    {
        return mCurrentItem;
    }

    void loadImagesFromDirectory(const QString &directory);
    void addItem(QImageComboBoxItem *item);
signals:
    void itemActivated(QImageComboBoxItem *item);
protected:
    void mousePressEvent(QMouseEvent *e) override;
    void paintEvent(QPaintEvent *e) override;
private:
    QListWidget *mListWidget;
    QMenu *mMenu;
    QImageComboBoxItem *mCurrentItem;

    bool isImage(const QString &filePath) const;
    void onItemSelected(QImageComboBoxItem *item);
};

#endif // QIMGCOMBOBOX_H
