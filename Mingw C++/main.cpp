#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

int giris;

int mapArr[15][64] = {
{ 6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6 },
{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 }
};


void board()
{


	cout << char(179);

}

void ball()
{
    cout << char(248);
}

void gotoXY(int, int);

void labr();
void move_1();


int main()
{

	labr();

	move_1();


}
void labr()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			switch (mapArr[i][j])
			{
			case 0:
				cout << " ";
				break;

			case 1:
				cout << char(219);
				break;
            case 2:
				cout << char(219);
				break;
            case 3:
				cout << char(219);
				break;
            case 4:
				cout << char(219);
				break;
            case 6:
				cout << " ";
				break;

			}

		}
		cout << " " << endl;

	}
}

void gotoXY(int x, int y)
{

	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void move_1()
{
    int player_one=0;
    int player_two=0;

    int ballx=33;
    int bally=5;
    gotoXY(ballx,bally);
    ball();


    int dirx=1;
    int diry=1;

    int ballxCln=0;
    int ballyCln=0;

    int paddle_two_x = 60;
	int paddle_two_y = 6;
	int paddle_two_xCln = 3;
	int paddle_two_yCln = 8;

	int paddle_one_x = 3;
	int paddle_one_y = 6;
	int paddle_one_xCln = 3;
	int paddle_one_yCln = 8;


		gotoXY(paddle_one_x, paddle_one_y);
		board();
		gotoXY(paddle_one_x, paddle_one_y+1);
		board();
		gotoXY(paddle_two_x, paddle_two_y);
		board();
		gotoXY(paddle_two_x, paddle_two_y+1);
		board();

	while (true)
	{
        if(_kbhit()){
            giris = _getch();
        if (giris == 'w')
		{
			paddle_one_y -= 1;
		}
		else if (giris == 's')
		{
			paddle_one_y += 1;
		}
        else if (giris == 'o')
		{
			paddle_two_y -= 1;
		}
		else if (giris == 'l')
		{
			paddle_two_y += 1;
		}

        if (mapArr[paddle_one_y][paddle_one_x] == 1 )
		{
			paddle_one_x = paddle_one_xCln;
			paddle_one_y = paddle_one_yCln;
		}
		else if (mapArr[paddle_one_y+1][paddle_one_x] == 3)
		{
			paddle_one_x = paddle_one_xCln;
			paddle_one_y = paddle_one_yCln;
		}

		if (mapArr[paddle_two_y][paddle_two_x] == 1)
		{
			paddle_two_x = paddle_two_xCln;
			paddle_two_y = paddle_two_yCln;
		}
		else if (mapArr[paddle_two_y+1][paddle_two_x] == 3)
		{
			paddle_two_x = paddle_two_xCln;
			paddle_two_y = paddle_two_yCln;
		}


        gotoXY(paddle_two_xCln, paddle_two_yCln);
		cout << " ";
        gotoXY(paddle_two_xCln, paddle_two_yCln+1);
        cout << " ";
		gotoXY(paddle_two_x, paddle_two_y);
		board();
		gotoXY(paddle_two_x, paddle_two_y+1);
		board();
		paddle_two_xCln = paddle_two_x;
		paddle_two_yCln = paddle_two_y;

        gotoXY(paddle_one_xCln, paddle_one_yCln);
		cout << " ";
        gotoXY(paddle_one_xCln, paddle_one_yCln +1);
        cout << " ";
		gotoXY(paddle_one_x, paddle_one_y);
		board();
		gotoXY(paddle_one_x, paddle_one_y+1);
		board();

		paddle_one_xCln = paddle_one_x;
		paddle_one_yCln = paddle_one_y;



        }

        else{
        gotoXY(paddle_two_xCln, paddle_two_yCln);
		cout << " ";
        gotoXY(paddle_two_xCln, paddle_two_yCln+1);
        cout << " ";
		gotoXY(paddle_two_x, paddle_two_y);
		board();
		gotoXY(paddle_two_x, paddle_two_y+1);
		board();
		paddle_two_xCln = paddle_two_x;
		paddle_two_yCln = paddle_two_y;

        gotoXY(paddle_one_xCln, paddle_one_yCln);
		cout << " ";
        gotoXY(paddle_one_xCln, paddle_one_yCln +1);
        cout << " ";
		gotoXY(paddle_one_x, paddle_one_y);
		board();
		gotoXY(paddle_one_x, paddle_one_y+1);
		board();

		paddle_one_xCln = paddle_one_x;
		paddle_one_yCln = paddle_one_y;
		if (mapArr[paddle_one_y][paddle_one_x] == 1 )
		{
			paddle_one_x = paddle_one_xCln;
			paddle_one_y = paddle_one_yCln;
		}
		else if (mapArr[paddle_one_y+1][paddle_one_x] == 3)
		{
			paddle_one_x = paddle_one_xCln;
			paddle_one_y = paddle_one_yCln;
		}

		if (mapArr[paddle_two_y][paddle_two_x] == 1)
		{
			paddle_two_x = paddle_two_xCln;
			paddle_two_y = paddle_two_yCln;
		}
		else if (mapArr[paddle_two_y+1][paddle_two_x] == 3)
		{
			paddle_two_x = paddle_two_xCln;
			paddle_two_y = paddle_two_yCln;
		}

        }


        gotoXY(ballx,bally);
        cout << " ";


        if(mapArr[bally][ballx]==0) {


        ballx+=dirx;
        bally+=diry;

        }
        if (mapArr[bally+1][ballx+1]==3 ){

           diry*=-1;


        }

        if (mapArr[bally-1][ballx+1]==1){

            diry*=-1;

        }
        if (ballx==paddle_two_x && bally==paddle_two_y){

            dirx*=-1;


        }
        if (ballx==paddle_two_x && bally==paddle_two_y+1){

            dirx*=-1;


        }
        if (ballx==paddle_one_x && bally==paddle_one_y){

            dirx*=-1;


        }
        if (ballx==paddle_one_x && bally==paddle_one_y+1){

            dirx*=-1;


        }

        if(mapArr[bally][ballx]==4) {

         ballx=33;
         bally=5;
         player_two+=1;
         dirx*=-1;
         diry*=-1;
        }
        if(mapArr[bally][ballx]==2) {

        ballx=33;
        bally=5;
        player_one+=1;
        dirx*=-1;
        diry*=-1;
        }

        if(mapArr[bally][ballx]==0){
        gotoXY(ballx,bally);
        ball();
        }

        gotoXY(8,0);
        cout << "Player 1 :"<<player_one;
        gotoXY(40,0);
        cout << "Player 2 :"<<player_two;

        Sleep(115);


	}

}




