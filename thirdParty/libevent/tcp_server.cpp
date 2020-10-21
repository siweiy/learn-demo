#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <signal.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <event2/thread.h>

#define SERVER_IP "0.0.0.0"
#define SERVER_PORT 8899

void listener_cb(struct evconnlistener *listener, evutil_socket_t fd, \
				 struct sockaddr *sock, int socklen, void *arg);
void socket_read_cb(struct bufferevent *bev, void *arg);
void conn_writecb(struct bufferevent *bev, void *user_data);
void socket_event_cb(struct bufferevent *bev, short events, void *arg);
void signal_cb(evutil_socket_t sig, short events, void *user_data);

int main(int argc, char **argv)
{
	// 创建监听套接字、绑定、监听、等待连接
	struct event_base *base = event_base_new();
	assert(base != NULL);

	// 初始化服务器地址和端口
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_IP, &sin.sin_addr.s_addr);

	struct evconnlistener *listener = evconnlistener_new_bind(base,
															  listener_cb, base,
															  LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,
															  10, (struct sockaddr *)&sin, sizeof(sin));
	assert(listener != NULL);

	event_base_dispatch(base);

	struct event *signal_event;
	signal_event = evsignal_new(base, SIGINT, signal_cb, (void *)base);
	if (!signal_event || event_add(signal_event, NULL) < 0)
	{
		fprintf(stderr, "Could not create/add a signal event!\n");
		return 1;
	}

	evconnlistener_free(listener);
	event_free(signal_event);
	event_base_free(base);

	printf("done\n");
	return 0;
}

void listener_cb(struct evconnlistener *listener, evutil_socket_t fd,
				 struct sockaddr *sock, int socklen, void *arg)
{

	printf("accept a client %d\n", fd);
	struct event_base *base = (struct event_base *)arg;

	//设置socket为非阻塞
	//evutil_make_socket_nonblocking(fd);

	// 创建一个struct bufferevent *bev，关联该sockfd，托管给event_base
	struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	if (!bev)
	{
		fprintf(stderr, "Error constructing bufferevent!");
		event_base_loopbreak(base);
		return;
	}

	// 设置读写对应的回调函数
	// bufferevent_setcb(bev, socket_read_cb, conn_writecb, socket_event_cb, NULL);
	bufferevent_setcb(bev, socket_read_cb, NULL, socket_event_cb, NULL);

	//启用读写事件,其实是调用了event_add将相应读写事件加入事件监听队列
	// EV_WRITE默认是使能
	bufferevent_enable(bev, EV_READ | EV_PERSIST);

	// 写数据回去，告诉连接上了
	const char *MESSAGE = "connect success.";
	bufferevent_write(bev, MESSAGE, strlen(MESSAGE) + 1);
}

void socket_read_cb(struct bufferevent *bev, void *arg)
{
#if 1

	// 读到
	char buf[1024] = {0};
	size_t len = bufferevent_read(bev, buf, sizeof(buf));
	printf("read = %s, len = %d\n", buf, (int)len);

	// 写回去
	const char *MESSAGE = "data is recv ok.";
	bufferevent_write(bev, MESSAGE, strlen(MESSAGE) + 1);

	printf("send bask ok.\n");
#else
	struct evbuffer *input, *output;
	char *request_line;
	size_t len;
	input = bufferevent_get_input(bev);	  //其实就是取出bufferevent中的input
	output = bufferevent_get_output(bev); //其实就是取出bufferevent中的output

	size_t input_len = evbuffer_get_length(input);
	printf("input_len: %d\n", input_len);
	size_t output_len = evbuffer_get_length(output);
	printf("output_len: %d\n", output_len);

	while (1)
	{
		request_line = evbuffer_readln(input, &len, EVBUFFER_EOL_CRLF); //从evbuffer前面取出一行，用一个新分配的空字符结束
																		// 的字符串返回这一行,EVBUFFER_EOL_CRLF表示行尾是一个可选的回车，后随一个换行符
		if (NULL == request_line)
		{
			printf("The first line has not arrived yet.\n");
			free(request_line); //之所以要进行free是因为 line = mm_malloc(n_to_copy+1))，在这里进行了malloc
			break;
		}
		else
		{
			printf("Get one line date: %s\n", request_line);
			if (strstr(request_line, "over") != NULL) //用于判断是不是一条消息的结束
			{
				char *response = "Response ok! Hello Client!\r\n";
				evbuffer_add(output, response, strlen(response)); //Adds data to an event buffer
				printf("服务端接收一条数据完成，回复客户端一条消息: %s\n", response);
				free(request_line);
				break;
			}
		}
		free(request_line);
	}

	size_t input_len1 = evbuffer_get_length(input);
	printf("input_len1: %d\n", input_len1);
	size_t output_len1 = evbuffer_get_length(output);
	printf("output_len1: %d\n\n", output_len1);

#endif
}

// bufferevent 写回调函数
void conn_writecb(struct bufferevent *bev, void *user_data)
{
	// bufferevent_write(bev, MESSAGE, strlen(MESSAGE)+1);已经发出去了
	struct evbuffer *output = bufferevent_get_output(bev);
	if (evbuffer_get_length(output) == 0)
	{
		printf("flushed answer\n");
		bufferevent_free(bev);
	}
}

void socket_event_cb(struct bufferevent *bev, short events, void *arg)
{
	if (events & BEV_EVENT_EOF)
	{
		printf("connection closed\n");
	}
	else if (events & BEV_EVENT_ERROR)
	{
		printf("some other error\n");
	}

	bufferevent_free(bev);
}

void signal_cb(evutil_socket_t sig, short events, void *user_data)
{
	struct event_base *base = static_cast<struct event_base *>(user_data);
	struct timeval delay = {2, 0};

	printf("Caught an interrupt signal; exiting cleanly in two seconds.\n");

	// 捕捉到信号2秒后退出
	event_base_loopexit(base, &delay);
}
