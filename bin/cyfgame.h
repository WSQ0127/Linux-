/*库名称：cyfgame.h
版本：1.0
这是一个基于graphics.h图形库编写的一个十分轻量级的游戏编程库
如要使用，请先下载EGE图形库或EasyX*/
#include<graphics.h>
#include<windows.h>
int cyf[1000];
void creat_window(int x,int y,char name[60],int w,int h)//显示窗口，此函数为非必要函数，用EGE的initgraph可以使用，格式一样
{
	initgraph(w,h);
	setcaption(name);
	movewindow(x,y);
}
void hide_cmd(void)//隐藏控制台
{
	ShowWindow(GetForegroundWindow(),SW_HIDE);
}
bool aniu(char name[60],int x,int y,int bian,mouse_msg mouse)//按钮函数 1.按钮的png文件路径,x,y为按钮坐标,4.按钮编号（必须填写）5.定义一个鼠标结构体getmouse(),此函数需要在循环中使用
{
	PIMAGE png=newimage();
	int w,h;
	getimage(png,name);
	w=getwidth(png);
	h=getheight(png);
	if(cyf[bian]==0)
	{
		putimage(x,y,png);
		cyf[bian]=1;
	}
	delimage(png);
	if(mouse.is_down() && mouse.is_left() && mouse.y>=y && mouse.y<=y+h && mouse.x>=x && mouse.x<=x+w)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void mkImg(char s[110], int x, int y, int w, int h) {
	PIMAGE img = newimage(w, h);
	getimage(img, s);
	putimage(x, y, img);
	delimage(img);
}
