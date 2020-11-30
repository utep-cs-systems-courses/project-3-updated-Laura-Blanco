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
     if(++count == 125){
       houses(house_state);
       house_state++;
       if(house_state > 2){
	 clearScreen(COLOR_PURPLE);
	 house_state = 0;
       }
      // clearScreen(COLOR_BLACK);
      // buzzer_set_period(0);
       //two_beats();
       // drawHouse();
       // houses();
       // two_beats();
       count = 0;
     }
    break;
    case 2:
     if(++count == 125){
       // buzzer_set_period(0);
      // if(++count == 125){
	// dimmer();
       count = 0;
       // }
       }
    break;
    case 3:
      buzzer_advance();
     if((++count % 25) == 0){
      buzzer_advance();
      // if(count == 250){
	//	main_siren();
	//	count = 0;
	// }
      count = 0;
      }
    break;
    case 4:
      //  else if (button_pressed == 4){
      if(++count == 125){
	red_on = 1;
	led_changed = 1;
	led_update();
      }
	//two_beats();
     // red_on = 0;
     // green_on = 0;
     // led_changed = 1;
     // led_update();
      count = 0;
      
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
      //  drawString5x7(20,20, "hello", fontFgColor, COLOR_BLUE);
      // drawString8x12(20,20, "hello",COLOR_GREEN, COLOR_BLUE);
  
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  } 
}
