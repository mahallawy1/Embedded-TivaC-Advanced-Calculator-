#include "systicTIMER.h"
#include "Keypad.h"
#include "lcd.h"



void timerSTART()
{
  LCD_String("Timer_Mode");
  char x = 0;
  x = keypad_getkey();
  int y = 0;
  y = x - '0';
  LCD_Cmd(clear_display);
  LCD_Cmd(FirstRowPosition0);
  LCD_Data(x);
  int counter = 0;
  while(counter != y)
  {
  GPIO_PORTF_DATA_R |= 0x00;
  NVIC_ST_CTRL_R = 0x0;
  NVIC_ST_RELOAD_R = 0xFFFFFF;
  NVIC_ST_CURRENT_R = 0x0;
  NVIC_ST_CTRL_R = 0x5;
  while ((NVIC_ST_CTRL_R & 0x10000) == 0)
    {
    }		
   counter++;
  }
  GPIO_PORTF_DATA_R |= 0xE;
  NVIC_ST_CTRL_R = 0x0;
}