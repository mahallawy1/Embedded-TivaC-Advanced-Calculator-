#include "Keypad.h"
#include "lcd.h"

unsigned  char symbol[RowsSize][ColsSize] = {
                                                {'1', '2',  '3', '+'},      
                                                {'4', '5',  '6', '-'},      
                                                {'7', '8',  '9', '/'},      
                                                {'.', '0',  '*', '='}
};

void keypad_init(void)
{
  SYSCTL_RCGCGPIO_R |= 0x08;
	while((SYSCTL_PRGPIO_R & 0x08)==0){}
	GPIO_PORTD_CR_R |= 0x0F;
	GPIO_PORTD_PDR_R |= 0x0F;
	GPIO_PORTD_DEN_R |= 0x0F;
	GPIO_PORTD_DIR_R |= 0x0F;
	GPIO_PORTD_PCTL_R &=~ 0x0F;
	GPIO_PORTD_AMSEL_R &=~ 0x0F;
	GPIO_PORTD_AFSEL_R &=~ 0x0F;

        
  SYSCTL_RCGCGPIO_R |= 0x10;
	while((SYSCTL_PRGPIO_R & 0x10)==0){}
	GPIO_PORTE_CR_R |= 0x0F;
	GPIO_PORTE_PDR_R |= 0x0F;
	GPIO_PORTE_DEN_R |= 0x0F;
	GPIO_PORTE_DIR_R &=~ 0x0F;
	GPIO_PORTE_PCTL_R &=~ 0x0F;
	GPIO_PORTE_AMSEL_R &=~ 0x0F;
	GPIO_PORTE_AFSEL_R &=~ 0x0F;
}

char keypad_getkey(void)
{
	int i,j;
	//short c = 0;
        
        while(1)
        {
          for(i = 0; i < ColsSize; i++)    //Scan columns loop
          {
		GPIO_PORTD_DATA_R = (1U << (i));
		delay_micro(2);
		for(j = 0; j < RowsSize; j++)  //Scan rows loop
		{
			if((GPIO_PORTE_DATA_R & 0x0F) & (1U << (j)))
			{
				return symbol[j][i];		//c = symbol pressed on keypad
			}
		}
          }
        }
	//return c;
}