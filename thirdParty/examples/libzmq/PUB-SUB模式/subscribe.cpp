#include <stdio.h>
#include <zmq.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    void *ctx, *sock;
    int ret = 0;
    char data[1024];
    ctx = zmq_ctx_new();
    sock = zmq_socket(ctx, ZMQ_SUB);
    zmq_setsockopt(sock, ZMQ_SUBSCRIBE, "", 0);
    ret = zmq_connect(sock, "tcp://127.0.0.1:5555");
    while (1)
    {
        bzero(data, sizeof(data));
        if (ret = zmq_recv(sock, data, sizeof(data) - 1, 0) < 0)
            printf("SUB : zmq_recv faild");
        printf("SUB:recv msg : %s\n", data);
        sleep(2);
    }
    zmq_close(sock);
    zmq_ctx_destroy(ctx);
    return 0;
}
