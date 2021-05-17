#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000L

#define adrr_devise 	2						// ����� ����� ���������� � ���� ������
#define leth_array		29						// ������ ������� ��� ��������/����������� ������. ������ ��� �������� ����������� ������ �� ������




// ��������� �������

static unsigned short CRC16(int *puchMsg, unsigned short usDataLen); // ������� ���������� ����������� �����






// ������������� ����������
volatile 	unsigned int 	var_1 					= 0;	// ���������� ��� �������� �������� ���
volatile 	unsigned int 	var_2 					= 0;	// ���������� ��� �������� �������� ���
volatile 	unsigned int 	var_3 					= 0;	// ���������� ��� �������� �������� ���
volatile 	unsigned int 	var_4 					= 0;	// ���������� ��� �������� �������� ���
volatile 	unsigned int 	var_5 					= 0;	// ���������� ��� �������� �������� ���
volatile 	unsigned int 	var_6 					= 0;	// ���������� ��� �������� �������� ���
volatile 	unsigned int 	var_7 					= 0;	// ���������� ��� �������� �������� ���
volatile 	unsigned int 	var_8 					= 0;	// ���������� ��� �������� �������� ���

volatile 	unsigned int 	switch_var				= 0;	// ���������� ��� ����������� ��������� ������������ ��� ���

volatile	char 			flag_UART_in 			= 0;	// ���� ������ ����� ������� �� UART
volatile	char 			count_timer0 			= 0;	// ������ ��� ������� ���� ��� ����� ���������
volatile	char			swith_modbas 			= 0;	// ���������� ������������� ��� ������� �������
	

volatile	int 			buf_UART_RXC 			= 0;	// ���������� ����� ��� �������� ��������� �����
volatile	int 			buf_UART_TXC 			= 0;	// ���������� ����� ��� �������� ����� ��� ��������


volatile	int 			array_modbas_in[60];			// ����� ��� ����� �� �����
volatile	int 			count_modbas_in 		= 0;	// ������� ���-�� �������� ����
volatile	int 			array_modbas_out[60];			// ����� ��� �������� �� �����
volatile	int 			count_modbas_out 		= 0;	// ������� ���-�� ���������� ����
volatile	int 			buffer_index			= 0;	// ������� ��� ��������
volatile	int 			count_transf_array 		= 0;	// ������� ��� ���������� ��������

volatile	int 			array_storage[59] 		= {};	// ������ ��� ��������/���������� ������


volatile	unsigned long 	crc_calc 				= 0;	// ��������� ����������� �����
volatile	unsigned long 	adrr_var 				= 0;	// �������� ����� �� ������� ��������� �� ����. ��� ���������.
volatile	unsigned long 	quantity_byte 			= 0;	// ���-�� ���� ������� ���������� �������� ��� ������� �� ���� �� ������
	
volatile	unsigned int 	crc_read_low 			= 0;	// �������� ���������� ��� ��������� ����������� �����
volatile	unsigned int 	crc_read_high 			= 0;	//
volatile	unsigned int 	crc_calc_low 			= 0;	//
volatile	unsigned int 	crc_calc_high 			= 0;	//

volatile	unsigned int 	buf_probe	 			= 0;	// ��� ��������� �������� ����� � �� �����





// ����������� ���������� UART.

ISR(USART_RXC_vect)								// UART. ���������� ������
{
	array_modbas_in[count_modbas_in] = UDR;		// �������� �������� ����
	count_modbas_in++;							// ����� �� ��������� ������� �������
	count_timer0 = 0;							// �������� ������� �����.
	flag_UART_in = 1;							// ���� ������ ����� �������
}






ISR(USART_UDRE_vect)							// ���������� �� ����������� �������� ������ UART. 
{
	buffer_index++;								// ����������� ������
 	
	if(buffer_index == count_modbas_out)  		// ������ ���� ������? 
		{
			UCSRB &=~(1<<UDRIE);				// ��������� ���������� �� ����������� - �������� ���������
		}
		else 
		{
			UDR = array_modbas_out[buffer_index];			// ����� ������ �� �������. 
		}

}







ISR(USART_TXC_vect)								// ���������� �� ���������� �������� ����� UART.
{

}



// ����������� ���������� Timer0.

ISR (TIMER0_OVF_vect)
{
	count_timer0++;								// ��� 16 ��� � ������������ �� 8, ������ ������������ 	
}												// ��� 0,0001275 �. 



////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

int main()
{
asm volatile("sei"); //��������� ���������� ����������

// ������������� ���������


// ������������� UART

#define baudrate 9600L
#define bauddivider (F_CPU/(16*baudrate)-1)
#define HI(x) ((x)>>8)
#define LO(x) ((x)& 0xFF)

UBRRL = LO(bauddivider);
UBRRH = HI(bauddivider);
UCSRA = 0;										// ��� ����� ���������
UCSRB = 1<<RXEN|1<<TXEN|1<<RXCIE|0<<TXCIE;		// ��� ����� ���������� 
UCSRC = 1<<URSEL|1<<UCSZ0|1<<UCSZ1;				// 8 ���



// ������������� ������� 0

TIMSK = 1 << TOIE0; 							// ��������� ������� ������
TCCR0 = (0<<CS02)|(1<<CS01)|(0<<CS00); 			// �������� ������� �� 8.
/*
	; ���� ��� ��� � ���:
	; 000 - �� ������
	; 001 - ������, �� ��� ��������
	; 010 - ����� ������� �� 8
	; 011 - ����� ������� �� 64
	; 100 - ����� ������� �� 256
	; 101 - ����� ������� �� 1024						!!!
	; 110 - ������ �� ����� �0 �� ��������� ������
	; 111 - ������ �� ����� �0 �� ������� ������
*/


// ������������� ���
// 
ADMUX = (0<<REFS1)|(1<<REFS0)|(0<<ADLAR)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0);
ADCSRA = (1<<ADEN)|(1<<ADIE)|(1<<ADSC)|(0<<ADATE)|(3<<ADPS0);
/* 
	; ���� ��� ��� � ���:
	; ADEN = 1 - ��������� ���
	; ADIE = 1 - ��������� ����������. 
	; ADSC = 1 - ��������� �������������� (������, ������ ���������)
	; ADFR = 1 - ����������� ���������������� ��������������, ���� �� ������.
	; ADPS2..0 = 3 �������� ������� �� 8 - ��� � ���� ���������� ����������� �������.
*/




// ������������� GPIO

DDRA = 0x0;										// PortA �� ����. ��� �������� ���

DDRD |= 1 << DDD2;								// ���������� ��������� � ����������� �� �����.
PORTD &= ~(0 << PORTD2);						// ������ ��� ����������� � �������.
DDRD |= 1 << DDD3;								// ���������� ��������� � ����������� �� �����.
PORTD &= ~(0 << PORTD3);						// ������ ��� ����������� � �������.



//PORTD |= 1 << PORTD2;							// �������� ���������
//PORTD |= 1 << PORTD3;							// �������� ���������

//PORTD &= ~(1 << PORTD2); 						// ����� ���������
//PORTD &= ~(1 << PORTD3); 						// ����� ���������







	for(;;) // ����������� ����
	{


		if (flag_UART_in == 1)					// �������� ����� ������ �����. ������ ����� ������ ������ ����.
			{
				if (count_timer0 >= 20)			// �������� �� ������� �����. ���� ����� �� ����� ��� �����
				{								// ���� ��� �������� 16 �� 0,001041� ������
					flag_UART_in = 0;			// ���������� ���� ������ ������, ��������� � ������� ���������	
					count_timer0 = 0;			// ���������� �������, ���� ����� ������� ������� ������ ����� �����
					swith_modbas = 1;			// ���� ������� ������. ��� ������, ��������� � ��� ���� ������.
					buffer_index = 0;				
				} // ������ �������� ��������

				
			} // ������ �������� ����� ������ �����




		switch (swith_modbas)
			{

				case 1:																// ������ ���� ��������� �������� ����� �� �������
				{	
					if (array_modbas_in[0] == adrr_devise) 							// �������� ������ ����������
					{																// ���� ����� ������, �� ������� ��� � ������ ������
						crc_calc = CRC16(array_modbas_in, (count_modbas_in-2));		// ������� CRC ��������� ������

						crc_read_high = array_modbas_in[count_modbas_in-2]; 		// �������
						crc_read_low = array_modbas_in[count_modbas_in-1];			// �������

						crc_calc_low = ((crc_calc >> 8) & 0x00FF);					// ������� (count_modbas_in+2)
						crc_calc_high = (crc_calc & 0x00FF);						// ������� (count_modbas_in+1)
						
						
						if((crc_read_low == crc_calc_low)&&(crc_read_high == crc_calc_high))// �������� ������������ ����������� �����.
						{															
							
							switch (array_modbas_in[1]) 	// ���� ���������� ����� ������� ������� � ������.
								{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
									case 0x06:				// ������ �������� � ���� ������� �������� (Preset Single Register).
									{
										adrr_var = array_modbas_in[2];								// �������� ����� �� ������� � ���� ����������
										adrr_var = ((adrr_var << 8) | array_modbas_in[3]);

										if (adrr_var <= leth_array)									// �������� ����������� ������ �� ���������� ������
										{
											array_storage[adrr_var * 2] = array_modbas_in[4];		// ����� � ������ ��� �������� ��������� �� ���� �����
											array_storage[(adrr_var * 2)+1] = array_modbas_in[5];

											for(int i = 0; i<= count_modbas_in; i++)				// ��������� ������. ��� ��� ����� ������ ���� ����� �� ��� ������� �����.
											{
												array_modbas_out[i] = array_modbas_in[i];
											}
											
											count_modbas_out = count_modbas_in;
											count_modbas_in = 0;
											swith_modbas = 2; 										// ����������� �� ���������� ������� �����
											

										} // ������ �������� ������ ����������
										else 														// ���� ����� ������� �� �������� ���������, ����� �������� ��� ������
										{
											count_modbas_in = 0;
											swith_modbas = 0;
										} // else ������ 

									} // ������ ������� 0�06
									break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
									case 0x10:	// ������ �������� � ��������� ��������� �������� (Preset Multiple Registers)
									{
										adrr_var = array_modbas_in[2];								// �������� ����� �� ������� � ���� ����������
										adrr_var = ((adrr_var << 8) | array_modbas_in[3]);

										if (array_modbas_in[5] == 2) 								// �������� ���-�� ���� � �����. ���� �� 2, �� � ��� ����� ������, � �� ���� ��� �� ������������, ������� � �������
										{
											if (adrr_var + (array_modbas_in[6]/2) <= leth_array)	// �������� ����������� ������ �� ���������� ������
											{
												adrr_var *= 2;

												for (int i =0; array_modbas_in[6] > i ; i++)
												{
													array_storage[adrr_var] = array_modbas_in[(7+i)];	//
													adrr_var++;
												} // ������ �����


												array_modbas_out[0] = array_modbas_in[0];
												array_modbas_out[1] = array_modbas_in[1];
												array_modbas_out[2] = array_modbas_in[2];
												array_modbas_out[3] = array_modbas_in[3];
												array_modbas_out[4] = array_modbas_in[4];
												array_modbas_out[5] = array_modbas_in[5];


												crc_calc = CRC16(array_modbas_out, 6);				// ������� CRC ������������� ������, 3 ����� ��������� ����� � ����� ��������� , ������� �� ����� � ����������

												crc_calc_low = ((crc_calc >> 8) & 0x00FF);			// ������� (count_modbas_in+2)
												crc_calc_high = (crc_calc & 0x00FF);				// ������� (count_modbas_in+1)

												array_modbas_out[6] = crc_calc_high;				// ���������� ����������, ����� � ������ ��� ��������
												array_modbas_out[7] = crc_calc_low;													
												

												count_modbas_out = 8;								// ����� ������ ����� 8 ����
												count_modbas_in = 0;
												swith_modbas = 2; 	
											} // ������ �������� ������ ����������
											else
											{
												count_modbas_in = 0;
												swith_modbas = 0;
											} // else ������ �������� ������ ����������
										} // �������� �������� ������� ���� � �����.
										else
										{
											count_modbas_in = 0;
											swith_modbas = 0;
										} // �������� else �������� ������� ���� � �����

									} // ������ ������� 0�10
									break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
									case 0x03:				// ������ �������� �� ���������� ��������� �������� (Read Holding Registers).
									{
										adrr_var = array_modbas_in[2];										// �������� ����� �� ������� � ���� ����������
										adrr_var = ((adrr_var << 8) | array_modbas_in[3]);

										quantity_byte = array_modbas_in[4];
										quantity_byte = ((quantity_byte << 8) | array_modbas_in[5]);		// ������ ���-�� ����, ������� ����� ���������


										if ((adrr_var <= leth_array) || ((adrr_var + quantity_byte) <= leth_array))	// �������� ����������� ������ ������ �� ���������� ������.
										{
											array_modbas_out[0] = array_modbas_in[0];						// ����� ������, ������� �������� �� ������
											array_modbas_out[1] = array_modbas_in[1];						// ��� �������, �� ������� �������� ����� (0�3 ��������� � ���� ������)
											array_modbas_out[2] = quantity_byte * 2;						// ����������� ����, ������� �������. ���������� 2 �����, ���� ��������, ������� �� ����� ����� � ���� ����� �������� ����� 255-�� ����

											adrr_var *= 2;													// ����� � ��� ���� �������, ����� ������� �� ����� � �������, �������� �� ��� (��� ��������)
											quantity_byte *= 2;

											for (int i = 0; i <= quantity_byte; i++)
											{
												array_modbas_out[i+3] = array_storage[adrr_var];			// ������ �� ������� �������� � ���� �� ���������� ������
												adrr_var++;
											}

																											// � ����� �� ��� �����

											crc_calc = CRC16(array_modbas_out, (quantity_byte + 3));		// ������� CRC ������������� ������, 3 ����� ��������� ����� � ����� ��������� , ������� �� ����� � ����������

											crc_calc_low = ((crc_calc >> 8) & 0x00FF);						// ������� (count_modbas_in+2)
											crc_calc_high = (crc_calc & 0x00FF);							// ������� (count_modbas_in+1)

											array_modbas_out[(quantity_byte + 3)] = crc_calc_high;			// ���������� ����������, ����� � ������ ��� ��������
											array_modbas_out[(quantity_byte + 3)+1] = crc_calc_low;			// 

											count_modbas_out = (quantity_byte + 3)+2;
											count_modbas_in = 0;
											swith_modbas = 2; 			// ����������� �� ���������� ������� �����

										} // ������ �������� ������ ����������
										else // ���� ����� ������� �� �������� ���������, ����� �������� ��� ������
										{
											count_modbas_in = 0;
											swith_modbas = 0;
										} // else ������
									} // ������ ������� 0�03
									break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
									case 0x04:				// ������ �������� �� ���������� ��������� ����� (Read Input Registers).
									{

									} // ������ ������� 0�04
									break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								} // ������ ����� ������� ������ �� �������. 



							PORTD &= ~(1 << PORTD3); 								// ����� ���������. �������. ���������� ��� ����������� ����� �������������.
						} // ������ �������� ���������� ��������� crc

						else
						{
							swith_modbas = 0; 										// ������� � ���� ��������� ��������� ��������.
							count_modbas_in = 0;
							PORTD |= 1 << PORTD3;									// �������� ���������. �������. ���������� ��� ����������� ����� �� �������
						} // else ������ �������� ���������� ��������� crc

/*						

						// �������� ���� ����. ����� � ����� �� ����� ���������� � �������� ����������� ���
						array_modbas_out[0] =  (crc_calc & 0x00FF);					// ������� (count_modbas_in+1)
						array_modbas_out[1] =  ((crc_calc >> 8) & 0x00FF);			// ������� (count_modbas_in+2)

						array_modbas_out[2] =	array_modbas_in[count_modbas_in-2]; // �������
						array_modbas_out[3] =	array_modbas_in[count_modbas_in-1];	// �������


						count_modbas_out = 4;		// ��� ����� ������� ������ ���-�� ���� � �������

*/


					} // ������ �������� ������


					else
					{
						swith_modbas = 0; 		// ���� ����� �� ���������, �� ������ ���� �� ��������� �����, ������� �� �����
						count_modbas_in = 0;
					} // else ������ �������� ������



				} // �������� ������� �����
				break;
				case 2:							// ������ ���� ��������� ����� �� �������� �����
				{

					
					buffer_index=0;				// ���������� ������
					UDR = array_modbas_out[0];	// ���������� ������ ���� �� ������� ��� ��������
					UCSRB|=(1<<UDRIE);			// ��������� ���������� UDRE

					swith_modbas = 0; 			// ���������� ���� � ������ � �� ������� ����
				} // �������� ������� �����
				break;
				case 3: // ���� ������, ���� �������� ��� ����������� ������. ����������!!!!
				{
					//swith_modbas = 0;
				}
				break;

				default:
				{
				}
			
			} // ������ �����

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��� ������������� ��������� ������ �����

/*
array_storage[30] =	array_storage[0];
array_storage[31] =	array_storage[1];							// ���������� ���������� ��� �������� �������� �� �����
array_storage[32] =	array_storage[2];
array_storage[33] =	array_storage[3];
array_storage[34] =	array_storage[4];
array_storage[35] =	array_storage[5];
array_storage[36] =	array_storage[6];
array_storage[37] =	array_storage[7];
array_storage[38] =	array_storage[8];
array_storage[39] =	array_storage[9];
array_storage[40] =	array_storage[10];
array_storage[41] =	array_storage[11];
array_storage[42] =	array_storage[12];
array_storage[43] =	array_storage[13];
array_storage[44] =	array_storage[14];

array_storage[45] =	array_storage[15];
array_storage[46] =	array_storage[16];							// ���������� ���������� ��� �������� �������� �� �����
array_storage[47] =	array_storage[17];
array_storage[48] =	array_storage[18];
array_storage[49] =	array_storage[19];
array_storage[50] =	array_storage[20];
array_storage[51] =	array_storage[21];
array_storage[52] =	array_storage[22];
array_storage[53] =	array_storage[23];
array_storage[54] =	array_storage[24];
array_storage[55] =	array_storage[25];
array_storage[56] =	array_storage[26];
array_storage[57] =	array_storage[27];
array_storage[58] =	array_storage[28];
array_storage[59] =	array_storage[29];
*/


array_storage[0] = ((var_1 >> 8) & 0x00FF);				
array_storage[1] = (var_1 & 0x00FF);


array_storage[2] = ((var_2 >> 8) & 0x00FF);				
array_storage[3] = (var_2 & 0x00FF);

buf_probe	=	var_3;

array_storage[4] = ((buf_probe >> 8) & 0x00FF);				
array_storage[5] = (buf_probe & 0x00FF);

buf_probe	=	var_4;

array_storage[6] = ((buf_probe >> 8) & 0x00FF);				
array_storage[7] = (buf_probe & 0x00FF);

buf_probe	=	var_5;

array_storage[8] = ((buf_probe >> 8) & 0x00FF);				
array_storage[9] = (buf_probe & 0x00FF);

buf_probe	=	var_6;

array_storage[10] = ((buf_probe >> 8) & 0x00FF);				
array_storage[11] = (buf_probe & 0x00FF);

buf_probe	=	var_7;

array_storage[12] = ((buf_probe >> 8) & 0x00FF);				
array_storage[13] = (buf_probe & 0x00FF);

buf_probe	=	var_8;

array_storage[14] = ((buf_probe >> 8) & 0x00FF);				
array_storage[15] = (buf_probe & 0x00FF);



		if (count_timer0 > 127)					// �������� ����, ���������� ��� ������ 0 �������
			{
				PORTD |= 1 << PORTD2;			// �������� ���������
			}
		else
			{
				PORTD &= ~(1 << PORTD2); 		// ����� ���������
			}
			


	}	//������ ������������ �����





	return 0;
}// ������ �����

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


// ������� ��� ������� ����������� �����
static unsigned short CRC16(int *puchMsg,  /* ���������       */
                            unsigned short usDataLen /* ����� ��������� */)
{
    unsigned short crc = 0xFFFF;
    unsigned short uIndex;
    int i;
    for (uIndex = 0; uIndex < usDataLen; uIndex += 1) {
        crc ^= (unsigned short)*(puchMsg + uIndex);
        for (i = 8; i != 0; i -= 1) {
          if ((crc & 0x0001) == 0) { crc >>= 1; }
          else { crc >>= 1; crc ^= 0xA001; }			// ������� ����� �����
        }
    }
    // ������� ������� ���������� ����
 //   crc = ((crc >> 8) & 0x00FF) | ((crc << 8) & 0xFF00);
    return crc;
}





// ���������� ���������� ������������ ���
ISR(ADC_vect)									
{	
	
if (switch_var <= 7)
{

	switch (switch_var)
	{
		case 0:
		{
			var_1 = ADCW;
			ADMUX = (0<<REFS1)|(1<<REFS0)|(0<<ADLAR)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(1<<MUX0);
		} break;
		case 1:
		{
			var_2 = ADCW;
			ADMUX = (0<<REFS1)|(1<<REFS0)|(0<<ADLAR)|(0<<MUX3)|(0<<MUX2)|(1<<MUX1)|(0<<MUX0);
		} break;
		case 2:
		{
			var_3 = ADCW;
			ADMUX = (0<<REFS1)|(1<<REFS0)|(0<<ADLAR)|(0<<MUX3)|(0<<MUX2)|(1<<MUX1)|(1<<MUX0);
		} break;
		case 3:
		{
			var_4 = ADCW;
			ADMUX = (0<<REFS1)|(1<<REFS0)|(0<<ADLAR)|(0<<MUX3)|(1<<MUX2)|(0<<MUX1)|(0<<MUX0);
		} break;
		case 4:
		{
			var_5 = ADCW;
			ADMUX = (0<<REFS1)|(1<<REFS0)|(0<<ADLAR)|(0<<MUX3)|(1<<MUX2)|(0<<MUX1)|(1<<MUX0);
		} break;
		case 5:
		{
			var_6 = ADCW;
			ADMUX = (0<<REFS1)|(1<<REFS0)|(1<<ADLAR)|(0<<MUX3)|(1<<MUX2)|(1<<MUX1)|(0<<MUX0);
		} break;
		case 6:
		{
			var_7 = ADCH;
			ADMUX = (0<<REFS1)|(1<<REFS0)|(1<<ADLAR)|(0<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0);
		} break;
		case 7:
		{
			var_8 = ADCH;
			ADMUX = (0<<REFS1)|(1<<REFS0)|(0<<ADLAR)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0);
		} break;
	}	// �������� �����

switch_var++;

} //�������� ���

else
{
	switch_var = 0;
}

// � ��� ����� ������ ����� ������������ �������������.
ADCSRA = (1<<ADEN)|(1<<ADIE)|(1<<ADSC)|(0<<ADATE)|(5<<ADPS0)	; //���������

}


