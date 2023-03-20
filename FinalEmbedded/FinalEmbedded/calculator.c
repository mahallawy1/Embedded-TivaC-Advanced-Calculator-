#include "calculator.h"

void calculatorbasic(){
  LCD_Cmd(clear_display);
  LCD_Cmd(FirstRowPosition0);
  LCD_String("Calculator Mode");
  delay_milli(3000);
  LCD_Cmd(clear_display);
  LCD_Cmd(FirstRowPosition0);
	int ans = 0;
	int div;
	int a=0,b=0,i=0;
	unsigned char tmp = ' ';	
        unsigned char op;	
	int count;
	unsigned char p[10];
	LCD_Cmd(0x01);
  while(1)
   {
     tmp =  keypad_getkey(); 
		 delay_milli(200);
      if (tmp == '=') break;
      if (tmp == '.') 
      {
	i--;
	LCD_Cmd(0x10);
	LCD_Data(' ');
	LCD_Cmd(0x10);
	LCD_Cmd(0x10);
	continue;
        }
	LCD_Data(tmp);
	p[i++] = tmp;
      if (tmp == '+' || tmp == '-' || tmp == '*'||tmp =='/')  
	{
	op = tmp; 
	}     
	}
	 for(count =0;count<i;count++)
	 {
            if ( p[count] =='+' || p[count] == '-' || p[count] == '*' || p[count] == '/') 
		{
			ans = b;
			b=0;
			continue;
		}
      b = b *10 + ( (int) p[count] -48);  
        }
 switch(op)
    {
            case '+':
                      a = ans + b;
                      break;
            case '-' :
                      a = ans - b;
                      break;
            case '*' :
                      a = ans * b;
                      break; 
            case '/' :				
                      div = ans;
                      a = ans / b;
                      if (b ==0)  { LCD_String("MATH_ERROR");return;}                 
                      break; 
   }	 
    LCD_Cmd(0xC0);
    for(i=0;i<=25;i++)
    LCD_Cmd(0x14);
    if (a < 0)  
        {
	LCD_Data('-');
	delay_milli(100); 
	a= -a;
	}	 
	displaynum(a);
	if ( op == '/' && a == 0 ) { 
		LCD_Data('.');
		delay_milli(100);
            }
	if ( op == '/') 
        {
            div = (div - a * b) * 10000 / b;
            LCD_Data('.');
            delay_milli(100); 
            a = div;
            if (a==0) return;
            LCD_Data('.');
            delay_milli(100); 
	  
    while(a < 1000) 
    {	
	LCD_Data('0');
	delay_milli(200);
	a=a*10;}
	displaynum(div);  
	 }
 }

void displaynum(int n)
{
  unsigned char num[30]; 
	short int count = 0;
        num[0] = '0'; 
	if(n == 0)  
        {
        LCD_Data('0');
        return;
        }
	while(n>0)
	{
       num[count++] = (unsigned char) ( n %10 + 48 );
        n /= 10; 
        }
   for(n=count-1;n>=0;n--) 
   {
       LCD_Data(num[n]);  
       delay_milli(2000);
   }
}
