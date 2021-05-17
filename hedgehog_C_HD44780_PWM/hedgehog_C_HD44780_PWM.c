#include <avr/io.h>
#include <avr/interrupt.h>

#include "HD44780.h"
#include "HD44780_def.h"
//#include "key_and_joy.h"


//#include ""
//#include ""


#define F_CPU 16000000L




volatile unsigned int count_timer0 = 			0;			// ������ ��� ������� ����
volatile unsigned int count_timer1 = 			0;			// ������ ��� ������� ���� �����������


volatile unsigned int strob_war 	= 			40;			// �������� � ������. ����� �������� �����
volatile unsigned int pause_war 	= 			100;		// �������� � ������
volatile unsigned int virtbyte 		= 			0;			// ���������� ��� �������� ������� ��� ������

volatile unsigned int ADC_buf		=			0;
volatile unsigned int ADC_flag		=			0;

volatile unsigned int var_1 		= 			0;
volatile unsigned int var_2 		= 			0;
volatile unsigned int var_3 		= 			0;
volatile unsigned int var_4 		= 			0;
volatile unsigned int var_5 		= 			0;
volatile unsigned int var_6 		= 			0;
//volatile unsigned int var_7 		= 			0;			// Axis Y
//volatile unsigned int var_8 		= 			0;			// Axis X

volatile unsigned int switch_var	= 			0;
//volatile unsigned int but_joy_flag	= 			0;			// ���� ������� ������ ���������

volatile unsigned int clamp			=			0;			// ������� ��� ��������� �������


struct joy_type {

	int button;
	int joy_up, joy_down, joy_left, joy_right;

	int axis_X;
	int axis_Y;

} ;

struct joy_type joy_1;



//


/// �������� ������� �� ����������. ������-�� ��� ����� ��������� ����� �������� ����� ���������.

void joy(struct joy_type * pt_joy);


void menu_str_page(unsigned int page, char * pt_mass_string_menu);
void display(char *pt_video_memory);
void copy_video_mem(char *in_mas, char *out_mas);





char str_mas[] = {};

////////////////////////123456789ABCDEF
char page_menu[] 	= {"      **       "
					   "    *    *     "
					   "    *    *     "
					   "      **       "};

////////////////////////123456789ABCDEF
char page_menu_1[] 	= {"               "
					   "      **       "
					   "      **       "
					   "               "};

////////////////////////123456789ABCDEF
char page_menu_2[] 	= {"Axis X:        "
					   "Axis Y:        "
					   "Flags :        "
					   "Button:        "};

char video_mem[64];		// �������� ����� ������ 

char * pt_video_mem;	// ��������� ��� ����� ������� ����






int main()														// ������� ����
{
asm volatile("sei"); 											//��������� ���������� ����������





// ������������� ������� 0

TIMSK = 1 << TOIE0; 							// ��������� ������� ������
TCCR0 = (0<<CS02)|(1<<CS01)|(1<<CS00); 			// �������� ������� �� 64.
/*
	; ���� ��� ��� � ���:
	; 000 - �� ������
	; 001 - ������, �� ��� ��������
	; 010 - ����� ������� �� 8
	; 011 - ����� ������� �� 64
	; 100 - ����� ������� �� 256
	; 101 - ����� ������� �� 1024						
	; 110 - ������ �� ����� �0 �� ��������� ������
	; 111 - ������ �� ����� �0 �� ������� ������
*/



// ������������� GPIO


DDR_DB7 |= 1 << DD_DB7;								// PB3 - DB7
DDR_DB6 |= 1 << DD_DB6;								// PB2 - DB6
DDR_DB5 |= 1 << DD_DB5;								// PB1 - DB5
DDR_DB4 |= 1 << DD_DB4;								// PB0 - DB4

DDR_RS |= 1 << DD_RS;								// PC5 - RS 
DDR_RW |= 1 << DD_RW;								// PC4 - R/W
DDR_E |= 1 << DD_E;									// PC3 - E



DDRD |= 1 << DDD2;								// PD2 - ���������. ����
//PORTD |= 1 << PORTD2;							// ������ ��� ����������� � �������.
//PORTD &= ~(1 << PORTD2); 						// ����� ���������


DDRA = 0x0;										// PortA �� ����
DDRD = 0xFF;									// PortD �� �����


DDRC &= ~(1 << DDC0);							// but joy 
PORTC |= 1 << PORTC0;

init_display();									// ������������� �������

count_timer0 = 0;								// �������� ������ ��� ������� ���������





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


copy_video_mem(page_menu_2,video_mem);


	for(;;) // ����������� ����
	{











		joy(&joy_1);						// �������� ��������� ��������� ����� 1


		
		if (joy_1.joy_up == 1)				// �������� ���������� ��� �������� ���������� � ���������
		{
			video_mem[28] = '*';
		}
		else
		{
			video_mem[28] = ' ';
		}



		if (joy_1.joy_down == 1)
		{
			video_mem[58] = '*';
		}
		else
		{
			video_mem[58] = ' ';
		}



		if (joy_1.joy_left == 1)
		{
			video_mem[42] = '*';
		}
		else
		{
			video_mem[42] = ' ';
		}




		if (joy_1.joy_right == 1)
		{
			video_mem[44] = '*';
		}
		else
		{
			video_mem[44] = ' ';
		}


		if (joy_1.button == 1)
		{
			video_mem[43] = ' ';
		}
		else
		{
			video_mem[43] = '*';
		}
		






		if(count_timer1 > 100)				// �������� ���������� �������
		{

			nomb_to_digit(video_mem, joy_1.axis_X, 12);		// ���������� �������� �������� ��� � ���������

			nomb_to_digit(video_mem, joy_1.axis_Y, 27);		// ���������� �������� �������� ��� � ���������


			display (video_mem);
			count_timer1 = 0;

		} //������ �������� ������ �������

	}	// �������� ������������ �����




}	// ������ �����


////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////



/*
struct joy_type {						// ��� ����� ������ ���� ��������� ��������� ��� ��������� ���������

	int button;
	int joy_up, joy_down, joy_left, joy_right;

	int axis_X;
	int axis_Y;

} joy_1, joy_2
*/


void joy(struct joy_type * pt_joy)
{


	static unsigned int flag_axis_X_up;
	static unsigned int flag_axis_X_down;
	static unsigned int flag_axis_Y_left;
	static unsigned int flag_axis_Y_right;

	


/////////////////////////////////////////	joy bat
		if ((PINC & (1 << PINC0)) == 1)
		{
			PORTD |= 1 << PORTD2;
			pt_joy->button = 1;			// ������ ������� ������ ���������

		}
		else
		{
			PORTD &= ~(1 << PORTD2); 
			pt_joy->button = 0;
		}
/////////////////////////////////////////





/////////////////////////////////////////////////////////////////////////////////////////////
// �������� �����

	if (pt_joy->axis_X < 300)
	{
		if (flag_axis_X_up == 1)		// ����������� �������� ��� � ������� ��������
		{
			flag_axis_X_up = 0;

			pt_joy->joy_up = 1;
		}
	}



	if (pt_joy->axis_X > 400)
	{
		pt_joy->joy_up = 0;

		flag_axis_X_up = 1;
	}
//////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////////////////////////////////////////////////
// �������� ����

	if (pt_joy->axis_X > 800)
	{

		if (flag_axis_X_down == 1)		
		{
			flag_axis_X_down = 0;
			
			pt_joy->joy_down = 1;
		}		

	}



	if (pt_joy->axis_X < 600)
	{
		flag_axis_X_down = 1;

		pt_joy->joy_down = 0;
	}
//////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////
// �������� ������

	if (pt_joy->axis_Y < 300)
	{
		if (flag_axis_Y_right == 1)		
		{
			flag_axis_Y_right = 0;

			pt_joy->joy_right = 1;
		}
	}



	if (pt_joy->axis_Y > 400)
	{
		flag_axis_Y_right = 1;

		pt_joy->joy_right = 0;
	}
//////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////////////////////////////////////////////////
// �������� �����

	if (pt_joy->axis_Y > 800)
	{

		if (flag_axis_Y_left == 1)		
		{
			flag_axis_Y_left = 0;
			
			pt_joy->joy_left = 1;
		}		

	}



	if (pt_joy->axis_Y < 600)
	{
		flag_axis_Y_left = 1;

		pt_joy->joy_left = 0;
	}
//////////////////////////////////////////////////////////////////////////////////////////////



} // ������ joy



//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
// �� ��������� ������������� ����������� ���������� ������� �����



// ����������� ���������� Timer0.

ISR (TIMER0_OVF_vect)
{
	count_timer0++;								// ��� 16 ��� � ������������ �� 8, ������ ������������ 	��� 0,0001275 �.
												//  						 �� 64,						��� 0,00102 �.	
	count_timer1++;

}												




ISR(ADC_vect)									// ���������� �� ��������� ������������ ���
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
			ADMUX = (0<<REFS1)|(1<<REFS0)|(0<<ADLAR)|(0<<MUX3)|(1<<MUX2)|(1<<MUX1)|(0<<MUX0);
		} break;
		case 6:
		{
			joy_1.axis_Y = ADCW;
			//var_7 = ADCW;
			ADMUX = (0<<REFS1)|(1<<REFS0)|(0<<ADLAR)|(0<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0);
		} break;
		case 7:
		{
			joy_1.axis_X = ADCW;
			//var_8 = ADCW;
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
ADCSRA = (1<<ADEN)|(1<<ADIE)|(1<<ADSC)|(0<<ADATE)|(2<<ADPS0)	; //���������

}





