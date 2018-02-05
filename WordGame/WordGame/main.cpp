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
static int count = 0; //�ɹ������
static int x = 2, y = 1; //�����ʼ����
static int a = 0, b = 0; //�ƶ�ָ���ֵ


void help()
{
	printf("�뽫�ĸ�����ȫ������4���ɹ���ͨ����Ϸ\n");
	printf("W�� A�� S�� D��\n\n");
	printf("��Ϸ���\n");
}
int prnmap()
{
	count = 0; //ÿ��ˢ�µ�ͼ��������
	system("cls");
	help(); //��ܰ��ʾ
	for (int i = 0; i<12; i++)
	{
		printf("\t\t"); //�Ƶ���Ļ�м�
		for (int j = 0; j<13; j++)
		{
			if (m[i][j] == 1)
				printf("#");
			else if (m[i][j] == 0)
				printf(" ");
			else if (m[i][j] == 8)
				printf("0");
			else if (m[i][j] == 2 || m[i][j] == 3) //��Ϊ�����ڿյغ������ڳɹ���
				printf("1");
			else if (m[i][j] == 4)
				printf("=");
			else if (m[i][j] == 5)
			{
				count++; //ÿɨ�赽һ���ɹ�ֵ ������1
				printf("+");
			}
		}
		printf("\n");
	}
	return count;
}


void key() //��������
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
	if (m[x + a][y + b] == 0) //����ǰ���Ƿ�Ϊ�յ�
	{
		if (m[x][y] == 3) //�����ʱ��λ���ڳɹ�����
		{
			x += a;
			y += b;
			m[x][y] = 2;
			m[x - a][y - b] = 4;
		}
		else //�����ʱ��λ�ò��ڳɹ�����
		{
			x += a;
			y += b;
			m[x][y] = 2;
			m[x - a][y - b] = 0;
		}
	}
	else if (m[x + a][y + b] == 4) //����ǰ���ǳɹ���
	{
		if (m[x][y] == 2) //��ʱ�ڿյ�
		{
			x += a;
			y += b;
			m[x][y] = 3;
			m[x - a][y - b] = 0;
		}
		else if (m[x][y] == 3) //��ʱ�ڳɹ���
		{
			x += a;
			y += b;
			m[x][y] = 3;
			m[x - a][y - b] = 4;
		}
	}
	else if (m[x + a][y + b] == 8 && m[x + 2 * a][y + 2 * b] == 0) //����ǰ�������� ��������ǰ���ǿյ�
	{
		if (m[x][y] == 2) //���ڿյ�
		{
			x += a;
			y += b;
			m[x][y] = 2;
			m[x - a][y - b] = 0;
			m[x + a][y + b] = 8;
		}
		else if (m[x][y] == 3) //���ڳɹ���
		{
			x += a;
			y += b;
			m[x][y] = 2;
			m[x - a][y - b] = 4;
			m[x + a][y + b] = 8;
		}
	}
	else if (m[x + a][y + b] == 8 && m[x + 2 * a][y + 2 * b] == 4) //����ǰ�������� ��������ǰ���ǳɹ���
	{
		x += a;
		y += b;
		m[x][y] = 2;
		m[x - a][y - b] = 0;
		m[x + a][y + b] = 5;
	}
	else if (m[x + a][y + b] == 5 && m[x + 2 * a][y + 2 * b] == 0) //����ǰ���ǳɹ����ӣ�����ǰ���ǿյ�
	{
		if (m[x][y] == 2) //���ڿյ�
		{
			x += a;
			y += b;
			m[x][y] = 3;
			m[x + a][y + b] = 8;
			m[x - a][y - b] = 0;
		}
		else if (m[x][y] == 3) //���ڳɹ���
		{
			x += a;
			y += b;
			m[x][y] = 3;
			m[x + a][y + b] = 8;
			m[x - a][y - b] = 4;
		}
	}
	else if (m[x + a][y + b] == 5 && m[x + 2 * a][y + 2 * b] == 4) //����ǰ���ǳɹ����� ����ǰ���ǳɹ���
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
	m[2][1] = 2; //��ʼ������ģ�͵�


	for (;;)
	{
		prnmap(); //��ͼ��ӡ
		key(); //����ָ��
		move(); //�ƶ��жϺ���
		if (prnmap() == 4) //ͨ������
		{
			printf("\n\n\t\t\t��ϲ��Ϸͨ��\n");
			break;
		}
	}
	system("pause"); //�ȴ��˳�ָ��
}


int main()
{
	game();
	return 0;
}

