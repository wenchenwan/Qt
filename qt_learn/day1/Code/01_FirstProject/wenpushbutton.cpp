#include "wenpushbutton.h"

wenPushbutton::wenPushbutton(QWidget *parent) : QPushButton(parent)
  //交给父类进行构造
{

}

wenPushbutton::~wenPushbutton(){
    qDebug() << "对象析构";
}

