#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSlider>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

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

signals:
    void countChanged(int value);

private:
    void send()
    {
        emit countChanged(imagesCount);
    }
    Ui::MainWindow *ui;
    QTimer theTimer;
    cv::Mat srcImage;
    cv::VideoCapture videoCap;
    std::vector<std::string> imagesPath;
    QTimer * timer;

private slots:
    void slotOpenImage(); //淇″彿妲
    void slotPlayImage(); //淇″彿妲
    void slotSliderPosition(int position);
};

#endif // MAINWINDOW_H
