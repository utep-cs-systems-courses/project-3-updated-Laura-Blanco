# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:main.elf

main.elf: ${COMMON_OBJECTS} main.o led.o buzzer.o stateMachines.o wdt_handler.o red_50.o houses.o dimmer.o switches.o p2_interrupt_handler.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

load: main.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
