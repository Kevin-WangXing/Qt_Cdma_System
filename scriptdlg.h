#ifndef SCRIPTDLG_H
#define SCRIPTDLG_H

#include <QDialog>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>

class scriptDlg : public QDialog
{
    Q_OBJECT
public:
    explicit scriptDlg(QWidget *parent = 0);
    QString SQL;

    bool islogin;

private:
    QLabel *label0;
    QPushButton *okBtn, *cancelBtn;
    QTextEdit *textEditSQL;

private slots:
    void onBtnclick();
    void cancelBtnclick();

};

#endif // SCRIPTDLG_H
