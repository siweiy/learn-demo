#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG

// KMP
static void __kmp_test(const unsigned char *P, unsigned int *T)
{
    unsigned int i = 0;
    unsigned len = strlen(P);
    printf("i:\tP[i]\tT[i]\n");
    while (i < len) {
        printf("%d:\t%c\t%d\n", i, P[i], T[i]);
        i++;
    }
}


void __get_next(int next[], unsigned char *p)
{
	int left = -1;
	int right = 0;

	next[0] = -1;
	int len = strlen(p);

	while(right < len)
	{
		if(left == -1 || p[right] == p[left])
		{
			left++;right++;
			next[right] = left;
		}
		else left = next[left];
 	}
}

int __index_KMP(unsigned char *src, unsigned char *dst, int pos[])
{
	int i = 0, j = 0;
	int num = 0, search_flag = 0;
	int slen = strlen(src);
	int dlen = strlen(dst);
	int next[slen];

	__get_next(next, src);

#ifdef DEBUG
	__kmp_test(src, next);
#endif

	while(i < slen /*&& j < dlen*/) {
		if(j == -1 || src[i] == dst[j]) {
			i++;
			j++;
		}
		else j = next[j];	//j回退

		if(j >= dlen) {
			pos[num++] = (i - dlen);
			search_flag = 1;
		}
	}

	if (search_flag)
		return num;
	else
		return (-1);
}

int main(int argc, char const *argv[]) {

	int posArr[32] = {0};
	unsigned char *s = "DAB";
	unsigned char *str = "ABC ABCDAB ABCDABCDABDE";
					//     0000123012012301230120

	int num = __index_KMP(str, s, posArr);
	printf("have %d child\n", num);

	for (int i = 0; i < num; i++) {
		printf("child[%d] index: %d\n", i, posArr[i]);
	}

	return 0;
}

