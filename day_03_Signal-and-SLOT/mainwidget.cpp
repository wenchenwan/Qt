#include "mainwidget.h"
#include <QPushButton>
#include <QString>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    /*QPushButton B;
    *
    * B.setText("^_^");
    * B.show();*/

    B1.setParent(this);
    B1.setText("close");
    B1.move(100,100);

    B2 = new QPushButton(this);
    B2->setText("ABC");

   connect(&B1, &QPushButton::clicked, this, &MainWidget::close);
   /*&B信号的发出者，指针类型
    *&QPushButton::clicked 处理的信号 &发送者的类名::信号名
    * this 信号接受者
    * &MainWidget::close 槽函数，信号处理函数  &接受的类名::槽函数名++名
    * */

   /*自定义槽函数，普通函数的用法
    * Qt5 可以任意的全局函数，任意的成员函数，静态函数
    * 参函数需要和信号一致（参数，返回值）
    * 由于信号函数没有返回值，所以槽函数一定没有返回值
    */
   connect(B2,&QPushButton::released,this,&MainWidget::My_Slot);

   connect(B2,&QPushButton::released,&B1,&QPushButton::hide);

   /*信号：短信
    *槽函数：接受短信的手机
    */

   setWindowTitle("Boss");
   //this->setWindowTitle("Boss");

   B3.setParent(this);
   B3.setText("切换到子窗口");
   B3.move(50,50);

   //显示子对象
   //w.show();
   connect(&B3, &QPushButton::clicked, this, &MainWidget::My_slot1);

   //处理子窗口信号

/*   void (SubWidget::*FunctionSignal)() = &SubWidget::My_Signal;
   //connect(&w,&SubWidget::My_Signal,this,&MainWidget::Deal_Sub);
   connect(&w,FunctionSignal,this,&MainWidget::Deal_Sub);

   void (SubWidget::*FunctionSignal1)(int,QString) = &SubWidget::My_Signal;
   connect(&w,FunctionSignal1,this, &MainWidget::Deal_Slot);
   /*函数指针使用
    * void  fun(int)
    * {
    *
    * }
    * void (*p)(int) = fun;
    *
    *
    *
*/
   //Qt4信号链接
   //Qt4槽函数必须要有slots：关键字来修饰
   connect(&w,SIGNAL(My_Signal()),this,SLOT(Deal_Sub()));
   connect(&w, SIGNAL(My_Signal(int,QString)),this,
           SLOT(Deal_Slot(int,QString)));

   // SIGNAL SLOT 将函数 -> 字符串  不进行错误检查

   //Lambda表达式   匿名函数对象
   //C++11增加的新特性 项目文件: CONFIG += C++11
   //Qt配合信号一起使用，非常方便

   QPushButton *B4 = new QPushButton(this);
   //按钮只是触发槽函数（触发软件中断）信号，具体的操作是由槽函数进行操作的
   B4 -> setText("Lambda表达式");
   B4-> move(150,150);
   int A=10,ab=0;
   connect(B4, &QPushButton::clicked,
           // =:把外部所有的局部变量、以及类中所有的成员以值传递方式传递进来
           //this: 类中的所有的成员以值传递方式
           //& :引用，把外部所有的局部变量，不包括类中的成员，一般不使用应用 ，会出现由于按钮内存里边的信息 未释放

           //[=]() mutable

           //没有mutable在括号内部的变量是只读变量，不可以修改

           [=](bool isCheck)
           {

            //isCheck = 1;
            qDebug() << isCheck;

            /*B4->setText("123");
            qDebug() << "1111111";
            qDebug() << A << ab ;
            A = 11;*/
            }
           );

   resize(400,300);
}

MainWidget::~MainWidget()
{

}

void MainWidget::My_Slot(){

    B2->setText("123");
}

void MainWidget::My_slot1(){
    //子窗口显示
    w.show();
    //本窗口隐藏
    this->hide();

}
void MainWidget::Deal_Sub()
{
    //子窗口隐藏
    w.hide();
    //本窗口显示
    this->show();
}
void MainWidget::Deal_Slot(int a, QString str){
    //qDebug() << a << str ;
    //str.toUtf8().data() -> 字节数组转换为QByteArray
    //.data() ->QByteArray -> 转换为 char *
    qDebug() << a << str.toUtf8().data();

}
