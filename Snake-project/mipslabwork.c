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


/* Interrupt Service Routine */
void user_isr( void ) {
  if (IFS(0) & (0x1 << 8)) {
    /*
      check  timeoutcount == 10 for IRS to
      run every 10 invocations of user_irs
    */
    IFSCLR(0) = 0x1 << 8; // set TMR2 IF to 0

    if(IFS(0) & (0x1 << 15)) {
      IFSCLR(0) = 0x1 << 15; // set INT3 IF to 0
      PORTE = PORTE + 1;
    }
    // btn1 turn right and continue from startscreen and game_over_screen
    if (PORTF & (0x1 << 1)) {
      PORTFCLR = (0x1 << 1);
      if (direction != LEFT) {
        direction = RIGHT;
      }
      if (game_over) {
        game_over = 0;
      }
      if (in_startscreen) {
        in_startscreen = 0;
      }
    }
    // btn2 turn left and continue from startscreen and game_over_screen
    if (PORTD & (0x1 << 5)) {
      PORTDCLR = (0x1 << 5);
      if (direction != RIGHT) {
        direction = LEFT;
      }
      if (game_over) {
        game_over = 0;
      }
      if (in_startscreen) {
        in_startscreen = 0;
      }
    }
    // btn3 turn up and continue from startscreen and game_over_screen
    if (PORTD & (0x1 << 6)) {
      PORTDCLR = (0x1 << 6);
      if (direction != DOWN) {
        direction = UP;
      }
      if (game_over) {
        game_over = 0;
      }
      if (in_startscreen) {
        in_startscreen = 0;
      }
    }
    // btn4 turn down and continue from startscreen and game_over_screen
    if (PORTD & (0x1 << 7)) {
      PORTDCLR = (0x1 << 7);
      if (direction != UP) {
        direction = DOWN;
      }
      if (game_over) {
        game_over = 0;
      }
      if (in_startscreen) {
        in_startscreen = 0;
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
}

/* This function is called repetitively from the main program */
void labwork( void ) {
  display_update_screen();
  run();
  quicksleep(800000);
}
