#include "qimagecombobox.h"
#include "qimagecomboboxitem.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QStylePainter>
#include <QStyleOptionComboBox>
#include <QListWidget>
#include <QMenu>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPixmap>
#include <QDir>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

QImageComboBox::QImageComboBox(QWidget *parent)
    : QWidget { parent }
{
    mListWidget = new QListWidget(this);
    mListWidget->setMinimumHeight(250);
    mListWidget->setMaximumHeight(250);

    mCurrentItem = nullptr;

    mMenu = new QMenu(this);
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(mListWidget);
    vbox->setMargin(0);
    vbox->setSpacing(0);
    mMenu->setLayout(vbox);
}

void QImageComboBox::mousePressEvent(QMouseEvent *e)
{
    mListWidget->setMinimumWidth(width());
    mListWidget->setMaximumWidth(width());
    QPoint p = parentWidget()->mapToGlobal(pos());
    p.setY(p.y() + height());
    mMenu->popup(p);
    QWidget::mousePressEvent(e);
}

void QImageComboBox::paintEvent(QPaintEvent *e)
{
    QStylePainter painter(this);
    QStyleOptionComboBox option;
    option.initFrom(this);
    painter.drawComplexControl(QStyle::CC_ComboBox, option);
    if (mCurrentItem)
    {
        painter.drawText(10, rect().center().y() + height()/4, mCurrentItem->text());
    }
    QWidget::paintEvent(e);
}

void QImageComboBox::loadImagesFromDirectory(const QString &directory)
{
    QDir imagenesDir(directory);
    imagenesDir.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    const int nImages = int(imagenesDir.count());
    for (int iImg = 0; iImg < nImages; ++iImg)
    {
        QString filepath = directory + "/" + imagenesDir[iImg];
        if (isImage(filepath))
        {
            QFileInfo finfo(filepath);
            QListWidgetItem *imgItem = new QListWidgetItem;
            mListWidget->addItem(imgItem);
            QImageComboBoxItem *comboItem = new QImageComboBoxItem(this);
            connect(comboItem, &QImageComboBoxItem::selected, this, &QImageComboBox::onItemSelected);
            comboItem->setText(finfo.fileName());
            comboItem->setPixmap(QPixmap(finfo.filePath()));
            mListWidget->setItemWidget(imgItem, comboItem);
        }
    }
}

void QImageComboBox::addItem(QImageComboBoxItem *item)
{
    connect(item, &QImageComboBoxItem::selected, this, &QImageComboBox::onItemSelected);
    QListWidgetItem *imgItem = new QListWidgetItem;
    mListWidget->addItem(imgItem);
    mListWidget->setItemWidget(imgItem, item);
}

bool QImageComboBox::isImage(const QString &filePath) const
{
    QFile JSFile(":/imageFormats.json");
    if (JSFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QJsonDocument doc = QJsonDocument::fromJson(JSFile.readAll());
        JSFile.close();
        QJsonArray formatsArray = doc.array();
        const int nFormats = formatsArray.size();
        for (int ix = 0; ix < nFormats; ++ix)
        {
            if (filePath.endsWith(formatsArray.at(ix).toString(), Qt::CaseInsensitive))
            {
                return true;
            }
        }
    }
    return false;
}

void QImageComboBox::onItemSelected(QImageComboBoxItem *item)
{
    mCurrentItem = item;
    emit itemActivated(mCurrentItem);
    update();
    mMenu->hide();
}
