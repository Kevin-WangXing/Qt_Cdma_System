#include "logindlg.h"
#include <QGridLayout>
#include <QPalette>

logindlg::logindlg(QWidget *parent) :
    QDialog(parent)
{
    islogin = false;
    label0 = new QLabel;
    label0->setText(tr("�û���"));
    label1 = new QLabel;
    label1->setText(tr("��¼����"));
    label2 = new QLabel;
    label2->setText(tr("���ݿ�����"));
    label3 = new QLabel;
    label3->setText(tr("�����IP"));

    lineEditUserID = new QLineEdit;
    lineEditPasswd = new QLineEdit;
    lineEditPasswd->setEchoMode(QLineEdit::Password);
    lineEditDBName = new QLineEdit;
    lineEditHostIP = new QLineEdit;

    loginBtn = new QPushButton;
    loginBtn->setText(tr("��¼"));
    logoutBtn = new QPushButton;
    logoutBtn->setText(tr("ȡ��"));

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(label0, 0, 0);
    layout->addWidget(lineEditUserID, 0, 1);
    layout->addWidget(label1, 1, 0);
    layout->addWidget(lineEditPasswd, 1, 1);
    layout->addWidget(label2, 2, 0);
    layout->addWidget(lineEditDBName, 2, 1);
    layout->addWidget(label3, 3, 0);
    layout->addWidget(lineEditHostIP, 3, 1);
    layout->addWidget(loginBtn, 4, 0);
    layout->addWidget(logoutBtn, 4, 1);

    layout->setColumnStretch(0, 1);//����0��
    layout->setColumnStretch(1, 1);//����1��
    layout->setMargin(15);//����layout�߾�
    layout->setSpacing(10);//����layout���пؼ��Ϳؼ��ļ��
    layout->setSizeConstraint(QLayout::SetFixedSize);//���öԻ����С���ɸı�

    //���ñ���ͼƬ
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap("2.jpg")));
    setPalette(palette);

    setWindowTitle(tr("��¼"));

    connect(loginBtn, SIGNAL(clicked()), this, SLOT(loginBtnOn_click()));
    connect(logoutBtn, SIGNAL(clicked()), this, SLOT(logoutBtnOn_click()));

}

void logindlg::loginBtnOn_click()
{
    userid = lineEditUserID->text();
    passwd = lineEditPasswd->text();
    dbname = lineEditDBName->text();
    hostip = lineEditHostIP->text();
    islogin = true;//ֻ�е���˰�ť��λ��
    close();
}

void logindlg::logoutBtnOn_click()
{
    close();
}
