#include <QApplication>
#include <QWidget> //窗口控件基类
#include <QPushButton>

int main(int argc, char **argv)
{
    QApplication app(argc,argv);

    QWidget W;

    W.setWindowTitle("主要看气质");
    //W.show();

    /*如果不指定父对象窗口之间相互独立
     *指定父对象的两种办法
            1.SetParent
            2.通过构造函数传参
    */
    QPushButton B;
    B.setText("wo");
    //B.show();
    B.setParent(&W);

    B.move(100,100);//移动控件位置

    QPushButton B1(&W);
    B1.setText("你好");
    B1.move(200,200);

    W.show();

    app.exec();
    return 0;
}
