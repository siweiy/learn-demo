#include <stdio.h>
#include <string.h>

void getNext(int *next, const char *p)
{
	int  left  = 0;
	int  right = 1;
	int len = strlen(p);

	next[1] = 0;
	while (right < p[0])
	{
		if (left == 0 || p[right] == p[left])
		{
			left++;
			right++;
			next[right] = left;
		}
		else{
			left = next[left];
		}
	}
}

void KMP(char *p)
{
	int next[100] = {};
	p[0] = strlen(p) - 1;
	getNext(next, p);

	for (int i = 1; i < p[0]; i++)
	{
		printf("%d", next[i]);
	}
}

int main(int argc, char const *argv[])
{
	char p[] = " ababaaaba";
	KMP(p);

	return 0;
}
