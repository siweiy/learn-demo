#include <stdio.h>
#include <zmq.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    void *ctx, *sock;
    int ret = 0;
    char data[1024];
    int i = 0;
    ctx = zmq_ctx_new();
    sock = zmq_socket(ctx, ZMQ_PUB);
    ret = zmq_bind(sock, "tcp://127.0.0.1:5555");
    while (1)
    {
        sprintf(data, "[%d]PUB: Hello World", i++);
        ret = zmq_send(sock, data, strlen(data), 0);
        sleep(2);
    }
    zmq_close(sock);
    zmq_ctx_destroy(ctx);
    return 0;
}