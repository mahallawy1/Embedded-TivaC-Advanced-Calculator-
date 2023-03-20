#include "Stopwatch.h"
#include "lcd.h"
#include "Keypad.h"

#include <stdbool.h>

void stopwatchinit(void){
	
    SYSCTL_RCGCTIMER_R |= 0x01;
    TIMER0_CTL_R = 0x0;
    TIMER0_CFG_R = 0x4; 
    TIMER0_TAMR_R = 0x11;
    TIMER0_TAPR_R |= 0xF4;
    TIMER0_TAILR_R = 0xffff;                     
}

void enableStopwatch(){
        int sec = 0;
	int min = 0;
	int hour = 0;
	unsigned int sw2 = GPIO_PORTF_DATA_R & 0x01;
        while(1)
        {
        LCD_Cmd(clear_display);
        displayTime(sec , min , hour);
        TIMER0_CTL_R |= 0x03;
        bool stopped = false;
		while(getOvrFlwFlg() == false){
		sw2 = GPIO_PORTF_DATA_R & 0x01;
		if(!sw2){
		disableTimer();
						
		stopped = true;
		break;
		}
		}
		if(stopped){
		GPIO_PORTF_DATA_R |= 0xE;
                                        
		break;
		}
					
		if((++sec) == 60) {
		sec = 0;
		if((++min) == 60){
		min = 0;
		hour++;
		}
		}
        }
	
	
}

void disableTimer(){
	TIMER0_CTL_R &= ~(0x01);
	return;
}

void displayTime(int sec, int min, int hour){
	if(hour != 0){
		LCD_Int(hour);
		LCD_Data(':');
	}
	
	if(min != 0){
		LCD_Int(min);
		LCD_Data(':');
	}
	
	LCD_Int(sec);
}

bool getOvrFlwFlg(){
	if((TIMER0_RIS_R & 0x1) != 0){
		TIMER0_ICR_R = 0x1;
		return true;
	}
	else
		return false;

}