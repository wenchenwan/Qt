#include "subwidget.h"

SubWidget::SubWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("小弟");
    B.setParent(this);
    B.setText("切换到主窗口");
    connect(&B, &QPushButton::clicked, this, &SubWidget::Send_Slot);

    resize(400,300);
}

void SubWidget::Send_Slot()
{
    emit My_Signal();
    emit My_Signal(250,"我是中国人");
}
