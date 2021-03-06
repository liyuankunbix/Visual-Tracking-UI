#include <iostream>
#include <QPainter>
#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMouseTracking(true);
    gotBeginSignal = false;
    isDrawing = false;
}

//void PaintWidget::beginIntialize()
//{
//    isInitializing = true;
//}

void PaintWidget::beginDraw()
{
    gotBeginSignal = true;
    std::cout << gotBeginSignal << std::endl;
}

void PaintWidget::mousePressEvent( QMouseEvent *evt )
{
    if (gotBeginSignal)
    {
        isDrawing = true;
        x1 = evt->x();
        y1 = evt->y();
        x2 = evt->x();
        y2 = evt->y();
    }
}

void PaintWidget::mouseReleaseEvent( QMouseEvent *evt )
{
    if (gotBeginSignal)
    {
        isDrawing = false;
        x2 = evt->x();
        y2 = evt->y();
        float left_ = x1 < x2 ? x1:x2;
        float top_ = y1 < y2 ? y1:y2;
        float width_ = x1 > x2 ? (x1-left_):(x2-left_);
        float height_ = y1 > y2 ? (y1-top_):(y2-top_);
        rectRatio = QRectF(left_/this->width(), top_/this->height(), width_/this->width(), height_/this->height());
        emit finishedDraw(true);
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *evt)
{
    if (gotBeginSignal && isDrawing)
    {
        x2 = evt->x();
        y2 = evt->y();
        update();// Mouse is moving and brush is drawing, so we need update() to call paintEvent();
    }
}

void PaintWidget::paintEvent(QPaintEvent *evt)
{
    QPainter painter0(this);
    painter0.setPen(Qt::black);
    //painter0.setBrush(QBrush(QColor(244,248,251)));
    //painter0.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    QRect rectangle0(0, 0, this->width()-1, this->height()-1);
    painter0.drawRoundedRect(rectangle0, 15, 15);
//    if(isInitializing)
//    {
//        std::cout << "asdasd" << std::endl;
//        QPainter painter0(this);
//        painter0.setPen(Qt::black);
//        painter0.setBrush(QBrush(QColor(244,248,251)));
//        painter0.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
//        QRect rectangle0(0, 0, this->width()-1, this->height()-1);
//        painter0.drawRoundedRect(rectangle0, 15, 15);
//        isInitializing = false;
//    }
    int left_ = x1 < x2 ? x1:x2;
    int top_ = y1 < y2 ? y1:y2;
    int width_ = x1 > x2 ? (x1-left_):(x2-left_);
    int height_ = y1 > y2 ? (y1-top_):(y2-top_);
    if (isDrawing)
    {
        QPainter painter(this);
        painter.setPen(Qt::red);
        painter.drawRect(left_, top_, width_, height_);
    }
//    QLineF line(x1, y1, x_curr, y_curr);
//    painter.drawLine(line);
}
