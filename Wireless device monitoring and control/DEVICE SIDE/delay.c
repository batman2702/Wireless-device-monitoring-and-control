void delay_ms(unsigned int i)
{
	unsigned int j;
 	for(;i>0;i--)
	    for(j=12000;j>0;j--);
}

void  delay_s(unsigned int  dly)
{  
	unsigned int  i;

   	for(; dly>0; dly--) 
      	for(i=12000000; i>0; i--);
}

