#include <stdio.h>

typedef void (*UnityTestFunction)(void);
#define RUN_TEST(func) UnityDefaultTestRun(func, #func, __LINE__)

void UnityDefaultTestRun(UnityTestFunction Func, const char* FuncName, const int FuncLineNum)
{
	printf("FuncName = %s, FuncLineNum = %d\n", FuncName, FuncLineNum);
    Func();
}

void test()
{
	printf("222222222222222\n");
}

int main(int argc, char const *argv[])
{
	RUN_TEST(test);

	return 0;
}
