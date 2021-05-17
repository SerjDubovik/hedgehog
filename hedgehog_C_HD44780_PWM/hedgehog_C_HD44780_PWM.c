#include <avr/io.h>
#include <avr/interrupt.h>

#include "HD44780.h"
#include "HD44780_def.h"
//#include "key_and_joy.h"


//#include ""
//#include ""


#define F_CPU 16000000L




volatile unsigned int count_timer0 = 			0;			// таймер для расчёта пауз
volatile unsigned int count_timer1 = 			0;			// таймер для расчёта пауз видеопамяти


volatile unsigned int strob_war 	= 			40;			// задержка в стробе. число итераций цикла
volatile unsigned int pause_war 	= 			100;		// задержка в стробе
volatile unsigned int virtbyte 		= 			0;			// переменная для передачи команды или данных

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
//volatile unsigned int but_joy_flag	= 			0;			// флаг нажатия кнопки джойстика

volatile unsigned int clamp			=			0;			// защёлка для проходной функции


struct joy_type {

	int button;
	int joy_up, joy_down, joy_left, joy_right;

	int axis_X;
	int axis_Y;

} ;

struct joy_type joy_1;



//


/// прототип функции со структурой. почему-то его нужно объявлять после создания самой структуры.

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

char video_mem[64];		// страница видео памяти 

char * pt_video_mem;	// указатель для смены страниц меню






int main()														// главный цикл
{
asm volatile("sei"); 											//разрешаем глобальное прерывание





// инициализация таймера 0

TIMSK = 1 << TOIE0; 							// запускаем нулевой таймер
TCCR0 = (0<<CS02)|(1<<CS01)|(1<<CS00); 			// делитель частоты на 64.
/*
	; итак что тут у нас:
	; 000 - не тикает
	; 001 - тикает, но без делителя
	; 010 - делим тикание на 8
	; 011 - делим тикание на 64
	; 100 - делим тикание на 256
	; 101 - делим тикание на 1024						
	; 110 - тикаем со входа Т0 по переднему фронту
	; 111 - тикаем со входа Т0 по заднему фронту
*/



// инициализация GPIO


DDR_DB7 |= 1 << DD_DB7;								// PB3 - DB7
DDR_DB6 |= 1 << DD_DB6;								// PB2 - DB6
DDR_DB5 |= 1 << DD_DB5;								// PB1 - DB5
DDR_DB4 |= 1 << DD_DB4;								// PB0 - DB4

DDR_RS |= 1 << DD_RS;								// PC5 - RS 
DDR_RW |= 1 << DD_RW;								// PC4 - R/W
DDR_E |= 1 << DD_E;									// PC3 - E



DDRD |= 1 << DDD2;								// PD2 - светодиод. тест
//PORTD |= 1 << PORTD2;							// зажгли для наглядности и отладки.
//PORTD &= ~(1 << PORTD2); 						// тушим светодиод


DDRA = 0x0;										// PortA на вход
DDRD = 0xFF;									// PortD на выход


DDRC &= ~(1 << DDC0);							// but joy 
PORTC |= 1 << PORTC0;

init_display();									// инициализация дисплея

count_timer0 = 0;								// сбросили таймер для отсчёта интервала





// инициализация АЦП
// 
ADMUX = (0<<REFS1)|(1<<REFS0)|(0<<ADLAR)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0);
ADCSRA = (1<<ADEN)|(1<<ADIE)|(1<<ADSC)|(0<<ADATE)|(3<<ADPS0);
/* 
	; Итак что тут у нас:
	; ADEN = 1 - разрешаем АЦП
	; ADIE = 1 - Разрешаем прерывания. 
	; ADSC = 1 - Запускаем преобразование (первое, дальше автоматом)
	; ADFR = 1 - Непрерывные последовательные преобразования, одно за другим.
	; ADPS2..0 = 3 Делитель частоты на 8 - так у меня получается оптимальная частота.
*/


copy_video_mem(page_menu_2,video_mem);


	for(;;) // бесконечный цикл
	{











		joy(&joy_1);						// проверка состояния джойстика номер 1


		
		if (joy_1.joy_up == 1)				// звёздочка показывает что джойстик установлен в положение
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
		






		if(count_timer1 > 100)				// задержка обновления дисплея
		{

			nomb_to_digit(video_mem, joy_1.axis_X, 12);		// показывает числовле значение оси Х джойстика

			nomb_to_digit(video_mem, joy_1.axis_Y, 27);		// показывает числовое значение оси У джойстика


			display (video_mem);
			count_timer1 = 0;

		} //скобка задержки вывода дисплея

	}	// скобочка бесконечного цикла




}	// скобка мейна


////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////



/*
struct joy_type {						// вот такой должна быть объявлена структура для обработки джойстика

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
			pt_joy->button = 1;			// флажок нажатия кнопки джойстика

		}
		else
		{
			PORTD &= ~(1 << PORTD2); 
			pt_joy->button = 0;
		}
/////////////////////////////////////////





/////////////////////////////////////////////////////////////////////////////////////////////
// Джойстик вверх

	if (pt_joy->axis_X < 300)
	{
		if (flag_axis_X_up == 1)		// выполняется действие оси Х верхнее значение
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
// Джойстик вниз

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
// Джойстик вправо

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
// Джойстик влево

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



} // скобка joy



//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
// до выяснения обстоятельств обработчики прерываний побудут здесь



// обработчики прерываний Timer0.

ISR (TIMER0_OVF_vect)
{
	count_timer0++;								// при 16 мгц и предделителе на 8, каждое переполнение 	это 0,0001275 с.
												//  						 на 64,						зто 0,00102 с.	
	count_timer1++;

}												




ISR(ADC_vect)									// прерывание по окончанию сканирование АЦП
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
	}	// скобочка кейса

switch_var++;

} //скобочка ифа

else
{
	switch_var = 0;
}

// а тут выбор канала нужно организовать автоматически.
ADCSRA = (1<<ADEN)|(1<<ADIE)|(1<<ADSC)|(0<<ADATE)|(2<<ADPS0)	; //Запустили

}





