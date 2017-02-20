#include "logindlg.h"
#include <QGridLayout>
#include <QPalette>

logindlg::logindlg(QWidget *parent) :
    QDialog(parent)
{
    islogin = false;
    label0 = new QLabel;
    label0->setText(tr("用户名"));
    label1 = new QLabel;
    label1->setText(tr("登录密码"));
    label2 = new QLabel;
    label2->setText(tr("数据库名称"));
    label3 = new QLabel;
    label3->setText(tr("服务端IP"));

    lineEditUserID = new QLineEdit;
    lineEditPasswd = new QLineEdit;
    lineEditPasswd->setEchoMode(QLineEdit::Password);
    lineEditDBName = new QLineEdit;
    lineEditHostIP = new QLineEdit;

    loginBtn = new QPushButton;
    loginBtn->setText(tr("登录"));
    logoutBtn = new QPushButton;
    logoutBtn->setText(tr("取消"));

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

    layout->setColumnStretch(0, 1);//设置0列
    layout->setColumnStretch(1, 1);//设置1列
    layout->setMargin(15);//设置layout边距
    layout->setSpacing(10);//设置layout当中控件和控件的间距
    layout->setSizeConstraint(QLayout::SetFixedSize);//设置对话框大小不可改变

    //设置背景图片
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap("2.jpg")));
    setPalette(palette);

    setWindowTitle(tr("登录"));

    connect(loginBtn, SIGNAL(clicked()), this, SLOT(loginBtnOn_click()));
    connect(logoutBtn, SIGNAL(clicked()), this, SLOT(logoutBtnOn_click()));

}

void logindlg::loginBtnOn_click()
{
    userid = lineEditUserID->text();
    passwd = lineEditPasswd->text();
    dbname = lineEditDBName->text();
    hostip = lineEditHostIP->text();
    islogin = true;//只有点击了按钮财位真
    close();
}

void logindlg::logoutBtnOn_click()
{
    close();
}
