#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <QPushButton>

class My_Button : public QPushButton
{
    Q_OBJECT
public:
    explicit My_Button(QWidget *parent = 0);
    ~My_Button();

signals:

public slots:
};

#endif // MY_BUTTON_H
