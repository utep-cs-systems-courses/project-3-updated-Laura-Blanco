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

  clearScreen(COLOR_BLUE);

  int r = 0;
  int c = 0;
  int center = 60;
  int row = 25;
   for(r = 0; r < 40; r++){
     for(c = 0; c <= r; c++){
       drawPixel(center + c, r+ row, COLOR_WHITE);
       drawPixel(center -c ,r + row, COLOR_WHITE);
     }
   }

   for(r = 0; r < 58; r++){
     for(c = 0; c < 58; c++){
       drawPixel(c+ 31 ,r+ 65,COLOR_GOLD);
     }
   }
   /*
   
   for(r = 0; r < 16; r++){
     for(c = 0; c < 16 ; c++){
       drawPixel(c+51, r + 107, COLOR_FOREST_GREEN);
     }
   }

   for(r = 0; r < 4 ; r++){
     for(c = 0; c < 4; c++){
       drawPixel(c+52, r + 113, COLOR_PINK);
     }
     } */

   //draws outline of door
   fillRectangle(65,107,4,16,COLOR_FOREST_GREEN);

   //draws black box
   for(r = 0; r < 16; r++){
     for(c = 0; c < 15; c++){
       drawPixel(c+51, r+ 107, COLOR_BLACK);
     }
   }

   //draws outline of stick figure
   fillRectangle(58,113,2,8,COLOR_RED);

   // draw hands
   for(r = 0; r < 3; r++){
     drawPixel(r + 56, r + 115, COLOR_RED);
     drawPixel(r + 59, r + 115, COLOR_RED);
   }

   //draw feets
   for(r = 0; r < 2; r++){
     drawPixel(r + 60, r+ 120, COLOR_RED);
     drawPixel(r + 56, 2-(r+137), COLOR_RED);
     // drawPixel( r+ 60,r+ 120, COLOR_RED);
   }

   /* for(r = 0; r < 2; r++){
     drawPixel(r+ 56, 120, COLOR_RED);
   } */

   /* for(r = 0; r < 2; r++){
     drawPixel(r+ 56,2-( r + 137), COLOR_RED);
   } */

   /*
   int offc = 29;
   int offr = 22;
   for(r = 0; r < 11; r++){
     for(c = 0; c < 11; c++){
       drawPixel(r+(offr-5), c+(offc - 5), COLOR_WHITE);
     }
     }*/
  //drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);
   // drawString8x12(20,20,"hello",COLOR_GREEN,COLOR_BLUE);

  // fillRectangle(30,30, 60, 60, COLOR_ORANGE);
  
}
