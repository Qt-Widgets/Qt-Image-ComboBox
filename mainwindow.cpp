#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qimagecomboboxitem.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->imgCombobox->addItem(new QImageComboBoxItem("red", makePixmap(Qt::red)));
    ui->imgCombobox->addItem(new QImageComboBoxItem("green", makePixmap(Qt::green)));
    ui->imgCombobox->addItem(new QImageComboBoxItem("blue", makePixmap(Qt::blue)));
    ui->imgCombobox->loadImagesFromDirectory("C:/users/cedo/desktop/imagenes");

    ui->imgCombobox->setMinimumHeight(ui->imgCombobox->height());
    ui->imgCombobox->setMaximumHeight(ui->imgCombobox->height());

    connect(ui->imgCombobox, &QImageComboBox::itemActivated, this, [&](QImageComboBoxItem *item)
    {
        ui->label->setPixmap(item->pixmap());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPixmap MainWindow::makePixmap(const QColor &color) const
{
    QImage img(250, 250, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&img);
    painter.fillRect(0, 0, 250, 250, color);
    return QPixmap::fromImage(img);
}
