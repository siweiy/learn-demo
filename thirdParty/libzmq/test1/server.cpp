#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <zmq.hpp> // zmq作用域

/*
ØMQ支持以下几种传输协议：
tcp :点对点传输协议tcp，参见zmq_tcp(7)
ipc :本地线程间通信，参见zmq_ipc(7)
inproc :本地进程内（线程间）通信，参见zmq_inproc(7)
pgm,epgm:使用PGM进行可靠的多路广播，参见zmq_pgm(7)
除了ZMQ_PAIR之外，所有的ZMQ socket类型都支持一对多和多对一传输方式。这种精确的多路传输依赖于在zmq_socket(3)中定义的socket类型。
ipc和tcp传输方式接受通配符形式的地址
*/

#if 0
static int s_send(void *socket, char *string)
{
    int rc;
    
    zmq_msg_t msg;
    zmq_msg_init_size(&msg, 5);
    memcpy(zmq_msg_data(&msg), string, strlen(string));
    
    rc = zmq_msg_send(&msg, socket, 0);
    zmq_msg_close(&msg);
 
    return rc;
}
 
static char *s_recv(void *socket)
{
    int rc;
    zmq_msg_t msg;
    zmq_msg_init(&msg);
    
    rc = zmq_msg_recv(&msg, socket, 0);
    if(rc == -1)
        return NULL;
    
    char *string = (char*)malloc(rc + 1);
    memcpy(string, zmq_msg_data(&msg), rc);
    zmq_msg_close(&msg);
    
    string[rc] = 0;
    return string;
}

int main()
{
    // 1.创建上下文
    void *context = zmq_ctx_new();
 
    // 2.创建、绑定套接字
    void *responder = zmq_socket(context, ZMQ_REP);
    zmq_bind(responder, "tcp://*:5555");
 
    int rc;
    // 3.循环接收数据、发送数据
    while(1)
    {
        // 4.接收数据
        char *request = s_recv(responder);
        assert(request != NULL);
        printf("Request: %s\n", request);
        free(request);
 
        // 5.回送数据
        char *reply = "World";
        rc = s_send(responder, reply);
        assert(rc > 0);
    }
 
    // 6.关闭套接字、销毁上下文
    zmq_close(responder);
    zmq_ctx_destroy(context);
 
    return 0;
}

#else

int main()
{
    //创建新的上下文
    zmq::context_t context(1);

    //创建套接字、绑定地址
    zmq::socket_t socket(context, ZMQ_REP);
    socket.bind("tcp://*:5555");

    //循环发送数据、接收数据
    while(true)
    {
        //阻塞接收数据
        zmq::message_t request;
        socket.recv(&request);
		
        puts((const char *)request.data());

        //这个中间可以做一些事情，我们在此处休眠1秒
        sleep(1);

        //发送数据
        zmq::message_t reply(5);
        memcpy((void*)reply.data(), "World", 5);
        socket.send(reply);
    }
}
#endif
