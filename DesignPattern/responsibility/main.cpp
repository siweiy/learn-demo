// 责任链模式：很多对象由每一个对象对其下家的引用而接起来形成一条链
// 系统可以在不影响客户端的情况下动态的重新组织链和分配责任。
// 处理者有两个选择：承担责任或者把责任推给下家。一个请求可以最终不被任何接收端对象所接受。

#include "Handler.h"

int main()
{
    //创建责任链
    //一般将责任大（最有可能处理用户请求）的对象放在前面
    Handler *beijing = new Beijing();
    Handler *tianjin = new Tianjin();
    Handler *shanghai = new Shanghai();
    Handler *guangdong = new Guangdong();

    beijing->setNextHandler(tianjin);
    tianjin->setNextHandler(shanghai);
    shanghai->setNextHandler(guangdong);

    //用户进行请求
    //从责任链的第一个对象开始
    beijing->handleRequest("10029812340930091");

    return 0;
}
