#include "mymysql.h"
#include <QMessageBox>
#include <QObject>


//建这个类的目的是实现封装，封装所有和mysql相关的函数
//建这个类的目的是实现封装，封装所有和MYSQL相关的函数
mymysql::mymysql()
{
    mysql_init(&mysql);
    connection = NULL;
}

int mymysql::sql_connect(const char *Hostname, const char *User, const char *Passwd, const char *Dbname)
{
    connection = mysql_real_connect(&mysql, Hostname, User, Passwd, Dbname, 0, 0, 0);
    if(connection == NULL)
    {
        QMessageBox::information(0, "dd", mysql_error(&mysql));
        //QMessageBox::information(this, tr("dd"), tr("dd"));
        QMessageBox::information(0, QObject::tr("成功秘诀"), QObject::tr("要多敲键盘"));

        return -1;
    }
    else
        return 0;
}
