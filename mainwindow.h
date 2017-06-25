#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QTimer>
#include <QSlider>
#include <QMouseEvent>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "paintwidget.h"
#include "aboutdialog.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    uint imagesCount;
    bool gotGroundTruth;

signals:
    void countChanged(int value);

protected:

private:
    Ui::MainWindow *ui;
    PaintWidget *paintWidget;
    AboutDialog *aboutDialog;
    QTimer *timer;
    cv::VideoCapture videoCap;
    std::vector<std::string> imagesPath;
    cv::Mat firstFrame;
    cv::Rect groundTruth;

private slots:
    void aboutThisApp();
    void slotOpenImage(); //信号槽
    void slotPlayImage(); //信号槽
    void startReadRect();
    void startRectangle();
    void endRectangle(bool flag);
    void slotSliderPosition(int position);
};

#endif // MAINWINDOW_H
