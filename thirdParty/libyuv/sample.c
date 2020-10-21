#include <stdio.h>
#include "include/libyuv.h"

typedef unsigned char uint8;

int libyuv_I420_to_Rgb()
{   
    const int width = 1920, height = 1080;
    FILE *src_file = fopen("test.yuv", "rb");
    FILE *dst_file = fopen("test.rgb", "wb");
 
    int size_src = width * height * 3 / 2;
    int size_dest = width * height * 4;
    char *buffer_src = (char *)malloc(size_src);
    char *buffer_dest = (char *)malloc(size_dest);
    if (buffer_dest == NULL || buffer_src == NULL) {
        printf("malloc null \n");
        return -1;
    }

    while (1){
        if (fread(buffer_src, 1, size_src, src_file) != size_src){
            //fseek(src_file, 0, 0);
            //fread(buffer_src, 1, size_src, src_file);
            break;
        }
        //libyuv::I420ToARGB(const uint8* src_y, int src_stride_y,
        //  const uint8* src_u, int src_stride_u,
        //  const uint8* src_v, int src_stride_v,
        //  uint8* dst_argb, int dst_stride_argb,
        //  int width, int height);
        I420ToARGB((const uint8*)buffer_src, width,
            (const uint8*)(buffer_src + width * height), width / 2,
            (const uint8*)(buffer_src + width * height * 5 / 4), width / 2,
            (uint8*)buffer_dest, width * 4,
            width, height);
        fwrite(buffer_dest, 1, size_dest, dst_file);
    }
 
    free(buffer_src);
    free(buffer_dest);
    fclose(dst_file);
    fclose(src_file);
    return 0;
}


int main(int argc, char const *argv[])
{
	libyuv_I420_to_Rgb();
	return 0;
}
