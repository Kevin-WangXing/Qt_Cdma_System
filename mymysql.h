#ifndef MYMYSQL_H
#define MYMYSQL_H

//·��C����ʹ��/����
#include <windows.h>
#include <C:/mymysql/mysql/include/mysql.h>
class mymysql
{
public:
    mymysql();
    //��һ����������server IP��ַ���ڶ����û��������������룬���ĸ����ݿ�����
    int sql_connect(const char *Hostname, const char *User,
                    const char *Passwd, const char *Dbname);

private:
    MYSQL *connection;
    MYSQL mysql;
};

#endif // MYMYSQL_H
