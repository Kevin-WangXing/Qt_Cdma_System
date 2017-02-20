#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QString>

class logindlg : public QDialog
{
    Q_OBJECT
public:
    explicit logindlg(QWidget *parent = 0);

private:
    QLabel *label0, *label1, *label2, *label3;
    QLineEdit *lineEditUserID, *lineEditPasswd, *lineEditDBName, *lineEditHostIP;
    QPushButton *loginBtn, *logoutBtn;
public:
    QString userid;
    QString passwd;
    QString dbname;
    QString hostip;
    bool islogin;

signals:

private slots:
    void loginBtnOn_click();
    void logoutBtnOn_click();

};

#endif // LOGINDLG_H
