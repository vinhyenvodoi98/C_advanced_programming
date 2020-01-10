#include<graphics.h>
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
int main()
{
    int gd,gm=VGAMAX; gd=DETECT;
    initgraph(&gd,&gm,NULL);
    setbkcolor(1);
    cleardevice();
    setcolor(4);
    char s1[] = "nguyenvanquan7826",
        s2[] = "Welcome to C++ graphics!",
        s3[] = "graphics on Linux";
  
    outtextxy(100,60,s3);
    outtextxy(70,40,s2);
    outtextxy(130,80,s1);
  
    setcolor(14);
    line(50,200,400,200);
    setcolor(4);
    for (int i=1; i<20; i++)
    {
        setcolor(i);
        delay(500);
        circle(100+10*i,200,80);
    }
  
    cin.get();
    closegraph();
    return 0;
}