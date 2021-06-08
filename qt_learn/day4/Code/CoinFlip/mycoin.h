#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QtDebug>
#include<QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString btnImg);

    //金币的属性
    int posX;//x坐标
    int poxY;//y坐标
    int flag;//正反表示

    void changeFlag();//改变标志的方法
    QTimer *timer1;//正面翻反面的定时器
    QTimer *timer2;//反面翻正面的定时器

    int min = 1;
    int max = 8;

    //执行动画的标志
    bool isAnmation = false;

    //是否获胜的标志
    bool isWin = false;

    //重写 摁下
    void mousePressEvent(QMouseEvent* e);
signals:

public slots:
};

#endif // MYCOIN_H
