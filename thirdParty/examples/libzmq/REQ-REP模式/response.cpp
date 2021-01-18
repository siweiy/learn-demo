#include <iostream>
#include <unistd.h>
#include "zmq.hpp"

#ifdef CXX_PROCESS

int main(int argc, char const *argv[])
{
    zmq::context_t ctx(1);
    zmq::socket_t socket(ctx, ZMQ_REP);
    socket.bind("tcp://*:5555");

    while (1)
    {
        zmq::message_t request;
        if (!socket.recv(request))
        {
            std::cout << "REQ : zmq_recv faild" << std::endl;
            break;
        }
        std::printf("%s\n", request.data());

        zmq::message_t msg("Recv ok\n", 7);
        socket.send(msg);
    }

    return 0;
}

#else

int main(void)
{
    void *ctx, *sock;
    int ret = 0;
    char data[1024];
    ctx = zmq_ctx_new();
    sock = zmq_socket(ctx, ZMQ_REP);
    ret = zmq_bind(sock, "tcp://127.0.0.1:5555");
    while (1)
    {
        bzero(data, sizeof(data) - 1);
        if ((ret = zmq_recv(sock, data, sizeof(data) - 1, 0)) < 0)
            printf("REP : zmq_recv faild");
        sleep(3);
        printf("REP : recv msg %s\n", data);
        memcpy(data, "world", 5);
        if ((ret = zmq_send(sock, data, 5, 0)) < 0)
            printf("REP : zmq_send faild");
    }
    zmq_close(sock);
    zmq_ctx_destroy(ctx);
    return 0;
}

#endif