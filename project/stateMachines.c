#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "p2switches.h"
#include "lcdutils.h"
#include "lcddraw.h"

char beats;
static char sb = 1;
static int x = 500;
static char dim_state = 0;

char red_state(char red) /* changes red led based on parameter if parameter is not valid then it turns it off */
{
  red_on = red;
  green_on = 0;

  return 1;
  // led_changed = 1;
  // led_update();
}

void both_on() /* turns on both leds */
{
  green_on = 1;
  red_on = 1;
  led_changed = 1;
  led_update();
}

void two_beats(char state){   /* will go green on then both on then red on then both on and repeat */
  char led = 0;
  // static char two_state = 0;
  switch(state){
  case 0:
    led = red_state(0);
    buzzer_set_period(0);
    beats = 1;
    break;
  case 1:
    led = red_state(1);
    buzzer_set_period(1000);
    beats = 2;
    break;
  case 2:
    led = red_state(0);
    buzzer_set_period(0);
    beats = 3;
    break;
  case 3:
    led = red_state(1);
    buzzer_set_period(1000);
    beats = 0;
    break;
  
  }
  led_changed = led;
  led_update();
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
    sb = 1;
    state++;
    break;
  case 3:
  case 2:
    sb = 0;
    state = 0;
  default:
    break;
  }
}

void dimmer(char light) /* dims the lgihts at different intensities */
{
  char led = 0;
  switch(light){
  case 0: //red 25
    led = red_25();;
    break;
  case 1: //50 %
    led = red_50();
    break;
  case 2: //75 %
    led = red_75();
    break;
  }

  led_changed = led;
  led_update();
}

char red_25()  /* goes on off off off */
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
  }
  return 1;
}

char red_75() /* goes on on on off */
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

  return 1;
}

char red_50()		/* turns on and off leds */
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
 return 1;
}


void houses(){
  static char house_state = 0;
  switch(house_state){
  case 0:
    clearScreen(COLOR_BLACK);
    house_state = 1;
    break;
  case 1:
    drawHouse();
    house_state = 2;
    break;
  case 2:
    House2(0);
    house_state =3;
    break;
  case 3:
    House2(1);
    house_state = 0;
    break;
  default:
    house_state = 0;
  }
}

void drawShape(){
  static char color = 0;
  switch(color){
  case 0: clearScreen(COLOR_BLACK); color = 1;
  case 1: drawDiamond(COLOR_BLUE,COLOR_FIREBRICK); color = 2; break;
  case 2:drawDiamond(COLOR_FIREBRICK,COLOR_BLUE); color = 0; break;
  }
}
