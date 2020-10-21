#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dlfcn.h>

int main(int argc, char const *argv[])
{
	void *handle = dlopen(argv[1], RTLD_NOW);
	if (handle == NULL) {
		printf("打开动态库失败\n");
		exit(0);
	}

	void (*func)(void);
	func = dlsym(handle, "regconize");// 找函数
	if (func == NULL) {
		printf("error: %s\n", strerror(errno));
		exit(0);
	}

	// 调用接口
	func();

	dlclose(handle);

	return 0;
}
