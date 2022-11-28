#include <iostream>
#include <windows.h>
#include <conio.h>


using namespace std;

bool gameOver;
const int widht = 40;
const int height = 20;
int x , y , fruitX , fruitY , score;
int tailX[100];
int tailY[100];
int nTail;
enum eDirection{STOP = 0 , LEFT , RIGHT , UP , DOWN};
eDirection dir;
void setup(){

	gameOver = false;
	dir = STOP;
	x = widht / 2;
	y = height / 2;
	fruitX = rand() % widht;
	fruitY = rand() % height;
	score = 0;
}

void drawing(){

	Sleep(10);
	system("cls");
	for(int i = 0; i < widht + 2; i++){
		cout << "#";
	}

	cout << endl;

	for(int i = 0; i < height; i++){
		for(int j = 0; j < widht; j++){
			if(j == 0){
				cout << "#";
			}
			if(i == y && j == x){
				cout << "O";
			}
			else if(i == fruitY && j == fruitX){
				cout << "F";
			}
			else{

				bool print = false;
				for(int k = 0; k < nTail; k++){
					if(tailX[k] == j && tailY[k] == i){
						cout << "o";
						print = true;
					}
				}
				if(!print)
					cout << " ";
		}

			

			if(j == widht - 1){
				cout << "#";
			}

		}
		cout << endl;
	}

	for(int i = 0; i < widht + 2; i++){
		cout << "#";
	}
	cout << endl;
	cout << "YOUR SCORE = " << score << endl;
}

void input(){
	if(_kbhit()){
		switch(_getch()){
			case 'a':
			dir = LEFT;
			break;

			case 'd':
			dir = RIGHT;
			break;

			case 'w':
			dir = UP;
			break;

			case 's':
			dir = DOWN;
			break;

			case 'x':
			gameOver = true;
			break;
		}
	}
}

void logic(){

	int prevX = tailX[0];
	int prevY = tailY[0];
	int prevX2 = x;
	int prevY2 = y;
	tailX[0] = x;
	tailY[0] = y;

	for(int i = 1; i < nTail; i++){
		prevX2 = tailX[i];
		prevY2 = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prevX2;
		prevY = prevY2;
	}
	switch(dir){
		case LEFT:
		x--;
		break;

		case RIGHT:
		x++;
		break;

		case UP:
		y--;
		break;

		case DOWN:
		y++;
		break;

		default:
		break;
	}

	//if(x > widht || x < 0 || y > height || y < 0){
	//	gameOver = true;
	//}

	if(x >= widht){
		x = 1;
	}else if(x < 0){
		x = widht - 1;
	}

	if(y >= height){
		y = 1;
	}else if(y < 0){
		y = height - 1;
	}

	for(int i = 0; i < nTail; i++){
		if(tailX[i] == x && tailY[i] == y){
			gameOver = true;
		}
	}

	if(x == fruitX && y == fruitY){
		score += 10;

		fruitX = rand() % widht;
		fruitY = rand() % height;
		nTail++;
	}
}

int main()
{

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h,FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	setup();
	while(!gameOver){
		drawing();
		input();
		logic();
	}

	return 0;
}