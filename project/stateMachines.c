#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "p2switches.h"
#include "lcdutils.h"
#include "lcddraw.h"

static char sb = 1;
static int x = 500;
static char dim_state = 0;

void go_down()               /* will set sb to move frequency down */
{
  sb = 0;
  turn_on_red();
}

void go_up()                // will set sb to move frequency up
{
  sb = 1;
  turn_on_green();
}

void turn_on_red()      /* turns red light on and green off */
{
  red_on = 1;
  green_on = 0;
  led_changed = 1;
  led_update();
}

void turn_on_green()     /*turns on green light and red off */
{
  green_on = 1;
  red_on = 0;
  led_changed = 1;
  led_update();
}

void both_on() /* turns on both leds */
{
  green_on = 1;
  red_on = 1;
  led_changed = 1;
  led_update();
}

void two_beats(){   /* will go green on then both on then red on then both on and repeat */
  static char two_state = 0;
  switch(two_state){
  case 0:
    turn_on_red();
    buzzer_set_period(0);
    two_state = 1;
    break;
  case 1:
    red_on = 0;
    led_changed = 1;
    led_update();
    buzzer_set_period(1000);
    two_state = 2;
    break;
  case 2:
    turn_on_red();
    buzzer_set_period(0);
    two_state = 3;
    break;
  case 3:
    red_on = 0;
    led_changed = 1;
    led_update();
    buzzer_set_period(1000);
    two_state = 0;
    break;
  }
}
void buzzer_advance()
{
  if(sb){
    x += 225;  
  }
  else{
    x -= 450;
  }
  buzzer_set_period(2000000/x); //set buzzer frequency
}

void main_siren() //state machine for siren
{
  static char state = 0;
  switch(state){
  case 0:
  case 1: //for two states it will do the same thing (go up)
    go_up();
    state++;
    break;
  case 2:
    go_down();
    state = 0;
  default:
    break;
  }
}

void dimmer() /* dims the lgihts at different intensities */
{
  static char dim_select = 0;
  switch(dim_select){
  case 0: //red 25
    red_25();
    dim_select = 1;
    break;
  case 1: //50 %
    red_50();
    dim_select = 2;
    break;
  case 2: //75 %
    red_75();
    dim_select = 3;
    break;
  case 3:
    red_on = 1;
    led_update();
    dim_select = 0;
    break;
  }
}

void red_25()  /* goes on off off off */
{
  switch(dim_state){
  case 0:
    red_on = 1;
    dim_state = 1;
    break;
  case 1:
    red_on = 0;
    dim_state = 2;
    break;
  case 2:
    red_on = 0;
    dim_state = 3;
    break;
  case 3:
    red_on = 0;
    dim_state = 0;
    break;
    // default: buzzer_set_period(1000);
  }
  led_changed = 1;
  led_update();
}

void red_75() /* goes on on on off */
{
  switch(dim_state){
  case 0:
    red_on = 1;
    dim_state = 1;
    break;
  case 1:
    red_on = 1;
    dim_state = 2;
    break;
  case 2:
    red_on = 1;
    dim_state = 3;
  case 3:
    red_on = 0;
    dim_state = 0;
    break;
  }
  led_changed = 1;
  led_update();
}

void red_50()		/* turns on and off leds */
{
 switch (dim_state) {
 case 0:
   red_on = 1;
   dim_state = 1;
   break;
 case 1:
  red_on = 0;
  dim_state = 0;
  break;
 }
 led_changed = 1;
 led_update();			/* always changes an led */
}


void houses(char house_state){
  // drawPixel(0,0,COLOR_RED);
  switch(house_state){
  case 0:
    drawHouse();
    house_state = 1;
    break;
  case 1:
    House2(0);
    house_state =2;
    break;
  case 2:
    House2(1);
    house_state = 0;
    break;
  default:
    house_state = 0;
  }
}
