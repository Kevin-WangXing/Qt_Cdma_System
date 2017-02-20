#include "scriptdlg.h"
#include <QGridLayout>
#include <QHBoxLayout>

scriptDlg::scriptDlg(QWidget *parent) :
    QDialog(parent)
{
    okBtn = new QPushButton;
    okBtn->setText(tr("执行"));
    cancelBtn = new QPushButton;
    cancelBtn->setText(tr("取消"));
    label0 = new QLabel(tr("请输入SQL"));

    textEditSQL = new QTextEdit;

    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(okBtn);
    layout1->addWidget(cancelBtn);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(label0, 0, 0);
    layout->addWidget(textEditSQL, 0, 1);
    layout->addLayout(layout1, 1, 1);

}
