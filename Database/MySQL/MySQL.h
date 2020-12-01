#include "IMySQL.h"

class MySQL : public IMySQL {
public:
    MySQL(MySQL_Info &info);
    ~MySQL();
    virtual void initMysqlInfo();
    virtual bool connectToMysql();
    virtual void operateMysqlSelect(const char *Mysql_Sentence);
    virtual void operateMysqlQuery(const char *Mysql_Sentence);
    virtual void disconnectToMysql();

private:

};
