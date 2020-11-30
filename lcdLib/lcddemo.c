/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLACK);
  drawDiamonds();
  // drawHouse();
  //  House2(0);
  //  House2(1);
 
  //drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);
  //  drawString8x12(20,20,"hello",COLOR_GREEN,COLOR_BLUE);

  // fillRectangle(30,30, 60, 60, COLOR_ORANGE);
 
}
