/*
* Copyright (C) 2014  Arjun Sreedharan
* License: GPL version 2 or higher http://www.gnu.org/licenses/gpl.html
*/
#include "keyboard_map.h"


/* there are 25 lines each of 80 columns; each element takes 2 bytes */
#define LINES 25
#define COLUMNS_IN_LINE 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08

#define ENTER_KEY_CODE 0x1C

extern unsigned char keyboard_map[128];
extern void keyboard_handler(void);
extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *idt_ptr);

/* current cursor location */
unsigned int current_loc = 0;
/* video memory begins at address 0xb8000 */
char *vidptr = (char*)0xb8000;

/**********  MY DEFINITIONS ***********/
unsigned int r1_xpos = 2;
unsigned int r1_ypos = 9;
unsigned int r2_xpos = 77;
unsigned int r2_ypos = 9;
unsigned int r1_move = 1;
unsigned int ballx = 40;
unsigned int bally = 7;
unsigned int dirx= -1;
unsigned int diry =-1;
unsigned int player_one = 0;
unsigned int player_two = 0;
unsigned int mapArr[21][80] = {
{ 6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6 },
{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2 },
{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 }
};

void gotoxy(unsigned int x, unsigned int y);
void draw_strxy(const char *str,unsigned int x, unsigned int y);
void draw_rkt(void);
void clear_rkt(void);
void move_rkt_right(void);

struct IDT_entry {
	unsigned short int offset_lowerbits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_higherbits;
};

struct IDT_entry IDT[IDT_SIZE];


void idt_init(void)
{
	unsigned long keyboard_address;
	unsigned long idt_address;
	unsigned long idt_ptr[2];

	/* populate IDT entry of keyboard's interrupt */
	keyboard_address = (unsigned long)keyboard_handler;
	IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
	IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = INTERRUPT_GATE;
	IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;

	/*     Ports
	*	 PIC1	PIC2
	*Command 0x20	0xA0
	*Data	 0x21	0xA1
	*/

	/* ICW1 - begin initialization */
	write_port(0x20 , 0x11);
	write_port(0xA0 , 0x11);

	/* ICW2 - remap offset address of IDT */
	/*
	* In x86 protected mode, we have to remap the PICs beyond 0x20 because
	* Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
	*/
	write_port(0x21 , 0x20);
	write_port(0xA1 , 0x28);

	/* ICW3 - setup cascading */
	write_port(0x21 , 0x00);
	write_port(0xA1 , 0x00);

	/* ICW4 - environment info */
	write_port(0x21 , 0x01);
	write_port(0xA1 , 0x01);
	/* Initialization finished */

	/* mask interrupts */
	write_port(0x21 , 0xff);
	write_port(0xA1 , 0xff);

	/* fill the IDT descriptor */
	idt_address = (unsigned long)IDT ;
	idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16 ;

	load_idt(idt_ptr);
}

void kb_init(void)
{
	/* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
	write_port(0x21 , 0xFD);
}

void kprint(const char *str)
{
	unsigned int i = 0;
	while (str[i] != '\0') {
		vidptr[current_loc++] = str[i++];
		vidptr[current_loc++] = 0x07;
	}
}

void kprint_newline(void)
{
	unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
	current_loc = current_loc + (line_size - current_loc % (line_size));
}

void clear_screen(void)
{
	unsigned int i = 0;
	while (i < SCREENSIZE) {
		vidptr[i++] = ' ';
		vidptr[i++] = 0x07;
	}
}

void gotoxy(unsigned int x, unsigned int y)
{
	unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
	current_loc = BYTES_FOR_EACH_ELEMENT * (y * COLUMNS_IN_LINE + x);
}

void draw_strxy(const char *str,unsigned int x, unsigned int y)
{
	gotoxy(x,y);
	kprint(str);
}
void draw_walls(){


for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			switch (mapArr[i][j])
			{
	    case 0:
				kprint(" ");
				break;

	    case 1:
				kprint("-");
				break;
            case 2:
				kprint("|");
				break;
            case 3:
				kprint("-");
				break;
            case 4:
				kprint("|");
				break;
            case 6:
				kprint(" ");
				break;

			}

		}
		

	}

}



void draw_ball(){
	const char *rkt_b = "O";
	if(mapArr[bally][ballx]==0){
	draw_strxy(rkt_b,ballx,bally);
}
}
void draw_rkt(void)
{
	const char *rkt_s = "l";
	draw_strxy(rkt_s,r2_xpos,r2_ypos);
	draw_strxy(rkt_s,r2_xpos,r2_ypos+1);
	draw_strxy(rkt_s,r2_xpos,r2_ypos+2);
	draw_strxy(rkt_s,r2_xpos,r2_ypos+3);
	
	draw_strxy(rkt_s,r1_xpos,r1_ypos);
	draw_strxy(rkt_s,r1_xpos,r1_ypos+1);
	draw_strxy(rkt_s,r1_xpos,r1_ypos+2);
	draw_strxy(rkt_s,r1_xpos,r1_ypos+3);
	
}

void clear_rkt1(void)
{
	const char *rkt_s = "  ";

	draw_strxy(rkt_s,r1_xpos,r1_ypos);
	draw_strxy(rkt_s,r1_xpos,r1_ypos+1);
	draw_strxy(rkt_s,r1_xpos,r1_ypos+2);
	draw_strxy(rkt_s,r1_xpos,r1_ypos+3);
}
void clear_rkt2(void)
{
	const char *rkt_s = "  ";

	draw_strxy(rkt_s,r2_xpos,r2_ypos);
	draw_strxy(rkt_s,r2_xpos,r2_ypos+1);
	draw_strxy(rkt_s,r2_xpos,r2_ypos+2);
	draw_strxy(rkt_s,r2_xpos,r2_ypos+3);
}

void move_rkt1_up(void)
{
	clear_rkt1();
	r1_ypos = r1_ypos - r1_move;
	draw_rkt();
}
void move_rkt1_down(void)
{
	clear_rkt1();
	r1_ypos = r1_ypos + r1_move;
	draw_rkt();
}
void move_rkt2_up(void)
{
	clear_rkt2();
	r2_ypos = r2_ypos - r1_move;
	draw_rkt();
}
void move_rkt2_down(void)
{
	clear_rkt2();
	r2_ypos = r2_ypos + r1_move;
	draw_rkt();
}
void keyboard_handler_main(void)
{
	unsigned char status;
	char keycode;

	/* write EOI */
	write_port(0x20, 0x20);

	status = read_port(KEYBOARD_STATUS_PORT);
	/* Lowest bit of status will be set if buffer is not empty */
	if (status & 0x01) {
		keycode = read_port(KEYBOARD_DATA_PORT);
		if(keycode < 0)
			return;

		if(keycode == ENTER_KEY_CODE) {
			return;
		}
	}

	keycode = keyboard_map[(unsigned char) keycode];
 	if(keycode == 'w' && mapArr[r1_ypos-1][r1_xpos] ==0 ){
 	move_rkt1_up();
 	} 
	if(keycode == 'W' && mapArr[r1_ypos-1][r1_xpos] ==0){
 	move_rkt1_up();
 	} 
 	if(keycode == 'S' && mapArr[r1_ypos+4][r1_xpos] ==0){
 	move_rkt1_down();
 	} 
 	if(keycode == 's' && mapArr[r1_ypos+4][r1_xpos] ==0){
 	move_rkt1_down();
 	} 
 	if(keycode == 'o' && mapArr[r2_ypos-1][r2_xpos] ==0 ){
 	move_rkt2_up();
 	} 
	if(keycode == 'O' && mapArr[r2_ypos-1][r2_xpos] ==0){
 	move_rkt2_up();
 	} 
 	if(keycode == 'L' && mapArr[r2_ypos+4][r2_xpos] ==0){
 	move_rkt2_down();
 	} 
 	if(keycode == 'l' && mapArr[r2_ypos+4][r2_xpos] ==0){
 	move_rkt2_down();
 	} 
}
void score(){
	
	if(player_one==0) {
	
	const char *rkt_ğ = "Player one - 0";
	draw_strxy(rkt_ğ,8,0);
	
	}
	else if(player_one==1) {
	
	const char *rkt_ğ = "Player one - 1";
	draw_strxy(rkt_ğ,8,0);
	
	}
	else if(player_one==2) {
	
	const char *rkt_ğ = "Player one - 2";
	draw_strxy(rkt_ğ,8,0);
	
	}
	else if(player_one==3) {
	
	const char *rkt_ğ = "Player one - 3";
	draw_strxy(rkt_ğ,8,0);
	
	}
	else if(player_one==4) {
	
	const char *rkt_ğ = "Player one - 4";
	draw_strxy(rkt_ğ,8,0);
	
	}
	else if(player_one==5) {
	
	const char *rkt_ğ = "Player one - 5";
	draw_strxy(rkt_ğ,8,0);
	
	}
	
	if(player_two==0) {
	
	const char *rkt_ğ = "Player two - 0";
	draw_strxy(rkt_ğ,55,0);
	
	}
	else if(player_two==1) {
	
	const char *rkt_ğ = "Player two - 1";
	draw_strxy(rkt_ğ,55,0);
	
	}
	else if(player_two==2) {
	
	const char *rkt_ğ = "Player two - 2";
	draw_strxy(rkt_ğ,55,0);
	
	}
	else if(player_two==3) {
	
	const char *rkt_ğ = "Player two - 3";
	draw_strxy(rkt_ğ,55,0);
	
	}
	else if(player_two==4) {
	
	const char *rkt_ğ = "Player two - 4";
	draw_strxy(rkt_ğ,55,0);
	
	}
	else if(player_two==5) {
	
	const char *rkt_ğ = "Player two - 5";
	draw_strxy(rkt_ğ,55,0);
	
	}
	
 	
 	
}
void sleep(int x){
 
 for(int i =0; i< x; i++){
 
 	for (int j =0; j< x; j++)  {
 	
 		
 	}  
 }

}
void move_ball(){
	
 	ballx+=dirx;
 	bally+=diry;
    	draw_ball();
    	sleep(5000);
}
void delete_ball(){
	const char *rkt_b = " ";
	draw_strxy(rkt_b,ballx,bally);
}

void run(){

   draw_ball();
   draw_rkt();
   
   while (1)
	{
	delete_ball();
	move_ball();
	
	if (mapArr[bally+1][ballx+1]==3 ){

           diry*=-1;


        }

        if (mapArr[bally-1][ballx+1]==1){

            diry*=-1;

        }
        if (ballx-1==r1_xpos && bally-1==r1_ypos){

            dirx*=-1;


        }
        if (ballx-1==r1_xpos && bally-1==r1_ypos+1){

            dirx*=-1;


        }
        if (ballx-1==r1_xpos && bally-1==r1_ypos+2){

            dirx*=-1;


        }
        if (ballx-1==r1_xpos && bally-1==r1_ypos+3){

            dirx*=-1;


        }
        if (ballx+1==r2_xpos && bally+1==r2_ypos){

            dirx*=-1;


        }
        if (ballx+1==r2_xpos && bally+1==r2_ypos+1){

            dirx*=-1;


        }
        if (ballx+1==r2_xpos && bally+1==r2_ypos+2){

            dirx*=-1;


        }
        if (ballx+1==r2_xpos && bally+1==r2_ypos+3){

            dirx*=-1;


        }
        if(mapArr[bally][ballx]==4) {

         ballx=40;
         bally=7;
         player_two+=1;
         dirx*=-1;
         diry*=-1;
        r2_ypos=9;
        r1_xpos=2;
        r2_xpos=77;
        r1_ypos=9;
        }
        if(mapArr[bally][ballx]==2) {

        ballx=40;
        bally=7;
        player_one+=1;
        dirx*=-1;
        diry*=-1;
        r2_ypos=9;
        r1_xpos=2;
        r2_xpos=77;
        r1_ypos=9;
        }
        
	
	if(player_two==5){
	
	break;
	
	
	} 
	else if(player_one==5 ){
	
	break;
	
	} 
	score();
	}
	
	
	
	
	
	
}

void kmain(void)
{
	clear_screen();

	idt_init();
	kb_init();

	draw_walls();
	draw_rkt();
	
	move_ball();
	
	run();
	
	clear_screen();
	if(player_one==5){
	const char *rkt_x = "Player one win";
	draw_strxy(rkt_x,32,10);
	}
	else {
	const char *rkt_x = "Player two win";
	draw_strxy(rkt_x,32,10); 
	}
	
	
}
