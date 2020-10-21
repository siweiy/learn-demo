#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>

int main(int argc, char *argv[])
{
    int inotifyFd = inotify_init();
    if (inotifyFd < 0) {
        printf("inotify_init error\n");
        return -1;
    }

    int wd = inotify_add_watch(inotifyFd, "./tmp", IN_ALL_EVENTS);
    if (wd < 0) {
        printf("inotify_add_watch error\n");
        return -1;
    }

#define BUF_LEN_inotify 1024
    while(1) {
        char buf[BUF_LEN_inotify];
        ssize_t numRead = read(inotifyFd, buf, BUF_LEN_inotify);
        if(numRead == -1) {
            printf("read byte -1\n");
            continue;
        }

        for(char *p = buf; p < buf+numRead;) {
            struct inotify_event *event = (struct inotify_event *)p;

            switch (event->mask) {
            case IN_ACCESS: printf("IN_ACCESS\n"); break;
            case IN_MODIFY: printf("IN_MODIFY\n"); break;
            case IN_ATTRIB: printf("IN_ATTRIB\n"); break;
            case IN_CLOSE_WRITE: printf("IN_CLOSE_WRITE\n"); break;
            case IN_CLOSE_NOWRITE: printf("IN_CLOSE_NOWRITE\n"); break;
            case IN_OPEN: printf("IN_OPEN\n"); break;
            case IN_MOVED_FROM: printf("IN_MOVED_FROM\n"); break;
            case IN_MOVED_TO: printf("IN_MOVED_TO\n"); break;
            case IN_CREATE: printf("IN_CREATE\n"); break;
            case IN_DELETE: printf("IN_DELETE\n"); break;
            case IN_DELETE_SELF: printf("IN_DELETE_SELF\n"); break;
            case IN_MOVE_SELF: printf("IN_MOVE_SELF\n"); break;
            default: printf("default\n"); break;
            }

            p += sizeof(struct inotify_event) + event->len;
        }
    }

    inotify_rm_watch(inotifyFd, wd);
    return 0;
}

