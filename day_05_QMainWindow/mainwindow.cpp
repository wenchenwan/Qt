#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QTextEdit>
#include <QDockWidget>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //菜单栏
    QMenuBar *mBar = menuBar();
    //添加菜单
    QMenu *pFile = mBar->addMenu("文件");
    //添加菜单选项，添加动作
    QAction *pNew = pFile->addAction("新建");

    connect(pNew,&QAction::triggered,
            [=]()
            {
                qDebug() << "新建被按下";
            }


            );
    pFile->addSeparator();//添加分割线

    QAction *pOpen = pFile->addAction("打开");

    //工具栏，菜单栏上的快捷方式
    QToolBar *toolBar = addToolBar("toolBar");

    //工具栏添加快捷键
    toolBar->addAction(pNew);

    QPushButton *b = new QPushButton(this);
    b->setText("wen");
    //添加小控件
    toolBar->addWidget(b);

    connect(b,&QPushButton::clicked,
            [=]()
            {
                b->setText("qing");
            }

            );


    //状态栏
    QStatusBar *staBar = statusBar();

    QLabel *label = new QLabel(this);
    label->setText("Normal text file");
    staBar->addWidget(label);
    //addWidget 从左往右依次添加
    staBar->addWidget(new QLabel("2",this));

    //addPermanentWidget 从右往左依次添加
    staBar->addPermanentWidget(new QLabel("3",this));

    //核心控件
    QTextEdit *Text_Edit = new QTextEdit(this);
    setCentralWidget(Text_Edit);

    //浮动窗口
    QDockWidget *Dock_Widget = new QDockWidget(this);
    addDockWidget(Qt::BottomDockWidgetArea,Dock_Widget);

    //添加浮动窗口控件
    QTextEdit *Text_Edit1 = new QTextEdit(this);
    Dock_Widget->setWidget(Text_Edit1);

}

MainWindow::~MainWindow()
{

}
