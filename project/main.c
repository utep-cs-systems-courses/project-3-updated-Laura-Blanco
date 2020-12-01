#include <msp430.h>
#include <libTimer.h>
#include "stateMachines.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "buzzer.h"
#include "p2switches.h"

char beats;
char size = 0;
short redrawScreen = 1;
char button_pressed;
static char house_state;
unsigned int fontColor1 = COLOR_BLUE;
unsigned int fontColor2 = COLOR_RED;

void wdt_c_handler()
{
  static char count = 0;
  static char dim = 0;
  
  if(++count == 250){
    if(fontColor1 == COLOR_BLUE){
      fontColor1 = COLOR_RED;
      fontColor2 = COLOR_BLUE;
    }
    else{
      fontColor1 = COLOR_BLUE;
      fontColor2 = COLOR_RED;
    }

    if(size){
      size = 0;
    }
    else{
      size = 1;
    }
    redrawScreen = 1;     
    count = 0;
  }

  if(button_pressed == 4){
    if(count == 125){
      count = 0;
      dim++;
    }
    if(dim == 3){
      dim = 0;
    }
    dimmer(dim);
    redrawScreen = 1;
  }
}

void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  p2sw_init(15);
  lcd_init();
  led_init();
  buzzer_init();

  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  clearScreen(COLOR_BLACK);
  int count = 0;
  while (1) {			/* forever */
   if (redrawScreen) {
     button_states();
     redrawScreen = 0;
   }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  } 
}
