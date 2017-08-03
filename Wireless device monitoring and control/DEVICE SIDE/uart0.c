#include<lpc214x.h>

#include "delay.h"

#define UART0_INT_ENABLE 1

char buff[40],dummy,r_flag,ch;
int i=0,l;

void UART0_isr(void) __irq
{
	if((U0IIR & 0x04)) //check if receive interrupt
	{
		ch = U0RBR;   /* Read to Clear Receive Interrupt */
		if(ch == '$')
		{
			r_flag=1;
			buff[i] = '\0';   
			i=0;
		}
		else
			buff[i++] = ch;
	}
	else
	{
		dummy=U0IIR; //Read to Clear transmit interrupt
	}
	VICVectAddr = 0; /* dummy write */
}
void uart0_init(void) /* Initialize Serial Interface       */ 
{            		
	PINSEL0 |= 0x00000005; /* Enable RxD0 and TxD0              */
	U0LCR = 0x83;         /* 8 bits, no Parity, 1 Stop bit     */
	U0DLL = 97;           /* 9600 Baud Rate @ CCLK/4 VPB Clock  */
	U0LCR = 0x03;         /* DLAB = 0  */
	
	#if UART0_INT_ENABLE > 0
	
	VICIntSelect = 0x00000000; // IRQ
	VICVectAddr0 = (unsigned)UART0_isr;
	VICVectCntl0 = 0x20 | 6; /* uart0 Interrupt */
	VICIntEnable = 1 << 6;   /* Enable uart0 Interrupt */
	U0IER = 0x01;       /* Enable uart0 RX */ 
	#endif
}

void uart0_tx(char ch)  /* Write character to Serial Port    */  
{ 
	while (!(U0LSR & 0x20));
	U0THR = ch;                
}

char uart0_rx(void)    /* Read character from Serial Port   */
{                     
	while (!(U0LSR & 0x01));
	return (U0RBR);
}


void uart0_str(char *s)
{
   	while(*s)
   	{
       uart0_tx(*s++);
	   delay_ms(300);
	}
}

/** DISPLAY INTEGER VALUE ON LCD **/				
void uart0_int(unsigned int n)
{
  unsigned char a[10]={0};
  int i=0;
  if(n==0)
  {
    uart0_tx('0');
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
	   uart0_tx(a[i]);
	 }
   }
}

/** DISPLAY FLOAT VALUE ON LCD **/
void uart0_float(float f)
{
  int x;
  double temp;
  x=f;
  uart0_int(x);
  uart0_tx('.');
  temp=(f-x)*1000;
  x=temp;
  uart0_int(x);
}




