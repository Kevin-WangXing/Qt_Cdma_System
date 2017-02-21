#ifndef MYMYSQL_H
#define MYMYSQL_H

//路径C语言使用/符号
#include <windows.h>
#include <C:/mymysql/mysql/include/mysql.h>
#include <QStandardItemModel>
class mymysql
{
public:
    mymysql();
    const char *geterror();//返回一个有效地址，
    //第一个参数代表server IP地址，第二个用户名，第三个密码，第四个数据库名称
    int sql_connect(const char *Hostname, const char *User,
                    const char *Passwd, const char *Dbname);
    void sql_disconnet();
    int sql_exec(const char *SQL);
    int sql_open(const char *SQL, QStandardItemModel **p);

private:
    MYSQL *connection;
    MYSQL mysql;
    char buf[1024];//存放错误描述  geterror()
};

#endif // MYMYSQL_H
