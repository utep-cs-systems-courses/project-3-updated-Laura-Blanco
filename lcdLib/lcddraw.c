/** \file lcddraw.c
 *  \brief Adapted from RobG's EduKit
 */
#include "lcdutils.h"
#include "lcddraw.h"


void drawDiamond(){
  int r = 0;
  int c = 0;
  int center = 50;
  int row = 30;
  
  for(r = 0; r < 31; r++){
    for(c = 0; c <= r; c++){
      drawPixel(center + c, r+ row, COLOR_FIREBRICK);
      drawPixel(center -c, r+ row, COLOR_FIREBRICK);
    }
  }

  
  for(c = 0; c < 31; c++){
    for(r = 0; r <= 30 - c ; r++){
      drawPixel(center + c,( r+ center) + 10, COLOR_SEA_GREEN);
      drawPixel(center - c, (r+ center) + 10 ,COLOR_SEA_GREEN);
    }
  }
  
}


void drawHouse(){
 
  int r = 0;
  int c = 0;
  int center = 60;
  int row = 25;
   for(r = 0; r < 58; r++){
     for(c = 0; c < 58; c++){
       //roof
       drawPixel(c+ 31 ,r+ 65,COLOR_GOLD);
       //house square
       if(r < 40){
	 if(c <= r){
	   drawPixel(center + c, r + row, COLOR_WHITE);
	   drawPixel(center -c, r + row, COLOR_WHITE);
	 }
       }
     }
   }
   for(r = 0; r < 16; r++){
     for(c = 0; c < 16; c++){
       //door
       drawPixel(c + 51, r + 107, COLOR_FOREST_GREEN);
     }
   }

   for(r = 0; r < 4; r++){
     for(c = 0; c < 4; c++){
       //door know
       drawPixel(c+ 52, r + 113, COLOR_PINK);
     }
   }
       
}


void House2(int wave){
  
  int r = 0;
  int c = 0;
  int center = 60;
  int row = 25;
   for(r = 0; r < 58; r++){
     for(c = 0; c < 58; c++){
       //roof
       drawPixel(c+ 31 ,r+ 65,COLOR_GOLD);
       //house square
       if(r < 40){
	 if(c <= r){
	   drawPixel(center + c, r + row, COLOR_WHITE);
	   drawPixel(center -c, r + row, COLOR_WHITE);
	 }
       }
     }
     } 
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

   
   
   //draw feets
   for(r = 0; r < 2; r++){
     drawPixel(r + 60, r+ 120, COLOR_RED);
     drawPixel(r + 56, 2-(r+137), COLOR_RED);
     // drawPixel( r+ 60,r+ 120, COLOR_RED);
    } 
   

   if(wave){
   // draw hands
     for(r = 0; r < 3; r++){
       drawPixel(r + 56, r + 115, COLOR_RED);
       drawPixel(r + 59, r + 115, COLOR_RED);
     }
   }else{
     for(r = 0; r < 3; r++){
       drawPixel(r+56,2-(r+141),COLOR_RED);
       drawPixel(r + 59, r+ 115, COLOR_RED);
     }
   }  
}



/** Draw single pixel at x,row 
 *
 *  \param col Column to draw to
 *  \param row Row to draw to
 *  \param colorBGR Color of pixel in BGR
 */
void drawPixel(u_char col, u_char row, u_int colorBGR) 
{
  lcd_setArea(col, row, col, row);
  lcd_writeColor(colorBGR);
}

/** Fill rectangle
 *
 *  \param colMin Column start
 *  \param rowMin Row start
 *  \param width Width of rectangle
 *  \param height height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height, 
		   u_int colorBGR)
{
  u_char colLimit = colMin + width, rowLimit = rowMin + height;
  lcd_setArea(colMin, rowMin, colLimit - 1, rowLimit - 1);
  u_int total = width * height;
  u_int c = 0;
  while ((c++) < total) {
    lcd_writeColor(colorBGR);
  }
}

/** Clear screen (fill with color)
 *  
 *  \param colorBGR The color to fill screen
 */
void clearScreen(u_int colorBGR) 
{
  u_char w = screenWidth;
  u_char h = screenHeight;
  fillRectangle(0, 0, screenWidth, screenHeight, colorBGR);
}

/** 5x7 font - this function draws background pixels
 *  Adapted from RobG's EduKit
 */
void drawChar5x7(u_char rcol, u_char rrow, char c, 
     u_int fgColorBGR, u_int bgColorBGR) 
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x01;
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 4, rrow + 7); /* relative to requested col/row */
  while (row < 8) {
    while (col < 5) {
      u_int colorBGR = (font_5x7[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    bit <<= 1;
    row++;
  }
}

void drawChar8x12(u_char rcol, u_char rrow, char c,u_int fgColorBGR, u_int bgColorBGR)
{
  u_char col = 0;
  u_char row = 0;
  u_int bit = 0x80;
  u_char oc = c - 0x20;

  lcd_setArea(rcol,rrow,rcol + 7, rrow + 12);
  while(row < 12){
    while(col < 8){
      u_int colorBGR = (font_8x12[oc][row] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
      bit >>= 1;
    }
    col = 0;
    bit=  0x80;
    row++;
  }
}


/** Draw string at col,row
 *  Type:
 *  FONT_SM - small (5x8,) FONT_MD - medium (8x12,) FONT_LG - large (11x16)
 *  FONT_SM_BKG, FONT_MD_BKG, FONT_LG_BKG - as above, but with background color
 *  Adapted from RobG's EduKit
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawString5x7(u_char col, u_char row, char *string,
		u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string) {
    drawChar5x7(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 6;
  }
}

void drawString8x12(u_char col, u_char row, char *string, u_int fgColorBGR, u_int bgColorBGR){
  u_char cols = col;
  while(*string){
    drawChar8x12(cols,row,*string++, fgColorBGR, bgColorBGR);
    cols += 9;
  }
}

/** Draw rectangle outline
 *  
 *  \param colMin Column start
 *  \param rowMin Row start 
 *  \param width Width of rectangle
 *  \param height Height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void drawRectOutline(u_char colMin, u_char rowMin, u_char width, u_char height,
		     u_int colorBGR)
{
  /**< top & bot */
  fillRectangle(colMin, rowMin, width, 1, colorBGR);
  fillRectangle(colMin, rowMin + height, width, 1, colorBGR);

  /**< left & right */
  fillRectangle(colMin, rowMin, 1, height, colorBGR);
  fillRectangle(colMin + width, rowMin, 1, height, colorBGR);
}

