#include "tm4c123gh6pm.h"
#include "calculator.h"
#include "systicTIMER.h"
#include <stdlib.h>
#include <stdio.h>
#include "Stopwatch.h"


/*                  Interrupt Functions                */
int state = 0;
void GPIOF_Handler(void)
{
  if (GPIO_PORTF_MIS_R & 0x10)
  {
    delay_milli(200);
    switch (state){
    case 0:
      GPIO_PORTF_DATA_R = 0x00;
      GPIO_PORTF_DATA_R |= 0x02;
      calculatorbasic();
      break;
    case 1:
      GPIO_PORTF_DATA_R = 0x00;
      GPIO_PORTF_DATA_R |= 0x04;
      timerSTART();
      break;
    case 2:
      GPIO_PORTF_DATA_R = 0x00;
      GPIO_PORTF_DATA_R |= 0x08;
      enableStopwatch();
      break;
    
    }
    //clear interrupt flag 
    GPIO_PORTF_ICR_R |= 0x10;
  
  }else if (GPIO_PORTF_MIS_R & 0x01)
  {
    //GPIO_PORTF_DATA_R &= ~0x02;
    GPIO_PORTF_ICR_R |= 0x01;
    disableTimer();
    //do nothing
  }
  if(state == 3)
  {
    state = 0;
  }
  state++;
}

void interrupt_init()
{
  SYSCTL_RCGCGPIO_R |= 0X20;
  while ((SYSCTL_RCGCGPIO_R & 0x20) ==0x00){};
  GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
  GPIO_PORTF_CR_R = 0x1F;
  GPIO_PORTF_DIR_R = 0x0E;
  GPIO_PORTF_PUR_R = 0x11;
  GPIO_PORTF_DEN_R = 0x1F;
  GPIO_PORTF_DATA_R |= 0x00;
  
  /* configure PORTF4, 0 for falling edge trigger interrupt */
    GPIO_PORTF_IS_R &= (1<<4)|(1<<0);        /* make bit 4, 0 edge sensitive */
    GPIO_PORTF_IBE_R &=(1<<4)|(1<<0);         /* trigger is controlled by IEV */
    GPIO_PORTF_IEV_R &= (1<<4)|(1<<0);        /* falling edge trigger */
    GPIO_PORTF_ICR_R |= (1<<4)|(1<<0);          /* clear any prior interrupt */
    GPIO_PORTF_IM_R  |= (1<<4)|(1<<0);          /* unmask interrupt */
    
    /* enable interrupt in NVIC and set priority to 3 */
    NVIC_PRI7_R = 3 << 5;     /* set interrupt priority to 3 */
    NVIC_EN0_R |= (1<<30);  /* enable IRQ30 (D30 of ISER[0]) */
}


int main()
{
 interrupt_init();
 LCD_init();
 keypad_init();
 stopwatchinit();
 LCD_Cmd(clear_display);
 LCD_Cmd(FirstRowPosition0); 
 delay_milli(500);
 
 //LCD_String("omar");
 
 //LCD_Write("A");
 //delay_milli(500);
 

while(1)
    {
    //value =  keypad_getkey(); //get the key pressed value
    //y = value - '0';
    //LCD_Data(value); // display key value on LCD
    //delay_milli(1000);  // delay of one second
    //calculatorbasic();
    //timerSTART(y);
    }
  

  
  
  //return 0;
}
