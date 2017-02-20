#include "mainwindow.h"
#include <QTextCodec>
#include <QIcon>
#include <QMessageBox>
#include <QWidget>
#include <QMdiSubWindow>
#include "logindlg.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QTextCodec *codec = QTextCodec::codecForName("system");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);

    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);
    mdiArea->setBackground(Qt::NoBrush);
    //将QMdiArea组里的background 下的style设置成no brush    就是不用任何画刷填充颜色
    mdiArea->setStyleSheet("background-image: url(1.jpg);");//背景设置为1.
    //mdiArea->setStyleSheet("border-image: url(1.jpg);");
    //利用stylesheet设置background-image或者borde,r-image前者是平铺方式设置背景，后者是拉伸方式设置背景

    QIcon icon("main.png"); //setWindowIcon(QIcon("main.png"));
    setWindowIcon(icon);//设置窗口光标。在CDMA前面

    createActions();
    createMenus();

    setWindowTitle(tr("CDMA无线基站管理系统"));

}

MainWindow::~MainWindow()
{

}

void MainWindow::createMenus()
{
    adminMenu = menuBar()->addMenu(tr("管理"));
    adminMenu->addAction(loginAction);
    adminMenu->addAction(logoutAction);
    adminMenu->addSeparator();
    adminMenu->addAction(exitAction);

    dataMenu = menuBar()->addMenu(tr("数据"));
    dataMenu->addAction(scripAction);

    windowMenu = menuBar()->addMenu(tr("窗口"));
    windowMenu->addAction(cascadeAction);
    windowMenu->addAction(tileAction);

    helpMenu = menuBar()->addMenu(tr("帮助"));
    helpMenu->addAction(helpAction);
    helpMenu->addAction(aboutAction);


}

void MainWindow::createActions()
{
    loginAction = new QAction(tr("登录"), this);
    loginAction->setShortcut(tr("Ctrl+U"));
    connect(loginAction, SIGNAL(triggered()), this, SLOT(on_login()));

    logoutAction = new QAction(this);
    logoutAction->setText(tr("注销"));
    logoutAction->setShortcut(tr("Ctrl+B"));
    connect(logoutAction, SIGNAL(triggered()), this, SLOT(on_logout()));

    exitAction = new QAction(tr("退出"), this);
    exitAction->setShortcut(tr("Ctrl+W"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(on_exit()));

    scripAction = new QAction(tr("执行脚本"), this);
    scripAction->setShortcut(tr("Ctrl+P"));
    connect(scripAction, SIGNAL(triggered()), this, SLOT(on_script()));

    cascadeAction = new QAction(tr("层叠"), this);
    cascadeAction->setShortcut(tr("Ctrl+Q"));
    connect(cascadeAction, SIGNAL(triggered()), this, SLOT(cascadeSubWindows()));

    tileAction = new QAction(tr("并列"), this);
    tileAction->setShortcut(tr("Ctrl+R"));
    connect(tileAction, SIGNAL(triggered()), this, SLOT(tileSubWindows()));

    helpAction = new QAction(tr("帮助"), this);
    helpAction->setShortcut(tr("Ctrl+S"));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(on_help()));

    aboutAction = new QAction(tr("关于"), this);
    aboutAction->setShortcut(tr("Ctrl+T"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(on_about()));


}

void MainWindow::on_login()
{
//    logindlg *dlg = new logindlg;//非模式，错误
//    dlg->show();
    //QMessageBox::information(this, tr("提示"), tr("Success"), QMessageBox::Ok | QMessageBox::No);
    logindlg dlg;//将对话框实例
    dlg.exec();//调用exec产生一个模式对话框，程序在exec函数这个地方阻塞

    if(dlg.islogin)
    {
        if((dlg.userid == "dbuser1") && (dlg.passwd == "wx456456"))
            QMessageBox::information(this, "", "登录成功");
        else
            QMessageBox::information(this, "", "登陆失败");
    }
}

void MainWindow::on_logout()
{
}

void MainWindow::on_exit()
{
        close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //通过question函数的返回值来判断用户点击的是yes还是NO
    QMessageBox::StandardButton button = QMessageBox::question(this, "提示",
                                                                  "是否退出程序",
                                                                  QMessageBox::Yes | QMessageBox::No);
    if(button == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}

void MainWindow::on_script()
{
    showsub();
}

void MainWindow::tileSubWindows()
{
    mdiArea->tileSubWindows();
}

void MainWindow::on_help()
{
    QMessageBox::information(this, tr("成功秘诀"), tr("要多敲键盘"));

}

void MainWindow::on_about()
{
    QMessageBox::about(this, tr("关于"), tr("版本不收费，随意使用"));

}

void MainWindow::cascadeSubWindows()
{
    mdiArea->cascadeSubWindows();//cascadeSubWindows这个函数就是mdiarea下的重叠函数
}

void MainWindow::showsub()
{
    QWidget *w1 = new QWidget;
    w1->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget时，自动将这个widget delete
    mdiArea->addSubWindow(w1);
    w1->setWindowTitle("SQL");
    w1->setStyleSheet("border-image: url(3.jpg);");//设置widget背景图片
    w1->show();
    mdiArea->activeSubWindow()->resize(width() - 100, height() - 100);//设置widget活动窗口大小

}
