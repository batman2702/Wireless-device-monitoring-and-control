#include <lpc214x.h>
#include <string.h>

#include "lcd.h"
#include "delay.h"
#include "uart0.h"
#include "adc.h"

extern int i;
extern char r_flag,buff[40];

float val;
void device_status(void);
void send_devicestatus(void);

#define relay 1<<29

/*
int main()
{
	float f;
	int val;
	PINSEL1 |= 0x15400000;
	init_lcd();
	uart0_init();

	cmd_lcd(0x80);
	str_lcd("project");
	delay_ms(1000);

	while(1)
	{
		cmd_lcd(0xc0);
		f=read_AD0_chNo1(1<<1);
		float_lcd(f);
		val=f*1000;	
		cmd_lcd(0x94);	
		int_lcd(val);
		str_lcd(" mV  ");
		delay_ms(1000);
	}
}
*/



int main()
{
	PINSEL1 |= 0x01000000;
	IODIR0 |= relay;
	IOCLR0 = relay;

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
	cmd_lcd(0x01);
	cmd_lcd(0x80);
	str_lcd("********************");
	cmd_lcd(0xc0);
	str_lcd("ADC Result:       ");
	cmd_lcd(0xd4);
	str_lcd("Device Status:     ");
	i=0;
	while(1)
	{
		device_status();

		if(r_flag)
		{
			cmd_lcd(0x94);
			str_lcd(buff);
			delay_ms(300);
			cmd_lcd(0x94);
			str_lcd("                    ");
			r_flag = 0;
			i=0;
			if(strcmp(buff,"INFO") == 0)	
			{
				device_status();
				send_devicestatus();
			}
			else if(strcmp(buff,"BON") == 0)	
			{
				IOSET0 = relay;
				delay_ms(1500);
				device_status();
				send_devicestatus();
			}
			else if(strcmp(buff,"BOFF") == 0)	
			{
				IOCLR0 = relay;
				delay_ms(1500);
				device_status();
				send_devicestatus();
			}
			else
			{
				cmd_lcd(0x94);
				str_lcd("Invalid Message");
				delay_ms(300);
				cmd_lcd(0x94);
				str_lcd("                    ");
			}
		}
	}

}

void device_status()
{
	val = read_AD0_chNo1(1<<1); //0.28
	//delay_ms(1000);
	cmd_lcd(0xCC);
	float_lcd(val);
	str_lcd(" V ");	
	cmd_lcd(0xE3);
	if(val>1.5 && val <=5.0)	
		str_lcd("OFF");
	else
		str_lcd(" ON");	
	delay_ms(1000);
}

void send_devicestatus()
{
	cmd_lcd(0x94);
	str_lcd("sending.............");
	delay_ms(300);
	if(val>1.5 && val <=5.0)
		uart0_str("BOFF$");
	else
		uart0_str("BON$");
	cmd_lcd(0x94);
	str_lcd("                    ");
}
  

