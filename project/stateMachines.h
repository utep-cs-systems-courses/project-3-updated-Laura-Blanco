#ifndef stateMachine_included
#define stateMachine_included

extern unsigned int fontColor1;
extern unsigned int fontColor2;
extern unsigned char dim_state;
extern unsigned char house_state;

void two_beats();
void buzzer_advance();
void main_siren();
void dimmer(signed char light);
char red_25();
char red_75();
char red_50();
void houses();
void diamonds();
void hearts();
void button_states();

#endif // included
