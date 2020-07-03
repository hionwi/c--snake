#include <Windows.h>
#include <time.h>
#include<iostream>
#include<string>
#include<fstream>
#include <conio.h>
#define size 100//�ߵ�����������
#define width 118 //�߿���
#define height 29//�߿�߶�
using namespace std;
//��� 
struct Player{
	string name;//���� 
	int sc;//�ɼ�
	string difficulty;//�Ѷ� 
};
int pi=1;
Player play[100]; 
int key=72;//���ƶ��ķ���72Ϊ���¡����������������
int changeFlag = 0;//�ж����Ƿ�Ե�ʳ��
int score = 0;//��ҵĵ÷�
//ʳ��
struct Food{
	int x;
	int y;
}food;
//��
struct Snake{
	int speed;//���ƶ����ٶ�
	int len;//�ߵĳ��� 
	int x[size];//�ߵ�x����
	int y[size];//�ߵ�y����
 
}snake;
//��ȡ��������
void readrank(); 
//���汾������
void saverank(); 
//���Ʊ߿�
void draw();
//����ʳ�� 
void creatfood();
//�Ե�ʳ��
void eatfood();
//��������
void operate();
//�ߵ�״̬
bool state();
//�ƶ����
void moveCursor(int x, int y);
//���ع��
void HideCursor();
//����˵��
void explain();
//��ʾ����
void showrank();
//�Ѷ�����
void dif();
//��ʼ��Ϸ
void game();
//��ʼ��
void init();
//��ʼ�˵�
void menu(); 
void readrank()
{
		ifstream fin("rank.txt");
		while(fin>>play[pi].sc>>play[pi].difficulty>>play[pi].name)//��ȡ���� 
		{
			pi++;
		}
		pi--;
} 
void saverank()
{
	ofstream fout("rank.txt");
	for(int j=1;j<=pi;j++)
	fout<<play[j].sc<<' '<<play[j].difficulty<<' '<<play[j].name<<endl;//�������� 
	fout.close();
}
void explain()
{
		system("CLS");
		cout<<"ͨ��С���̿�����ǰ�����򣬻�ȡʳ�����ӻ��֣�\n���ųԵ�ʳ��Խ��Խ�࣬�ٶȻ�Խ��Խ�죬\n��ͷ����ǽ�ڻ���������Ϸ����"<<endl;
		cout<<"��1���ز˵�";
		if(getch()=='1')
		menu();
 } 
void showrank()
{
		system("cls");
		if(pi==0)
		cout<<"��������"<<endl;
		for(int j=1;j<=pi;j++)
		{
		cout<<"�ɼ�"<<'\t'<<"�Ѷ�"<<'\t'<<"����"<<endl;
		cout<<play[j].sc<<'\t'<<play[j].difficulty<<'\t'<<play[j].name<<endl;}
		cout<<"��1���ز˵�";
		if(getch()=='1')
		menu();
} 
void dif()
{
		system("cls");
		cout<<"ѡ���Ѷȣ�"<<endl<<"1.��"<<endl<<"2.�е�"<<endl<<"3.����"<<endl; 
		char cp;
		cp=getch();
		if(cp=='1')
		{
		snake.speed=150;
		play[pi+1].difficulty="Simple";} 
		if(cp=='2')
		{snake.speed=100;
		play[pi+1].difficulty="Mid";} 
		if(cp=='3')
		{snake.speed=50;
		play[pi+1].difficulty="Hard";} 
		pi++;
		return;
 } 
void game()
{
	dif();
	system("cls");
	draw();
	while (1)
	{
		operate();
		if (!state())
			break;
		eatfood();
		Sleep(snake.speed);
	}
	moveCursor(width / 2, height / 2);
	cout<<"Game over!";
	moveCursor(width / 2, height / 2 + 1);
	cout<<"Score: "<<score;
	moveCursor(width / 2, height / 2 + 2);
	cout<<"����������֣�";
	moveCursor(width / 2, height / 2 + 3);
	cin>>play[pi].name;
	play[pi].sc=score;
	saverank();
	moveCursor(width / 2, height / 2 + 5);
	cout<<"�����ѱ���";
	Sleep(1000);
	return;
	} 
void init()
{
	snake.speed=150;
	snake.len=3;
	score=0; 
} 
void moveCursor(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor;    
	cursor.bVisible = FALSE;    
	cursor.dwSize = sizeof(cursor);    
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    
	SetConsoleCursorInfo(handle, &cursor);
}
void creatfood()
{
	while (1)
		{
			int flag = 1;
			srand((unsigned int)time(NULL));
			food.x = rand() % (width - 4) + 2;
			while(food.x%2!=0)//ʳ������겻��Ϊ���� 
			{
			food.x = rand() % (width - 4) + 2;
			} 
			food.y = rand() % (height - 2) + 1;
			//���ɵ�ʳ�ﲻ�����ߵ�������
			for (int i = 0; i < snake.len; i++)
			{
				if (snake.x[i] == food.x && snake.y[i] == food.y)
				{
					flag = 0;
					break;
				}
			}
			//���ɵ�ʳ�ﲻ��������
			if (flag)
				break;
		}
	moveCursor(food.x, food.y);
	cout<<"��";//����ʳ�� 
}
void menu()
{	
	system("CLS");
	cout<<"\t\t\t̰����С��Ϸ";
	cout<<endl;
	cout<<"1.��ʼ��Ϸ"<<endl<<"2.��Ϸ˵��"<<endl<<"3.�˳���Ϸ"<<endl<<"4.��������"; 
	char a=getch();
	switch (a)
	{
		case '1':game();break;
		case '2':explain();break;
		case '3':return;
		case '4':showrank();break;
	}
}
void draw()
{
	//��ӡ���±߿�
	for (int i = 0; i <= width; i += 2)
	{
		moveCursor(i, 0);
		cout<<"��";
		moveCursor(i, height);
		cout<<"��";
	}
 
	//��ӡ���ұ߿�
	for (int i = 1; i < height; i++)
	{
		moveCursor(0, i);
		cout<<"��";
		moveCursor(width, i);
		cout<<"��";
	}
	//�����ߵ�ͷ�� 
	snake.x[0] = width / 2 + 1;//x����Ϊż��
	snake.y[0] = height / 2;
	moveCursor(snake.x[0], snake.y[0]);
	cout<<"��";
 
	//���ɳ�ʼ������
	for (int i = 1; i < snake.len; i++)
	{
		snake.x[i] = snake.x[i - 1] + 2;
		snake.y[i] = snake.y[i - 1];
		moveCursor(snake.x[i], snake.y[i]);
		cout<<"��";
	}
	//���ɳ�ʼʳ��
	creatfood();
	return;
}
void operate()
{
	int pre_key = key;//��¼ǰһ�������ķ���
	if (kbhit())
	{
		fflush(stdin);
		key = getch();//��һ�ε��÷��صĲ���ʵ��ֵ
		key = getch();//�ڶ��ε��÷���ʵ��ֵ
	}
 
	/*
	*���ƶ�ʱ���Ȳ�ȥ��β��һ��
	*changeFlagΪ0������ʱû�гԵ�ʳ����ÿ��һ����Ҫ��������β���Դ�Ӫ��һ���ƶ���Ч��
	*Ϊ1�����Ե���ʳ��Ͳ���Ҫ������β���Դ�Ӫ��һ������������Ч��
	*/
	if (changeFlag == 0)
	{
		moveCursor(snake.x[snake.len - 1], snake.y[snake.len - 1]);
		cout<<"  ";//����β������ո񼴲�ȥ��β
	}
 
	//���ߵ�ÿһ��������ǰ�ƶ�һ�ڣ���ͷ���⣩
	for (int i = snake.len - 1; i > 0; i--)
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1];
	}
 
	//�ߵ�ǰ�ƶ��ķ����ܺ�ǰһ�εķ����෴�������������ߵ�ʱ����ֱ�Ӱ��Ҽ�������
	//�����ǰ�ƶ������ǰһ�η����෴�Ļ����ѵ�ǰ�ƶ��ķ����Ϊǰһ�εķ���
	if (pre_key == 72 && key == 80)
		key = 72;
	if (pre_key == 80 && key == 72)
		key = 80;
	if (pre_key == 75 && key == 77)
		key = 75;
	if (pre_key == 77 && key == 75)
		key = 77;
 
	/**
	*����̨���������������
	*��������72
	*��������80
	*��������75
	*��������77
	*/
 
	//�ж���ͷӦ�����ĸ������ƶ�
	switch (key)
	{
	case 75:
		snake.x[0] -= 2;//����
		break;
	case 77:
		snake.x[0] += 2;//����
		break;
	case 72:
		snake.y[0]--;//����
		break;
	case 80:
		snake.y[0]++;//����
		break;
	}
	//��ӡ����ͷ
	moveCursor(snake.x[0], snake.y[0]);
	cout<<"��";
	//����Ŀǰû�гԵ�ʳ�changFlagֵΪ0
	changeFlag = 0;
	return;
}
void eatfood()
{
	if (snake.x[0] == food.x && snake.y[0] == food.y)//��ͷ����ʳ��
	{
		//��ͷ����ʳ�ＴΪҪ�Ե����ʳ���ˣ������Ҫ�ٴ�����һ��ʳ��
		creatfood(); //����ʳ��
		snake.len++;//�Ե�ʳ������ȼ�1
		score++;//ÿ��ʳ���1��
		snake.speed -= 5;//���ųԵ�ʳ��Խ��Խ�࣬�ٶȻ�Խ��Խ��
		changeFlag = 1;//����Ҫ����Ϊ�Ե���ʳ��Ͳ����ٲ�����β����һ�ڣ��Դ������������������Ч��
	}
	return;
}
bool state()
{
	//��ͷ�������±߽磬��Ϸ����
	if (snake.y[0] == 0 || snake.y[0] == height)
		return false;
	//��ͷ�������ұ߽磬��Ϸ����
	if (snake.x[0] == 0 || snake.x[0] == width)
		return false;
	//��ͷ����������Ϸ����
	for (int i = 1; i < snake.len; i++)
	{
		if (snake.x[i] == snake.x[0] && snake.y[i] == snake.y[0])
			return false;
	}
	return true;
}
int main()
{	
	readrank();	
	init();
	HideCursor();
	menu();
	return 0;
}

