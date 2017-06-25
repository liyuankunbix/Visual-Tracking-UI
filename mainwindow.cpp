#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QGraphicsScene>
#include <QFileDialog>
#include <opencv2/imgproc.hpp>
#include "imageconvert.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //////////// Set Up Some UI Stuff /////////////////
    ui->setupUi(this);
    paintWidget = new PaintWidget(this);
    QPalette pal(paintWidget->palette());
    pal.setColor(QPalette::Background, Qt::white);
    paintWidget->setAutoFillBackground(true);
    paintWidget->setPalette(pal);
    ui->widget_8->layout()->addWidget(paintWidget);
    ui->pushButton_6->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_7->setIcon(style()->standardIcon(QStyle::SP_MediaStop));

    //connect the button listener event
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(aboutThisApp()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slotOpenImage()));
    connect(ui->actionOpen_Image, SIGNAL(triggered()), this, SLOT(slotOpenImage()));

    // connect slider and image-count or frame-count
    connect(this, SIGNAL(countChanged(int)), this, SLOT(slotSliderPosition(int)));

    if(imagesCount >=1 )
    {
        timer = new QTimer(this);
        timer->start(37);
    }
}

/*********** Dialog : About this Application ************/
void MainWindow::aboutThisApp()
{
    ui->statusBar->showMessage("guanyu");
    aboutDialog = new AboutDialog(this);
    aboutDialog->show();
}

/*******  Open Sequence Dir and Display First Image *****/
void MainWindow::slotOpenImage()
{
    QString dirPath = QFileDialog::getExistingDirectory(this,"请选择图像序列所在文件夹...","./");
    if(dirPath != "")
    {
        imagesCount = 0;
        gotGroundTruth = false;
        emit countChanged(0);
        disconnect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(startReadRect()));
        disconnect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(startRectangle()));
        disconnect(paintWidget, SIGNAL(finishedDraw(bool)), this, SLOT(endRectangle(bool)));
        disconnect(timer, SIGNAL(timeout()), this, SLOT(slotPlayImage()));

        imagesPath = readFileList(dirPath.toLatin1().data());
        firstFrame = cv::imread(imagesPath[0], CV_LOAD_IMAGE_UNCHANGED);
        if(!firstFrame.empty())
        {
            cv::Mat img_resized;
            cv::resize(firstFrame, img_resized, cv::Size(paintWidget->width(), paintWidget->height()));
            QImage image = MatToQImage(img_resized);
            QPixmap pixmap = QPixmap::fromImage(image);
            QPalette palette;
            palette.setBrush(QPalette::Background, QBrush(pixmap));
            paintWidget->setPalette(palette);
            update();
            imagesCount = 1;

            connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(startReadRect()));
            connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(startRectangle()));
        }
    }
//    QString fileName = QFileDialog::getOpenFileName(this, "打开图片",".","图形文件 (*.bmp *.jpg *.png);;所有文件 (*.*)");
//    if(fileName != "")
}

/*********** What Happened when "文读" is Clicked ***********/
void MainWindow::startReadRect()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开初始坐标文件",".","文本文件 (*.txt *.dat);;所有文件 (*.*)");
    if(fileName != "")
    {}
}

/*********** What Happened when "框取" is Clicked ***********/
void MainWindow::startRectangle()
{
    //// 按下"框取"后，主界面随时准备接收"画完"信号，并执行画完后的操作
    connect(paintWidget, SIGNAL(finishedDraw(bool)), this, SLOT(endRectangle(bool)));
}

/*** What Happened when MainWindow Received "画完" Signal ***/
void MainWindow::endRectangle(bool flag)
{
    gotGroundTruth = flag;
    QRectF gtRatio = paintWidget->rectRatio;
    std::cout << gtRatio.x() << " " << gtRatio.y() << " " << gtRatio.width() << " " << gtRatio.height() << std::endl;
    groundTruth = cv::Rect(gtRatio.x()*firstFrame.cols, gtRatio.y()*firstFrame.rows, gtRatio.width()*firstFrame.cols, gtRatio.height()*firstFrame.rows);
    ui->statusBar->showMessage("已获取原始目标位置");
    //////////////////////////////////////
    // 在这儿初始化tracker
    //////////////////////////////////////
    ui->statusBar->showMessage("所选跟踪器启动完成，准备跟踪");
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(imagesPath.size());
    connect(timer, SIGNAL(timeout()), this, SLOT(slotPlayImage()));
}

/******************* Display Image Sequence ****************/
void MainWindow::slotPlayImage()
{
    disconnect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(startReadRect()));
    disconnect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(startRectangle()));
    disconnect(paintWidget, SIGNAL(finishedDraw(bool)), this, SLOT(endRectangle(bool)));
    if ((imagesCount >= 1) && (gotGroundTruth))
    {
        cv::Mat img = cv::imread(imagesPath[imagesCount-1], CV_LOAD_IMAGE_UNCHANGED);
        if(!img.empty())
        {
            cv::Mat img_resized;
            cv::resize(img, img_resized, cv::Size(paintWidget->width(), paintWidget->height()));
            QImage image = MatToQImage(img_resized);
            QPixmap pixmap = QPixmap::fromImage(image);
            QPalette palette;
            palette.setBrush(QPalette::Background, QBrush(pixmap));
            paintWidget->setPalette(palette);
        }
        emit countChanged(imagesCount);
        //delete scene;
        imagesCount ++;
        if (imagesCount == imagesPath.size()+1)
        {
            imagesCount = 0;
            disconnect(timer, SIGNAL(timeout()), this, SLOT(slotPlayImage()));
        }
    }
}

void MainWindow::slotSliderPosition(int position)
{
    ui->horizontalSlider->setValue(position);
}

MainWindow::~MainWindow()
{
    delete ui;
}
