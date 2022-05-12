#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>

#define paddle_one_w   'w'
#define paddle_one_s   's'
#define paddle_two_o   'o'
#define paddle_two_L   'L'
#define paddle_one_W   'W'
#define paddle_one_S   'S'
#define paddle_two_O   'O'
#define paddle_two_l   'l'
using namespace std;
char const *pone,*ptwo;
int ballx=400;
int bally=250;
int dirx=1;
int diry=1;

char giris;
int paddle_one_x1=10;
int paddle_one_y1=200;
int paddle_one_x2=15;
int paddle_one_y2=300;

int paddle_two_x1=785;
int paddle_two_y1=200;
int paddle_two_x2=790;
int paddle_two_y2=300;

int player_one=0;
int player_two=0;

void drawRectangle(int left, int top, int right, int bottom, int color)
{
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    bar(left, top, right, bottom);
}

void drawFilledCircle(int centerx, int centery, int radius, int color)
{
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    fillellipse(centerx, centery, radius, radius);
}
void draw_ball(){
       drawFilledCircle(ballx,bally,9,BLACK);

        if(ballx<800 && bally<500 && ballx>0 && bally>0 ){



            bally+=diry;
            ballx-=dirx;
            drawFilledCircle(ballx,bally,9,YELLOW);


        }
          if(bally+9>=500){

                diry*=-1;
            }
          if(bally-9<=0){

                diry*=-1;
            }

        if( ballx-5==paddle_one_x2 && bally<=paddle_one_y2 && bally>=paddle_one_y1 ){

            dirx*=-1;
          }
        if(ballx>paddle_two_x1  && bally<=paddle_two_y2 && bally>=paddle_two_y1 ){
            dirx*=-1;
          }


          if(ballx>=800){
            player_two+=1;
            dirx*=-1;
            drawFilledCircle(ballx,bally,9,BLACK);
            ballx=400;
            bally=250;

            drawRectangle(paddle_one_x1,paddle_one_y1,paddle_one_x2,paddle_one_y2,BLACK);
            drawRectangle(paddle_two_x1,paddle_two_y1,paddle_two_y1,paddle_two_y2,BLACK);
            paddle_one_x1=10;
            paddle_one_y1=200;
            paddle_one_x2=15;
            paddle_one_y2=300;

            paddle_two_x1=785;
            paddle_two_y1=200;
            paddle_two_x2=790;
            paddle_two_y2=300;
            Sleep(500);

          }
           if(ballx<=0){
            player_one+=1;
            dirx*=-1;
            drawFilledCircle(ballx,bally,9,BLACK);
            ballx=400;
            bally=250;
            drawRectangle(paddle_one_x1,paddle_one_y1,paddle_one_x2,paddle_one_y2,BLACK);
            drawRectangle(paddle_two_x1,paddle_two_y1,paddle_two_x2,paddle_two_y2,BLACK);
            paddle_one_x1=10;
            paddle_one_y1=200;
            paddle_one_x2=15;
            paddle_one_y2=300;

            paddle_two_x1=785;
            paddle_two_y1=200;
            paddle_two_x2=790;
            paddle_two_y2=300;
            Sleep(500);
          }

}

void run()
{



    drawFilledCircle(ballx,bally,5,RED);


	while (true)
	{
    setcolor(CYAN);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);

    std::string playeronee = std::to_string(player_one);
    char const *one = playeronee.c_str();
    std::string player_twoo= std::to_string(player_two);
    char const *two = player_twoo.c_str();

    outtextxy(170,30,"Player 1-");
    outtextxy(300, 30, (char*)one);
    outtextxy(520,30,"Player 2-");
    outtextxy(650, 30, (char*)two);


    drawRectangle(paddle_one_x1,paddle_one_y1,paddle_one_x2,paddle_one_y2,BLUE);
    drawRectangle(paddle_two_x1,paddle_two_y1,paddle_two_x2,paddle_two_y2,RED);


	int keyPressed;
    if (kbhit()) {
        keyPressed = getch();
        if (keyPressed == paddle_one_w || keyPressed == paddle_one_W) {

        drawRectangle(paddle_one_x1,paddle_one_y1,paddle_one_x2,paddle_one_y2,BLACK);

        paddle_one_y1= paddle_one_y1!=0?paddle_one_y1-10:paddle_one_y1+0;
        paddle_one_y2= paddle_one_y1!=0?paddle_one_y2-10:paddle_one_y2+0;
        }
        if (keyPressed == paddle_one_s || keyPressed == paddle_one_S) {
        drawRectangle(paddle_one_x1,paddle_one_y1,paddle_one_x2,paddle_one_y2,BLACK);

        paddle_one_y1= paddle_one_y2!=500?paddle_one_y1+10:paddle_one_y1+0;
        paddle_one_y2= paddle_one_y2!=500?paddle_one_y2+10:paddle_one_y2+0;
        }
        if (keyPressed == paddle_two_o || keyPressed == paddle_two_O) {
        drawRectangle(paddle_two_x1,paddle_two_y1,paddle_two_x2,paddle_two_y2,BLACK);
        paddle_two_y1= paddle_two_y1!=0?paddle_two_y1-10:paddle_two_y1+0;
        paddle_two_y2= paddle_two_y1!=0?paddle_two_y2-10:paddle_two_y2+0;
        }
        if (keyPressed == paddle_two_L || keyPressed == paddle_two_l) {
        drawRectangle(paddle_two_x1,paddle_two_y1,paddle_two_x2,paddle_two_y2,BLACK);
        paddle_two_y1= paddle_two_y2!=500?paddle_two_y1+10:paddle_two_y1+0;
        paddle_two_y2= paddle_two_y2!=500?paddle_two_y2+10:paddle_two_y2+0;
        }

    }
        drawRectangle(paddle_one_x1,paddle_one_y1,paddle_one_x2,paddle_one_y2,BLUE);
        drawRectangle(paddle_two_x1,paddle_two_y1,paddle_two_x2,paddle_two_y2,RED);



        draw_ball();
        Sleep(6);




}
getch();
}


int main()
{
    initwindow(799,499);

    setbkcolor(BLACK);
    cleardevice();
    run();

    getch();


return 0;

}





