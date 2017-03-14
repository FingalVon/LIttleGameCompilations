#include<conio.h>
#include<iostream>
#include<time.h>
#include<Windows.h>
using namespace std;

#define TPUCHWALL 1
#define TOUCHBODY 2
#define WIN 0
#define LENGTH 30
#define WIDTH 10
#define BEGINLEN 4
#define BEGINHEAD LENGTH*WIDTH/2-LENGTH/2
#define DT 10

short SNAKE[2701];
short FOOD;

void gotoxy(int y, int x) //定位到第x行的第y列
{
	int xx=0x0b;
	HANDLE hOutput;
	COORD loc;
	loc.X = x;
	loc.Y=y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, loc);
	return;
}
void newFood(){//生成一个新食物，坐标存储于FOOD
	short i;
	short temp;
	srand((int)time(0));
	FOOD=rand()%(LENGTH*WIDTH)+1;
//	FOOD=1;
	for(i=1;i<=SNAKE[0];i++){
		if(SNAKE[i]==FOOD){
			FOOD=2*SNAKE[SNAKE[0]]-SNAKE[SNAKE[0]-1];
			if(FOOD>LENGTH*WIDTH)FOOD=1;
			i--;
		}
	}
	temp=FOOD%LENGTH;
	if(temp==0)temp=LENGTH;
	gotoxy(FOOD/LENGTH+1,temp);
	cout<<"%";
	return ;
}
void touchWhat(short prev){
	short i;
	short temp;
	for(i=4;i<SNAKE[0];i++){
		if(SNAKE[i]==SNAKE[1]){
				gotoxy(WIDTH+2,0);
				cout<<"GAME OVER!"<<endl;
				getch();
				getch();
				exit(2);
			}
	}
	for(i=2;i<=SNAKE[0];i++){
		temp=SNAKE[i];
		SNAKE[i]=prev;
		prev=temp;
	}
	if(SNAKE[0]==LENGTH*WIDTH){
		gotoxy(WIDTH+2,0);
		cout<<"YOU WIN!"<<endl;
		exit(0);
	}
	if(SNAKE[1]==FOOD){
		gotoxy(FOOD/LENGTH+1,FOOD%LENGTH);
		cout<<" ";
		SNAKE[0]++;
		SNAKE[SNAKE[0]]=prev;
		newFood();
	}
	return ;
}
void run(short lv){
	char key;
	short count=0;
	short dir=0;
	short temp;
	short head;
	short temp0,temp1;
	clock_t start,finish;
	start=clock();
	while(count<lv){
		finish=clock();
		if(finish-start>=DT||start-finish>=DT){
			if(kbhit()){
				key=getch();
				switch(key){
				case 'W':
				case 'w':dir=1;break;
				case 'S':
				case 's':dir=-1;break;
				case 'A':
				case 'a':dir=2;break;
				case 'D':
				case 'd':dir=-2;break;
				case ' ':
					gotoxy(WIDTH+2,0);
					system("Pause");
					gotoxy(WIDTH+2,0);
					cout<<"                     ";
					break;
				}
			}
			start=0;
			count++;
			start=clock();
		}
	}
	temp0=SNAKE[SNAKE[0]]%LENGTH;
	temp1=SNAKE[SNAKE[0]]/LENGTH+1;
	if(temp0==0){
		temp0=LENGTH;
		temp1--;
	}
	gotoxy(temp1,temp0);
	cout<<" ";
	temp=SNAKE[1]-SNAKE[2];
	switch(temp){
	case LENGTH:
	case -LENGTH:
		if(dir==2){
			if(SNAKE[1]%LENGTH==1){
				gotoxy(WIDTH+2,0);
				cout<<"GAME OVER!"<<endl;
				getch();
				getch();
				exit(1);
			}
			head=SNAKE[1]--;
			touchWhat(head);
		}
		else{
			if(dir==-2){
				if(SNAKE[1]%LENGTH==0){
				gotoxy(WIDTH+2,0);
				cout<<"GAME OVER!"<<endl;
				getch();
				getch();
				exit(1);
			}
				head=SNAKE[1]++;
				touchWhat(head);
			}
			else{
				head=SNAKE[1];
				SNAKE[1]+=temp;
				if(SNAKE[1]<=0||SNAKE[1]>LENGTH*WIDTH){
				gotoxy(WIDTH+2,0);
				cout<<"GAME OVER!"<<endl;
				getch();
				getch();
				exit(1);
			}
				touchWhat(head);
			}
		}
		break;
	case 1:
	case -1:
		if(dir==1){
			head=SNAKE[1];
			SNAKE[1]-=LENGTH;
			if(SNAKE[1]<=0){
				gotoxy(WIDTH+2,0);
				cout<<"GAME OVER!"<<endl;
				getch();
				getch();
				exit(1);
			}
			touchWhat(head);
		}
		else{
			if(dir==-1){
				head=SNAKE[1];
				SNAKE[1]+=LENGTH;
				if(SNAKE[1]>=LENGTH*WIDTH){
				gotoxy(WIDTH+2,0);
				cout<<"GAME OVER!"<<endl;
				getch();
				getch();
				exit(1);
			}
				touchWhat(head);
			}
			else{
				if(dir==2||temp==-1)
					if(SNAKE[1]%LENGTH==1){
				gotoxy(WIDTH+2,0);
				cout<<"GAME OVER!"<<endl;
				getch();
				getch();
				exit(1);
			}
				if(dir==-2||temp==1)
					if(SNAKE[1]%LENGTH==0){
				gotoxy(WIDTH+2,0);
				cout<<"GAME OVER!"<<endl;
				getch();
				getch();
				exit(1);
			}
				head=SNAKE[1];
				SNAKE[1]+=temp;
				touchWhat(head);
			}
		}
	}
	return ;
}

void printScreen(){
	short temp0,temp1;
	temp0=SNAKE[1]%LENGTH;
	temp1=SNAKE[1]/LENGTH+1;
	if(temp0==0){
		temp0=LENGTH;
		temp1--;
	}
	gotoxy(temp1,temp0);
	cout<<"O";
	temp0=SNAKE[2]%LENGTH;
	temp1=SNAKE[2]/LENGTH+1;
	if(temp0==0){
		temp0=LENGTH;
		temp1--;
	}
	gotoxy(temp1,temp0);
	cout<<"@";
	gotoxy(3,LENGTH+12);
	cout<<SNAKE[0]-4;
	return ;
}
char chushihua(){//初始化，返回值为游戏难度（e/E简单，n/N一般，h/H困难）
	char lv;
	short i,j;

	SNAKE[0]=BEGINLEN;
	for(i=1;i<=BEGINLEN;i++){
		SNAKE[i]=BEGINHEAD+i-1;
	}
	cout<<"              *                               *                                *                   "<<endl;
	cout<<"             * *                             *                     *            *                  "<<endl;
	cout<<"           *     *                         *  ********             *     **************            "<<endl;
	cout<<"        *     **    *                    *                         *     *             *           "<<endl;
	cout<<"      *        *      **              *   ***********              *     *     *       *           "<<endl;
	cout<<"            *******             ****               *            ******         *   *               "<<endl;
	cout<<"                 *              *  *             *              *  * *         *  *                "<<endl;
	cout<<"                *               *  *           *                *  * *         **                  "<<endl;
	cout<<"            *******             *  *          *                 ******         *                   "<<endl;
	cout<<"            *  *  *             ****         *                     *           *                   "<<endl;
	cout<<"            *  *  *                         *                      *           *                   "<<endl;
	cout<<"              * *                          *                       * *         *                   "<<endl;
	cout<<"            *     *                       *           *           ****         *       *           "<<endl;
	cout<<"          *         *                     *************         **    *         ********           "<<endl;
	cout<<endl;
	cout<<"                                                                                       版本：1.0   "<<endl;
	cout<<endl;
	cout<<"                                      ";
	system("Pause");
	system("cls");
	cout<<"Input a letter to choose level.(E to Easy,N to Normal,H to Hard)"<<endl;
	while(1){
		cin>>lv;
		if(lv!='E'&&lv!='e'&&lv!='N'&&lv!='n'&&lv!='H'&&lv!='h'){
			cout<<"Error input.Please try again."<<endl;
			continue;
		}
		break;
	}
	system("cls");
	cout<<"GAME START!";
	system("cls");
	for(i=0;i<=LENGTH+1;i++)cout<<"*";
	cout<<endl;
	for(i=1;i<=WIDTH;i++){
		cout<<"*";
		for(j=1;j<=LENGTH;j++){
			cout<<" ";
		}
		cout<<"*"<<endl;
	}
	for(i=0;i<=LENGTH+1;i++)cout<<"*";
	gotoxy(SNAKE[1]/LENGTH+1,SNAKE[1]%LENGTH);
	cout<<"O";
	for(i=2;i<=SNAKE[0];i++){
		gotoxy(SNAKE[i]/LENGTH+1,SNAKE[i]%LENGTH);
		cout<<"@";
	}
	gotoxy(2,LENGTH+6);
	cout<<"LEVEL:";
	switch(lv){
	case 'e':
	case 'E':cout<<"EASY";break;
	case 'n':
	case 'N':cout<<"NORMAL";break;
	case 'h':
	case 'H':cout<<"HARD";break;
	}
	gotoxy(3,LENGTH+6);
	cout<<"SCORE:"<<SNAKE[0]-4;
	newFood();
	return lv;
}
short main(){
	char c;
	short lv;
	c=chushihua();
	switch(c){
	case 'e':
	case 'E':lv=70;break;
	case 'n':
	case 'N':lv=30;break;
	case 'h':
	case 'H':lv=8;break;
	}
	while(1){
		run(lv);
		printScreen();
	}
	return 0;
}