#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#ifdef _MSC_VER
    #include <windows.h>
#else
    #include <pthread.h>
#endif

#ifdef _MSC_VER
    #define mysleep(n)  Sleep(n)
#else
    #define mysleep(n)  sleep(n/1000)
#endif

using namespace std;


class xiabo_C{
public:
    xiabo_C():a(10),d(8)
    {
        printf("I am xiabo_C() function\n");
    }
    static int sfunc(); //静态成员函数也遵循public,private,protected访问规则
    int func(void);

public:
    int a;
    static int b ;      //此处不能初始化
    static const int c = 9;//只有静态常量才能直接初始化
    const  int d;
};

int  xiabo_C::b = 11;   //静态成员变量的初始化只能这样，不能在构造中初始化

int xiabo_C::sfunc(){   //!!!静态成员函数在类外部实现时，千万不要加static，不要写成了static int sfunc(){},这是内外部的静态C函数
    //xiabo::a = 11;    //error   静态成员函数不能应用非静态成员
    xiabo_C::b = 12;
    printf("I am static member function,b = %d\n",xiabo_C::b );
    return 0;
}
static int sfunc1(){
    printf("I am static function, not member function \n" );

    return 0;
}
int xiabo_C::func(void){
    xiabo_C::b = 12;
    xiabo_C::sfunc();
    sfunc1();
    return 0;
}
void test_statichunc(void){
    xiabo_C xiabo;
    xiabo.func();
    xiabo_C::sfunc();  //静态成员函数是类的，不是某个对象的，引用必须通过类名来访问

}
//-------------
class xiabo2_C{
public:
    typedef int (*pcb)(int a);
    typedef struct parameter{
        int a ;
        pcb callback;
    }parameter; 
    xiabo2_C():m_a(1){

    }
    //普通函数
    void GetCallBack(parameter* p)  // 写回调者实现的回调函数
    {
        m_a = 2;
        //do something
        while(1)
        {
            printf("GetCallBack print! \n");
            mysleep(2000);
            p->callback(p->a);
        }
    }
    int SetCallBackFun(int a, pcb callback)
    {
        printf("SetCallBackFun print! \n");
        parameter *p = new parameter ; 
        p->a  = 10;
        p->callback = callback;
        GetCallBack(p);
        return 0;
    }

public:
    int m_a;
};

class xiabo2Test_C{
public:
    xiabo2Test_C():m_b(1){

    }
    static int fCallBack(int a)         // 应用者实现的回调函数，静态成员函数，但是不能访问类中非静态成员了，破坏了类的结构
    {
        //do something
        //m_b = a;      // 不能访问类中非静态成员了，破坏了类的结构,应用者使用很麻烦
        printf("a = %d\n",a);
        printf("fCallBack print! \n");
        return 0;
    }
public:
    int m_b;
};

//-------------------
template<typename Tobject,typename Tparam>
class xiabo3_C{
    typedef void (Tobject::*Cbfun)(Tparam* );
public:
    bool Exec(Tparam* pParam);
    void Set(Tobject *pInstance,Cbfun pFun,Tparam* pParam);

private:
    Cbfun pCbfun;
    Tobject* m_pInstance;
};

template<typename Tobject,typename Tparam>
void xiabo3_C<Tobject,Tparam>::Set(Tobject *pInstance,Cbfun pFun,Tparam* pParam){
    printf("Set print!\n");
    m_pInstance = pInstance;
    (pInstance->*pFun)(pParam);     //可以直接在这里回调传过来的函数指针
    pCbfun = pFun;
}
template<typename Tobject,typename Tparam>
bool xiabo3_C<Tobject,Tparam>::Exec(Tparam* pParam){
    printf("Exec print!\n");
    (m_pInstance->*pCbfun)(pParam);//也可以在这里回调传过来的函数指针
    return true;
}

class xiabo3Test_C{
public:
    xiabo3Test_C():m_N(13){

    }
    void fCallBack(int *p){
        printf("fCallBack : Sum = m_N + *p = %d\n",*p + m_N);
        printf("fCallBack print! I am a member function! I can access all the member ,HaHa...\n");
    }

private:
    int m_N;

};

//--------------
//类中定义线程
class  xiabo4_C{
public:
    struct ThreadParam{
        xiabo4_C* pthis;
        int a ;
        int b ;
    };//根据线程参数自定义结构

public:
    xiabo4_C():m_N(1){

    }
    void print(void){
        printf("print : m_N = %d \n",m_N);
    }
    //静态实现
    void CreatAlgorithmThread(void);
    static void *funThreadAlgorithm(void* p);  //静态成员函数实现线程Wrapper
    //非静态实现
    void CreatAlgorithm2Thread(int a ,int b);
    static void *funThreadAlgorithm2(void* param);  //非静态成员函数实现线程Wrapper
    void ThreadFunc(int a ,int b){
        printf("ThreadFunc : I am ThreadFunc,I am a member function! I can access all the member ,HaHa...\n");
        printf("ThreadFunc : m_N = %d \n",m_N);
    }

private:
    int m_N;
};

void xiabo4_C::CreatAlgorithmThread(void){  //静态实现
#ifdef _MSC_VER
    HANDLE handle1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)funThreadAlgorithm,0,0,NULL);  
    CloseHandle(handle1);
#else
    pthread_t thing1;
    pthread_create(&thing1,NULL,&funThreadAlgorithm,(void *) 0);
    pthread_join(thing1,NULL);
#endif
}
void* xiabo4_C::funThreadAlgorithm(void* p){
    while(1)
    {
        mysleep(2000);
        printf("I am a static meeber function! I can not access the member\n");
    }
}

void xiabo4_C::CreatAlgorithm2Thread(int a ,int b){
    ThreadParam* p = new ThreadParam;
    p->pthis = this;
    p->a     = a;
    p->b     = b;
#ifdef _MSC_VER
    HANDLE handle2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)funThreadAlgorithm2,p,0,NULL); 
    CloseHandle(handle2);
#else
    pthread_t thing1;
    pthread_create(&thing1,NULL,&funThreadAlgorithm2,(void *) p);
    pthread_join(thing1,NULL);
#endif
}
void* xiabo4_C::funThreadAlgorithm2(void* param){
    ThreadParam* p = (ThreadParam*)param;

    printf("I am a static meeber function! I can not access the member\n");
    printf("But I can call a member func ,I can instigate ThreadFunc ,ThreadFunc can access all member\n");
    printf("ThreadParam p->a = %d, p->b = %d \n",p->a,p->b);
    p->pthis->ThreadFunc(p->a,p->b);
    return 0;
}

//--------------
//类中定义线程，并实现回调
//A程序员
template<typename Tobject,typename Tparam>
class  xiabo5_C{
public:
    struct ThreadParam{
        xiabo5_C* pthis;
        Tparam a ;
    };//根据线程参数自定义结构
    typedef void (Tobject::*Cbfun)(Tparam );
public:
    xiabo5_C():m_N(1){
        printf("xiabo5_C : xiabo5_C()\n");
    }
    void print(void){
        printf("print : m_N = %d \n",m_N);
    }
    //非静态实现
    void CreateCallbackThread(Tobject *pInstance,Cbfun pFun,Tparam a );
    static void* funCallbackThread(void* param);  //非静态成员函数实现线程Wrapper
    void ThreadFunc(Tparam a );  //线程执行函数

private:
    int m_N;
    Cbfun pCbfun;
    Tobject* m_pInstance;
};
template<typename Tobject,typename Tparam>
void xiabo5_C<Tobject,Tparam>:: CreateCallbackThread(Tobject *pInstance,Cbfun pFun,Tparam a ){
    ThreadParam* p = new ThreadParam;
    p->pthis = this;
    p->a     = a;
    m_pInstance = pInstance;
    pCbfun = pFun;

#ifdef _MSC_VER
    HANDLE handle2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)funCallbackThread,p,0,NULL);   
    CloseHandle(handle2);
#else
    pthread_t thing1;
    pthread_create(&thing1,NULL,&funCallbackThread,(void *) p);
    //pthread_join(thing1,NULL); //warning !! can not be join !!!
#endif
}
template<typename Tobject,typename Tparam>
void* xiabo5_C<Tobject,Tparam>::funCallbackThread(void* param){
    ThreadParam* p  = (ThreadParam*)param;
    printf("I am a static meeber function! I can not access the member\n");
    printf("But I can call a member func ,I can instigate ThreadFunc ,ThreadFunc can access all member\n");
    printf("ThreadParam p->a = %d\n",p->a);
    p->pthis->ThreadFunc(p->a);
    return 0;
}
template<typename Tobject,typename Tparam>
void xiabo5_C<Tobject,Tparam>::ThreadFunc(Tparam a ){
    printf("I am ThreadFunc,I am a member function and access all the member ,HaHa...\n");
    //printf("%d ThreadFunc : m_N = %d \n",m_N);
    while(1)
    {
        const pthread_t me = pthread_self();
        mysleep(a*1000);
        (m_pInstance->*pCbfun)(me);
    }
}
//B程序员
class xiabo5Test_C{
public:
    xiabo5Test_C():m_N(0){

    }
    void fCallBack(int p){
        printf("Thread ID = %d fCallBack : Sum = m_N + *p = %d\n",p,p + m_N);
        //printf("fCallBack print! I am a member function! I can access all the member ,HaHa...\n");
    }
public:

private:
    int m_N;
};


int main(void ){
    //测试静态成员函数
    //test_statichunc();

    //测试静态成员函数，用于回调
    //xiabo2_C xiabo2;
    //xiabo2.SetCallBackFun(5,xiabo2Test_C::fCallBack);

    //测试非静态成员函数，用于回调，good
    //xiabo3_C<xiabo3Test_C,int> xiabo3;
    //xiabo3Test_C xiabo3Test;
    //int p = 13;
    //xiabo3.Set(&xiabo3Test,&xiabo3Test_C::fCallBack,&p); //
    //xiabo3.Exec(&p);

    //类中定义线程
    //xiabo4_C xiabo4;
    //xiabo4.CreatAlgorithm2Thread(1,2);

    //类中定义线程，并实现回调
    xiabo5_C<xiabo5Test_C,int> xiabo5;
    xiabo5Test_C xiabo5Test;
    int p = 2;
    xiabo5.CreateCallbackThread(&xiabo5Test,&xiabo5Test_C::fCallBack,p);


    xiabo5_C<xiabo5Test_C,int> xiabo51;
    xiabo5Test_C xiabo5Test1;
    int p1 = 4;
    xiabo51.CreateCallbackThread(&xiabo5Test1,&xiabo5Test_C::fCallBack,p1);
    getchar();
    return 0;
}