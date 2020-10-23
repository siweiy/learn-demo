#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG

// KMP
#ifdef DEBUG
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
#endif

static void __kmp_table(const unsigned char *p, unsigned int *T)
{
    unsigned int pos = 2, left = 0;
    unsigned int len = strlen(p);

    T[0] = -1; // T数组
    T[1] = 0;  // 第一位必定0
    while (pos < len) {
        if (p[pos-1] == p[left]){
            left = left + 1;
            T[pos] = left;
            pos = pos + 1;
        }
        else if (left > 0) {
            left = T[left];
        } else {
            T[pos] = 0;
            pos = pos + 1;
        }
    }
}

unsigned int kmp_search(unsigned char *S, unsigned int slen,
                        unsigned char *W, unsigned int wlen)
{
    unsigned int m=0, i=0;
    unsigned int *T;
    __assert(S && W);
    
    T = (unsigned int*)__malloc(wlen * sizeof(unsigned int));
    __assert(T);
    __kmp_table(W, wlen, T);

#ifdef DEBUG
    __kmp_test(W, wlen, T);
#endif

    while (m+i < slen) {
        if (W[i] == S[m+i]) {
            if (i == wlen-1)
            {
                __free(T);
                return m;
            }
            i = i+1;
        }
        else {
            m = m+i-T[i];
            if (T[i] > -1)
                i = T[i];
            else
                i = 0;
        }
    }
    __free(T);
    return slen;
}

int main(int argc, char const *argv[]) {
	int next[101];
	const unsigned char *str = "ABC ABCDAB ABCDABCDABDE";
	__kmp_table(str, next);
	__kmp_test(str, next);

	return 0;
}

