//***************************************************************************
// ConnectFour2D_Z.ino
// Zig Zag Square Version
// Use with ESP8266 and 8x8 WS2812B pixel board
// Will work with Zig Zag or Progressive style board
// Encoder selects column position for play.
// Push button sets play in motion.
// 
// Code modified from Kelly Bodeman and Jack Whelan
//
// ported and modified by RCI
// 1-16-2021
//***************************************************************************
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <ESPRotary.h>
#include "shapes.h"

int brightness = 25;
int startbrightness = 10;

ESPRotary r;  // See setup() for initialization
//ESPRotary r = ESPRotary(ROTARY_PIN1, ROTARY_PIN2, CLICKS_PER_STEP, MIN_POS, MAX_POS);

int repeat, countLEDPosY;
int Speed = 500;
int buttonblock = 0;
unsigned int EncVal, EncVal2; 
unsigned int EncValLast = 0;
bool InitFlag = 0;

//button sensing
int buttonstate[] = {0, 0, 0, 0, 0, 0, 0, 0};
int buttonState0;
int buttonState1;
int buttonState2;
int buttonState3;
int buttonState4;
int buttonState5;
int buttonState6;
int buttonState7;

//windetect variables
int wincolor;
int wincount = 0;
int winrow[5][3] = {
                   {0, 0, 0},    // dummy
                   {0, 0, 0},    // winrow1
                   {0, 0, 0},    // winrow2
                   {0, 0, 0},    // winrow3
                   {0, 0, 0},    // winrow4                                     
                   };
                   
unsigned char primarycolors[10][3] = {
                            {255, 0, 0},    // red
                            {0, 0, 255},    // blue
                            {0, 200, 0},    // green                           
                            {255, 200, 0},  // yellow
                            {255, 0, 255},  // magenta
                            {0, 200, 255},  // cyan 
                            {0, 0, 0},      // black 
                            {255, 30, 0},  // orange 
                            {255, 100, 0}, // gold                            
                            {14, 200, 10}, // lime                                                                   
                            }; 
                            
int score[3];
int winstate = 0;
int winner;
int winningPos[5];
int columnFull[8];
int lastmatrix;
int scanX;
int scanY;
int LEDPosX, a, b;
int LEDPosY;
int player, playerfirst;
int Max_Y;
int Max_X;
int State;
int count;
int gameFull;
int skipAniFlag = 0;
int rowFullFlag[8];

//***** Animation variables
int y[] = {7, 7, 7, 7, 7, 7, 7, 7}; //to tell the height of each row
int anistate = 1; //animation state machine
int yAni = 0;
int yAniPast; 

int gameMatrix[MATRIX_HEIGHT][MATRIX_WIDTH] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
};

//************************************************************************************************
// Delay (loops) 
void delayms(int loops) 
{
unsigned long time_now = 0;
    time_now = millis();
    
    while(millis() < time_now + loops)
      {
      r.loop();  
      delay(1);   
      }
   
}
//*********************************************************************************
void InitEnc(int initVal) 
{ 
    EncVal2 = r.getPosition();
    r.resetPosition(initVal);    //Resets encoder to START_POS
}
//*********************************************************************************
void InitBoard()
{
int row, col;

  winner = 0;
  player = playerfirst;
  Max_Y = 8;
  Max_X = 8;
  wincount = 0;
  winstate = 0; 
  State = 0; 
  buttonblock = 0;
  EncValLast = 0;
  EncVal = 6;
  gameFull = 0;

  // Clear moves
  buttonState0 = 0;
  buttonState1 = 0;
  buttonState2 = 0;
  buttonState3 = 0;
  buttonState4 = 0;
  buttonState5 = 0;
  buttonState6 = 0;
  buttonState7 = 0;
  
  // Clear Board Matrix
  for(col = 0; col < 8; col++)
     {
     for(row = 0; row < 8; row++) 
        {
        gameMatrix[row][col] = 0;
        }
     }
      
  // Clear Overload    
  for(repeat = 0; repeat < 8; repeat++)
     {
     buttonstate[repeat] = 0; 
     }
     
  // Clear LEDPosY   
  for(repeat = 0; repeat < 8; repeat++)
     {
     columnFull[repeat] = 0;
     y[repeat] = 7;  
     }
     
  r.loop();  
  InitEnc(START_POS);       // START_POS = 240
  r.loop(); 
     
  matrix.clear();  
  matrix.show(); 
                      
}
//*********************************************************************************
// Called very time encoder rotates
void rotate(ESPRotary& r) 
{   
   EncVal2 = r.getPosition();       
}
//***********************************************************************************
unsigned int GetEnc() 
{
unsigned int tempEnc;

    r.loop();
    tempEnc = EncVal2;
              
    // Print EncVal value when EncVal value changed
    if (EncValLast != tempEnc) 
        {
        EncValLast = tempEnc;
        return tempEnc;
        }
        
}
//***********************************************************************************
void DrawCol(unsigned char X, unsigned startingLEDPosY, int colour)
{
 int i;
 
    for (countLEDPosY = startingLEDPosY; countLEDPosY < 8; countLEDPosY++) 
       {      
       matrix.drawPixel(X, countLEDPosY, colour); 
       }    
}
//***********************************************************************************
void flashPixel(int xpos, int ypos, int clr)
{
  
    matrix.drawPixel(xpos, ypos, COLOR[0]); 
    matrix.show();
    delayms(50);
    matrix.drawPixel(xpos, ypos, clr); 
    matrix.show();
    delayms(50);    
}
//***********************************************************************************
void onlyOnePixel()
{
    // ***** Clear player selection ********************
    for(repeat = 0; repeat < 7; repeat++)
       {      
       matrix.drawPixel(repeat, 0, COLOR[0]); 
       }
       matrix.show();
}
//***********************************************************************************
void rowFullFlash(int col, int playr)
{
int x, y;

    // ***** Flash the winning row 6 times ********************
    for(repeat = 0; repeat < 6; repeat++)
       {
       // Draw Game Sides 
       DrawCol(0, 1, dimyellow); //dimyellow
       DrawCol(7, 1, dimyellow); 
       
       // Flash column when it is already full                     
         for(y = 1; y < Max_Y; y++)      // Dummy For
            {              
            matrix.drawPixel(col, y, COLOR[0]);  // Flash a blank for winning section          
            }          
          matrix.show();
          delay(100);
          
         for(y = 1; y < Max_Y; y++)
            { 
            for(x = 0; x < Max_X; x++)
               {                 
               matrix.drawPixel(x, y, COLOR[gameMatrix[x][y]]);   // Flash All game tiles        
               } 
            }          
          matrix.show();
          delay(100);         
       }      
         
}// End RowFull
//*******************************************************************************************  
// Rain Random Comets Down
void RandomColor(int wait)
{
unsigned char x, y, b, rr, gg, bb, ypos;
int bright;

 if(digitalRead(BUTTON) != 0)
    {
    while(digitalRead(BUTTON) != 0)   // Repeat
       {
          x = random(8);
          y = random(10);
          b = random(7);
          rr = primarycolors[b][0] / 1;
          gg = primarycolors[b][1] / 1;
          bb = primarycolors[b][2] / 1;

          matrix.drawPixel(x, y, matrix.Color(rr, gg, bb)); 
          matrix.show();
          delay(wait); 

          if(digitalRead(BUTTON) == 0)
             {
             while(digitalRead(BUTTON) == 0)   
                {             
                }
                InitBoard();               
                delay(1000);
                return;
             }// End If
       }// End While digitalRead
    }// End If digitalRead
            
}// End RandomColor
//*****************************************************************************
void ReadEncoder()
{
  r.loop();
  EncVal = GetEnc();

  // When BUTTON is pressed, go to Chip Drop Routine
  if((digitalRead(BUTTON) == 0) && (EncVal == 0))
    {
    while (digitalRead(BUTTON) == 0){} 
    buttonstate[0] = 1;
    buttonblock = 1;
    }
  if((digitalRead(BUTTON) == 0) && (EncVal == 1))
    {
    while (digitalRead(BUTTON) == 0){} 
    buttonstate[1] = 1;
    buttonblock = 1;
    }
  if((digitalRead(BUTTON) == 0) && (EncVal == 2))    
    {
    while (digitalRead(BUTTON) == 0){} 
    buttonstate[2] = 1;
    buttonblock = 1;
    }
  if((digitalRead(BUTTON) == 0) && (EncVal == 3))
    {
    while (digitalRead(BUTTON) == 0){} 
    buttonstate[3] = 1;
    buttonblock = 1;
    }
  if((digitalRead(BUTTON) == 0) && (EncVal == 4))    
    {
    while (digitalRead(BUTTON) == 0){} 
    buttonstate[4] = 1;
    buttonblock = 1;
    }
  if((digitalRead(BUTTON) == 0) && (EncVal == 5))    
    {
    while (digitalRead(BUTTON) == 0){} 
    buttonstate[5] = 1;
    buttonblock = 1;
    }
  if((digitalRead(BUTTON) == 0) && (EncVal == 6))    
    {
    while (digitalRead(BUTTON) == 0){} 
    buttonstate[6] = 1;
    buttonblock = 1;
    }
  if((digitalRead(BUTTON) == 0) && (EncVal == 7))
    {
    while (digitalRead(BUTTON) == 0){} 
    buttonstate[7] = 1;
    }  
}

//*****************************************************************************
void setup() 
{
  Serial.begin(115200);
  pinMode(BUTTON, INPUT_PULLUP);
  r.begin(ROTARY_PIN1, ROTARY_PIN2, CLICKS_PER_STEP, MIN_ENC_VAL, MAX_ENC_VAL, START_POS, INCREMENT); 
  r.setChangedHandler(rotate);
  randomSeed(analogRead(0));
  matrix.begin();
  matrix.setBrightness(startbrightness);
  matrix.clear();
  score[1] = 0;
  score[2] = 0;
  player = 1;
  playerfirst = player;
  ExpandingSquare(100, 5); 
  SmileyDown(0, 0, orange, 3000);
  //DisplayDigit(number, colour, wait)  
  DisplayDigit(score[1], COLOR[1], 2000);
  DisplayDigit(score[2], COLOR[2], 2000);
  RandomColor(40);
  InitFlag = 0;
  InitBoard();
  matrix.setBrightness(brightness);  

}
//*****************************************************************************
void loop() 
{
  
  ReadEncoder();
  
  switch (State) 
  {
    //******************************************************  
    case 0: // State = 0, Clear game, reset, no need for this state.
    
      matrix.clear(); 
      matrix.show();       
      State = 1;
      break;
    //******************************************************  
    case 1: // State = 1, Select Column to Populate Routine
           //DrawCol(X, startingLEDPosY, color)
                      
      DrawCol(0, 1, dimyellow); //dimyellow
      DrawCol(7, 1, dimyellow);
      onlyOnePixel();   // clear first pixel row
      matrix.drawPixel(EncVal, 0, COLOR[player]); 
      matrix.show();
      
      // If column is full, jump to row scan without pressing button
      if(gameMatrix[EncVal][1] > 0)
         {
         ReadEncoder(); 
         anistate = 1; 
         State = 2;                       
         break;
         }       
      if (buttonState0 == 0 && buttonstate[0] == 1) 
         {
         anistate = 1; 
         State = 2;
         LEDPosX = 0;
         break;
         }
      if (buttonState1 == 0 && buttonstate[1] == 1) 
         {
         anistate = 1; 
         State = 2;
         LEDPosX = 1;        
         break;
         }
      if (buttonState2 == 0 && buttonstate[2] == 1) 
         {
         anistate = 1; 
         State = 2;
         LEDPosX = 2;
         break;
         }
      if (buttonState3 == 0 && buttonstate[3] == 1) 
         {
         anistate = 1; 
         State = 2;
         LEDPosX = 3;
         break;
         }
      if (buttonState4 == 0 && buttonstate[4] == 1) 
         {
         anistate = 1; 
         State = 2;
         LEDPosX = 4;
         break;
         }
      if (buttonState5 == 0 && buttonstate[5] == 1) 
         {        
         anistate = 1; 
         State = 2;
         LEDPosX = 5;
         break;
         }
      if (buttonState6 == 0 && buttonstate[6] == 1) 
         {
         anistate = 1; 
         State = 2;
         LEDPosX = 6;
         break;
         }

      break;
    //******************************************************  
    case 2: // State = 2, Chip Drop Animation
      switch (anistate) 
      {
        //*****************************
        case 1: // anistate = 1, Checking for overload and adjusting if it sees anything
        // If all Columns are Full, End Game
        
        if(((columnFull[1] == 1) && (columnFull[2] == 1) && (columnFull[3] == 1) && (columnFull[4] == 1) && (columnFull[5] == 1) && (columnFull[6] == 1)) == 1) 
          {
          DisplayTie(wwhite, 3000); 
          RoamingSquare(wwhite, 50, 10); 
          State = 5;
          break;
          }

        // If current column is not full, check board for top row full
        if(columnFull[EncVal] != 1) 
           {                       
           for(repeat = 1; repeat < 7; repeat++)
              {
              // if top pixel is full for the first time                
              if(gameMatrix[repeat][1] > 0 && rowFullFlag[repeat] != 1) 
                 {                   
                 columnFull[repeat] = 1;
                 rowFullFlag[repeat] = 1;
                 rowFullFlash(repeat, player);
                 State = 1;
                 anistate = 1;
                 break;
                 }
              }      
           }

        if(columnFull[EncVal] == 1)
          {
          // do something here to show full and go back to button read
          flashPixel(EncVal, 0, COLOR[player]);
          State = 1;                  
          anistate = 1;        
          break; 
          }
           
          anistate = 2;
          
          break;
        //*****************************  
        case 2: // anistate = 2, Animate Chip Drop
        
          matrix.drawPixel(EncVal, 0, COLOR[player]);  
          matrix.drawPixel(LEDPosX, yAniPast, COLOR[0]);
          matrix.drawPixel(LEDPosX, yAni, COLOR[player]);
          matrix.show();
          yAniPast = yAni;
          yAni++;
          if(yAni - 1 == y[LEDPosX] && player == 1)  
             {
             anistate = 3;
             }
          if(yAni - 1 == y[LEDPosX] && player == 2) 
             {
             anistate = 4;
             }
          delayms(100);
          break;
        //*****************************  
        case 3:  // anistate = 3, Setting color for player 1
          y[LEDPosX]--;
          if(y[LEDPosX] <= 0) y[LEDPosX] = 0;
          //player = 1;
          LEDPosY = y[LEDPosX] + 1;
          gameMatrix[LEDPosX][LEDPosY] = player; // 1 is red, 2 is blue, 0 is off
          yAni = 0;
          yAniPast = -1;
          buttonblock = 0;
          buttonstate[LEDPosX] = 0;
          winstate = 0;
          anistate = 1;
          State = 3;
          player = 2;
          break;
        //*****************************  
        case 4:  // anistate = 3, Setting color for player 2
          y[LEDPosX]--;
          if(y[LEDPosX] <= 0) y[LEDPosX] = 0;
          //player = 2;
          LEDPosY = y[LEDPosX] + 1;
          gameMatrix[LEDPosX][LEDPosY] = player;
          yAni = 0;
          yAniPast = -1;
          buttonblock = 0;
          buttonstate[LEDPosX] = 0;
          winstate = 0;
          anistate = 1;
          State = 3;
          player = 1;
          break;
      }// End switch anistate
      break;
    //******************************************************  
    case 3: // State = 3, win detect routine
      switch (winstate) 
      {
        //*****************************  
        case 0: // winstate = 0, Setting led states         
          scanX = 0;
          wincount = 0;
          scanY = y[LEDPosX] + 1;
          winstate = 1;
          if(scanY <= 0) scanY = 0;
          break;
        //*****************************  
        case 1: // winstate  = 1, Horizontal scan   

          if (gameMatrix[scanX][scanY] == gameMatrix[LEDPosX][LEDPosY]) 
             {             
             wincount++;
             winrow[wincount][0] = scanX;
             winrow[wincount][1] = scanY;
             winrow[wincount][2] = gameMatrix[scanX][scanY];
             }
          else 
             {
             wincount = 0;
             }
          if (wincount >= 4 ) 
             {
             winner = winrow[wincount][2]; 
             ++score[winner];
             State = 4; // move to State = 4 Win Animation Flash Routine
             break;
             }
          if (scanX >= Max_X) 
             {
             wincount = 0;
             scanY = 0;
             scanX = LEDPosX;
             winstate = 2; // move to vertical scan
             //Serial.println("");
             break;
             }
          scanX++;
        break;
        //*****************************  
        case 2: // winstate = 2, Vertical scan
          
          if (gameMatrix[scanX][scanY] == gameMatrix[LEDPosX][LEDPosY]) 
             {             
             wincount++;
             winrow[wincount][0] = scanX;
             winrow[wincount][1] = scanY;  
             winrow[wincount][2] = gameMatrix[scanX][scanY];                               
             }
          else 
             {
             wincount = 0;
             }
          if (wincount >= 4) 
             {
             winner = winrow[wincount][2]; 
             ++score[winner];
             State = 4;  // move to State = 4 Win Animation Flash Routine
             break;
             }
          if (scanY >= Max_Y) 
             {
             scanY = LEDPosY - Max_Y;
             scanX = LEDPosX - Max_X;
             //Serial.println("");
             winstate = 3; // move to diagonal check top left to bottom right
             break;
             }
          scanY++;
        break;
        //*****************************    
        case 3: // winstate = 3, Diagonal check bottom left to top right
       
          if (gameMatrix[scanX][scanY] == gameMatrix[LEDPosX][LEDPosY]) 
             {
             wincount++;
             winrow[wincount][0] = scanX;
             winrow[wincount][1] = scanY;
             winrow[wincount][2] = gameMatrix[scanX][scanY];
             }
          else 
             { 
             wincount = 0;
             }
          if (wincount >= 4) 
             {
             winner = winrow[wincount][2]; 
             ++score[winner];
             State = 4;  // move to State = 4 Win Animation Flash Routine
             break;
             }
          if(scanY >= Max_Y || scanX >= Max_X)
             {
             scanX = LEDPosX + Max_X;             
             scanY = LEDPosY - Max_Y;
             winstate = 4; //diagonal check ++
             break;
             }
          scanX++;
          scanY++;
          break;            
        //***************************** 
        //WORKS!!!! 
        case 4: // winstate = 4, Diagonal check top right to bottom left

          if (gameMatrix[scanX][scanY] == gameMatrix[LEDPosX][LEDPosY]) 
             {
             wincount++;
             winrow[wincount][0] = scanX;
             winrow[wincount][1] = scanY;
             winrow[wincount][2] = gameMatrix[scanX][scanY];
             }
          else 
             {
             wincount = 0;
             }
          if (wincount >= 4) 
             {
             winner = winrow[wincount][2]; 
             ++score[winner];
             State = 4;    // move to State = 4 Win Animation Flash Routine
             break;
             }
          if (scanY >= Max_Y || scanX <= 0 ) 
             {                       
             winstate = 0; // move to winstate = 0 Setting led states
             anistate = 1; // move to checking for overload and adjusting if it sees anything
             State = 1;    // move to State = 1 Select Row to Populate Routine
             break;
             }
          scanX--;
          scanY++;
          break;
        //*****************************  
      }// End switch winstate      
      break;
    //******************************************************  
    case 4: // State = 4, Win Animation Flash Routine
      //Serial.println("in state 4");
      // 1 is blue, 2 is red, 0 is off
    delay(1000);

    JumpingJack(COLOR[winner], 200, 10);
    delay(1000); 
    matrix.clear();  
    // ***** Flash the winning row 6 times ********************
    for(repeat = 0; repeat < 6; repeat++)
       {
       // Draw Game Sides 
       DrawCol(0, 1, dimyellow); //dimyellow
       DrawCol(7, 1, dimyellow); 
       //                 
       if(winner == 1) 
         {       
         for(b = 0; b < 3; b++)      // Dummy For
            { 
            for(a = 1; a < 5; a++)
               {                 
               matrix.drawPixel(winrow[a][0], winrow[a][1], COLOR[0]);  // Flash a blank for winning section          
               } 
            }          
          matrix.show();
          delay(500);
          
         for(b = 1; b < Max_Y; b++)
            { 
            for(a = 0; a < Max_X; a++)
               {                 
               matrix.drawPixel(a, b, COLOR[gameMatrix[a][b]]);   // Flash All game tiles        
               } 
            }          
          matrix.show();
          delay(500);         
          }      
       else    // If winner == 2
         {       
         for(b = 0; b < 3; b++)       // Dummy For
            { 
            for(a = 1; a < 5; a++)
               {                 
               matrix.drawPixel(winrow[a][0], winrow[a][1], COLOR[0]); // Flash a blank for winning section          
               } 
            }          
          matrix.show();
          delay(500);
          
         for(b = 1; b < Max_Y; b++)
            { 
            for(a = 0; a < Max_X; a++)
               {
               matrix.drawPixel(a, b, COLOR[gameMatrix[a][b]]);   // Flash All game tiles                       
               } 
            }          
          matrix.show();
          delay(500);         
          } 
         } 
           // (int number, int colour, int wait) 
      DisplayDigit(score[1], COLOR[1], 2000);
      DisplayDigit(score[2], COLOR[2], 2000);
      State = 5; 
      break;
    //******************************************************  
    case 5:  // Init and go to Start

         if(playerfirst == 1) 
           {
           playerfirst = 2;
           }         
         else 
           {
           playerfirst = 1;
           }
         InitBoard();
         State = 0;
                
      
      break;
    //******************************************************    
  }
}
//*********************************************************************************
//*********************************************************************************
