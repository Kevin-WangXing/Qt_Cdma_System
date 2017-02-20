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
    //��QMdiArea�����background �µ�style���ó�no brush    ���ǲ����κλ�ˢ�����ɫ
    mdiArea->setStyleSheet("background-image: url(1.jpg);");//��������Ϊ1.
    //mdiArea->setStyleSheet("border-image: url(1.jpg);");
    //����stylesheet����background-image����borde,r-imageǰ����ƽ�̷�ʽ���ñ��������������췽ʽ���ñ���

    QIcon icon("main.png"); //setWindowIcon(QIcon("main.png"));
    setWindowIcon(icon);//���ô��ڹ�ꡣ��CDMAǰ��

    createActions();
    createMenus();

    setWindowTitle(tr("CDMA���߻�վ����ϵͳ"));

}

MainWindow::~MainWindow()
{

}

void MainWindow::createMenus()
{
    adminMenu = menuBar()->addMenu(tr("����"));
    adminMenu->addAction(loginAction);
    adminMenu->addAction(logoutAction);
    adminMenu->addSeparator();
    adminMenu->addAction(exitAction);

    dataMenu = menuBar()->addMenu(tr("����"));
    dataMenu->addAction(scripAction);

    windowMenu = menuBar()->addMenu(tr("����"));
    windowMenu->addAction(cascadeAction);
    windowMenu->addAction(tileAction);

    helpMenu = menuBar()->addMenu(tr("����"));
    helpMenu->addAction(helpAction);
    helpMenu->addAction(aboutAction);


}

void MainWindow::createActions()
{
    loginAction = new QAction(tr("��¼"), this);
    loginAction->setShortcut(tr("Ctrl+U"));
    connect(loginAction, SIGNAL(triggered()), this, SLOT(on_login()));

    logoutAction = new QAction(this);
    logoutAction->setText(tr("ע��"));
    logoutAction->setShortcut(tr("Ctrl+B"));
    connect(logoutAction, SIGNAL(triggered()), this, SLOT(on_logout()));

    exitAction = new QAction(tr("�˳�"), this);
    exitAction->setShortcut(tr("Ctrl+W"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(on_exit()));

    scripAction = new QAction(tr("ִ�нű�"), this);
    scripAction->setShortcut(tr("Ctrl+P"));
    connect(scripAction, SIGNAL(triggered()), this, SLOT(on_script()));

    cascadeAction = new QAction(tr("���"), this);
    cascadeAction->setShortcut(tr("Ctrl+Q"));
    connect(cascadeAction, SIGNAL(triggered()), this, SLOT(cascadeSubWindows()));

    tileAction = new QAction(tr("����"), this);
    tileAction->setShortcut(tr("Ctrl+R"));
    connect(tileAction, SIGNAL(triggered()), this, SLOT(tileSubWindows()));

    helpAction = new QAction(tr("����"), this);
    helpAction->setShortcut(tr("Ctrl+S"));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(on_help()));

    aboutAction = new QAction(tr("����"), this);
    aboutAction->setShortcut(tr("Ctrl+T"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(on_about()));


}

void MainWindow::on_login()
{
//    logindlg *dlg = new logindlg;//��ģʽ������
//    dlg->show();
    //QMessageBox::information(this, tr("��ʾ"), tr("Success"), QMessageBox::Ok | QMessageBox::No);
    logindlg dlg;//���Ի���ʵ��
    dlg.exec();//����exec����һ��ģʽ�Ի��򣬳�����exec��������ط�����

    if(dlg.islogin)
    {
        if((dlg.userid == "dbuser1") && (dlg.passwd == "wx456456"))
            QMessageBox::information(this, "", "��¼�ɹ�");
        else
            QMessageBox::information(this, "", "��½ʧ��");
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
    //ͨ��question�����ķ���ֵ���ж��û��������yes����NO
    QMessageBox::StandardButton button = QMessageBox::question(this, "��ʾ",
                                                                  "�Ƿ��˳�����",
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
    QMessageBox::information(this, tr("�ɹ��ؾ�"), tr("Ҫ���ü���"));

}

void MainWindow::on_about()
{
    QMessageBox::about(this, tr("����"), tr("�汾���շѣ�����ʹ��"));

}

void MainWindow::cascadeSubWindows()
{
    mdiArea->cascadeSubWindows();//cascadeSubWindows�����������mdiarea�µ��ص�����
}

void MainWindow::showsub()
{
    QWidget *w1 = new QWidget;
    w1->setAttribute(Qt::WA_DeleteOnClose);//����ر����widgetʱ���Զ������widget delete
    mdiArea->addSubWindow(w1);
    w1->setWindowTitle("SQL");
    w1->setStyleSheet("border-image: url(3.jpg);");//����widget����ͼƬ
    w1->show();
    mdiArea->activeSubWindow()->resize(width() - 100, height() - 100);//����widget����ڴ�С

}
