#include<stdio.h>
#include<time.h>

#define X 8
#define Y 8

int chess[X][Y];

int nextxy(int *x,int *y,int count)
{
    switch(count)//对于上下左右及其四周等八个情况判断
    {
        //注意xy大小写
        case 0:
        if(*x+2<=X-1&&*y-1>=0&&chess[*x+2][*y-1]==0)//判断是否出界和是否经过，没进过为0
        {
            *x+=2;
            *y-=1;
            return 1;//标志可行
        }
        break;
        case 1:
        if(*x+2<=X-1&&*y+1<=Y-1&&chess[*x+2][*y+1]==0)//判断是否出界和是否经过，没进过为0
        {
            *x+=2;
            *y+=1;
            return 1;//标志可行
        }
        break;
        case 2:
        if(*x+1<=X-1&&*y-2>=0&&chess[*x+1][*y-2]==0)//判断是否出界和是否经过，没进过为0
        {
            *x+=1;
            *y-=2;
            return 1;//标志可行
        }
        break;
        case 3:
        if(*x+1<=X-1&&*y+2<=Y-1&&chess[*x+1][*y+2]==0)//判断是否出界和是否经过，没进过为0
        {
            *x+=1;
            *y+=2;
            return 1;//标志可行
        }
        break;
        case 4:
        if(*x-2>=0&&*y-1>=0&&chess[*x-2][*y-1]==0)//判断是否出界和是否经过，没进过为0
        {
            *x-=2;
            *y-=1;
            return 1;//标志可行
        }
        break;
        case 5:
        if(*x-2>=0&&*y+1<=Y-1&&chess[*x-2][*y+1]==0)//判断是否出界和是否经过，没进过为0
        {
            *x-=2;
            *y+=1;
            return 1;//标志可行
        }
        break;
        case 6:
        if(*x-1>=0&&*y-2>=0&&chess[*x-1][*y-2]==0)//判断是否出界和是否经过，没进过为0
        {
            *x-=1;
            *y-=2;
            return 1;//标志可行
        }
        break;
        case 7:
        if(*x-1>=0&&*y+2<=Y-1&&chess[*x-1][*y+2]==0)//判断是否出界和是否经过，没进过为0
        {
            *x-=1;
            *y+=2;
            return 1;//标志可行
        }
        break;
        default:
            break;

    }
    return 0;
}

void print()
{
    int i,j;
    for(i=0;i<Y;i++)
    {   
        for(j=0;j<Y;j++)
        {
            printf("%2d\t",chess[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int TravelChessBoard(int x,int y,int tag)//tag为标记变量每走一步tag+1
{
    int x1=x,y1=y,flag=0,count=0;//初始位置即初始化
    chess[x][y]=tag;
    if(tag==X*Y)//完了
    {
        print();
        return 1;
    }
    //找马的下一个坐标(x1,y1)，成功则flag=1否则=0
    //第一次搜索
    flag=nextxy(&x1,&y1,count);
    while(flag==0&&count<7)//已进入，进不去了
    {
        count++;
        flag=nextxy(&x1,&y1,count);
    }
    while(flag)
    {
        if(TravelChessBoard(x1,y1,tag+1))
            return 1;
        //出错则找马的下一个坐标(x1,y1)，成功则flag=1否则=0
        //第一次搜索错，接下来搜索
        x1=x;
        y1=y;
        count++;
        flag=nextxy(&x1,&y1,count);
        while(flag==0&&count<7)//已进入，进不去了
        {
            count++;
            flag=nextxy(&x1,&y1,count);
        }
    }
    if(flag==0)
    {
        chess[x][y]=0;
    }
    return 0;
}
int main()
{
    int i,j;
    clock_t start,finish;
    start=clock();
    for(i=0;i<X;i++)
    {
        for(j=0;j<Y;j++)
        {
            chess[i][j]=0;
        }
    }
    if(!TravelChessBoard(2,0,1))
        printf("错误");
    finish=clock();
    printf("\n用时%f秒",(double)(finish-start)/CLOCKS_PER_SEC);//CLOCKS_PER_SEC为time 中的宏定义，每秒的数量
    return 0;
}