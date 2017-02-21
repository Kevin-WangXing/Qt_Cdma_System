#include "mymysql.h"
#include <QMessageBox>
#include <QObject>
#include <string.h>

//所有的有关MYSQL API函数电泳，都放在

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

int mymysql::sql_open(const char *SQL)
{
    if(mysql_query(connection, SQL) != 0)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if(result == NULL)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        return -1;
    }

    int rowcount = mysql_affected_rows(connection);//这个函数返回SQL语句执行后有多少航
    int fieldcount = mysql_field_count(connection);//返回有多少列
    MYSQL_FIELD *field;
    while(1)
    {
        field = mysql_fetch_field(result);
        if(field == NULL)
            break;
        QMessageBox::information(0, "", field->name);
    }

    int i = 0, j = 0;
    for(; i < rowcount; i++)//遍历每一行
    {
        MYSQL_ROW row = mysql_fetch_row(result);
        for(; j < fieldcount; j++)
        {
            QMessageBox::information(0, "", row[j]);
        }
    }


    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}
