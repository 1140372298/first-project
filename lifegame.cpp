
#include<stdio.h>
#include<windows.h>
#define High 25                     //游戏尺寸
#define Width 50
//定义全局变量
int cells[High][Width];         //细胞生1死0
void HideCursor()                //隐藏光标
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0};
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void gotoxy(int x,int y) //光标移动到(x,y)位置
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}
void startup()  //数据初始化
{
    int i,j;
    for(i=0;i<=High;i++)
        for(j=0;j<=Width;j++)
            cells[i][j]=1;                          //所有细胞初始生，可用rand()随机函数使细胞初始状态随机
 
 
    HideCursor();
}
void show()     //显示界面
{
    gotoxy(0,0);
    int i,j;
    for(i=1;i<High;i++)
    {
        for(j=0;j<Width;j++)
        {
            if(cells[i][j]==1)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
    Sleep(200);            //控制刷新速度
}
void updateWithoutInput()           //无需用户输入
{
    int i,j;
    int NeibourNumber;
    int temp[High][Width];
    for(i=1;i<High;i++)
    {
        for(j=1;j<Width;j++)
        {
            NeibourNumber=cells[i-1][j-1]+cells[i-1][j]+cells[i-1][j+1]+cells[i][j-1]+cells[i][j+1]+cells[i+1][j-1]+cells[i+1][j]+cells[i+1][j+1];
            if(NeibourNumber==3)            //周围有3个活细胞时，该细胞生
                temp[i][j]=1;
            else if(NeibourNumber==2)       //周围有2个活细胞时，该细胞状态不变
                        temp[i][j]=cells[i][j];
            else
                temp[i][j]=0;
        }
    }
    for(i=1;i<High;i++)
        for(j=1;j<Width;j++)
            cells[i][j]=temp[i][j];
}
int main()
{
    startup();
    while(1)
    {
        show();
        updateWithoutInput();
    }
}

