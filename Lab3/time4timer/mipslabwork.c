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

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  // init PORTE so bit 7:0 are outputs with TRISE
  int volatile *trise = 0xbf886100;
  *trise = *trise & ~0xff; // clears bits 7:0

  // init PORTD so 11:5 are inputs with TRISD
  TRISDSET = (0x7f << 5);// 111 1111 = 7f shifted 5 bits left

  // init timer2
  T2CON = 0x0;                  // disable timer2 and clear control registers
  T2CON = 0x7 << 4;             // set prescaler (TCKPS at bits 6:4) to 1:256
  PR2 = (80000000 / 256) / 10;  // 10 timeouts per second (clock frequency/prescaler/10times per second)
  TMR2 = 0x0;                   // clear timer register
  T2CONSET = 0x1 << 15;         // enable timer2


}

/* This function is called repetitively from the main program */
void labwork( void )
{
  if (getbtns()) {
    int btns = getbtns();
    int sw = getsw();

    if (btns & 0x1) {
      mytime = (mytime & ~0x000f0) | (sw << 4);
    }
    if (btns & 0x2) {
      mytime = (mytime & ~0x00f00) | (sw << 8);
    }
    if (btns & 0x4) {
      mytime = (mytime & ~0x0f000) | (sw << 12);
    }
  }

  int volatile *porte = (int volatile *) 0xbf886110;
  *porte += 1;

  if (IFS(0) & (0x1 << 8)) {
    IFSCLR(0) = (0x1 << 8);
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
  }

  display_image(96, icon);
}
