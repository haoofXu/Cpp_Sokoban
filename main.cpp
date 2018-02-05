#define _CRT_SECURE_NO_WARNINGS  

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>


int m[12][13] = {
	1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,8,0,0,1,
	1,0,0,0,0,0,0,0,0,8,0,0,1,
	1,0,0,0,0,4,0,0,0,8,0,0,1,
	1,0,0,0,0,4,0,0,0,8,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,4,0,0,0,4,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,
};
static int count = 0; //成功点计数
static int x = 2, y = 1; //人物初始坐标
static int a = 0, b = 0; //移动指令辅助值


void help()
{
	printf("请将四个箱子全部推向4个成功点通关游戏\n");
	printf("W上 A左 S下 D右\n\n");
	printf("游戏愉快\n");
}
int prnmap()
{
	count = 0; //每次刷新地图计数回零
	system("cls");
	help(); //温馨提示
	for (int i = 0; i<12; i++)
	{
		printf("\t\t"); //移到屏幕中间
		for (int j = 0; j<13; j++)
		{
			if (m[i][j] == 1)
				printf("#");
			else if (m[i][j] == 0)
				printf(" ");
			else if (m[i][j] == 8)
				printf("0");
			else if (m[i][j] == 2 || m[i][j] == 3) //分为人物在空地和人物在成功点
				printf("1");
			else if (m[i][j] == 4)
				printf("=");
			else if (m[i][j] == 5)
			{
				count++; //每扫描到一个成功值 计数加1
				printf("+");
			}
		}
		printf("\n");
	}
	return count;
}


void key() //按键操作
{
	char z;
	for (;;)
	{
		z = getchar();
		if (z == 'w' || z == 'W')
		{
			a = -1;
			b = 0;
			break;
		}
		else if (z == 'a' || z == 'A')
		{
			a = 0;
			b = -1;
			break;
		}
		else if (z == 's' || z == 'S')
		{
			a = 1;
			b = 0;
			break;
		}
		else if (z == 'd' || z == 'D')
		{
			a = 0;
			b = 1;
			break;
		}
	}
}


void move()
{
	if (m[x + a][y + b] == 0) //人物前面是否为空地
	{
		if (m[x][y] == 3) //人物此时的位置在成功点上
		{
			x += a;
			y += b;
			m[x][y] = 2;
			m[x - a][y - b] = 4;
		}
		else //人物此时的位置不在成功点上
		{
			x += a;
			y += b;
			m[x][y] = 2;
			m[x - a][y - b] = 0;
		}
	}
	else if (m[x + a][y + b] == 4) //人物前面是成功点
	{
		if (m[x][y] == 2) //此时在空地
		{
			x += a;
			y += b;
			m[x][y] = 3;
			m[x - a][y - b] = 0;
		}
		else if (m[x][y] == 3) //此时在成功点
		{
			x += a;
			y += b;
			m[x][y] = 3;
			m[x - a][y - b] = 4;
		}
	}
	else if (m[x + a][y + b] == 8 && m[x + 2 * a][y + 2 * b] == 0) //人物前面是箱子 并且箱子前面是空地
	{
		if (m[x][y] == 2) //人在空地
		{
			x += a;
			y += b;
			m[x][y] = 2;
			m[x - a][y - b] = 0;
			m[x + a][y + b] = 8;
		}
		else if (m[x][y] == 3) //人在成功点
		{
			x += a;
			y += b;
			m[x][y] = 2;
			m[x - a][y - b] = 4;
			m[x + a][y + b] = 8;
		}
	}
	else if (m[x + a][y + b] == 8 && m[x + 2 * a][y + 2 * b] == 4) //人物前面是箱子 并且箱子前面是成功点
	{
		x += a;
		y += b;
		m[x][y] = 2;
		m[x - a][y - b] = 0;
		m[x + a][y + b] = 5;
	}
	else if (m[x + a][y + b] == 5 && m[x + 2 * a][y + 2 * b] == 0) //人物前面是成功箱子，箱子前面是空地
	{
		if (m[x][y] == 2) //人在空地
		{
			x += a;
			y += b;
			m[x][y] = 3;
			m[x + a][y + b] = 8;
			m[x - a][y - b] = 0;
		}
		else if (m[x][y] == 3) //人在成功点
		{
			x += a;
			y += b;
			m[x][y] = 3;
			m[x + a][y + b] = 8;
			m[x - a][y - b] = 4;
		}
	}
	else if (m[x + a][y + b] == 5 && m[x + 2 * a][y + 2 * b] == 4) //人物前面是成功箱子 箱子前面是成功点
	{
		x += a;
		y += b;
		m[x][y] = 3;
		m[x + a][y + b] = 5;
		m[x - a][y - b] = 0;
	}
}


void game()
{
	m[2][1] = 2; //初始化人物模型点


	for (;;)
	{
		prnmap(); //地图打印
		key(); //操作指令
		move(); //移动判断函数
		if (prnmap() == 4) //通关条件
		{
			printf("\n\n\t\t\t恭喜游戏通关\n");
			break;
		}
	}
	system("pause"); //等待退出指令
}


int main()
{
	game();
	return 0;
}

