#include "mymysql.h"
#include <QMessageBox>
#include <QObject>


//��������Ŀ����ʵ�ַ�װ����װ���к�mysql��صĺ���
//��������Ŀ����ʵ�ַ�װ����װ���к�MYSQL��صĺ���
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
        QMessageBox::information(0, QObject::tr("�ɹ��ؾ�"), QObject::tr("Ҫ���ü���"));

        return -1;
    }
    else
        return 0;
}
