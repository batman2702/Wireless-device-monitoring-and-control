#include<lpc214x.h>

#include "lcd.h"
#include "delay.h"

/** KEYPAD PORT PIN DEFINATIONS **/
#define c0 (IOPIN0 &(1<<16))
#define c1 (IOPIN0 &(1<<17))
#define c2 (IOPIN0 &(1<<18))
#define c3 (IOPIN0 &(1<<19))
#define r0 (1<<20)
#define r1 (1<<21)
#define r2 (1<<22)
#define r3 (1<<23)

#define COL_MASK (c0!=0)&&(c1!=0)&&(c2!=0)&&(c3!=0)
#define ROW_MASK r0|r1|r2|r3

/** KEYPAD ARRAY DEFINATION **/
unsigned char keypad[4][4]={ '1','2','3','A',
                             '4','5','6','B',
                             '7','8','9','C',
                             'E','0','F','D'}; 

/** VARIABLES DECLARATION **/
char j,pwd[10],pass1[]="12345";

/** KEYPAD ARRAY SCAN FUNCTION DEFINATION **/							
unsigned char keyscan(void)
{
//LOCAL VARIABLES DECLARATION
 	unsigned char keyVal;
  	unsigned int row;	
	
	IODIR0  |= ROW_MASK;//SELECTING ROWS AS O/P  
  	   
  	IOCLR0=ROW_MASK; 
  	while(COL_MASK);
	IOSET0|=r1|r2|r3;
   	IOCLR0|=r0;
	if(!(COL_MASK))  
	{
		row=0;
		goto ColCheck;
	}
   	IOSET0|=r0|r2|r3;
   	IOCLR0|=r1;
	if(!(COL_MASK))  
	{
		row=1;
		goto ColCheck;
	}
	IOSET0|=r0|r1|r3;
   	IOCLR0|=r2;
	if(!(COL_MASK))  
	{
	 	row=2;
	 	goto ColCheck;
	}
	IOSET0|=r0|r1|r2;
   	IOCLR0|=r3;
	if(!(COL_MASK))	
	 	row=3;
	
ColCheck:
    if(c0==0)
	     keyVal=keypad[row][0];
	else if(c1==0)
	     keyVal=keypad[row][1];
	else if(c2==0)
	     keyVal=keypad[row][2];
	else if(c3==0)
	     keyVal=keypad[row][3];
 	
	while((COL_MASK)==0);
	return(keyVal);
}


/** PASSWORD FUNCTION DEFINATION **/
void password(void)       //PASSWORD CHECKING
{
	char i=0;
	while(1)
	{
		j=keyscan();
		if(j=='E')
			break;
		if(j=='C')
		{
			if(i!=0)
			{
				--i;
				cmd_lcd(0x10);
				char_lcd(' ');
				cmd_lcd(0x10);
			}
		}
		else
		{
			pwd[i++]=j;
			char_lcd('*');
		}
	}
	pwd[i]='\0'; 
} 




