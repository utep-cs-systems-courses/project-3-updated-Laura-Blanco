#include <msp430.h>
#include <libTimer.h>
#include "stateMachines.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "buzzer.h"
#include "p2switches.h"

char beats;
short redrawScreen = 1;
char button_pressed;
static char house_state;
u_int fontColor1 = COLOR_BLUE;
u_int fontColor2 = COLOR_RED;

void wdt_c_handler()
{
  static char count = 0;

  if(++count == 250){

    if(fontColor1 == COLOR_BLUE){
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
  

/*  
  if(button_pressed == 3){
    buzzer_set_period(0);
    static char dim = 0;
    if(count == 200){
      count = 0;
      dim++;
    }
    if(dim == 3){
      dim = 0;
      }
    dimmer(dim);
    // redrawScreen = 1;
  }
*/  
  /*
  switvh(button_pressed){
    case 1:
      // buzzer_set_period(0);
     if(++count == 250){
       // drawString8x12(30,10,"Welcome",COLOR_PURPLE,COLOR_BLACK);
       // houses();
       count = 0;
       // redrawScreen = 1;
     }
    break;
    case 3:
      if((++count % 25) == 0){
       	drawShape();
	buzzer_advance();
      } 
      if(++count == 250){
	main_siren();
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
     else if(dim == 3){
       dim = 0;
     }
     
     drawString8x12(30,30,"Goodbye", COLOR_TURQUOISE,COLOR_WHITE);
     dimmer(dim);
     redrawScreen =1; 
    break;
    case 4:
       if(++count == 62){
	 //	 draw4();
	 two_beats(beats);
	 // redrawScreen = 1;
       }
       if(count == 125){
	 draw4();
	 redrawScreen = 1;
	 count = 0;
       }
       break; 
  }*/
  //  redrawScreen = 1;
  
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
   /* switch(button_pressed){
    case 1:
       buzzer_set_period(0);
      // if(++count == 250){
       drawString8x12(30,10,"Welcome",COLOR_PURPLE,COLOR_BLACK);
       houses();
       // count = 0;
       // redrawScreen = 1;
       //  }
    break;
    case 2:
      // if((++count % 25) == 0){
      //	drawShape();
      //	buzzer_advance();
	// } 
	// if(++count == 250){
      //	main_siren();
	//	redrawScreen = 1;
	//	count = 0;
	// }
    break;
    case 3:
     buzzer_set_period(0);
     /* static char dim = 0;
     if(++count == 50){
       count = 0;
       dim++;
     }
     else if(dim == 3){
       dim = 0;
     } 
     
     drawString8x12(30,30,"Goodbye", COLOR_TURQUOISE,COLOR_WHITE);
     // dimmer(dim);
     // redrawScreen =1; 
    break;
    case 4:

      two_beats(beats);
      draw4();
      
       if(++count == 62){
	 //	 draw4();
	 two_beats(beats);
	 // redrawScreen = 1;
       }
       if(count == 125){
	 draw4();
	 redrawScreen = 1;
	 count = 0;
       } 
       break; */
 

   //    redrawScreen = 0;
  
   // clearScreen(COLOR_BLACK);
      //  drawString5x7(20,20, "hello", fontFgColor, COLOR_BLUE);
      // drawString8x12(20,20, "hello",COLOR_GREEN, COLOR_BLUE);
  
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  } 
}
