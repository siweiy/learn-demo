#include "MySQL.h"

int main()
{
    MySQL_Info info;
    info.user = "root";
    info.pswd = "123456";
    info.host = "172.16.100.147";
    info.database = "test";
    info.port = 3306;

    MySQL Mysql(info);
    Mysql.initMysqlInfo();

    if (Mysql.connectToMysql())
    {
        Mysql.operateMysqlQuery("create table if not exists \
                                   test_table(id int(4), name varchar(20) \
                                   character set gb2312 collate gb2312_chinese_ci)");

        Mysql.operateMysqlQuery("insert into test_table \
                                    values(1, 'aaa'), (2, 'bbb'), (3, 'ccc')");

        Mysql.operateMysqlQuery("insert into test_table(id) values(11), (22), (33)");

        Mysql.operateMysqlSelect("select * from test_table where id=22 lock in share mode");

        Mysql.operateMysqlSelect("select * from test_table for update");

        Mysql.operateMysqlQuery("update test_table set id=22 where name='aaa'");

        Mysql.operateMysqlQuery("alter table test_table rename re_test_table");

        Mysql.operateMysqlQuery("delete from re_test_table where  id=2"); //删除表中的特定条件的记录

        Mysql.operateMysqlQuery("truncate table re_test_table"); //删除表中的所有数据记录，清空表
        // Mysql.Operate_Mysql_Modify("delete from test_table"); //删除表中的所有数据记录，清空表

        Mysql.operateMysqlQuery("drop table re_test_table"); //删除表

        Mysql.disconnectToMysql();
    }

    return 0;
}