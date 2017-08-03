#include<lpc214x.h>
#include <string.h>
#include "lcd.h"
#include "delay.h"
#include "uart0.h"
#include "keypad.h"

extern int i;
extern char r_flag,buff[40];

extern char pwd[10],pass1[];

#define buzzer 1<<10 //0.10



main()
{
	unsigned char val,fi;

	PINSEL0 |= 0x00000000;
	IODIR0 |= buzzer;
	
	IOCLR0 = buzzer;    //buzzer off
	
	init_lcd();
	uart0_init();

	cmd_lcd(0x80);
	str_lcd("* Wireless device **");
	cmd_lcd(0xc0);
	str_lcd("**** monitoring ****");
	cmd_lcd(0x94);
	str_lcd("******** and *******");
	cmd_lcd(0xd4);
	str_lcd("***** control ******");

	delay_ms(5000);
	i=0;

	while(1)
	{
		cmd_lcd(0x01);	
		cmd_lcd(0x80);
		str_lcd("Enter Password:");
		cmd_lcd(0xc0);
		password();
		cmd_lcd(0x01);	
		cmd_lcd(0x80);
		str_lcd("Your request is     ");
		cmd_lcd(0xC0);
		str_lcd("processing......... ");
		cmd_lcd(0xd4);
		str_lcd("Please Wait.........");
		delay_ms(1000);
		
		if(strcmp(pwd,pass1) == 0)
		{
			cmd_lcd(0x01);
			cmd_lcd(0x80);
			str_lcd("Password is Correct ");
			delay_ms(500);
			cmd_lcd(0xd4);
			str_lcd("Follow the menu.....");
			delay_ms(1000);
			while(1)
			{
				cmd_lcd(0x01);
				cmd_lcd(0x80);
				str_lcd("1.INFO$-Devicestatus");
				cmd_lcd(0xC0);
				str_lcd("2.BON$-Device ON    ");
				cmd_lcd(0x94);
				str_lcd("3.BOFF$-Device OFF  ");
				cmd_lcd(0xd4);
				str_lcd("4.EXIT");
				do
				{
					val = keyscan();
				}while( (val != '1') && (val != '2') && (val != '3') && (val != '4'));

				cmd_lcd(0x01);
				str_lcd("Sending request.....");
				delay_ms(500);
				if(val == '1')
				{
					uart0_str("INFO$");
				}
				else if(val == '2')
				{
					uart0_str("BON$");
				}
				else if(val == '3')
				{
					uart0_str("BOFF$");
				}
				else if(val == '4')
					break;
				cmd_lcd(0x01);
				str_lcd("Waiting for response");
				i=0;
				while(r_flag==0);
				r_flag=0;
				cmd_lcd(0x01);
				str_lcd(buff);
				delay_ms(1000);
				cmd_lcd(0x94);
				str_lcd("to continue.........");
				cmd_lcd(0xd4);
				str_lcd("press E from keypad ");
				if(keyscan() == 'E')
					continue;
			}	
		}
		else
		{
			cmd_lcd(0xc0);
			str_lcd("Wrong Password");
			for(fi=0;fi<5;fi++)
		    {
			 	IOSET0 = buzzer;
			    delay_ms(200);
			    IOCLR0 = buzzer;
			    delay_ms(1000);
			}

		}

	}

}

