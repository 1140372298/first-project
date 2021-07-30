
#include<stdio.h>
#include<windows.h>
#define High 25                     //��Ϸ�ߴ�
#define Width 50
//����ȫ�ֱ���
int cells[High][Width];         //ϸ����1��0
void HideCursor()                //���ع��
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0};
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void gotoxy(int x,int y) //����ƶ���(x,y)λ��
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}
void startup()  //���ݳ�ʼ��
{
    int i,j;
    for(i=0;i<=High;i++)
        for(j=0;j<=Width;j++)
            cells[i][j]=1;                          //����ϸ����ʼ��������rand()�������ʹϸ����ʼ״̬���
 
 
    HideCursor();
}
void show()     //��ʾ����
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
    Sleep(200);            //����ˢ���ٶ�
}
void updateWithoutInput()           //�����û�����
{
    int i,j;
    int NeibourNumber;
    int temp[High][Width];
    for(i=1;i<High;i++)
    {
        for(j=1;j<Width;j++)
        {
            NeibourNumber=cells[i-1][j-1]+cells[i-1][j]+cells[i-1][j+1]+cells[i][j-1]+cells[i][j+1]+cells[i+1][j-1]+cells[i+1][j]+cells[i+1][j+1];
            if(NeibourNumber==3)            //��Χ��3����ϸ��ʱ����ϸ����
                temp[i][j]=1;
            else if(NeibourNumber==2)       //��Χ��2����ϸ��ʱ����ϸ��״̬����
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

