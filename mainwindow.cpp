#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QSlider>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "imageconvert.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0, 3);
    ui->splitter->setStretchFactor(1, 7);
    //connect the button listener event
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slotOpenImage()));
    connect(ui->actionOpen_Image, SIGNAL(triggered()), this, SLOT(slotOpenImage()));


    if(imagesCount >=1 )
    {
        timer = new QTimer(this);
        timer->start(37);
        connect(timer, SIGNAL(timeout()), this, SLOT(slotPlayImage()));
    }
    //connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(slotSliderPosition(int)));

}

/*******  Open Sequence Dir and Display First Image ******/
void MainWindow::slotOpenImage()
{
    QString dirPath = QFileDialog::getExistingDirectory(this,"请选择图像序列所在文件夹...","./");
    if(dirPath != "")
    {
        imagesPath = readFileList(dirPath.toLatin1().data());
        cv::Mat img = cv::imread(imagesPath[0], CV_LOAD_IMAGE_UNCHANGED);
        if(!img.empty())
        {
//          cv::Mat img_resized;
//          cv::resize(img, img_resized, cv::Size(ui->graphicsView->width()-10, ui->graphicsView->height()-10));
//          QImage image = MatToQImage(img_resized);
//          QGraphicsScene *scene = new QGraphicsScene;
//          scene->addPixmap(QPixmap::fromImage(image));
//          ui->graphicsView->setScene(scene);
//          ui->graphicsView->show();
            imagesCount = 1;

            ui->horizontalSlider->setMinimum(0);
            ui->horizontalSlider->setMaximum(imagesPath.size());
            //connect
            connect(this, SIGNAL(countChanged(int)), this, SLOT(slotSliderPosition(int)));
        }
    }
//    QString fileName = QFileDialog::getOpenFileName(this, "打开图片",".","图形文件 (*.bmp *.jpg *.png);;所有文件 (*.*)");
//    if(fileName != "")
}

/************   Display First Image Sequence ***********/
void MainWindow::slotPlayImage()
{
    if (imagesCount >= 1)
    {
        cv::Mat img = cv::imread(imagesPath[imagesCount-1], CV_LOAD_IMAGE_UNCHANGED);
        QGraphicsScene *scene = new QGraphicsScene;
        if(!img.empty())
        {
            cv::Mat img_resized;
            cv::resize(img, img_resized, cv::Size(ui->graphicsView->width()-10, ui->graphicsView->height()-10));
            QImage image = MatToQImage(img_resized);
            scene->addPixmap(QPixmap::fromImage(image));
            ui->graphicsView->setScene(scene);
            ui->graphicsView->show();
        }
        emit countChanged(imagesCount);
        //delete scene;
        imagesCount ++;
        if (imagesCount == imagesPath.size()+1)
            imagesCount = 0;
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