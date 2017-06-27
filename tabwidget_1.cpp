#include "tabwidget_1.h"
#include "ui_tabwidget_1.h"

TabWidget_1::TabWidget_1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabWidget_1)
{
    ui->setupUi(this);
    QPalette pal;
    pal.setColor(QPalette::Background, Qt::blue);
    this->setPalette(pal);
}

TabWidget_1::~TabWidget_1()
{
    delete ui;
}
