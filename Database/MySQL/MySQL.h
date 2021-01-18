#include "MySqlAbstract.h"

class MySQL : public MySqlAbstract {
public:
    MySQL(MySQL_Info &info);
    virtual ~MySQL();
    virtual bool connectToMysql();
    virtual void operateMysqlSelect(const char *Mysql_Sentence);
    virtual void operateMysqlQuery(const char *Mysql_Sentence);
    virtual void resetConn();
    virtual void disconnectToMysql();

private:

};
