#include "scriptdlg.h"
#include <QGridLayout>
#include <QHBoxLayout>

scriptDlg::scriptDlg(QWidget *parent) :
    QDialog(parent)
{
    islogin = false;
    okBtn = new QPushButton;
    okBtn->setText(tr("ִ��"));
    cancelBtn = new QPushButton;
    cancelBtn->setText(tr("ȡ��"));
    label0 = new QLabel(tr("������SQL"));

    textEditSQL = new QTextEdit;

    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(okBtn);
    layout1->addWidget(cancelBtn);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(label0, 0, 0);
    layout->addWidget(textEditSQL, 0, 1);
    layout->addLayout(layout1, 1, 1);

    connect(okBtn, SIGNAL(clicked()), this, SLOT(onBtnclick()));
    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(cancelBtnclick()));

}

void scriptDlg::onBtnclick()
{
    SQL = textEditSQL->toPlainText();//TextediTû��text�������õ�textedit���û���������ݺ���Ϊtoplainedit
    islogin = true;
    close();
}

void scriptDlg::cancelBtnclick()
{
    close();
}
