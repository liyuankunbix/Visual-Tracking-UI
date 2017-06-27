#ifndef TABWIDGET_1_H
#define TABWIDGET_1_H

#include <QWidget>

namespace Ui {
class TabWidget_1;
}

class TabWidget_1 : public QWidget
{
    Q_OBJECT

public:
    explicit TabWidget_1(QWidget *parent = 0);
    ~TabWidget_1();

private:
    Ui::TabWidget_1 *ui;
};

#endif // TABWIDGET_1_H
