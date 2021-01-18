#include <iostream>
#include <string.h>
#include <unistd.h>
#include "zmq.hpp"

// #define CXX_PROCESS

#ifdef CXX_PROCESS
int main(int argc, char const *argv[])
{
    zmq::context_t ctx(1);
    zmq::socket_t socket(ctx, ZMQ_REQ);
    socket.connect("tcp://localhost:5555");

    while (1)
    {

        zmq::message_t msg("hello world\n", 13);
        if (!socket.send(msg))
        {
            std::cout << "REQ : zmq_send faild" << std::endl;
            break;
        }

        zmq::message_t request;
        socket.recv(request);
        std::printf("%s\n", request.data());
        sleep(1);
    }

    return 0;
}
#else

int main(int argc, char const *argv[])
{
    int ret;
    char data[1024];
    void *ctx, *socket;
    ctx = zmq_ctx_new();
    socket = zmq_socket(ctx, ZMQ_REQ);
    zmq_connect(socket, "tcp://localhost:5555");

    while (1)
    {
        if ((ret = zmq_send(socket, "hello", 5, 0)) < 0)
            printf("REQ : zmq_send faild");
        sleep(3);
        bzero(data, sizeof(data) - 1);
        if ((ret = zmq_recv(socket, data, sizeof(data) - 1, 0)) < 0)
            printf("REQ : zmq_recv faild");
        printf("REQ : recv msg %s\n", data);
    }

    zmq_close(socket);
    zmq_ctx_destroy(ctx);

    return 0;
}

#endif
