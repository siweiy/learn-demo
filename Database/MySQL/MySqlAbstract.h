#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <mutex>
#include </usr/include/mysql/mysql.h>

typedef struct _MySQL_INFO {
    std::string user;       //username
    std::string pswd;       //password
    std::string host;       //host address
    std::string database;   //database
    unsigned int port;      //server port
}MySQL_Info;

class MySqlAbstract {
public:
    MySqlAbstract(MySQL_Info &info):m_bInfo(info) { m_bMysql.reset(new MYSQL()); };
    virtual ~MySqlAbstract() {};

    /* Connect to MYSQL */
    virtual bool connectToMysql() = 0;
    /* select informations */
    virtual void operateMysqlSelect(const char *Mysql_Sentence) = 0;
    /* Exec MYSQL instruction */
    virtual void operateMysqlQuery(const char *Mysql_Sentence) = 0;
    /* reconnected */
    virtual void resetConn() = 0;
    /* Disconnect */
    virtual void disconnectToMysql() = 0;

protected:
    std::shared_ptr<MYSQL> m_bMysql;
    MySQL_Info m_bInfo;
};
