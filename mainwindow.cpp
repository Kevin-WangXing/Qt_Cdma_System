#include "mainwindow.h"
#include <QTextCodec>
#include <QIcon>
#include <QMessageBox>
#include <QWidget>
#include <QMdiSubWindow>
#include "logindlg.h"
#include <QStandardItemModel>
#include <QTableView>
#include "scriptdlg.h"
#include "mymysql.h"

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

    //���Ӵ��ڵķ�Χ���������ڵ���ʾ��Χ���������Զ���Ӻ��������
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    //���Ӵ��ڵķ�Χ���������ڵ���ʾ��Χ���������Զ���Ӻ����������
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

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
        mymysql db;
        //data()���Է���һ���ַ�ָ��
        int res = db.sql_connect(dlg.hostip.toStdString().data(),
                                 dlg.userid.toStdString().data(),
                                 dlg.passwd.toStdString().data(),
                                 dlg.dbname.toStdString().data());
        if(res == -1)
            QMessageBox::information(this, "", "��¼ʧ��");
        else
            QMessageBox::information(this, "", "��½�ɹ�");
    }

//    if(dlg.islogin)
//    {
//        if((dlg.userid == "dbuser1") && (dlg.passwd == "wx456456"))
//            QMessageBox::information(this, "", "��¼�ɹ�");
//        else
//            QMessageBox::information(this, "", "��½ʧ��");
//    }
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
    //showview();
    scriptDlg dlg;//����scriptdlg���ʵ����
    dlg.exec();
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

void MainWindow::showview()//����һ�����
{
    QStandardItemModel *model = new QStandardItemModel(5, 3);//����һ��5��3�еı��

    //����module���б�ͷ����
    model->setHeaderData(0, Qt::Horizontal, "����");
    model->setHeaderData(1, Qt::Horizontal, "�Ա�");
    model->setHeaderData(2, Qt::Horizontal, "����");
    //����module��ÿһ����Ԫ�������
    model->setData(model->index(0, 0, QModelIndex()), tr("����"));
    model->setData(model->index(0, 1, QModelIndex()), "�Ա�");
    model->setData(model->index(0, 2, QModelIndex()), "30");

    model->setData(model->index(1, 0, QModelIndex()), "����");
    model->setData(model->index(1, 1, QModelIndex()), "��");
    model->setData(model->index(1, 2, QModelIndex()), "30");

    model->setData(model->index(2, 0, QModelIndex()), "����");
    model->setData(model->index(2, 1, QModelIndex()), "Ů");
    model->setData(model->index(2, 2, QModelIndex()), "10");

    model->setData(model->index(3, 0, QModelIndex()), "����");
    model->setData(model->index(3, 1, QModelIndex()), "Ů");
    model->setData(model->index(3, 2, QModelIndex()), "40");

    model->setData(model->index(4, 0, QModelIndex()), "������");
    model->setData(model->index(4, 1, QModelIndex()), "��");
    model->setData(model->index(4, 2, QModelIndex()), "30");

    QTableView *view = new QTableView;
    view->setAttribute(Qt::WA_DeleteOnClose);
    //view��closeʱ����Զ�delete�����ʱ�����view
    mdiArea->addSubWindow(view);
    view->setStyleSheet("border-image: url(3.jpg);");//���߱���ͼƬ

    //view�̳���widget�����û��model,��ôview������ʾ�κ�����
    view->setModel(model);
    view->show();
    mdiArea->activeSubWindow()->resize(width() - 100, height() - 100);
}
