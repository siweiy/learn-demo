// 斐波那锲 -- 兔子繁衍问题
#include <stdio.h>

int Fib(int i) {
	if (i < 2)
		return i == 0 ? 0 : 1;
	return Fib(i-1) + Fib(i-2);
}


int main(int argc, char const *argv[])
{
	int i;
	int a[40];

	a[0] = 0;
	a[1] = 1;
	printf("%d %d ", a[0], a[1]);

	for (i = 2; i < 40; i++) {
		a[i] = a[i-1] + a[i-2];
		printf("%d ", a[i]);
	}
	printf("\n");

	Fib(40);
	
	return 0;
}
