#include <msp430.h>
#include <libTimer.h>
#include "stateMachines.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "buzzer.h"
#include "p2switches.h"

char previous;
char beats;
short redrawScreen = 1;
char button_pressed;
//static char house_state;
unsigned int fontColor1 = COLOR_BLUE;
unsigned int fontColor2 = COLOR_RED;

void wdt_c_handler()
{
  static char count = 0;
  static signed char dim = 0;
  
  if(++count == 250){
    if(fontColor1 == COLOR_BLUE){ //changes font colors each time around
      fontColor1 = COLOR_RED;
      fontColor2 = COLOR_BLUE;
    }
    else{
      fontColor1 = COLOR_BLUE;
      fontColor2 = COLOR_RED;
    }
    redrawScreen = 1;     
    count = 0;
  }

  if(button_pressed == 4){ 
    if(count == 125){ //when it hits 125 we move on to the next dimming 
      drawString8x12(30,60,"goodbye",COLOR_WHITE,COLOR_MAGENTA);
      count = 0;
      dim++;
    }
    if(dim == 3){ //when we have reached the limit of possible switch cases we restart
      dim = 0;
    }
    dimmer(dim); //call dimming function
    redrawScreen = 1;
  }
}

void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  p2sw_init(15); //initialize buttons
  lcd_init();
  led_init();
  buzzer_init();

  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  clearScreen(COLOR_BLACK);
  while (1) {			/* forever */
   if (redrawScreen) {
     button_states(); //call statee machine for buttons
     redrawScreen = 0;
   }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  } 
}
