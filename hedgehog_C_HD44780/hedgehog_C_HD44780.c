#include <avr/io.h>
#include <avr/interrupt.h>
#include "HD44780_def.h"
//#include "HD44780_func.h"


#define F_CPU 16000000L


/* записки себе буду оставлять здесь
*/



// прототипы функций
void init_display();													// инициализация дисплея
void pause_disp(unsigned int time_ms);									// тупняк в функции инициализации
void strob(unsigned int time_strob);									// строб с тупняком внутри
void read_write(unsigned int set);
void set_bus_disp(unsigned int set);
void send_byte(unsigned int virtbyte);
void clear_disp();
void setCursor (int line_cursor,int position_cursor);
void nomb_to_digit (char *pointMas, unsigned int n);
void LCD_SendStr(char *str);
void DBG_SendValue( unsigned int value );



volatile unsigned long int count_timer0 = 		0;			// таймер для расчёта пауз
volatile unsigned int strob_war 	= 			1;			// задержка в стробе
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
volatile unsigned int var_7 		= 			0;
volatile unsigned int var_8 		= 			0;

volatile unsigned int switch_var	= 			0;

volatile unsigned int count_X		= 			0;
volatile unsigned int count_Y		= 			0;
volatile unsigned int count_pause_var = 		0;


char str_mas[] = {};
char str_mas_1[] = {"Axis X:"};
char str_mas_2[] = {"Axis Y:"};
char str_mas_3[] = {"3:"};
char str_mas_4[] = {"4:"};





// обработчики прерываний Timer0.

ISR (TIMER0_OVF_vect)
{
	count_timer0++;								// при 16 мгц и предделителе на 8, каждое переполнение 	это 0,0001275 с.
}												//  						 на 64,						зто 0,00102 с.




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
			var_7 = ADCW;
			ADMUX = (0<<REFS1)|(1<<REFS0)|(0<<ADLAR)|(0<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0);
		} break;
		case 7:
		{
			var_8 = ADCW;
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



int main()
{
asm volatile("sei"); //разрешаем глобальное прерывание



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
PORTD |= 1 << PORTD2;							// зажгли для наглядности и отладки.
//PORTD &= ~(1 << PORTD2); 						// тушим светодиод


DDRA = 0x0;										// PortA на вход
DDRD = 0xFF;									// PortD на выход


DDRC &= ~(1 << DDC0);							// but joy 
PORTC |= 1 << PORTC0;










init_display();									// инициализация дисплея



setCursor(0,0);
LCD_SendStr(str_mas_1);

setCursor(1,0);
LCD_SendStr(str_mas_2);

setCursor(2,0);
LCD_SendStr(str_mas_3);

setCursor(3,0);
LCD_SendStr(str_mas_4);



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



	for(;;) // бесконечный цикл
	{




setCursor(0,11);
set_bus_disp(data);
send_byte(0x10);

		setCursor(0,8);
		DBG_SendValue(var_8);		// X

setCursor(1,11);
set_bus_disp(data);
send_byte(0x10);


		setCursor(1,8);
		DBG_SendValue(var_7);		// Y




		setCursor(2,3);
		DBG_SendValue(count_X);		// count X


		setCursor(3,3);
		DBG_SendValue(count_Y);		// count Y



		if ((PINC & (1 << PINC0)) == 1)
		{
			PORTD |= 1 << PORTD2;
		}
		else
		{
			PORTD &= ~(1 << PORTD2); 
		}







			if (var_8 <500)
			{
				if (var_8 < 100)
				{
				count_X++;
/*
				setCursor(2,3);
				set_bus_disp(data);
				send_byte(0x10);
				send_byte(0x10);
				send_byte(0x10);
				send_byte(0x10);
				send_byte(0x10);
*/
				}


				else
				{
					if (count_pause_var > 10000)
					{
						count_pause_var = 0;
						count_X++;
					}
					else
					{
						count_pause_var++;
					}
					
				}

			}


			if (var_8 > 600)
			{
				if (var_8 > 900)
				{

					count_X--;
/*
				setCursor(2,3);
				set_bus_disp(data);
				send_byte(0x10);
				send_byte(0x10);
				send_byte(0x10);
				send_byte(0x10);
				send_byte(0x10);
*/
				}

				else
				{
					if (count_pause_var > 10000)
					{
						count_pause_var = 0;
						count_X--;
					}
					else
					{
						count_pause_var++;
					}
				}

			}
		
		
		//count_X
		//count_Y
			
	} //скобочка бесконечного цикла

} //скобочка главной функции










void pause_disp(unsigned int time_ms)
{
	for (count_timer0 = 0;count_timer0 < time_ms;){}		// тупняк-задержка, число сравнения * 0,00102 = время паузы в сек.
}




void strob(unsigned int time_strob)
{
	PORT_E |= 1 << PinPort_E;						// E on
	pause_disp(time_strob);
	PORT_E &= ~(1 << PinPort_E);					// E off
}




void set_bus_disp(unsigned int set)
{
	if (set != data)
	{
		PORT_RS &= ~(1 << PinPort_RS); 				// команда
	}
	else
	{
		PORT_RS |= 1 << PinPort_RS;					// данные
	}	
}



void read_write(unsigned int set)
{
	if (set != read_disp)			
	{
		PORT_RW &= ~(1 << PinPort_RW);				// запись в дисплей
	}
	else
	{
		PORT_RW |= 1 << PinPort_RW;					// чтение из дисплея
	}	
}




void send_byte(unsigned int virtbyte)
{
	
		

		if ( ( virtbyte & 1<<7 ) == 0)
		{
			PORT_DB7 &= ~(1 << PinPort_DB7);		//reset
		}
		else
		{
			PORT_DB7 |= 1 << PinPort_DB7;			//set
		}
		//////////////////////////////////////////
		if ( ( virtbyte & 1<<6 ) == 0)
		{
			PORT_DB6 &= ~(1 << PinPort_DB6);		//reset
		}
		else
		{
			PORT_DB6 |= 1 << PinPort_DB6;			//set
		}
		//////////////////////////////////////////
		if ( ( virtbyte & 1<<5 ) == 0)
		{
			PORT_DB5 &= ~(1 << PinPort_DB5);			//reset
		}
		else
		{
			PORT_DB5 |= 1 << PinPort_DB5;			//set
		}
		//////////////////////////////////////////
		if ( ( virtbyte & 1<<4 ) == 0)
		{
			PORT_DB4 &= ~(1 << PinPort_DB4);		//reset
		}
		else
		{
			PORT_DB4 |= 1 << PinPort_DB4;			//set
		}
		//////////////////////////////////////////



	strob(strob_war);


		if ( ( virtbyte & 1<<3 ) == 0)
		{
			PORT_DB7 &= ~(1 << PinPort_DB7);		//reset
		}
		else
		{
			PORT_DB7 |= 1 << PinPort_DB7;			//set
		}
		//////////////////////////////////////////
		if ( ( virtbyte & 1<<2 ) == 0)
		{
			PORT_DB6 &= ~(1 << PinPort_DB6);		//reset
		}
		else
		{
			PORT_DB6 |= 1 << PinPort_DB6;			//set
		}
		//////////////////////////////////////////
		if ( ( virtbyte & 1<<1 ) == 0)
		{
			PORT_DB5 &= ~(1 << PinPort_DB5);		//reset
		}
		else
		{
			PORT_DB5 |= 1 << PinPort_DB5;			//set
		}
		//////////////////////////////////////////
		if ( ( virtbyte & 1<<0 ) == 0)
		{
			PORT_DB4 &= ~(1 << PinPort_DB4);		//reset
		}
		else
		{
			PORT_DB4 |= 1 << PinPort_DB4;			//set
		}
		//////////////////////////////////////////


	strob(strob_war);


}



void init_display()

{

// инициализация дисплея


pause_disp(400);

PORT_RS &= ~(1 << PinPort_RS);						// RS off 		Команда
PORT_RW &= ~(1 << PinPort_RW);						// R/W off		Запись

PORT_DB7 &= ~(1 << PinPort_DB7);					// DB7 off
PORT_DB6 &= ~(1 << PinPort_DB6);					// DB6 off
PORT_DB5 |= 1 << PinPort_DB5;						// DB5 on					 
PORT_DB4 |= 1 << PinPort_DB4;						// DB4 on					

strob(strob_war);
pause_disp(400);				
strob(strob_war);
pause_disp(200);
strob(strob_war);
pause_disp(100);



/////// базовые три команды закончились		0x32 0x28 0xF 0x1 0x6

send_byte(0x32);
pause_disp(pause_war);
send_byte(0x28);
pause_disp(pause_war);
send_byte(0xC);
pause_disp(pause_war);
send_byte(0x1);
pause_disp(pause_war);
send_byte(0x6);
pause_disp(pause_war);

}	// скобка init_display





void clear_disp()											// очистка дисплея
{
	set_bus_disp(command);
	send_byte(0x1);
}





void setCursor (int line_cursor,int position_cursor)
{

set_bus_disp(command);

					switch (line_cursor)
					{
						case 0: 
							{
								if (position_cursor <= 15)
								{
									position_cursor += 128;
									send_byte(position_cursor);
								}
								
							}
							break;
						case 1:
							{
								if (position_cursor <= 15)
								{
									position_cursor += 192;
									send_byte(position_cursor);
								}
							}
							break;
						case 2:
							{
								if (position_cursor <= 15)
								{
									position_cursor += 144;
									send_byte(position_cursor);
								}
							}
							break;
						case 3:
							{
								if (position_cursor <= 15)
								{
									position_cursor += 208;
									send_byte(position_cursor);
								}
							}
							break;
								
						default :;
					}
}	// скобка setCursor

// 1 	2  3  4  5  6  7  8  9  10 11 12 13 14 15 16			// адреса знакомест для 4-х строчного дисплея

// 80 81 82 83 84 85 86 87 88 89 8A 8B 8C 8D 8E 8F 				// 
// C0 C1 C2 C3 C4 C5 C6 C7 C8 C9 CA CB CC CD CE CF				// 
// 90 91 92 93 94 95 96 97 98 99 9A 9B 9C 9D 9E 9F				// 
// D0 D1 D2 D3 D4 D5 D6 D7 D8 D9 DA DB DC DD DE DF				// 



	void nomb_to_digit (char *pointMas, unsigned int n)
{
	
	unsigned int b = 10000;
	unsigned int c = 0;
	unsigned int count_mas = 0;		
	
	for (unsigned int i = 0; i<10; i++)
		{
			while (n >= b)
			{
			n = n - b;
			c++;
			}
				if (c != 0)
				{
						c = c+0x30;					
						pointMas[count_mas] = c;
						count_mas++;	
				}
						
			b = b/10; 
			c  = 0;
		}
			pointMas[count_mas] = 0;			
}	// скобочка nomb_to_digit







void DBG_SendValue( unsigned int value )  // раскладывает число на цифры и отправляет на экран

{    

   unsigned char  i       = 0;
   unsigned char  pos     = 0;
   unsigned char  chbuf;
   unsigned char  string[16];

    do 
    {
        string[i++] = value % 10 + '0';
    } 
    while ( ( value /= 10 ) > 0 );

    string[i] = '\0';
    
    for(unsigned char i = 0; i < 16; i++ )
    {
        if( string[i] != 0 )
        {
            pos++;
        }
        else
        {
            break;
        }
    }

    for (unsigned char i = 0, j = pos-1; i < j; i++, j-- )
    {
        chbuf = string[i];
        string[i] = string[j];
        string[j] = chbuf;
    }


	LCD_SendStr(string);		// выводим на экран
}





void LCD_SendStr(char *str)				// функция вывода строки из ОЗУ
{
  char  buf;

  set_bus_disp(data);

  while (*str)
  {
    buf =  *str++;
    send_byte(buf);
  }
}





