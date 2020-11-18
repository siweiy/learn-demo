#include <iostream>
#include <stdlib.h>
#include "zlib.h"

using namespace std;

#define MaxBufferSize 1024 * 10

int main()
{
    FILE *File_src;
    FILE *File_tmp;
    FILE *File_dest;

    unsigned long len_src;
    unsigned long len_tmp;
    unsigned long len_dest;

    unsigned char *buffer_src = new unsigned char[MaxBufferSize];
    unsigned char *buffer_tmp = new unsigned char[MaxBufferSize];
    unsigned char *buffer_dest = new unsigned char[MaxBufferSize];

    File_src = fopen("src.txt", "r");
    len_src = fread(buffer_src, 1, MaxBufferSize - 1, File_src);
    fclose(File_src);

    // 压缩
    compress2(buffer_tmp, &len_tmp, buffer_src, len_src, MAX_MEM_LEVEL);

    File_tmp = fopen("tmp.txt", "w");
    fwrite(buffer_tmp, 1, len_tmp, File_tmp);
    fclose(File_tmp);

    // 解压
    uncompress(buffer_dest, &len_dest, buffer_tmp, len_tmp);

    File_dest = fopen("dest.txt", "w");
    fwrite(buffer_dest, 1, len_dest, File_dest);
    fclose(File_dest);

    delete[] buffer_src;
    delete[] buffer_tmp;
    delete[] buffer_dest;

    return 0;
}