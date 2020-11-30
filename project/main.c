#include <msp430.h>
#include <libTimer.h>
#include "stateMachines.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "buzzer.h"
#include "p2switches.h"

#define LED_GREEN BIT6

short redrawScreen = 1;
char button_pressed;
static char house_state;

void wdt_c_handler()
{
  static char count = 0;
  switch(button_pressed){
    case 1:
      buzzer_set_period(0);
     if(++count == 250){
       drawString8x12(30,10,"Welcome",COLOR_PURPLE,COLOR_BLACK);
       houses(house_state);
       house_state++;
       if(house_state > 2){
	 house_state = 0;
       }
       count = 0;
     }
    break;
    case 3:
      if((++count % 25) == 0){
	buzzer_advance();
      } 
      if(++count == 250){
	main_siren();
	drawShape();
	redrawScreen = 1;
	count = 0;
      }
    break;
    case 2:
     buzzer_set_period(0);
     static char dim = 0;
     if(++count == 200){
       count = 0;
       dim++;
     }
     else if(dim == 10){
       dim = 0;
     }
     dimmer(dim);
    break;
    case 4:
       if(++count == 62){
	two_beats();
	count = 0;
	redrawScreen = 1;
      }
     break;
  }
  redrawScreen = 1;
  
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

  //  button_pressed = 0;
  clearScreen(COLOR_BLACK);
  while (1) {			/* forever */
   if (redrawScreen) {
    redrawScreen = 0;
   }
   // clearScreen(COLOR_BLACK);
      //  drawString5x7(20,20, "hello", fontFgColor, COLOR_BLUE);
      // drawString8x12(20,20, "hello",COLOR_GREEN, COLOR_BLUE);
  
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  } 
}
