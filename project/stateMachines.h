#ifndef stateMachine_included
#define stateMachine_included

extern unsigned int fontColor1;
extern unsigned int fontColor2;
//extern static char size;

void two_beats(char beats);
void buzzer_advance();
void main_siren();
void dimmer(char light);
char red_state(char red);
void turn_on_green();
void both_on();
char red_25();
char red_75();
char red_50();
void houses();
void drawShape();
void draw4();
void button_states();

#endif // included
