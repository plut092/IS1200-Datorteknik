#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw( void ) {
  // get switches SW4 - SW1 from PORTD
  // returns bits 11:8 as 4 least significant bits (xxxx 0000 0000)
  return (PORTD & 0x0f00) >> 8;;
}

int getbtns(void) {
  // return the current status of BTN4 - BTN2
  // returns bits 7:5 as 3 least significant bits (xxx0 0000)
  return (PORTD & 0x0e0) >> 5;
}
