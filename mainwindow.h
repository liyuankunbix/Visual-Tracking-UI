#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QTimer>
#include <QSlider>
#include <QMouseEvent>
#include <QStackedWidget>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "tabwidget_1.h"
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
//    void initPaintWidget();
    void beginDraw();

protected:

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackWidget;
    PaintWidget *paintWidget;
    PaintWidget *paintWidget_2;
    PaintWidget *paintWidget_3;
    TabWidget_1 *tabWidget_1;
    AboutDialog *aboutDialog;
    QTimer *timer;
    cv::VideoCapture videoCap;
    std::vector<std::string> imagesPath;
    cv::Mat firstFrame;
    cv::Rect groundTruth;

private slots:
    void aboutThisApp();
    void slotOpenImage(); //信号槽
    void slotShowTab_1();
    void slotShowTab_2();
    void slotShowTab_3();
    void slotPlayImage(); //信号槽
    void startReadRect();
    void startRectangle();
    void endRectangle(bool flag);
    void slotSliderPosition(int position);
};

#endif // MAINWINDOW_H
