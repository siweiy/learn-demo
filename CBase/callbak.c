#include <stdio.h>

//@CallbackFun 指向函数的指针类型
typedef void (*CallbackFun)(double height, void *contex);

CallbackFun m_pCallback;

//1.定义函数onHeight（回调函数）
void onHeight(double height, void *contex)
{
    if (contex != NULL)
    {
        int *num = (int*)(contex);
        printf("contex is %d", *num);
    }
    printf("current height is %lf", height);
}

//@registHeightCallback 注册函数名
void RegistCallback(CallbackFun callback)
{
    m_pCallback = callback;
}

void printHeightFun(double height)
{
    int num = 5;
    m_pCallback(height, (void*)&num);
}

int main()
{
    //注册onHeight函数，即通过registHeightCallback的参数将onHeight函数指针
    RegistCallback(onHeight);
    
    double h = 99;
    printHeightFun(99);

    return 0;
}