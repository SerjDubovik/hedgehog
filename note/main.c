

#include <avr/io.h>

char				array_in[10] = {'1','A','3','B','5','C','7','E','9','F'};	
unsigned short		array_mb[10];


void charToHex(char c, char hex[3]);
char hexDigit(unsigned n);

void ascii_to_hex(char*pt_in, unsigned short*pt_out, int count);	// аргументы массив чаров из протокола ascii, выходной собраный массив, кол-во чаров во входном массиве



int main(void)
{

    while (1) 
    {		
		
		
		ascii_to_hex(array_in, array_mb,10);
    }
}





void ascii_to_hex(char*pt_in, unsigned short*pt_out, int count)
{
	for(int i = 0; i < count; i++)
	{
		switch(pt_in[i])
		{
			case '0':{pt_in[i] = 0x0;}break;
			case '1':{pt_in[i] = 0x01;}break;
			case '2':{pt_in[i] = 0x02;}break;
			case '3':{pt_in[i] = 0x03;}break;
			case '4':{pt_in[i] = 0x04;}break;
			case '5':{pt_in[i] = 0x05;}break;
			case '6':{pt_in[i] = 0x06;}break;
			case '7':{pt_in[i] = 0x07;}break;
			case '8':{pt_in[i] = 0x08;}break;
			case '9':{pt_in[i] = 0x09;}break;
			case 'A':{pt_in[i] = 0x0A;}break;
			case 'B':{pt_in[i] = 0x0B;}break;
			case 'C':{pt_in[i] = 0x0C;}break;
			case 'D':{pt_in[i] = 0x0D;}break;
			case 'E':{pt_in[i] = 0x0E;}break;
			case 'F':{pt_in[i] = 0x0F;}break;
		}
	}
	
	for (int i = 0; i < count/2; i++)
	{
		pt_out[i] = pt_in[i*2];
		pt_out[i] = ((pt_out[i] << 4) | pt_in[(i*2)+1]);		// соберём кол-во байт, которое нужно прочитать
	}
}
