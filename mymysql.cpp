#include "mymysql.h"
#include <QMessageBox>
#include <QObject>
#include <string.h>

//���е��й�MYSQL API������Ӿ��������

//��������Ŀ����ʵ�ַ�װ����װ���к�mysql��صĺ���
//��������Ŀ����ʵ�ַ�װ����װ���к�MYSQL��صĺ���
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
        //QMessageBox::information(0, "dd", mysql_error(&mysql));//�˴�ֻ����0
        //QMessageBox::information(this, tr("dd"), tr("dd"));//����tr��object���ۣ�

        return -1;
    }
    else
    {
        mysql_query(connection, "set names utf8");
        return 0;
    }
}

const char * mymysql::geterror()//�����ִ����ʱ�䣬����������message�Ի����Լ����ڿ��Ե���
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

int mymysql::sql_open(const char *SQL, QStandardItemModel **p)
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

    int rowcount = mysql_affected_rows(connection);//�����������SQL���ִ�к��ж��ٺ�
    int fieldcount = mysql_field_count(connection);//�����ж�����

    *p = new QStandardItemModel(rowcount, fieldcount);
    MYSQL_FIELD *field;
    int i = 0, j = 0;
    for(i = 0; i < fieldcount; i++)
    {
        field = mysql_fetch_field(result);
        (*p)->setHeaderData(i, Qt::Horizontal, field->name);
    }

    for(i = 0; i < rowcount; i++)//����ÿһ��
    {
        MYSQL_ROW row = mysql_fetch_row(result);
        for(j = 0; j < fieldcount; j++)
        {
            (*p)->setData((*p)->index(i, j, QModelIndex()), row[j]);
        }
    }


    mysql_free_result(result);//�ͷ�ͨ��mysql_store_result����������ڴ�ռ�
    return 0;
}
