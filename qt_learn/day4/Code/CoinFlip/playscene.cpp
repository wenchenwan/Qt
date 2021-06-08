#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include "mycoin.h"
#include "dataconfig.h"
#include <QPropertyAnimation>
#include <QSound>
//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}


PlayScene::PlayScene(int levelNum)
{
    QString str = QString("进入了第 %1 关 ").arg(levelNum);
    qDebug() << str;
    this->levelIndex = levelNum;

    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币场景");

    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");

    //创建退出 菜单项
    QAction *  quitAction = startMenu->addAction("退出");

    //点击退出 实现退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //添加音效资源
    //返回音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    //翻金币音效
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
    //胜利按钮音效
    QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png" , ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width() , this->height() - backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        backSound->play();
        qDebug() << "翻金币场景中：点击了返回按钮";

        QTimer::singleShot(500,this,[=](){
            emit this->chooseSceneBack();
        });

    });


    //显示当前关卡数
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str1 = QString("Level: %1").arg(this->levelIndex);
    //将字体设置到标签控件中
    label->setFont(font);
    label->setText( str1);
    label->setGeometry(30, this->height() - 50,120, 50);

    dataConfig config;
    //初始化每个关卡的二维数组
    for(int i = 0; i < 4 ;i++){
        for(int j = 0; j<4;j++){
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());



    //显示金币图案
    for(int i = 0 ;i< 4;i++){
        for(int j = 0; j<4;j++){
            //绘制图片
            QPixmap pix = QPixmap(":/res/BoardNode.png");
            QLabel* label = new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57 + i*50,200 + j * 50);

            //创建金币
            QString str;
            if(this->gameArray[i][j] == 1){
                //显示金币
                str = ":/res/Coin0001.png";
            }else{
                str = ":/res/Coin0008.png";
            }
            MyCoin * coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59 + i*50,204 + j * 50);

            coin->posX = i;
            coin->poxY = j;
            coin->flag = gameArray[i][j];
            //将金币放入金币的二维数组中，以便后期的维护
            Coinbtn[i][j] = coin;
            connect(coin,&MyCoin::clicked,[=]{

                flipSound->play();
                //点击按钮,将所有的按钮都禁用
                for(int i = 0; i< 4;i++){
                    for(int j = 0; j< 4;j++){
                            this->Coinbtn[i][j]->isWin = true;

                    }
                }


                coin->changeFlag();
                this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;

                //翻转周的硬币,延时反转
                QTimer::singleShot(300,this,[=]{
                    //右侧硬币
                    if(coin->posX + 1 <= 3){
                        Coinbtn[coin->posX+1][coin->poxY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->poxY] = this->gameArray[coin->posX+1][coin->poxY] == 1 ? 0 : 1;
                    }
                    //左侧硬币
                    if(coin->posX -1 >= 0){
                        Coinbtn[coin->posX-1][coin->poxY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->poxY] = this->gameArray[coin->posX-1][coin->poxY] == 1 ? 0 : 1;
                    }

                    //上侧硬币
                    if(coin->poxY +1 <= 3){
                        Coinbtn[coin->posX][coin->poxY +1]->changeFlag();
                        this->gameArray[coin->posX][coin->poxY +1] = this->gameArray[coin->posX][coin->poxY +1] == 1 ? 0 : 1;
                    }

                    //下侧硬币
                    if(coin->poxY -1 >= 0){
                        Coinbtn[coin->posX][coin->poxY -1]->changeFlag();
                        this->gameArray[coin->posX][coin->poxY -1] = this->gameArray[coin->posX][coin->poxY -1] == 1 ? 0 : 1;
                    }

                    //翻完金币后将所有的金币都解开禁用
                    for(int i = 0; i< 4;i++){
                        for(int j = 0; j< 4;j++){
                                this->Coinbtn[i][j]->isWin = false;

                        }
                    }

                    //判断是否胜利
                    this->isWin = true;
                    for(int i = 0; i< 4;i++){
                        for(int j = 0; j< 4;j++){
                            if(Coinbtn[i][j]->flag == false){
                                this->isWin = false;
                                break;
                            }

                        }
                    }

                    if(this->isWin == true){
                        //胜利了
                        winSound->play();
                        qDebug() << "游戏胜利";

                        //将游戏的所有按钮全部禁用,将所有按钮的胜利标志设置为true，如果再次点击直接return不做响应
                        for(int i = 0; i< 4;i++){
                            for(int j = 0; j< 4;j++){
                                Coinbtn[i][j]->isWin= true;
                            }
                        }

                        //将胜利的图片砸下来
                        QPropertyAnimation * animation = new QPropertyAnimation(winLabel,"geometry");
                        animation->setDuration(1000);
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                    }

                });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *)
{
    //创建背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);

}
