/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int timeoutcount = 0;

/* Interrupt Service Routine */
void user_isr( void ) {
  if (IFS(0) & (0x1 << 8)) {
    /*
      check  timeoutcount == 10 for IRS to
      run every 10 invocations of user_irs
    */
    IFSCLR(0) = 0x1 << 8; // set TMR2 IF to 0
    timeoutcount++;

    if (timeoutcount == 10) {
      timeoutcount = 0; // reset timeoutcount at 10 invocations of user_irs
    }
    if(IFS(0) & (0x1 << 15)) {
      IFSCLR(0) = 0x1 << 15; // set INT3 IF to 0
      PORTE = PORTE + 1;
    }
    // btn1 interrupt turn right
    if (PORTF & (0x1 << 1)) {
      PORTFCLR = (0x1 << 1);
      if (direction != LEFT) {
        direction = RIGHT;
      }
    }
    // btn2 interrupt turn left
    if (PORTD & (0x1 << 5)) {
      PORTDCLR = (0x1 << 5);
      if (direction != RIGHT) {
        direction = LEFT;
      }
    }
    // btn3 interrupt turn up
    if (PORTD & (0x1 << 6)) {
      PORTDCLR = (0x1 << 6);
      if (direction != DOWN) {
        direction = UP;
      }
    }
    // btn4 interrupt turn down
    if (PORTD & (0x1 << 7)) {
      PORTDCLR = (0x1 << 7);
      if (direction != UP) {
        direction = DOWN;
      }
    }
  }
}

/* Lab-specific initialization goes here */
void labinit( void ) {
  // init PORTE so bit 7:0 are outputs with TRISE
  int volatile *trise = (int volatile *) 0xbf886100;
  *trise = *trise & ~0xff; // clears bits 7:0

  // init PORTE to zero at startup
  PORTE = 0x0;

  //Button init
  // init PORTD so 11:5 are inputs with TRISD
  TRISDSET = (0x7f << 5);// 111 1111 = 7f shifted 5 bits left
  // init PORTF bit 1
  TRISFSET = (0x1 << 1); // button 1


  // init timer2
  T2CON = 0x0;                  // disable timer2 and clear control registers
  T2CON = 0x7 << 4;             // set prescaler (TCKPS at bits 6:4) to 1:256
  PR2 = (80000000 / 256) / 10;  // 10 timeouts per second (clock frequency/prescaler/10times per second)
  TMR2 = 0x0;                   // clear timer register
  T2CONSET = 0x1 << 15;         // enable timer2

  // init interrupt from Timer2
  IPCSET(2) = 0x3 << 2; // interrupt priority set to 3
  IECSET(0) = 0x1 << 8; // enable TMR2 interrupt

  // init interrupt from SW3
  IPCSET(3) = 0x2 << 26; // interrupt priority set to 2
  IECSET(0) = 0x1 << 15; // enable SW3 interrupt

  enable_interrupt();

  // Draws the game background walls, food and the snake's start position
  draw_init_game();
}

/* This function is called repetitively from the main program */
void labwork( void ) {
  run();
  display_update_screen();
  quicksleep(800000);
}
