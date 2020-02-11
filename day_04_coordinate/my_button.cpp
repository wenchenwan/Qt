#include "my_button.h"
#include <QDebug>


My_Button::My_Button(QWidget *parent) : QPushButton(parent)
{

}

My_Button::~My_Button(){
    qDebug() << "按钮被析构";
}
