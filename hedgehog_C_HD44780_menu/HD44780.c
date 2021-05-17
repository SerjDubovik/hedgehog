
#include "HD44780_def.h"
#include <avr/io.h>





void pause_disp(unsigned int time_ms)
{
	extern unsigned int count_timer0;						// внешняя переменная для счётчика времени

	for (count_timer0 = 0;count_timer0 < time_ms;){}		// тупняк-задержка, число сравнения * 0,00102 = время паузы в сек.
}







void strob(unsigned int time_strob)
{
	
		PORT_E |= 1 << PinPort_E;						// E on
		for (char count = 0; count < time_strob; count++) {}	// тупнячок задержка для строба. выяснить почему так много нужно
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
		extern unsigned int strob_war;
		

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

extern unsigned int count_timer0;
extern unsigned int strob_war;
extern unsigned int pause_war;

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





void clear_disp()									// очистка дисплея
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



	void nomb_to_digit (char *pointMas, unsigned int value, unsigned int position)
{
	


	for (char i = position; i > position - 5; i--)
	{
		pointMas[i] = ' ';
	}

    do 
    {
        pointMas[position--] = value % 10 + '0';
    } 
    while ( ( value /= 10 ) > 0 );

//    string[i] = '\0';
    

/*
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
*/

	
}	// скобочка nomb_to_digit



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






void LCD_SendStr_NN(char *str,int coun1, int count2)
{
  char  buf;

  set_bus_disp(data);

	str+=coun1;

  for(;count2 > 0; count2--)
  {
    buf =  *str++;
    send_byte(buf);
  }

}




void LCD_SendStr_Quant(char *str, int count)				// функция вывода строки из ОЗУ по счётчику символов
{
  char  buf;

  set_bus_disp(data);

  for(;count > 0; count--)
  {
    buf =  *str++;
    send_byte(buf);
  }
}



int LCD_SendStr_mark (char *str, int count)	// функция вывода строки из ОЗУ до управляющего символа
{
  char  buf;
  set_bus_disp(data);

	str += count;

  while (*str != '~')
  {
  	count++;
    buf =  *str++;

		if (buf != '#')
		{
	 	   send_byte(buf);
		}
  }

  count++;
  return (count);
}








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








