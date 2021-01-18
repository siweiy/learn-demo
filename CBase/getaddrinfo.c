#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <arpa/inet.h>
#include <netinet/in.h>

//    int getaddrinfo(const char *node, const char *service,
//                    const struct addrinfo *hints,
//                    struct addrinfo **res);

//    void freeaddrinfo(struct addrinfo *res);

int main(int argc, char const *argv[])
{

    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];
    uint16_t port;

    if (argc < 2)
    {
        fprintf(stderr, "usage: %s hostname  port\n", argv[0]);
        return 1;
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // AF_INET 或 AF_INET6
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(argv[1], argv[2], &hints, &res)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }

    printf("IP addresses for %s:\n\n", argv[1]);

    for (p = res; p != NULL; p = p->ai_next)
    {
        void *addr;
        char *ipver;

        if (p->ai_family == AF_INET)
        { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
            port = ntohs(((struct sockaddr_in *)p->ai_addr)->sin_port);
        }
        else
        { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
            port = ntohs(((struct sockaddr_in6 *)p->ai_addr)->sin6_port);
        }

        // convert the IP to a string and print it:
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf(" %s: %s,port is %u\n", ipver, ipstr, port);
    }

    freeaddrinfo(res);

    return 0;
}
