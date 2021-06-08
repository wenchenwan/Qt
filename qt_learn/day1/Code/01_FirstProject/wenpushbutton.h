#ifndef WENPUSHBUTTON_H
#define WENPUSHBUTTON_H

#include <QPushButton>
#include <QtDebug>
class wenPushbutton : public QPushButton
{
    Q_OBJECT
public:
    explicit wenPushbutton(QWidget *parent = nullptr);

    ~wenPushbutton();
signals:

public slots:
};

#endif // WENPUSHBUTTON_H
