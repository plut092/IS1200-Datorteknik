/* mipslab.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

/* Declare display-related functions from mipslabfunc.c */
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update_screen(void);
void display_update_string(void);
uint8_t spi_send_recv(uint8_t data);

/* Declare lab-related functions from mipslabfunc.c */
char * itoaconv( int num );
void labwork(void);
int nextprime( int inval );
void quicksleep(int cyc);
void tick( unsigned int * timep );

/* Declare display_debug - a function to help debugging.

   After calling display_debug,
   the two middle lines of the display show
   an address and its current contents.

   There's one parameter: the address to read and display.

   Note: When you use this function, you should comment out any
   repeated calls to display_image; display_image overwrites
   about half of the digits shown by display_debug.
*/
void display_debug( volatile int * const addr );

//Declare screen pixels
extern uint8_t pixel[32][128];
//Declare snakearray for positions
extern uint8_t snakearray[32][128];

//Variables
extern uint8_t direction;
extern const uint8_t maxwidth;
extern const uint8_t maxheight;
extern uint8_t row;
extern uint8_t col;
extern int random_seed;
extern int in_startscreen;
extern int in_game;
extern int game_over;
extern int score;


//Snake orientation
#define UP          0
#define RIGHT       1
#define DOWN        2
#define LEFT        3
#define DIR_NULL    4 // directon null
#define WALL        5
#define FOOD        6
//Defines
#define BUTTON_DEBOUNCE 1000

//Snake functions
void random_seed_generator();
int random(int min, int max);
void snake_remove_tail();
void snake_move();
void put_food();
void draw_init_game();
void snake_eat();
void run();
void startscreen();
void game_over_screen();
void clear_screen();


/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];
/* Declare text buffer for display output */
extern char textbuffer[4][16];

/* Declare functions written by students.
   Note: Since we declare these functions here,
   students must define their functions with the exact types
   specified in the laboratory instructions. */
/* Written as part of asm lab: delay, time2string */
void delay(int);
void time2string( char *, int );
/* Written as part of i/o lab: getbtns, getsw, enable_interrupt */
int getbtns(void);
int getsw(void);
void enable_interrupt(void);
