#ifndef MYMYSQL_H
#define MYMYSQL_H

//路径C语言使用/符号
#include <windows.h>
#include <C:/mymysql/mysql/include/mysql.h>
class mymysql
{
public:
    mymysql();
    //第一个参数代表server IP地址，第二个用户名，第三个密码，第四个数据库名称
    int sql_connect(const char *Hostname, const char *User,
                    const char *Passwd, const char *Dbname);

private:
    MYSQL *connection;
    MYSQL mysql;
};

#endif // MYMYSQL_H
