
#include "HD44780_def.h"
#include <avr/io.h>







void init_display()

{

extern unsigned int count_timer0;
extern unsigned int strob_war;
extern unsigned int pause_war;

// инициализаци€ диспле€

pause_disp(400);

PORT_RS &= ~(1 << PinPort_RS);						// RS off 		 оманда
PORT_RW &= ~(1 << PinPort_RW);						// R/W off		«апись

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





void copy_video_mem(char *in_mas, char *out_mas)
{


	for (int count = 0; count < 60; count++)
	{
		out_mas[count] = in_mas[count];
	}


}





void display(char *pt_video_memory)
{
			setCursor(0,0);
				LCD_SendStr_NN(pt_video_memory,0, 15);
			setCursor(1,0);
				LCD_SendStr_NN(pt_video_memory,15, 15);
			setCursor(2,0);
				LCD_SendStr_NN(pt_video_memory,30, 15);
			setCursor(3,0);
				LCD_SendStr_NN(pt_video_memory,45, 15);

}	// скобка display





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




void pause_disp(unsigned int time_ms)
{
	extern unsigned int count_timer0;						// внешн€€ переменна€ дл€ счЄтчика времени

	for (count_timer0 = 0;count_timer0 < time_ms;){}		// тупн€к-задержка, число сравнени€ * 0,00102 = врем€ паузы в сек.
}







void strob(unsigned int time_strob)
{
	
		PORT_E |= 1 << PinPort_E;						// E on
		for (char count = 0; count < time_strob; count++) {}	// тупн€чок задержка дл€ строба. вы€снить почему так много нужно
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
		PORT_RW |= 1 << PinPort_RW;					// чтение из диспле€
	}	
}


void clear_disp()									// очистка диспле€
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

// 1 	2  3  4  5  6  7  8  9  10 11 12 13 14 15 16			// адреса знакомест дл€ 4-х строчного диспле€

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

	
}	// скобочка nomb_to_digit



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

} 	// скобочка LCD_SendStr_NN





