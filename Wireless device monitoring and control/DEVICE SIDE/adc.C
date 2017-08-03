#include <lpc214x.h>


/** ADC READ FUNCTION DEFINATION **/
float read_AD0_chNo1(unsigned char chNo)
{
    unsigned int val;  float val2;
	AD0CR = (0x00210300|chNo);
	AD0CR|= 0x01000000;

	do
	{
		val=AD0DR1;
	}while(!(AD0DR1 & 0x80000000));
	val=AD0DR1;

	val=val>>6;
	val=(val&0x03ff);
	val2=(val*3.300)/1023;
	return val2;
}

/** ADC READ FUNCTION DEFINATION **/
float read_AD0_chNo2(unsigned char chNo)
{
    unsigned int val;  float val2;
	AD0CR = (0x00210300|chNo);
	AD0CR|= 0x01000000;

	do
	{
		val=AD0DR2;
	}while(!(AD0DR2 & 0x80000000));
	val=AD0DR2;

	val=val>>6;
	val=(val&0x03ff);
	val2=(val*3.300)/1023;
	return val2;
}


/** ADC READ FUNCTION DEFINATION **/
float read_AD0_chNo3(unsigned char chNo)
{
    unsigned int val;  float val2;
	AD0CR = (0x00210300|chNo);
	AD0CR|= 0x01000000;

	do
	{
		val=AD0DR3;
	}while(!(AD0DR3 & 0x80000000));
	val=AD0DR3;

	val=val>>6;
	val=(val&0x03ff);
	val2=(val*3.300)/1023;
	return val2;
}
