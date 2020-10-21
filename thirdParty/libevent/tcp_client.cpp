#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/util.h>

#define SERVER_IP   "127.0.0.1"
#define SERVER_PORT 8899 

void write_cb(int fd, short events, void *arg);
void read_cb(struct bufferevent *bev, void *arg);
void write_over_cb(struct bufferevent *bev, void *arg);
void event_cb(struct bufferevent *bev, short event, void *arg);

int main(int argc, char **argv) 
{
    int ret;
    struct event_base *base = event_base_new();
    assert(base != NULL);

    // 为这个客户端分配一个 bufferevent，释放时关闭套接字
    struct bufferevent *bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
    assert(bev != NULL);

    // 分配并初始化一个新的event结构体，准备被添加。
    struct event *ev = event_new(base, STDIN_FILENO, EV_READ|EV_PERSIST,
                    write_cb, (void *)bev);
    assert(ev != NULL);

    // 将ev注册到event_base的I/O多路复用要监听的事件中
    ret = event_add(ev, NULL);
    assert(ret == 0);

    // 配置服务器地址
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    // 连接服务器
    ret = bufferevent_socket_connect(bev, (struct sockaddr *)&server_addr, sizeof(server_addr));
    assert(ret == 0);

    // 设置读回调、事件回调
    bufferevent_setcb(bev, read_cb, write_over_cb, event_cb, (void *)ev);
    // 默认写回调使能，这里必须使能读回调
    bufferevent_enable(bev, EV_READ | EV_PERSIST);

    event_base_dispatch(base);

    printf("Finished\n");

    return 0;
}

void write_cb(int fd, short events, void *arg)
{
    struct bufferevent *bev = (struct bufferevent *)arg;

    char msg[1024];

    int ret = read(fd, msg, sizeof(msg));
    if (ret < 0) {
        perror("read fail.\n");
        exit(1);
    }

    bufferevent_write(bev, msg, ret);
}

void read_cb(struct bufferevent *bev, void *arg) {
    char msg[1024];

    size_t len = bufferevent_read(bev, msg, sizeof(msg)-1);
    msg[len] = '\0';

    printf("Recv %s from server.\n", msg);
}

void write_over_cb(struct bufferevent *bev, void *arg)
{
    printf("我是客户端的写回调函数，没啥用\n");
}

void event_cb(struct bufferevent *bev, short event, void *arg) {
    if (event & BEV_EVENT_EOF) {
        printf("Connection closed.\n");
    }
    else if (event & BEV_EVENT_ERROR) {
        printf("Some other error.\n");
    }
    else if (event & BEV_EVENT_CONNECTED) {
        printf("Client has successfully cliented.\n");
        return;
    }

    bufferevent_free(bev);

    struct event *ev = (struct event *)arg;
    event_free(ev);
}


