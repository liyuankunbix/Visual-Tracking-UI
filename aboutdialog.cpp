#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(215,232,242));
    this->setPalette(palette);
    ui->widget->setPalette(palette);
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    QImage image(":/about/label/about-label.png");
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(image));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(close()));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
