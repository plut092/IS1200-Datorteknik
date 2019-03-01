#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
#include "snakeheader.h"

int main(int argc, char const *argv[]) {
  /*
  Initializing the snake linked list
  */
  snake_segment *head = init_snake_segment();


  add_snake_segment(&head, 0, 1);
  printf("Before remove_last_snake_segment\n");
  print_list(head);

  remove_last_snake_segment(head);

  printf("After remove_last_snake_segment\n");

  print_list(head);


  void OledHostInit()
  {
  unsigned int tcfg;
  /* Initialize SPI port 2.
  */
  SPI2CON = 0;
  SPI2BRG = 15; //8Mhz, with 80Mhz PB clock
  SPI2STATbits.SPIROV = 0;
  SPI2CONbits.CKP = 1;
  SPI2CONbits.MSTEN = 1;
  SPI2CONbits.ON = 1;
  /* Make pins RF4, RF5, and RF6 be outputs.
  */
  PORTSetBits(IOPORT_F, bitVddCtrl|bitVbatCtrl|bitDataCmd);
  PORTSetPinsDigitalOut(prtDataCmd, bitDataCmd); //Data/Command# select
  PORTSetPinsDigitalOut(prtVddCtrl, bitVddCtrl); //VDD power control
  (1=off)
  PORTSetPinsDigitalOut(prtVbatCtrl, bitVbatCtrl); //VBAT power control
  (1=off)
  /* Make the RG9 pin be an output. On the Basic I/O Shield, this pin
  ** is tied to reset.
  */
  PORTSetBits(prtReset, bitReset);
  PORTSetPinsDigitalOut(prtReset, bitReset);
  }




  return 0;
}


/*
snake_segment * head = NULL;
head = malloc(sizeof(snake_segment));
if (head == NULL) {
  return -1;
}

head->x = 2;
head->y = 1;
head->next = malloc(sizeof(snake_segment));
head->next->x = 2;
head->next->y = 2;
head->next->next = NULL;

add_snake_segment(&head, 1, 1);
add_snake_segment(&head, 0, 1);

printf("Before remove_last_snake_segment\n");
print_list(head);

remove_last_snake_segment(head);

printf("After remove_last_snake_segment\n");

print_list(head);

*/
