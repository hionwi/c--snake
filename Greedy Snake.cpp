#include <Windows.h>
#include <time.h>
#include<iostream>
#include<string>
#include<fstream>
#include <conio.h>
#define size 100//蛇的身体最大节数
#define width 118 //边框宽度
#define height 29//边框高度
using namespace std;
//玩家 
struct Player{
	string name;//名字 
	int sc;//成绩
	string difficulty;//难度 
};
int pi=1;
Player play[100]; 
int key=72;//蛇移动的方向，72为按下“↑”所代表的数字
int changeFlag = 0;//判断蛇是否吃掉食物
int score = 0;//玩家的得分
//食物
struct Food{
	int x;
	int y;
}food;
//蛇
struct Snake{
	int speed;//蛇移动的速度
	int len;//蛇的长度 
	int x[size];//蛇的x坐标
	int y[size];//蛇的y坐标
 
}snake;
//读取本地排名
void readrank(); 
//保存本地排名
void saverank(); 
//绘制边框
void draw();
//创造食物 
void creatfood();
//吃掉食物
void eatfood();
//按键操作
void operate();
//蛇的状态
bool state();
//移动光标
void moveCursor(int x, int y);
//隐藏光标
void HideCursor();
//操作说明
void explain();
//显示排名
void showrank();
//难度设置
void dif();
//开始游戏
void game();
//初始化
void init();
//初始菜单
void menu(); 
void readrank()
{
		ifstream fin("rank.txt");
		while(fin>>play[pi].sc>>play[pi].difficulty>>play[pi].name)//读取数据 
		{
			pi++;
		}
		pi--;
} 
void saverank()
{
	ofstream fout("rank.txt");
	for(int j=1;j<=pi;j++)
	fout<<play[j].sc<<' '<<play[j].difficulty<<' '<<play[j].name<<endl;//保存数据 
	fout.close();
}
void explain()
{
		system("CLS");
		cout<<"通过小键盘控制蛇前进方向，获取食物增加积分，\n随着吃的食物越来越多，速度会越来越快，\n蛇头碰到墙壁或蛇身则游戏结束"<<endl;
		cout<<"按1返回菜单";
		if(getch()=='1')
		menu();
 } 
void showrank()
{
		system("cls");
		if(pi==0)
		cout<<"暂无数据"<<endl;
		for(int j=1;j<=pi;j++)
		{
		cout<<"成绩"<<'\t'<<"难度"<<'\t'<<"名字"<<endl;
		cout<<play[j].sc<<'\t'<<play[j].difficulty<<'\t'<<play[j].name<<endl;}
		cout<<"按1返回菜单";
		if(getch()=='1')
		menu();
} 
void dif()
{
		system("cls");
		cout<<"选择难度："<<endl<<"1.简单"<<endl<<"2.中等"<<endl<<"3.困难"<<endl; 
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
	cout<<"输入你的名字：";
	moveCursor(width / 2, height / 2 + 3);
	cin>>play[pi].name;
	play[pi].sc=score;
	saverank();
	moveCursor(width / 2, height / 2 + 5);
	cout<<"数据已保存";
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
			while(food.x%2!=0)//食物横坐标不能为奇数 
			{
			food.x = rand() % (width - 4) + 2;
			} 
			food.y = rand() % (height - 2) + 1;
			//生成的食物不能在蛇的身体上
			for (int i = 0; i < snake.len; i++)
			{
				if (snake.x[i] == food.x && snake.y[i] == food.y)
				{
					flag = 0;
					break;
				}
			}
			//生成的食物不能在蛇身
			if (flag)
				break;
		}
	moveCursor(food.x, food.y);
	cout<<"★";//生成食物 
}
void menu()
{	
	system("CLS");
	cout<<"\t\t\t贪吃蛇小游戏";
	cout<<endl;
	cout<<"1.开始游戏"<<endl<<"2.游戏说明"<<endl<<"3.退出游戏"<<endl<<"4.本地排名"; 
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
	//打印上下边框
	for (int i = 0; i <= width; i += 2)
	{
		moveCursor(i, 0);
		cout<<"■";
		moveCursor(i, height);
		cout<<"■";
	}
 
	//打印左右边框
	for (int i = 1; i < height; i++)
	{
		moveCursor(0, i);
		cout<<"■";
		moveCursor(width, i);
		cout<<"■";
	}
	//生成蛇的头部 
	snake.x[0] = width / 2 + 1;//x坐标为偶数
	snake.y[0] = height / 2;
	moveCursor(snake.x[0], snake.y[0]);
	cout<<"■";
 
	//生成初始的蛇身
	for (int i = 1; i < snake.len; i++)
	{
		snake.x[i] = snake.x[i - 1] + 2;
		snake.y[i] = snake.y[i - 1];
		moveCursor(snake.x[i], snake.y[i]);
		cout<<"■";
	}
	//生成初始食物
	creatfood();
	return;
}
void operate()
{
	int pre_key = key;//记录前一个按键的方向
	if (kbhit())
	{
		fflush(stdin);
		key = getch();//第一次调用返回的不是实际值
		key = getch();//第二次调用返回实际值
	}
 
	/*
	*蛇移动时候先擦去蛇尾的一节
	*changeFlag为0表明此时没有吃到食物，因此每走一步就要擦除掉蛇尾，以此营造一个移动的效果
	*为1表明吃到了食物，就不需要擦除蛇尾，以此营造一个蛇身增长的效果
	*/
	if (changeFlag == 0)
	{
		moveCursor(snake.x[snake.len - 1], snake.y[snake.len - 1]);
		cout<<"  ";//在蛇尾处输出空格即擦去蛇尾
	}
 
	//将蛇的每一节依次向前移动一节（蛇头除外）
	for (int i = snake.len - 1; i > 0; i--)
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1];
	}
 
	//蛇当前移动的方向不能和前一次的方向相反，比如蛇往左走的时候不能直接按右键往右走
	//如果当前移动方向和前一次方向相反的话，把当前移动的方向改为前一次的方向
	if (pre_key == 72 && key == 80)
		key = 72;
	if (pre_key == 80 && key == 72)
		key = 80;
	if (pre_key == 75 && key == 77)
		key = 75;
	if (pre_key == 77 && key == 75)
		key = 77;
 
	/**
	*控制台按键所代表的数字
	*“↑”：72
	*“↓”：80
	*“←”：75
	*“→”：77
	*/
 
	//判断蛇头应该往哪个方向移动
	switch (key)
	{
	case 75:
		snake.x[0] -= 2;//往左
		break;
	case 77:
		snake.x[0] += 2;//往右
		break;
	case 72:
		snake.y[0]--;//往上
		break;
	case 80:
		snake.y[0]++;//往下
		break;
	}
	//打印出蛇头
	moveCursor(snake.x[0], snake.y[0]);
	cout<<"■";
	//由于目前没有吃到食物，changFlag值为0
	changeFlag = 0;
	return;
}
void eatfood()
{
	if (snake.x[0] == food.x && snake.y[0] == food.y)//蛇头碰到食物
	{
		//蛇头碰到食物即为要吃掉这个食物了，因此需要再次生成一个食物
		creatfood(); //绘制食物
		snake.len++;//吃到食物，蛇身长度加1
		score++;//每个食物得1分
		snake.speed -= 5;//随着吃的食物越来越多，速度会越来越快
		changeFlag = 1;//很重要，因为吃到了食物，就不用再擦除蛇尾的那一节，以此来造成蛇身体增长的效果
	}
	return;
}
bool state()
{
	//蛇头碰到上下边界，游戏结束
	if (snake.y[0] == 0 || snake.y[0] == height)
		return false;
	//蛇头碰到左右边界，游戏结束
	if (snake.x[0] == 0 || snake.x[0] == width)
		return false;
	//蛇头碰到蛇身，游戏结束
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

