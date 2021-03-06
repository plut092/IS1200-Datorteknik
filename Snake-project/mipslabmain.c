/*
	This project was written 2019 by Johan Engström and last edited 2019-03-03.
	It is based on the labfiles of lab 3 written by Axel Isaksson and F Lundevall.

	Parts written by Johan Engström is:
	void random_seed_generator()
	int random()
	void snake_remove_tail()
	void snake_move()
	void put_food()
	void draw_init_game()
	void snake_eat()
	void run()
	startscreen()
	void game_over_screen()
	void clear_screen()
	void display_update_screen()
	void user_isr()
	void labwork()
	Data and variables for snake-project in mipslabdata.c

	The main function part after hardware setup and initialization was
	written by Engström.

	The function void display_update_string(void) had it's name changed from
	diplsay_update().
*/


/* mipslabmain.c

   This file written 2015 by Axel Isaksson,
   modified 2015, 2017 by F Lundevall

   Latest update 2017-04-21 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int main(void) {
  /*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */

	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;

	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;

	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);

	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
        SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;

	display_init();
	startscreen();

	labinit(); /* Do any lab-specific initialization */

	while (in_startscreen) {
		// wait for buttonpress in user_isr
		quicksleep(1);
	}

	/* Get a random seed for FOOD spawnposition */
	// random_seed_generator();
	srand((unsigned) TMR2);

	while( 1 )
	{
		draw_init_game();
		while (in_game) {
	  	labwork(); /* Do lab-specific things again and again */
		}
		clear_screen();
		quicksleep(200000);
		game_over_screen();
		quicksleep(20000000);

		game_over = 1;
		while(game_over) {
			//wait for buttonpress in user_isr
			quicksleep(1);
		}
	}

	return 0;
}
