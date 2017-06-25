#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QRect>
#include <QMouseEvent>

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = 0);
    QRectF rectRatio;

signals:
    void finishedDraw(bool flag);

protected:
    void mousePressEvent(QMouseEvent *evt);
    void mouseReleaseEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);
    void paintEvent(QPaintEvent *evt);

private:
    int x1, y1, x2, y2;
    bool havePressed, haveReleased;
    bool isDrawing;
};

#endif // PAINTWIDGET_H
