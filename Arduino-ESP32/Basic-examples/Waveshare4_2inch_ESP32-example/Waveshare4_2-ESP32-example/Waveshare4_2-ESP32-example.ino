//Based on: GxEPD_Example 

//Import own byte array icons. Created with https://javl.github.io/image2cpp/
#include "icons.h"

#include <GxEPD.h>

//Display libary
#include <GxGDEW042T2/GxGDEW042T2.h> // 4.2inch b/w

//Fonts libaries
#include <Fonts/FreeSansBoldOblique18pt7b.h>
#include <Fonts/FreeSansBoldOblique9pt7b.h>
#include <Fonts/FreeSansOblique9pt7b.h>

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

//Pin configurations
GxIO_Class io(SPI, /*CS=*/ SS, /*DC=*/ 17, /*RST=*/ 16);
GxEPD_Class display(io, /*RST=*/ 16, /*BUSY=*/ 4);

//Fonts
const GFXfont* f_small = &FreeSansOblique9pt7b;//&FreeMono9pt7b; //Both are good
const GFXfont* f = &FreeSansBoldOblique9pt7b;//FreeMonoBold9pt7b;
const GFXfont* f_big = &FreeSansBoldOblique18pt7b;//FreeMonoBold9pt7b;


//####################################################################################################
//---------------------------------------------------------------------------------------------------
//-------------------------------------------Setup---------------------------------------------------
//---------------------------------------------------------------------------------------------------
//####################################################################################################
void setup()
{
  Serial.begin(115200);

  display.init(115200); //enable diagnostic on Serial
}

////####################################################################################################
////---------------------------------------------------------------------------------------------------
////-------------------------------------------Functions-----------------------------------------------
////---------------------------------------------------------------------------------------------------
////####################################################################################################

void print_air_pressure(int x,int y, float air_pressure_mess){
    //Air pressure
    display.drawExampleBitmap(air_pressure_icon,x+0, y+0, 40 , 40, GxEPD_BLACK);
    display.setFont(f);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(x+40, y+18);
    display.println(String(air_pressure_mess));
    
    display.setCursor(x+70, y+32);
    display.println("hpa");
  }

//Draws a horizontal line
//https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives
void print_horizontal_line(int y){
  display.drawLine(0,y,400,y,GxEPD_BLACK);
}

//Prints a vertical line over the entire screen
void draw_vertical_line(int x){
  display.drawLine(x,0,x,300,GxEPD_BLACK);
}

//Print only a vertical line for that 40px section
//x=line on x-achis, y=upper point of the vertical line
void draw_vertical_line_section(int x, int y){
  display.drawLine(x,y,x,y+40,GxEPD_BLACK);
}



//####################################################################################################
//---------------------------------------------------------------------------------------------------
//-------------------------------------------Loop---------------------------------------------------
//---------------------------------------------------------------------------------------------------
//####################################################################################################
void loop()
{
  //Clear display
  display.fillScreen(GxEPD_WHITE);

  //Print icons and lines
  print_air_pressure(110,0,992.39);
  draw_vertical_line_section(218,0);
  print_air_pressure(220,0,1002.29);
  draw_vertical_line(338);

  //Lines
  print_horizontal_line(40);
  print_horizontal_line(81);


  //Test
  display.drawExampleBitmap(humidity_icon,0, 41, 40 , 40, GxEPD_BLACK);
  
  //-------------------------------------------------------------------

  //Write display
  display.update();
  delay(10000);
}
