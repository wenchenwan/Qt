#include "my_widget.h"
#include <QPushButton>
#include <my_button.h>


My_Widget::My_Widget(QWidget *parent)
    : QWidget(parent)
{
    /*对于父窗口（主窗口），坐标系统是相对于屏幕左上角
     * 起点：相对于屏幕左上角
     * x：相对于屏幕往右递
     * y：相对于屏幕往下递增
     */
    this->move(200,100);
    //所有的控件类都支持QWidget
    //所有的控件下边都可以使用move

    QPushButton *b1 = new QPushButton(this);
    b1->setText("加油小庆");
    b1->move(100 , 100);
    b1->resize(200,100);
    /*对于子窗口，坐标系统是相对于主窗口的左上角
     * 起点：窗口的空白区域（不包括边框）
     * x：相对于屏幕往右递
     * y：相对于屏幕往下递增
     */
    QPushButton *b2 = new QPushButton(b1);
    b2->move(10,10);
    b2->setText("小文加油");

    My_Button *b3 = new My_Button(this);
    b3->setText("123");
    //1）指定父对象后 2）必须是直接或间接的继承于QObject
    //如果是动态分配的内存，不需要去手动的释放
    //系统会自动释放
}

My_Widget::~My_Widget()
{

}
