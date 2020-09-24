#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <unistd.h>

// 获取进程ID
pid_t getProcessPidByName(const char *proc_name) {
    FILE *fp;
    char buf[100] = {0};
    char cmd[200] = {'\0'};
    pid_t pid = -1;

    sprintf(cmd, "pidof -s %s", proc_name);
    if((fp = popen(cmd, "r")) != NULL) {
        if(fgets(buf, 255, fp) != NULL) {
            pid = atoi(buf);
        }
    }
    pclose(fp);

    return pid;
}

int main(int argc, char *argv[])
{
    // 设置/获取进程名并根据进程名获取进程ID,不能在同个进程直接获取
    //*******************************************************
    prctl(PR_SET_NAME, "test_proess");

    char buf[100] = {0};
    prctl(PR_GET_NAME, buf);
	printf("buf = %s\n", buf);

    pid_t process_pid = getProcessPidByName("code");
	printf("pid = %d\n", process_pid);
    //*******************************************************

    return 0;
}
