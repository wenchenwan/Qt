#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>
#include <QPushButton>

class SubWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SubWidget(QWidget *parent = 0);
    void Send_Slot();

signals:
    /* 信号必须要有signal关键字来声明
     * 信号没有返回值，但可以有参数
     * 信号就是函数的声明，只需声明，无需定义
     * 使用： emit mySignal（）；
     * 信号可以重载
    */
    void My_Signal();
    void My_Signal(int, QString );
public slots:

private:
    QPushButton B;

};

#endif // SUBWIDGET_H
