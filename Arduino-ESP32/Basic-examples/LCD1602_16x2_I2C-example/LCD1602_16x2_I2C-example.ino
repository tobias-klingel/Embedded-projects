
#include <LiquidCrystal_I2C.h>


                //Address, columns, row
LiquidCrystal_I2C lcd(0x27, 16, 2);  

//####################################################################################################
//---------------------------------------------------------------------------------------------------
//-------------------------------------------Setup---------------------------------------------------
//---------------------------------------------------------------------------------------------------
//####################################################################################################
void setup(){
  
  // initialize LCD
  lcd.init();
  
  // turn on LCD backlight                      
  lcd.backlight();
}

//####################################################################################################
//---------------------------------------------------------------------------------------------------
//-------------------------------------------Loop---------------------------------------------------
//---------------------------------------------------------------------------------------------------
//####################################################################################################
void loop(){
  // Sets the cursor to first column, first row
  lcd.setCursor(0, 0);
  
  // Print a message
  lcd.print("Hello world!");
  
  delay(2000);

}
