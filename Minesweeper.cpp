#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
int MAP[101][101];
int COUNT;
int X,Y;
int BOOMER;
int STEP;
void setBoomer(int boomer,int size){
	int b=boomer;
	int i,j;
	int m,n;
	int count;
	int flag;
	srand((int)time(0));
	if(b<size/2){
		while(b--){
			m=rand()%X+1;
			n=rand()%Y+1;
			if(MAP[m][n]==-2){
				b++;
				continue;
			}
			MAP[m][n]=-2;
			for(i=-1;i<=1;i++){
				for(j=-1;j<=1;j++){
					if(i==0&&j==0)continue;
					if(MAP[m+i][n+j]!=-2)
						MAP[m+i][n+j]+=1;
				}
			}
		}
	}
	else{
		MAP[0][0]=MAP[0][Y+1]=MAP[X+1][0]=MAP[X+1][Y+1]=1;
		MAP[0][1]=MAP[0][X]=MAP[1][0]=MAP[1][X+1]=MAP[Y][0]=MAP[Y][X+1]=MAP[Y+1][1]=MAP[Y+1][X]=2;
		for(i=2;i<X;i++){
			MAP[0][i]=MAP[X+1][i]=3;
		}
		for(i=2;i<Y;i++){
			MAP[i][0]=MAP[i][Y+1]=3;
		}
		for(i=1;i<=X;i++){
			for(j=1;j<=Y;j++){
				MAP[i][j]=-2;
			}
		}
		while(b--){
			m=rand()%X+1;
			n=rand()%Y+1;
			if(MAP[m][n]!=-2){
				b++;
				continue;
			}
			MAP[m][n]=0;
			for(i=-1;i<=1;i++){
				for(j=-1;j<=1;j++){
					if(i==0&&j==0)continue;
					if(MAP[m+i][n+j]==-2)MAP[m][n]++;
					else	MAP[m+i][n+j]--;
				}
			}
		}
	}
	return ;
}
void chushihua(){
	int i,j;
	STEP=0;
	COUNT=0;
	cout<<"   ";
	for(j=1;j<=Y;j++){
		if(j<10)cout<<" ";
		cout<<" "<<j;
	}
	cout<<endl;
	cout<<"    ";
	for(i=1;i<=Y;i++){
		cout<<"---";
	}
	cout<<endl;
	for(i=1;i<=X;i++){
		if(i<10)cout<<" ";
		cout<<i<<" |";
		for(j=1;j<=Y;j++){
			cout<<" ¨€";
		}
		cout<<endl;
	}
	for(i=0;i<=100;i++){
		for(j=0;j<=100;j++){
			MAP[i][j]=0;
		}
	}
	setBoomer(BOOMER,X*Y);
	return ;
}

void printScreen(int gameover){
	int i,j;
	system("cls");
	cout<<"   ";
	for(j=1;j<=Y;j++){
		if(j<10)cout<<" ";
		cout<<" "<<j;
	}
	cout<<endl;
	cout<<"    ";
	for(i=1;i<=Y;i++){
		cout<<"---";
	}
	cout<<endl;
	if(gameover==1){
		for(i=1;i<=X;i++){
			if(i<10)cout<<" ";
			cout<<i<<" |";
			for(j=1;j<=Y;j++){
				cout<<" ";
				if(MAP[i][j]==-1){cout<<"  ";continue;}
				if(MAP[i][j]==-2){cout<<"X ";continue;}
				if(MAP[i][j]<-2){cout<<MAP[i][j]+11<<" ";continue;}
				cout<<"¨€";
			}
			cout<<endl;
		}
		cout<<"BOOM!GAME OVER!"<<endl;
		cout<<"Press any key to exit."<<endl;
		system("Pause");
		return ;
	}
	for(i=1;i<=X;i++){
		if(i<10)cout<<" ";
		cout<<i<<" |";
		for(j=1;j<=Y;j++){
			cout<<" ";
			if(MAP[i][j]==-1){cout<<"  ";continue;}
			if(MAP[i][j]<-2){cout<<MAP[i][j]+11<<" ";continue;}
			cout<<"¨€";
		}
		cout<<endl;
	}
	return ;
}
int revealPlace(int x,int y){
	int i,j;
	if(MAP[x][y]==-2)return -1;
	if(MAP[x][y]>0){
			MAP[x][y]-=11;
			COUNT++;
			return 1;
	}
	if(MAP[x][y]==0){
		MAP[x][y]=-1;
		for(i=-1;i<=1;i++){
			for(j=-1;j<=1;j++){
				if(x+i>0&&x+i<=X&&y+j>0&&y+j<=Y)
					revealPlace(x+i,y+j);
			}
		}
		COUNT++;
		return 0;
	}
}

int victoryOrNot(int size){
	return size-BOOMER-COUNT;
}
int main(){
	int i,j;
	int size;
	int m,n;
	int temp;
	int step;
	cout<<"Plase input the size of gameboard."<<endl;
	cout<<"length:(¡Ý1£¬¡Ü99)";
	cin>>X;
	cout<<"width:£¨¡Ý1£¬¡Ü99)";
	cin>>Y;
	cout<<"Please input the number of boomer."<<endl;
	cin>>BOOMER;
	size=X*Y;
	if(X<1||X>99||Y<1||Y>99||BOOMER<1||BOOMER>=size){
		cout<<"Error size!"<<endl;
		return -1;
	}
	cout<<"GAME START!"<<endl;
	system("cls");
	chushihua();
	while(victoryOrNot(size)){
			cout<<"Please input the coordinate you want to reveal."<<endl;
			cout<<"x:";
			cin>>i;
			cout<<"y:";
			cin>>j;
			if(i<=0||i>X||j<=0||j>Y){
				cout<<"Error coordinate!"<<endl;
				continue;
			}
			if((++STEP)==1){
				if(MAP[i][j]==-2){
					setBoomer(1,size-BOOMER);
					MAP[i][j]=0;
					temp=0;
					for(m=-1;m<=1;m++){
						for(n=-1;n<=1;n++){
							if(MAP[i+m][j+n]==-2)temp++;
							else	MAP[i+m][j+n]--;
						}
					}
					MAP[i][j]=temp;
				}
			}
			if(revealPlace(i,j)==-1){
				printScreen(1);
				return 0;
		}
		printScreen(0);
	}
	cout<<"YOU WIN!"<<endl;
	cout<<STEP<<" steps have been used."<<endl;
	cout<<"Press any key to exit."<<endl;
	system("Pause");
	return 1;
}
