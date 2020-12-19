//********************************************
// shapes.h
//
//
//********************************************
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>

#define BUTTON 14              // D5
#define ROTARLEDPosY_PIN1  13  // D7
#define ROTARLEDPosY_PIN2  12  // D6
#define CLICKS_PER_STEP   2    // this number depends on your rotary encoder 
#define MIN_POS   1
#define MAX_POS   6
#define MATRIX_WIDTH 8
#define MATRIX_HEIGHT 8
#define STARTING_PIXEL 1

#define PIN 4            // D2
#define LED_COUNT 64

// USE FOR PROGRESSIVE SQUARE
//Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(MATRIX_WIDTH, MATRIX_HEIGHT, PIN,
//                            NEO_MATRIX_TOP  + NEO_MATRIX_LEFT+
//                            NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
//                            NEO_GRB            + NEO_KHZ800);
                           
// USE FOR ZIGZAG Square
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(MATRIX_WIDTH, MATRIX_HEIGHT, PIN,
                            NEO_MATRIX_TOP  + NEO_MATRIX_LEFT+
                            NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB            + NEO_KHZ800);

#define black matrix.Color(0, 0, 0)        // black
#define rred matrix.Color(75, 0, 0)        // red
#define bblue matrix.Color(0, 0, 75)        // blue
#define ggreen matrix.Color(0, 75, 0)       // green                           
#define wwhite matrix.Color(75, 75, 75)   // white
#define dimyellow matrix.Color(30, 10, 0)    // yellow
#define yellow matrix.Color(75, 75, 0)    // yellow
#define magenta matrix.Color(75, 0, 75)   // magenta
#define cyan matrix.Color(0, 75, 75)      // cyan                      
#define orange matrix.Color(75, 15, 0)     // orange 
#define gold matrix.Color(75, 50, 0)      // gold
#define lime matrix.Color(7, 75, 10 )     // lime     

unsigned int COLOR[] = {black, rred, bblue, black, dimyellow, magenta, ggreen};
//********************************************
const byte TieGame[8] = {
  
  B00000000,
  B11100000,
  B01000000,
  B01000011,
  B01010100,
  B01010111,
  B01010100,
  B01010011
};
//********************************************
const byte RightArrowSm[8] = {
  
  B00000000,
  B00000100,
  B00000110,
  B11111111,
  B00000110,
  B00000100,
  B00000000,
  B00000000
};
//********************************************
const byte RightArrow8[8] = {
  
  B00001000,
  B00001100,
  B00001010,
  B11111001,
  B00001010,
  B00001100,
  B00001000,
  B00000000
};
//********************************************
const byte LeftArrowSm[8] = {
  
  B00000000,
  B00100000,
  B01100000,
  B11111111,
  B01100000,
  B00100000,
  B00000000,
  B00000000
};
//********************************************
const byte LeftArrow8[8] = {
  
  B00010000,
  B00110000,
  B01010000,
  B10011111,
  B01010000,
  B00110000,
  B00010000,
  B00000000
};
//********************************************
const byte DnArrowSm[8] = {
  
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B01111100,
  B00111000,
  B00010000
};
//********************************************
const byte DnArrow8[8] = {
  
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B11111110,
  B01000100,
  B00101000,
  B00010000
};
//********************************************
const byte UpArrowSm[8] = {
  
  B00010000,
  B00111000,
  B01111100,
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B00010000
};
//********************************************
const byte UpArrow8[8] = {
  
  B00010000,
  B00101000,
  B01000100,
  B11111110,
  B00010000,
  B00010000,
  B00010000,
  B00010000
};
//********************************************
const byte HollowQuarter4[8] = {

  B11110000,
  B10010000,
  B10010000,
  B11110000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};
//********************************************
const byte HollowSquare8[8] = {

  B11111111,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B11111111
};

//********************************************
const byte HollowSquare6[8] = {

  B00000000,
  B01111110,
  B01000010,
  B01000010,
  B01000010,
  B01000010,
  B01111110,
  B00000000
}; 
//******************************************** 
const byte HollowSquare4[8] = {

  B00000000,
  B00000000,
  B00111100,
  B00100100,
  B00100100,
  B00111100,
  B00000000,
  B00000000
};
//******************************************** 
const byte HollowSquare2[8] = {

  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00011000,
  B00000000,
  B00000000,
  B00000000
};
//******************************************** 
const byte Smiley[8] = {

  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};
//******************************************** 
const byte ArmsUp[8] = {

  B00111000,
  B00101000,
  B00111000,
  B01010100,
  B00111000,
  B00010000,
  B00101000,
  B01000100
};
//******************************************** 
const byte ArmsMid[8] = {

  B00111000,
  B00101000,
  B00111000,
  B00010000,
  B01111100,
  B00010000,
  B00101000,
  B00101000
};
//******************************************** 
const byte ArmsDn[8] = {

  B00111000,
  B00101000,
  B00111000,
  B00010000,
  B00111000,
  B01010100,
  B00101000,
  B01000100
};
//********************************************
const byte DIGIT[10][8] = {
{
  B00000000,
  B00111000,
  B01000100,
  B01001100,
  B01010100,
  B01100100,
  B01000100,
  B00111000
},
/*
{
  B00000000,
  B00111000,
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B00111000
},
*/
{
  B00000000,
  B00011000,
  B00011000,
  B00111000,
  B00011000,
  B00011000,
  B00011000,
  B01111110
},{
  B00000000,
  B00111100,
  B01100110,
  B00000110,
  B00001100,
  B00110000,
  B01100000,
  B01111110
},{
  B00000000,
  B00111100,
  B01100110,
  B00000110,
  B00011100,
  B00000110,
  B01100110,
  B00111100
},{
  B00000000,
  B00001100,
  B00011100,
  B00101100,
  B01001100,
  B01111110,
  B00001100,
  B00001100
},{
  B00000000,
  B01111110,
  B01100000,
  B01111100,
  B00000110,
  B00000110,
  B01100110,
  B00111100
},{
  B00000000,
  B00111100,
  B01100110,
  B01100000,
  B01111100,
  B01100110,
  B01100110,
  B00111100
},{
  B00000000,
  B01111110,
  B01100110,
  B00001100,
  B00001100,
  B00011000,
  B00011000,
  B00011000
},{
  B00000000,
  B00111100,
  B01100110,
  B01100110,
  B00111100,
  B01100110,
  B01100110,
  B00111100
},{
  B00000000,
  B00111100,
  B01100110,
  B01100110,
  B00111110,
  B00000110,
  B01100110,
  B00111100
}};
//******************************************************    
void DisplayTie(int colour, int wait) 
{
      matrix.clear();  
      matrix.drawBitmap(0, 0,  TieGame, 8, 8, colour);
      matrix.show();
      delay(wait);  
      matrix.clear();          
       
}
//******************************************************    
void SmileyDown(signed int startpos, signed int endpos, int colour, int wait) 
{
signed int x, y;

   matrix.clear();  
   for(y = startpos; y < endpos + 1; y++)
      {
      matrix.drawBitmap(0, y,  Smiley, 8, 8, colour);
      matrix.show();
      delay(wait);  
      matrix.clear();          
      } 
}
//******************************************************    
void MovingArrowUp(signed int startpos, signed int endpos, int colour, int wait) 
{
signed int a, b;

   for(b = startpos; b > endpos - 1; b--)
      {
      matrix.drawBitmap(0, b,  UpArrow8, 8, 8, colour);
      matrix.show();
      delay(wait);  
      matrix.clear();          
      } 
}
//******************************************************    
void MovingArrowUpSm(signed int startpos, signed int endpos, int colour, int wait) 
{
signed int a, b;

   for(b = startpos; b > endpos - 1; b--)
      {
      matrix.drawBitmap(0, b,  UpArrowSm, 8, 8, colour);
      matrix.show();
      delay(wait);  
      matrix.clear();          
      } 
}
//******************************************************    
void MovingArrowDown(signed int startpos, signed int endpos, int colour, int wait) 
{
signed int a, b;

   for(b = startpos; b < endpos + 1; b++)
      {
      matrix.drawBitmap(0, b,  DnArrow8, 8, 8, colour);
      matrix.show();
      delay(wait);  
      matrix.clear();          
      } 
}
//******************************************************    
void MovingArrowDownSm(signed int startpos, signed int endpos, int colour, int wait) 
{
signed int a, b;

   for(b = startpos; b < endpos + 1; b++)
      {
      matrix.drawBitmap(0, b,  DnArrowSm, 8, 8, colour);
      matrix.show();
      delay(wait);  
      matrix.clear();          
      } 
}
//******************************************************    
void MovingArrowLeft(signed int startpos, signed int endpos, int colour, int wait) 
{
signed int a, b;

   for(a = startpos; a > endpos - 1; a--)
      {
      matrix.drawBitmap(a, 0,  LeftArrow8, 8, 8, colour);
      matrix.show();
      delay(wait);  
      matrix.clear();          
      } 
}
//******************************************************    
void MovingArrowLeftSm(signed int startpos, signed int endpos, int colour, int wait) 
{
signed int a, b;

   for(a = startpos; a > endpos - 1; a--)
      {
      matrix.drawBitmap(a, 0,  LeftArrowSm, 8, 8, colour);
      matrix.show();
      delay(wait);  
      matrix.clear();          
      } 
}
//******************************************************    
void MovingArrowRight(signed int startpos, signed int endpos, int colour, int wait) 
{
signed int a, b;

   for(a = startpos; a < endpos + 1; a++)
      {
      matrix.drawBitmap(a, 0,  RightArrow8, 8, 8, colour);
      matrix.show();
      delay(wait);  
      matrix.clear();          
      } 
}
//******************************************************    
void MovingArrowRightSm(signed int startpos, signed int endpos, int colour, int wait) 
{
signed int a, b;

   for(a = startpos; a < endpos + 1; a++)
      {
      matrix.drawBitmap(a, 0,  RightArrowSm, 8, 8, colour);
      matrix.show();
      delay(wait);  
      matrix.clear();          
      } 
}
//******************************************************    
void JumpingJack(int colour, int wait, int repeats) 
{
int y; 

   for(y = 0; y < repeats; y++)
      { 
      matrix.clear();
      matrix.drawBitmap(0, 0,  ArmsUp, 8, 8, colour);
      matrix.show();      
      delay(wait); 
      matrix.clear();
      matrix.drawBitmap(0, 0,  ArmsMid, 8, 8, colour);
      matrix.show();      
      delay(wait); 
      matrix.clear();
      matrix.drawBitmap(0, 0,  ArmsDn, 8, 8, colour);
      matrix.show();      
      delay(wait); 
      }
}
//******************************************************    
void RoamingSquare(int colour, int wait, int repeats) 
{
int a, x, y;  

   for(a = 0; a < repeats; a++)
      {
      if(digitalRead(BUTTON) == 0) return;
      for(x = 0; x < 4; x++) 
         { 
         matrix.clear();
         matrix.drawBitmap(x, y,  HollowQuarter4, 8, 8, colour);
         matrix.show();      
         delay(wait);
         }
      for(y = 0; y < 4; y++) 
         { 
         matrix.clear();
         matrix.drawBitmap(x, y,  HollowQuarter4, 8, 8, colour);
         matrix.show();      
         delay(wait);
         }      
      for(x = 4; x > 0; x--) 
         { 
         matrix.clear();
         matrix.drawBitmap(x, y,  HollowQuarter4, 8, 8, colour);
         matrix.show();      
         delay(wait);
         }
      for(y = 4; y > 0; y--) 
         { 
         matrix.clear();
         matrix.drawBitmap(x, y,  HollowQuarter4, 8, 8, colour);
         matrix.show();      
         delay(wait);
         }       
      
      
      
      }   
}
//******************************************************    
void ExpandingSquare(int wait, int repeats) 
{
int y;  

   for(y = 0; y < repeats; y++)
      {
      if(digitalRead(BUTTON) == 0) return;
      matrix.clear();
      matrix.drawBitmap(0, 0,  HollowSquare8, 8, 8, rred);
      matrix.show();      
      delay(wait);
      matrix.clear();
      matrix.drawBitmap(0, 0,  HollowSquare6, 8, 8, ggreen);
      matrix.show();
      delay(wait);
      matrix.clear();
      matrix.drawBitmap(0, 0,  HollowSquare4, 8, 8, bblue);
      matrix.show();
      delay(wait);
      matrix.clear();
      matrix.drawBitmap(0, 0,  HollowSquare2, 8, 8, yellow);
      matrix.show();
      delay(wait);
      matrix.clear();
      matrix.drawBitmap(0, 0,  HollowSquare2, 8, 8, yellow);
      matrix.show();      
      delay(wait);
      matrix.clear();
      matrix.drawBitmap(0, 0,  HollowSquare4, 8, 8, ggreen);
      matrix.show();
      delay(wait);
      matrix.clear();
      matrix.drawBitmap(0, 0,  HollowSquare6, 8, 8, bblue);
      matrix.show();
      delay(wait);
      matrix.clear();
      matrix.drawBitmap(0, 0,  HollowSquare8, 8, 8, rred);
      matrix.show();
      delay(wait);
      }
}
//******************************************************    
void CountDown() 
{
int count;  
 
   matrix.clear(); 
   for(count = 9; count >= 0; count--)
      {       
      matrix.drawBitmap(0, 0,  DIGIT[count], 8, 8, rred);
      matrix.show();
      delay(1000);
      matrix.clear();
      }     
}
//******************************************************    
void CountUp() 
{ 
int count;

   matrix.clear(); 
   for(count = 0; count < 10; count++)
      {       
      matrix.drawBitmap(0, 0,  DIGIT[count], 8, 8, orange);
      matrix.show();
      delay(1000);
      matrix.clear();
      }    
}
//******************************************************    
void DisplayDigit(int number, int colour, int wait) 
{ 
      matrix.clear(); 
      matrix.drawBitmap(0, 0,  DIGIT[number], 8, 8, colour);
      matrix.show();
      delay(wait);
}
