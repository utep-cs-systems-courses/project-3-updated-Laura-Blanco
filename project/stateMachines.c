#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "p2switches.h"
#include "lcdutils.h"
#include "lcddraw.h"

char beats;
char size;
static char sb = 1;
static int x = 500;
static char dim_state = 0;

void two_beats(char state){   /* will go green on then both on then red on then both on and repeat */
  char led = 0;
  // static char two_state = 0;
  switch(state){
  case 0:
    buzzer_set_period(0);
    beats = 1;
    break;
  case 1:
    buzzer_set_period(1000);
    beats = 2;
    break;
  case 2:
    buzzer_set_period(0);
    beats = 3;
    break;
  case 3:
    buzzer_set_period(1000);
    beats = 0;
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
  }
}

void drawShape(){
  static char color = 0;
  switch(color){
  case 0: clearScreen(COLOR_BLACK); color = 1;break;
  case 1: drawDiamond(fontColor1,fontColor2); color = 2; break;
  case 2:drawDiamond(fontColor1,fontColor2); color = 1; break;
  }
}

void draw4(){
  static char heart = 0;
  switch(heart){
    // case 1: clearScreen(COLOR_BLACK); heart = 2;break;
  case 0: drawHeart(0); heart = 1; break;
  case 1: drawHeart(1); heart = 2; break;
  case 2: clearScreen(COLOR_BLACK); heart = 0; break;
  }
}

void button_states(){
  switch(button_pressed){
  case 1:
    buzzer_set_period(0);
    drawString8x12(30,10,"Welcome",COLOR_PURPLE,COLOR_BLACK);
    houses();
    break;
  case 2:
    buzzer_advance();
    main_siren();
    drawShape();
    break;
  case 3:
    draw4();
    two_beats(beats);
    break;
  case 4:
    buzzer_set_period(0);
    drawString8x12(30,60,"Goodbye",COLOR_WHITE,COLOR_MAGENTA);
    break;
    
  }
}
    
