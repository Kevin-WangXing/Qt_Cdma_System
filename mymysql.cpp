#include "mymysql.h"
#include <QMessageBox>
#include <QObject>
#include <string.h>

//建这个类的目的是实现封装，封装所有和mysql相关的函数
//建这个类的目的是实现封装，封装所有和MYSQL相关的函数
mymysql::mymysql()
{
    mysql_init(&mysql);
    connection = NULL;
    memset(buf, 0, sizeof(buf));
}

int mymysql::sql_connect(const char *Hostname, const char *User, const char *Passwd, const char *Dbname)
{
    connection = mysql_real_connect(&mysql, Hostname, User, Passwd, Dbname, 0, 0, 0);
    if(connection == NULL)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        //QMessageBox::information(0, "dd", mysql_error(&mysql));//此处只能用0
        //QMessageBox::information(this, tr("dd"), tr("dd"));//错误tr是object积累，

        return -1;
    }
    else
    {
        mysql_query(connection, "set names utf8");
        return 0;
    }
}

const char * mymysql::geterror()//当出现错误的时间，不弹出其他message对话框，自己窗口可以弹出
{
    return buf;
}

void mymysql::sql_disconnet()
{
    if(connection)
    {
        mysql_close(connection);
        connection = NULL;
    }
}

int mymysql::sql_exec(const char *SQL)
{
    if(mysql_query(connection, SQL) != 0)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        return -1;
    }
    return 0;
}
