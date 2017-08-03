#include<LPC214x.h>

#include"delay.h"

/** LCD DATA PINS CONNECTIONS **/
#define lcd_data 0x03fc0000 	//1.18 to 1.25

/** LCD control lines **/
#define RS  (1<<16)	    // p1.16
#define EN	(1<<17)     // p1.17

unsigned char flag=0;  


void write_lcd(char c)
{
  IOPIN1 = c<<18;
    
  if(flag==1)
    IOSET1 = RS;
  else
    IOCLR1 = RS;
		
  IOSET1 = EN;
  delay_ms(1);
  IOCLR1 = EN;
  
  delay_ms(2);
  IOCLR1 = 0x03fc0000;
}

/** COMMAND FUNCTION DEFINATION **/
void cmd_lcd(char cmd)
{
   flag=0;
   write_lcd(cmd); 
}

  /** DISPLAY CHARACTER ON LCD **/
void char_lcd(char c)
{
  flag=1;
  write_lcd(c);		   
}

/** LCD INITIALIZATION FUNCTION DEFINATION **/
void init_lcd()
{
  IODIR1 |= lcd_data | RS | EN;  

  delay_ms(10);
  cmd_lcd(0x38);
  cmd_lcd(0x0C);
  cmd_lcd(0x01);
  cmd_lcd(0x06);
  cmd_lcd(0x80);    
}

/** DISPLAY STRING ON LCD **/
void str_lcd(char *s)
{
  while(*s)
		char_lcd(*s++);
}

/** DISPLAY INTEGER VALUE ON LCD **/				
void int_lcd(unsigned int n)
{
  unsigned char a[10]={0};
  int i=0;
  if(n==0)
  {
    char_lcd('0');
	return;
  }
  else
  {
     while(n>0)
	 {
	   a[i++]=(n%10)+48;
	   n=n/10;
	 }
	 --i;
	 for(;i>=0;i--)
	 {
	   char_lcd(a[i]);
	 }
   }
}

/** DISPLAY FLOAT VALUE ON LCD **/
void float_lcd(float f)
{
  int x;
  double temp;
  x=f;
  int_lcd(x);
  char_lcd('.');
  temp=(f-x)*1000;
  x=temp;
  int_lcd(x);
}

