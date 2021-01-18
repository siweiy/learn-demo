#include "MySQL.h"

MySQL::MySQL(MySQL_Info &info) 
    : MySqlAbstract(info) {
    
    if (0 != mysql_library_init(0, NULL, NULL))
    {
        std::cout << "mysql_library_init() failed" << std::endl;
    }
}

MySQL::~MySQL() {
    mysql_library_end();
}

bool MySQL::connectToMysql() {
    //初始化数据结构
    mysql_init(m_bMysql.get());

    //在连接数据库之前，设置额外的连接选项
    if (0 != mysql_options(m_bMysql.get(), MYSQL_SET_CHARSET_NAME, "gbk")) {
        std::cout << "mysql_options() failed" << std::endl;
    }

    if (m_bMysql.get() != NULL && mysql_real_connect(m_bMysql.get(),
                                                     m_bInfo.host.c_str(),
                                                     m_bInfo.user.c_str(),
                                                     m_bInfo.pswd.c_str(),
                                                     m_bInfo.database.c_str(),
                                                     m_bInfo.port, NULL, 0)) {
        std::cout << "Connect_to_Mysql Success" << std::endl;
        return true;
    } else {
        std::cout << "Connect_to_Mysql Failed" << std::endl;
        std::cout << mysql_error(m_bMysql.get()) << std::endl;
        return false;
    }
}

// select 视情况封装
void MySQL::operateMysqlSelect(const char *Mysql_Sentence) {

    if (0 == mysql_query(m_bMysql.get(), Mysql_Sentence)) {
        // 返回0表示插入、更新等操作
        if (mysql_field_count(m_bMysql.get()) != 0) {
            MYSQL_RES *result = NULL;
            result = mysql_store_result(m_bMysql.get());

            // mysql_num_rows() 返回结果集中行的数目。此命令仅对 SELECT 语句有效。
            // 要取得被 INSERT，UPDATE 或者 DELETE 查询所影响到的行的数目，
            // 用 mysql_affected_rows()。

            // 行
            unsigned int rows = (unsigned int)mysql_num_rows(result);
            std::cout << "总记录条数： " << rows << std::endl;

            // 列
            unsigned int fields = mysql_num_fields(result);
            std::cout << "每条记录总共 " << fields << " 个字段" << std::endl;

            // 字段
            MYSQL_FIELD *field = NULL;
            for (unsigned int i = 0; i < fields; i++) {
                field = mysql_fetch_field_direct(result, i);
                std::cout << field->name << "\t\t";
            }
            std::cout << std::endl;

            // 一行行输出信息
            MYSQL_ROW row = NULL;
            while ((row = mysql_fetch_row(result)) != NULL) {
                for (unsigned int i = 0; i < fields; ++i) {
                    if (row[i] != NULL) {
                        std::cout << row[i] << "\t\t";
                    } else {
                        std::cout << "null"
                                  << "\t\t";
                    }
                }
                std::cout << std::endl;
            }
            mysql_free_result(result);
        }
    } else {
        std::cout << "Operate_Mysql Select Failed" << std::endl;
        std::cout << mysql_error(m_bMysql.get()) << std::endl;
    }
}

void MySQL::operateMysqlQuery(const char *Mysql_Sentence)
{
    if (0 == mysql_query(m_bMysql.get(), Mysql_Sentence)) {
        std::cout << "Operate_Mysql Query Success" << std::endl;
        // std::cout << "Query:" << mysql_affected_rows(m_bMysql.get()) << std::endl;
    } else {
        std::cout << "Operate_Mysql Query Failed" << std::endl;
        std::cout << mysql_error(m_bMysql.get()) << std::endl;
    }
}

void MySQL::disconnectToMysql() {
    mysql_close(m_bMysql.get());
}

void MySQL::resetConn() {
    mysql_reset_connection(m_bMysql.get());// 恢复到刚连接时的状态
}
