#ifndef MYMYSQL_H
#define MYMYSQL_H

//·��C����ʹ��/����
#include <windows.h>
#include <C:/mymysql/mysql/include/mysql.h>
#include <QStandardItemModel>
class mymysql
{
public:
    mymysql();
    const char *geterror();//����һ����Ч��ַ��
    //��һ����������server IP��ַ���ڶ����û��������������룬���ĸ����ݿ�����
    int sql_connect(const char *Hostname, const char *User,
                    const char *Passwd, const char *Dbname);
    void sql_disconnet();
    int sql_exec(const char *SQL);
    int sql_open(const char *SQL, QStandardItemModel **p);

private:
    MYSQL *connection;
    MYSQL mysql;
    char buf[1024];//��Ŵ�������  geterror()
};

#endif // MYMYSQL_H
