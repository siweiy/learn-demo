
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <zmq.h>

int main(int argc, char const *argv[])
{
    void *zmq_ctx = zmq_ctx_new();
    void *socket = zmq_socket(zmq_ctx, ZMQ_REQ);
    if (zmq_connect(socket, "tcp://localhost:5559") < 0)
    {
        return -1;
    }

    int ret;
    while (true)
    {
        zmq_msg_t msg;
        zmq_msg_init_size(&msg, 5);
        memcmp(zmq_msg_data(&msg), "hello", 5);
        zmq_msg_send(&msg, socket, 0);
        zmq_msg_close(&msg);

        sleep(1);

        zmq_msg_init(&msg);
        ret = zmq_msg_recv(&msg, socket, 0);


        char *string = new char[ret + 1];
        memcpy(string, zmq_msg_data(&msg), ret);
        zmq_msg_close(&msg);

        string[ret] = 0;

        printf(string);
        fflush(stdout);

        delete[] string;
    }

    zmq_close(socket);
    zmq_ctx_destroy(zmq_ctx);

    return 0;
}
