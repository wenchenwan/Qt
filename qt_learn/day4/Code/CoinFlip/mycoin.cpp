#include "mycoin.h"

//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}
MyCoin::MyCoin(QString btnImg){
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret){
        QString str = QString("图片 %1 加载失败").arg(btnImg);
        qDebug() << str;
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器对象
    this->timer1 = new QTimer;
    this->timer2 = new QTimer;

    connect(timer1,&QTimer::timeout,[=]{
       QPixmap pix;
       QString str = QString(":/res/Coin000%1").arg(this->min++);
       pix.load(str);

       this->setFixedSize(pix.width(),pix.height());
       this->setStyleSheet("QPushButton{border:0px;}");
       this->setIcon(pix);
       this->setIconSize(QSize(pix.width(),pix.height()));

       //判断，如果翻完了，将min置为1
       if(this->min > this->max){
           isAnmation = false;
           this->min = 1;
           timer1->stop();
       }

    });

    connect(timer2,&QTimer::timeout,[=]{
       QPixmap pix;
       QString str = QString(":/res/Coin000%1").arg(this->max--);
       pix.load(str);

       this->setFixedSize(pix.width(),pix.height());
       this->setStyleSheet("QPushButton{border:0px;}");
       this->setIcon(pix);
       this->setIconSize(QSize(pix.width(),pix.height()));

       //判断，如果翻完了，将min置为1
       if(this->min > this->max){
           isAnmation = false;
           this->max = 8;
           timer2->stop();
       }

    });



}
void MyCoin::changeFlag(){
    if(this->flag){
        timer1->start(30);
        isAnmation = true;
        this->flag = false;

    }else{
        timer2->start(30);
        isAnmation = true;
        this->flag = true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent *e){
    if(this->isAnmation || this->isWin){
        return;
    }else{
        QPushButton::mousePressEvent(e);
    }
}
