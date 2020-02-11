#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "subwidget.h"  //子窗口头文件


class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
public slots:
    void My_Slot();
    void My_slot1();
    void Deal_Sub();
    void Deal_Slot(int, QString);

private:
    QPushButton B1;
    QPushButton *B2;
    QPushButton B3;

    SubWidget w;
};

#endif // MAINWIDGET_H
