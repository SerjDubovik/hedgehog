
//#include <HD44780_func.c>
/// Тут определяем пины для работы с дисплеем 



// PortA - 1	PortB - 2	PortC - 3	PortD - 4


#define DB7				3
#define DB6				2
#define DB5				1
#define DB4				0

#define Port_Data_7		2
#define Port_Data_6		2
#define Port_Data_5		2
#define Port_Data_4		2

#define RS				5
#define RW				4
#define E				3

#define Port_Data_RS	3
#define Port_Data_RW	3
#define Port_Data_E		3

#define command			1
#define data			0

#define read_disp		1
#define write_disp		0




/////////////////////////////////////////////////////7 pin ///////////////////////////////////////////////////

#if (Port_Data_7 == 1)

	#if (DB7 == 0)
		#define DDR_DB7			DDRA
		#define DD_DB7			DDA0
		#define PORT_DB7		PORTA
		#define PinPort_DB7		PORTA0
		#define PIN_DB7			PINA
		#define ReadPin			PINA0
	#endif
	#if (DB7 == 1)
		#define DDR_DB7			DDRA
		#define DD_DB7			DDA1
		#define PORT_DB7		PORTA
		#define PinPort_DB7		PORTA1
		#define PIN_DB7			PINA
		#define ReadPin			PINA1
	#endif
	#if (DB7 == 2)
		#define DDR_DB7			DDRA
		#define DD_DB7			DDA2
		#define PORT_DB7		PORTA
		#define PinPort_DB7		PORTA2
		#define PIN_DB7			PINA
		#define ReadPin			PINA2
	#endif
	#if (DB7 == 3)
		#define DDR_DB7			DDRA
		#define DD_DB7			DDA3
		#define PORT_DB7		PORTA
		#define PinPort_DB7		PORTA3
		#define PIN_DB7			PINA
		#define ReadPin			PINA3
	#endif
	#if (DB7 == 4)
		#define DDR_DB7			DDRA
		#define DD_DB7			DDA4
		#define PORT_DB7		PORTA
		#define PinPort_DB7		PORTA4
		#define PIN_DB7			PINA
		#define ReadPin			PINA4
	#endif
	#if (DB7 == 5)
		#define DDR_DB7			DDRA
		#define DD_DB7			DDA5
		#define PORT_DB7		PORTA
		#define PinPort_DB7		PORTA5
		#define PIN_DB7			PINA
		#define ReadPin			PINA5
	#endif
	#if (DB7 == 6)
		#define DDR_DB7			DDRA
		#define DD_DB7			DDA6
		#define PORT_DB7		PORTA
		#define PinPort_DB7		PORTA6
		#define PIN_DB7			PINA
		#define ReadPin			PINA6
	#endif
	#if (DB7 == 7)
		#define DDR_DB7			DDRA
		#define DD_DB7			DDA7
		#define PORT_DB7		PORTA
		#define PinPort_DB7		PORTA7
		#define PIN_DB7			PINA
		#define ReadPin			PINA7
	#endif

#endif



#if (Port_Data_7 == 2)

	#if (DB7 == 0)
		#define DDR_DB7			DDRB
		#define DD_DB7			DDB0
		#define PORT_DB7		PORTB
		#define PinPort_DB7		PORTB0
		#define PIN_DB7			PINB
		#define ReadPin			PINB0
	#endif
	#if (DB7 == 1)
		#define DDR_DB7			DDRB
		#define DD_DB7			DDB1
		#define PORT_DB7		PORTB
		#define PinPort_DB7		PORTB1
		#define PIN_DB7			PINB
		#define ReadPin			PINB1
	#endif
	#if (DB7 == 2)
		#define DDR_DB7			DDRB
		#define DD_DB7			DDB2
		#define PORT_DB7		PORTB
		#define PinPort_DB7		PORTB2
		#define PIN_DB7			PINB
		#define ReadPin			PINB2
	#endif
	#if (DB7 == 3)
		#define DDR_DB7			DDRB
		#define DD_DB7			DDB3
		#define PORT_DB7		PORTB
		#define PinPort_DB7		PORTB3
		#define PIN_DB7			PINB
		#define ReadPin			PINB3
	#endif
	#if (DB7 == 4)
		#define DDR_DB7			DDRB
		#define DD_DB7			DDB4
		#define PORT_DB7		PORTB
		#define PinPort_DB7		PORTB4
		#define PIN_DB7			PINB
		#define ReadPin			PINB4
	#endif
	#if (DB7 == 5)
		#define DDR_DB7			DDRB
		#define DD_DB7			DDB5
		#define PORT_DB7		PORTB
		#define PinPort_DB7		PORTB5
		#define PIN_DB7			PINB
		#define ReadPin			PINB5
	#endif
	#if (DB7 == 6)
		#define DDR_DB7			DDRB
		#define DD_DB7			DDB6
		#define PORT_DB7		PORTB
		#define PinPort_DB7		PORTB6
		#define PIN_DB7			PINA
		#define ReadPin			PINA6
	#endif
	#if (DB7 == 7)
		#define DDR_DB7			DDRB
		#define DD_DB7			DDB7
		#define PORT_DB7		PORTB
		#define PinPort_DB7		PORTB7
		#define PIN_DB7			PINB
		#define ReadPin			PINB7
	#endif

#endif


#if (Port_Data_7 == 3)

	#if (DB7 == 0)
		#define DDR_DB7			DDRC
		#define DD_DB7			DDC0
		#define PORT_DB7		PORTC
		#define PinPort_DB7		PORTC0
		#define PIN_DB7			PINC
		#define ReadPin			PINC0
	#endif
	#if (DB7 == 1)
		#define DDR_DB7			DDRC
		#define DD_DB7			DDC1
		#define PORT_DB7		PORTC
		#define PinPort_DB7		PORTC1
		#define PIN_DB7			PINC
		#define ReadPin			PINC1
	#endif
	#if (DB7 == 2)
		#define DDR_DB7			DDRC
		#define DD_DB7			DDC2
		#define PORT_DB7		PORTC
		#define PinPort_DB7		PORTC2
		#define PIN_DB7			PINC
		#define ReadPin			PINC2
	#endif
	#if (DB7 == 3)
		#define DDR_DB7			DDRC
		#define DD_DB7			DDC3
		#define PORT_DB7		PORTC
		#define PinPort_DB7		PORTC3
		#define PIN_DB7			PINC
		#define ReadPin			PINC3
	#endif
	#if (DB7 == 4)
		#define DDR_DB7			DDRC
		#define DD_DB7			DDC4
		#define PORT_DB7		PORTC
		#define PinPort_DB7		PORTC4
		#define PIN_DB7			PINC
		#define ReadPin			PINC4
	#endif
	#if (DB7 == 5)
		#define DDR_DB7			DDRC
		#define DD_DB7			DDC5
		#define PORT_DB7		PORTC
		#define PinPort_DB7		PORTC5
		#define PIN_DB7			PINC
		#define ReadPin			PINC5
	#endif
	#if (DB7 == 6)
		#define DDR_DB7			DDRC
		#define DD_DB7			DDC6
		#define PORT_DB7		PORTC
		#define PinPort_DB7		PORTC6
		#define PIN_DB7			PINC
		#define ReadPin			PINC6
	#endif
	#if (DB7 == 7)
		#define DDR_DB7			DDRC
		#define DD_DB7			DDC7
		#define PORT_DB7		PORTC
		#define PinPort_DB7		PORTC7
		#define PIN_DB7			PINC
		#define ReadPin			PINC7
	#endif

#endif


#if (Port_Data_7 == 4)

	#if (DB7 == 0)
		#define DDR_DB7			DDRD
		#define DD_DB7			DDD0
		#define PORT_DB7		PORTD
		#define PinPort_DB7		PORTD0
		#define PIN_DB7			PIND
		#define ReadPin			PIND0
	#endif
	#if (DB7 == 1)
		#define DDR_DB7			DDRD
		#define DD_DB7			DDD1
		#define PORT_DB7		PORTD
		#define PinPort_DB7		PORTD1
		#define PIN_DB7			PIND
		#define ReadPin			PIND1
	#endif
	#if (DB7 == 2)
		#define DDR_DB7			DDRD
		#define DD_DB7			DDD2
		#define PORT_DB7		PORTD
		#define PinPort_DB7		PORTD2
		#define PIN_DB7			PIND
		#define ReadPin			PIND2
	#endif
	#if (DB7 == 3)
		#define DDR_DB7			DDRD
		#define DD_DB7			DDD3
		#define PORT_DB7		PORTD
		#define PinPort_DB7		PORTD3
		#define PIN_DB7			PIND
	#endif
	#if (DB7 == 4)
		#define DDR_DB7			DDRD
		#define DD_DB7			DDD4
		#define PORT_DB7		PORTD
		#define PinPort_DB7		PORTD4
		#define PIN_DB7			PIND
		#define ReadPin			PIND4
	#endif
	#if (DB7 == 5)
		#define DDR_DB7			DDRD
		#define DD_DB7			DDD5
		#define PORT_DB7		PORTD
		#define PinPort_DB7		PORTD5
		#define PIN_DB7			PIND
		#define ReadPin			PIND5
	#endif
	#if (DB7 == 6)
		#define DDR_DB7			DDRD
		#define DD_DB7			DDD6
		#define PORT_DB7		PORTD
		#define PinPort_DB7		PORTD6
		#define PIN_DB7			PIND
		#define ReadPin			PIND6
	#endif
	#if (DB7 == 7)
		#define DDR_DB7			DDRD
		#define DD_DB7			DDD7
		#define PORT_DB7		PORTD
		#define PinPort_DB7		PORTD7
		#define PIN_DB7			PIND
		#define ReadPin			PIND7
	#endif

#endif


///////////////////////////////////////////////////// 6 pin ///////////////////////////////////////////////////

	
#if (Port_Data_6 == 1)

	#if (DB6 == 0)
		#define DDR_DB6			DDRA
		#define DD_DB6			DDA0
		#define PORT_DB6		PORTA
		#define PinPort_DB6		PORTA0
	#endif
	#if (DB6 == 1)
		#define DDR_DB6			DDRA
		#define DD_DB6			DDA1
		#define PORT_DB6		PORTA
		#define PinPort_DB6		PORTA1
	#endif
	#if (DB6 == 2)
		#define DDR_DB6			DDRA
		#define DD_DB6			DDA2
		#define PORT_DB6		PORTA
		#define PinPort_DB6		PORTA2
	#endif
	#if (DB6 == 3)
		#define DDR_DB6			DDRA
		#define DD_DB6			DDA3
		#define PORT_DB6		PORTA
		#define PinPort_DB6		PORTA3
	#endif
	#if (DB6 == 4)
		#define DDR_DB6			DDRA
		#define DD_DB6			DDA4
		#define PORT_DB6		PORTA
		#define PinPort_DB6		PORTA4
	#endif
	#if (DB6 == 5)
		#define DDR_DB6			DDRA
		#define DD_DB6			DDA5
		#define PORT_DB6		PORTA
		#define PinPort_DB6		PORTA5
	#endif
	#if (DB6 == 6)
		#define DDR_DB6			DDRA
		#define DD_DB6			DDA6
		#define PORT_DB6		PORTA
		#define PinPort_DB6		PORTA6
	#endif
	#if (DB6 == 7)
		#define DDR_DB6			DDRA
		#define DD_DB6			DDA7
		#define PORT_DB6		PORTA
		#define PinPort_DB6		PORTA7
	#endif

#endif


#if (Port_Data_6 == 2)

	#if (DB6 == 0)
		#define DDR_DB6			DDRB
		#define DD_DB6			DDB0
		#define PORT_DB6		PORTB
		#define PinPort_DB6		PORTB0
	#endif
	#if (DB6 == 1)
		#define DDR_DB6			DDRB
		#define DD_DB6			DDB1
		#define PORT_DB6		PORTB
		#define PinPort_DB6		PORTB1
	#endif
	#if (DB6 == 2)
		#define DDR_DB6			DDRB
		#define DD_DB6			DDB2
		#define PORT_DB6		PORTB
		#define PinPort_DB6		PORTB2
	#endif
	#if (DB6 == 3)
		#define DDR_DB6			DDRB
		#define DD_DB6			DDB3
		#define PORT_DB6		PORTB
		#define PinPort_DB6		PORTB3
	#endif
	#if (DB6 == 4)
		#define DDR_DB6			DDRB
		#define DD_DB6			DDB4
		#define PORT_DB6		PORTB
		#define PinPort_DB6		PORTB4
	#endif
	#if (DB6 == 5)
		#define DDR_DB6			DDRB
		#define DD_DB6			DDB5
		#define PORT_DB6		PORTB
		#define PinPort_DB6		PORTB5
	#endif
	#if (DB6 == 6)
		#define DDR_DB6			DDRB
		#define DD_DB6			DDB6
		#define PORT_DB6		PORTB
		#define PinPort_DB6		PORTB6
	#endif
	#if (DB6 == 7)
		#define DDR_DB6			DDRB
		#define DD_DB6			DDB7
		#define PORT_DB6		PORTB
		#define PinPort_DB6		PORTB7
	#endif

#endif


#if (Port_Data_6 == 3)

	#if (DB6 == 0)
		#define DDR_DB6			DDRC
		#define DD_DB6			DDC0
		#define PORT_DB6		PORTC
		#define PinPort_DB6		PORTC0
	#endif
	#if (DB6 == 1)
		#define DDR_DB6			DDRC
		#define DD_DB6			DDC1
		#define PORT_DB6		PORTC
		#define PinPort_DB6		PORTC1
	#endif
	#if (DB6 == 2)
		#define DDR_DB6			DDRC
		#define DD_DB6			DDC2
		#define PORT_DB6		PORTC
		#define PinPort_DB6		PORTC2
	#endif
	#if (DB6 == 3)
		#define DDR_DB6			DDRC
		#define DD_DB6			DDC3
		#define PORT_DB6		PORTC
		#define PinPort_DB6		PORTC3
	#endif
	#if (DB6 == 4)
		#define DDR_DB6			DDRC
		#define DD_DB6			DDC4
		#define PORT_DB6		PORTC
		#define PinPort_DB6		PORTC4
	#endif
	#if (DB6 == 5)
		#define DDR_DB6			DDRC
		#define DD_DB6			DDC5
		#define PORT_DB6		PORTC
		#define PinPort_DB6		PORTC5
	#endif
	#if (DB6 == 6)
		#define DDR_DB6			DDRC
		#define DD_DB6			DDC6
		#define PORT_DB6		PORTC
		#define PinPort_DB6		PORTC6
	#endif
	#if (DB6 == 7)
		#define DDR_DB6			DDRC
		#define DD_DB6			DDC7
		#define PORT_DB6		PORTC
		#define PinPort_DB6		PORTC7
	#endif

#endif


#if (Port_Data_6 == 4)

	#if (DB6 == 0)
		#define DDR_DB6			DDRD
		#define DD_DB6			DDD0
		#define PORT_DB6		PORTD
		#define PinPort_DB6		PORTD0
	#endif
	#if (DB6 == 1)
		#define DDR_DB6			DDRD
		#define DD_DB6			DDD1
		#define PORT_DB6		PORTD
		#define PinPort_DB6		PORTD1
	#endif
	#if (DB6 == 2)
		#define DDR_DB6			DDRD
		#define DD_DB6			DDD2
		#define PORT_DB6		PORTD
		#define PinPort_DB6		PORTD2
	#endif
	#if (DB6 == 3)
		#define DDR_DB6			DDRD
		#define DD_DB6			DDD3
		#define PORT_DB6		PORTD
		#define PinPort_DB6		PORTD3
	#endif
	#if (DB6 == 4)
		#define DDR_DB6			DDRD
		#define DD_DB6			DDD4
		#define PORT_DB6		PORTD
		#define PinPort_DB6		PORTD4
	#endif
	#if (DB6 == 5)
		#define DDR_DB6			DDRD
		#define DD_DB6			DDD5
		#define PORT_DB6		PORTD
		#define PinPort_DB6		PORTD5
	#endif
	#if (DB6 == 6)
		#define DDR_DB6			DDRD
		#define DD_DB6			DDD6
		#define PORT_DB6		PORTD
		#define PinPort_DB6		PORTD6
	#endif
	#if (DB6 == 7)
		#define DDR_DB6			DDRD
		#define DD_DB6			DDD7
		#define PORT_DB6		PORTD
		#define PinPort_DB6		PORTD7
	#endif

#endif

///////////////////////////////////////////////////// 5 pin ///////////////////////////////////////////////////


#if (Port_Data_5 == 1)

	#if (DB6 == 0)
		#define DDR_DB5			DDRA
		#define DD_DB5			DDA0
		#define PORT_DB5		PORTA
		#define PinPort_DB5		PORTA0
	#endif
	#if (DB5 == 1)
		#define DDR_DB5			DDRA
		#define DD_DB5			DDA1
		#define PORT_DB5		PORTA
		#define PinPort_DB5		PORTA1
	#endif
	#if (DB5 == 2)
		#define DDR_DB5			DDRA
		#define DD_DB5			DDA2
		#define PORT_DB5		PORTA
		#define PinPort_DB5		PORTA2
	#endif
	#if (DB5 == 3)
		#define DDR_DB5			DDRA
		#define DD_DB5			DDA3
		#define PORT_DB5		PORTA
		#define PinPort_DB5		PORTA3
	#endif
	#if (DB5 == 4)
		#define DDR_DB5			DDRA
		#define DD_DB5			DDA4
		#define PORT_DB5		PORTA
		#define PinPort_DB5		PORTA4
	#endif
	#if (DB5 == 5)
		#define DDR_DB5			DDRA
		#define DD_DB5			DDA5
		#define PORT_DB5		PORTA
		#define PinPort_DB5		PORTA5
	#endif
	#if (DB5 == 6)
		#define DDR_DB5			DDRA
		#define DD_DB5			DDA6
		#define PORT_DB5		PORTA
		#define PinPort_DB5		PORTA6
	#endif
	#if (DB5 == 7)
		#define DDR_DB5			DDRA
		#define DD_DB5			DDA7
		#define PORT_DB5		PORTA
		#define PinPort_DB5		PORTA7
	#endif

#endif



#if (Port_Data_5 == 2)

	#if (DB6 == 0)
		#define DDR_DB5			DDRB
		#define DD_DB5			DDB0
		#define PORT_DB5		PORTB
		#define PinPort_DB5		PORTB0
	#endif
	#if (DB5 == 1)
		#define DDR_DB5			DDRB
		#define DD_DB5			DDB1
		#define PORT_DB5		PORTB
		#define PinPort_DB5		PORTB1
	#endif
	#if (DB5 == 2)
		#define DDR_DB5			DDRB
		#define DD_DB5			DDB2
		#define PORT_DB5		PORTB
		#define PinPort_DB5		PORTB2
	#endif
	#if (DB5 == 3)
		#define DDR_DB5			DDRB
		#define DD_DB5			DDB3
		#define PORT_DB5		PORTB
		#define PinPort_DB5		PORTB3
	#endif
	#if (DB5 == 4)
		#define DDR_DB5			DDRB
		#define DD_DB5			DDB4
		#define PORT_DB5		PORTB
		#define PinPort_DB5		PORTB4
	#endif
	#if (DB5 == 5)
		#define DDR_DB5			DDRB
		#define DD_DB5			DDB5
		#define PORT_DB5		PORTB
		#define PinPort_DB5		PORTB5
	#endif
	#if (DB5 == 6)
		#define DDR_DB5			DDRB
		#define DD_DB5			DDB6
		#define PORT_DB5		PORTB
		#define PinPort_DB5		PORTB6
	#endif
	#if (DB5 == 7)
		#define DDR_DB5			DDRB
		#define DD_DB5			DDB7
		#define PORT_DB5		PORTB
		#define PinPort_DB5		PORTB7
	#endif

#endif


#if (Port_Data_5 == 3)

	#if (DB6 == 0)
		#define DDR_DB5			DDRC
		#define DD_DB5			DDC0
		#define PORT_DB5		PORTC
		#define PinPort_DB5		PORTC0
	#endif
	#if (DB5 == 1)
		#define DDR_DB5			DDRC
		#define DD_DB5			DDC1
		#define PORT_DB5		PORTC
		#define PinPort_DB5		PORTC1
	#endif
	#if (DB5 == 2)
		#define DDR_DB5			DDRC
		#define DD_DB5			DDC2
		#define PORT_DB5		PORTC
		#define PinPort_DB5		PORTC2
	#endif
	#if (DB5 == 3)
		#define DDR_DB5			DDRC
		#define DD_DB5			DDC3
		#define PORT_DB5		PORTC
		#define PinPort_DB5		PORTC3
	#endif
	#if (DB5 == 4)
		#define DDR_DB5			DDRC
		#define DD_DB5			DDC4
		#define PORT_DB5		PORTC
		#define PinPort_DB5		PORTC4
	#endif
	#if (DB5 == 5)
		#define DDR_DB5			DDRC
		#define DD_DB5			DDC5
		#define PORT_DB5		PORTC
		#define PinPort_DB5		PORTC5
	#endif
	#if (DB5 == 6)
		#define DDR_DB5			DDRC
		#define DD_DB5			DDC6
		#define PORT_DB5		PORTC
		#define PinPort_DB5		PORTC6
	#endif
	#if (DB5 == 7)
		#define DDR_DB5			DDRC
		#define DD_DB5			DDC7
		#define PORT_DB5		PORTC
		#define PinPort_DB5		PORTC7
	#endif

#endif


#if (Port_Data_5 == 4)

	#if (DB6 == 0)
		#define DDR_DB5			DDRD
		#define DD_DB5			DDD0
		#define PORT_DB5		PORTD
		#define PinPort_DB5		PORTD0
	#endif
	#if (DB5 == 1)
		#define DDR_DB5			DDRD
		#define DD_DB5			DDD1
		#define PORT_DB5		PORTD
		#define PinPort_DB5		PORTD1
	#endif
	#if (DB5 == 2)
		#define DDR_DB5			DDRD
		#define DD_DB5			DDD2
		#define PORT_DB5		PORTD
		#define PinPort_DB5		PORTD2
	#endif
	#if (DB5 == 3)
		#define DDR_DB5			DDRD
		#define DD_DB5			DDD3
		#define PORT_DB5		PORTD
		#define PinPort_DB5		PORTD3
	#endif
	#if (DB5 == 4)
		#define DDR_DB5			DDRD
		#define DD_DB5			DDD4
		#define PORT_DB5		PORTD
		#define PinPort_DB5		PORTD4
	#endif
	#if (DB5 == 5)
		#define DDR_DB5			DDRD
		#define DD_DB5			DDD5
		#define PORT_DB5		PORTD
		#define PinPort_DB5		PORTD5
	#endif
	#if (DB5 == 6)
		#define DDR_DB5			DDRD
		#define DD_DB5			DDD6
		#define PORT_DB5		PORTD
		#define PinPort_DB5		PORTD6
	#endif
	#if (DB5 == 7)
		#define DDR_DB5			DDRD
		#define DD_DB5			DDD7
		#define PORT_DB5		PORTD
		#define PinPort_DB5		PORTD7
	#endif

#endif

///////////////////////////////////////////////////// 4 pin ///////////////////////////////////////////////////


#if (Port_Data_4 == 1)

	#if (DB4 == 0)
		#define DDR_DB4			DDRA
		#define DD_DB4			DDA0
		#define PORT_DB4		PORTA
		#define PinPort_DB4		PORTA0
	#endif
	#if (DB4 == 1)
		#define DDR_DB4			DDRA
		#define DD_DB4			DDA1
		#define PORT_DB4		PORTA
		#define PinPort_DB4		PORTA1
	#endif
	#if (DB4 == 2)
		#define DDR_DB4			DDRA
		#define DD_DB4			DDA2
		#define PORT_DB4		PORTA
		#define PinPort_DB4		PORTA2
	#endif
	#if (DB4 == 3)
		#define DDR_DB4			DDRA
		#define DD_DB4			DDA3
		#define PORT_DB4		PORTA
		#define PinPort_DB4		PORTA3
	#endif
	#if (DB4 == 4)
		#define DDR_DB4			DDRA
		#define DD_DB4			DDA4
		#define PORT_DB4		PORTA
		#define PinPort_DB4		PORTA4
	#endif
	#if (DB4 == 5)
		#define DDR_DB4			DDRA
		#define DD_DB4			DDA5
		#define PORT_DB4		PORTA
		#define PinPort_DB4		PORTA5
	#endif
	#if (DB4 == 6)
		#define DDR_DB4			DDRA
		#define DD_DB4			DDA6
		#define PORT_DB4		PORTA
		#define PinPort_DB4		PORTA6
	#endif
	#if (DB4 == 7)
		#define DDR_DB4			DDRA
		#define DD_DB4			DDA7
		#define PORT_DB4		PORTA
		#define PinPort_DB4		PORTA7
	#endif

#endif

#if (Port_Data_4 == 2)

	#if (DB4 == 0)
		#define DDR_DB4			DDRB
		#define DD_DB4			DDB0
		#define PORT_DB4		PORTB
		#define PinPort_DB4		PORTB0
	#endif
	#if (DB4 == 1)
		#define DDR_DB4			DDRB
		#define DD_DB4			DDB1
		#define PORT_DB4		PORTB
		#define PinPort_DB4		PORTB1
	#endif
	#if (DB4 == 2)
		#define DDR_DB4			DDRB
		#define DD_DB4			DDB2
		#define PORT_DB4		PORTB
		#define PinPort_DB4		PORTB2
	#endif
	#if (DB4 == 3)
		#define DDR_DB4			DDRB
		#define DD_DB4			DDB3
		#define PORT_DB4		PORTB
		#define PinPort_DB4		PORTB3
	#endif
	#if (DB4 == 4)
		#define DDR_DB4			DDRB
		#define DD_DB4			DDB4
		#define PORT_DB4		PORTB
		#define PinPort_DB4		PORTB4
	#endif
	#if (DB4 == 5)
		#define DDR_DB4			DDRB
		#define DD_DB4			DDB5
		#define PORT_DB4		PORTB
		#define PinPort_DB4		PORTB5
	#endif
	#if (DB4 == 6)
		#define DDR_DB4			DDRB
		#define DD_DB4			DDB6
		#define PORT_DB4		PORTB
		#define PinPort_DB4		PORTB6
	#endif
	#if (DB4 == 7)
		#define DDR_DB4			DDRB
		#define DD_DB4			DDB7
		#define PORT_DB4		PORTB
		#define PinPort_DB4		PORTB7
	#endif

#endif


#if (Port_Data_4 == 3)

	#if (DB4 == 0)
		#define DDR_DB4			DDRC
		#define DD_DB4			DDC0
		#define PORT_DB4		PORTC
		#define PinPort_DB4		PORTC0
	#endif
	#if (DB4 == 1)
		#define DDR_DB4			DDRC
		#define DD_DB4			DDC1
		#define PORT_DB4		PORTC
		#define PinPort_DB4		PORTC1
	#endif
	#if (DB4 == 2)
		#define DDR_DB4			DDRC
		#define DD_DB4			DDC2
		#define PORT_DB4		PORTC
		#define PinPort_DB4		PORTC2
	#endif
	#if (DB4 == 3)
		#define DDR_DB4			DDRC
		#define DD_DB4			DDC3
		#define PORT_DB4		PORTC
		#define PinPort_DB4		PORTC3
	#endif
	#if (DB4 == 4)
		#define DDR_DB4			DDRC
		#define DD_DB4			DDC4
		#define PORT_DB4		PORTC
		#define PinPort_DB4		PORTC4
	#endif
	#if (DB4 == 5)
		#define DDR_DB4			DDRC
		#define DD_DB4			DDC5
		#define PORT_DB4		PORTC
		#define PinPort_DB4		PORTC5
	#endif
	#if (DB4 == 6)
		#define DDR_DB4			DDRC
		#define DD_DB4			DDC6
		#define PORT_DB4		PORTC
		#define PinPort_DB4		PORTC6
	#endif
	#if (DB4 == 7)
		#define DDR_DB4			DDRC
		#define DD_DB4			DDC7
		#define PORT_DB4		PORTC
		#define PinPort_DB4		PORTC7
	#endif

#endif


#if (Port_Data_4 == 4)

	#if (DB4 == 0)
		#define DDR_DB4			DDRD
		#define DD_DB4			DDD0
		#define PORT_DB4		PORTD
		#define PinPort_DB4		PORTD0
	#endif
	#if (DB4 == 1)
		#define DDR_DB4			DDRD
		#define DD_DB4			DDD1
		#define PORT_DB4		PORTD
		#define PinPort_DB4		PORTD1
	#endif
	#if (DB4 == 2)
		#define DDR_DB4			DDRD
		#define DD_DB4			DDD2
		#define PORT_DB4		PORTD
		#define PinPort_DB4		PORTD2
	#endif
	#if (DB4 == 3)
		#define DDR_DB4			DDRD
		#define DD_DB4			DDD3
		#define PORT_DB4		PORTD
		#define PinPort_DB4		PORTD3
	#endif
	#if (DB4 == 4)
		#define DDR_DB4			DDRD
		#define DD_DB4			DDD4
		#define PORT_DB4		PORTD
		#define PinPort_DB4		PORTD4
	#endif
	#if (DB4 == 5)
		#define DDR_DB4			DDRD
		#define DD_DB4			DDD5
		#define PORT_DB4		PORTD
		#define PinPort_DB4		PORTD5
	#endif
	#if (DB4 == 6)
		#define DDR_DB4			DDRD
		#define DD_DB4			DDD6
		#define PORT_DB4		PORTD
		#define PinPort_DB4		PORTD6
	#endif
	#if (DB4 == 7)
		#define DDR_DB4			DDRD
		#define DD_DB4			DDD7
		#define PORT_DB4		PORTD
		#define PinPort_DB4		PORTD7
	#endif

#endif
///////////////////////////////////////////////////// RS //////////////////////////////////////////////////////


#if (Port_Data_RS == 1)

	#if (RS == 0)
		#define DDR_RS			DDRA
		#define DD_RS			DDA0
		#define PORT_RS			PORTA
		#define PinPort_RS		PORTA0
	#endif
	#if (RS == 1)
		#define DDR_RS			DDRA
		#define DD_RS			DDA1
		#define PORT_RS			PORTA
		#define PinPort_RS		PORTA1
	#endif
	#if (RS == 2)
		#define DDR_RS			DDRA
		#define DD_RS			DDA2
		#define PORT_RS			PORTA
		#define PinPort_RS		PORTA2
	#endif
	#if (RS == 3)
		#define DDR_RS			DDRA
		#define DD_RS			DDA3
		#define PORT_RS			PORTA
		#define PinPort_RS		PORTA3
	#endif
	#if (RS == 4)
		#define DDR_RS			DDRA
		#define DD_RS			DDA4
		#define PORT_RS			PORTA
		#define PinPort_RS		PORTA4
	#endif
	#if (RS == 5)
		#define DDR_RS			DDRA
		#define DD_RS			DDA5
		#define PORT_RS			PORTA
		#define PinPort_RS		PORTA5
	#endif
	#if (RS == 6)
		#define DDR_RS			DDRA
		#define DD_RS			DDA6
		#define PORT_RS			PORTA
		#define PinPort_RS		PORTA6
	#endif
	#if (RS == 7)
		#define DDR_RS			DDRA
		#define DD_RS			DDA7
		#define PORT_RS			PORTA
		#define PinPort_RS		PORTA7
	#endif

#endif



#if (Port_Data_RS == 2)

	#if (RS == 0)
		#define DDR_RS			DDRB
		#define DD_RS			DDB0
		#define PORT_RS			PORTB
		#define PinPort_RS		PORTB0
	#endif
	#if (RS == 1)
		#define DDR_RS			DDRB
		#define DD_RS			DDB1
		#define PORT_RS			PORTB
		#define PinPort_RS		PORTB1
	#endif
	#if (RS == 2)
		#define DDR_RS			DDRB
		#define DD_RS			DDB2
		#define PORT_RS			PORTB
		#define PinPort_RS		PORTB2
	#endif
	#if (RS == 3)
		#define DDR_RS			DDRB
		#define DD_RS			DDB3
		#define PORT_RS			PORTB
		#define PinPort_RS		PORTB3
	#endif
	#if (RS == 4)
		#define DDR_RS			DDRB
		#define DD_RS			DDB4
		#define PORT_RS			PORTB
		#define PinPort_RS		PORTB4
	#endif
	#if (RS == 5)
		#define DDR_RS			DDRB
		#define DD_RS			DDB5
		#define PORT_RS			PORTB
		#define PinPort_RS		PORTB5
	#endif
	#if (RS == 6)
		#define DDR_RS			DDRB
		#define DD_RS			DDB6
		#define PORT_RS			PORTB
		#define PinPort_RS		PORTB6
	#endif
	#if (RS == 7)
		#define DDR_RS			DDRB
		#define DD_RS			DDB7
		#define PORT_RS			PORTB
		#define PinPort_RS		PORTB7
	#endif

#endif


#if (Port_Data_RS == 3)

	#if (RS == 0)
		#define DDR_RS			DDRC
		#define DD_RS			DDC0
		#define PORT_RS			PORTC
		#define PinPort_RS		PORTC0
	#endif
	#if (RS == 1)
		#define DDR_RS			DDRC
		#define DD_RS			DDC1
		#define PORT_RS			PORTC
		#define PinPort_RS		PORTC1
	#endif
	#if (RS == 2)
		#define DDR_RS			DDRC
		#define DD_RS			DDC2
		#define PORT_RS			PORTC
		#define PinPort_RS		PORTC2
	#endif
	#if (RS == 3)
		#define DDR_RS			DDRC
		#define DD_RS			DDC3
		#define PORT_RS			PORTC
		#define PinPort_RS		PORTC3
	#endif
	#if (RS == 4)
		#define DDR_RS			DDRC
		#define DD_RS			DDC4
		#define PORT_RS			PORTC
		#define PinPort_RS		PORTC4
	#endif
	#if (RS == 5)
		#define DDR_RS			DDRC
		#define DD_RS			DDC5
		#define PORT_RS			PORTC
		#define PinPort_RS		PORTC5
	#endif
	#if (RS == 6)
		#define DDR_RS			DDRC
		#define DD_RS			DDC6
		#define PORT_RS			PORTC
		#define PinPort_RS		PORTC6
	#endif
	#if (RS == 7)
		#define DDR_RS			DDRC
		#define DD_RS			DDC7
		#define PORT_RS			PORTC
		#define PinPort_RS		PORTC7
	#endif

#endif



#if (Port_Data_RS == 4)

	#if (RS == 0)
		#define DDR_RS			DDRD
		#define DD_RS			DDD0
		#define PORT_RS			PORTD
		#define PinPort_RS		PORTD0
	#endif
	#if (RS == 1)
		#define DDR_RS			DDRD
		#define DD_RS			DDD1
		#define PORT_RS			PORTD
		#define PinPort_RS		PORTD1
	#endif
	#if (RS == 2)
		#define DDR_RS			DDRD
		#define DD_RS			DDD2
		#define PORT_RS			PORTD
		#define PinPort_RS		PORTD2
	#endif
	#if (RS == 3)
		#define DDR_RS			DDRD
		#define DD_RS			DDD3
		#define PORT_RS			PORTD
		#define PinPort_RS		PORTD3
	#endif
	#if (RS == 4)
		#define DDR_RS			DDRD
		#define DD_RS			DDD4
		#define PORT_RS			PORTD
		#define PinPort_RS		PORTD4
	#endif
	#if (RS == 5)
		#define DDR_RS			DDRD
		#define DD_RS			DDD5
		#define PORT_RS			PORTD
		#define PinPort_RS		PORTD5
	#endif
	#if (RS == 6)
		#define DDR_RS			DDRD
		#define DD_RS			DDD6
		#define PORT_RS			PORTD
		#define PinPort_RS		PORTD6
	#endif
	#if (RS == 7)
		#define DDR_RS			DDRD
		#define DD_RS			DDD7
		#define PORT_RS			PORTD
		#define PinPort_RS		PORTD7
	#endif

#endif

///////////////////////////////////////////////////// RW //////////////////////////////////////////////////////


#if (Port_Data_RW == 1)

	#if (RW == 0)
		#define DDR_RW			DDRA
		#define DD_RW			DDA0
		#define PORT_RW			PORTA
		#define PinPort_RW		PORTA0
	#endif
	#if (RW == 1)
		#define DDR_RW			DDRA
		#define DD_RW			DDA1
		#define PORT_RW			PORTA
		#define PinPort_RW		PORTA1
	#endif
	#if (RW == 2)
		#define DDR_RW			DDRA
		#define DD_RW			DDA2
		#define PORT_RW			PORTA
		#define PinPort_RW		PORTA2
	#endif
	#if (RW == 3)
		#define DDR_RW			DDRA
		#define DD_RW			DDA3
		#define PORT_RW			PORTA
		#define PinPort_RW		PORTA3
	#endif
	#if (RW == 4)
		#define DDR_RW			DDRA
		#define DD_RW			DDA4
		#define PORT_RW			PORTA
		#define PinPort_RW		PORTA4
	#endif
	#if (RW == 5)
		#define DDR_RW			DDRA
		#define DD_RW			DDA5
		#define PORT_RW			PORTA
		#define PinPort_RW		PORTA5
	#endif
	#if (RW == 6)
		#define DDR_RW			DDRA
		#define DD_RW			DDA6
		#define PORT_RW			PORTA
		#define PinPort_RW		PORTA6
	#endif
	#if (RW == 7)
		#define DDR_RW			DDRA
		#define DD_RW			DDA6
		#define PORT_RW			PORTA
		#define PinPort_RW		PORTA6
	#endif

#endif



#if (Port_Data_RW == 2)

	#if (RW == 0)
		#define DDR_RW			DDRB
		#define DD_RW			DDB0
		#define PORT_RW			PORTB
		#define PinPort_RW		PORTB0
	#endif
	#if (RW == 1)
		#define DDR_RW			DDRB
		#define DD_RW			DDB1
		#define PORT_RW			PORTB
		#define PinPort_RW		PORTB1
	#endif
	#if (RW == 2)
		#define DDR_RW			DDRB
		#define DD_RW			DDB2
		#define PORT_RW			PORTB
		#define PinPort_RW		PORTB2
	#endif
	#if (RW == 3)
		#define DDR_RW			DDRB
		#define DD_RW			DDB3
		#define PORT_RW			PORTB
		#define PinPort_RW		PORTB3
	#endif
	#if (RW == 4)
		#define DDR_RW			DDRB
		#define DD_RW			DDB4
		#define PORT_RW			PORTB
		#define PinPort_RW		PORTB4
	#endif
	#if (RW == 5)
		#define DDR_RW			DDRB
		#define DD_RW			DDB5
		#define PORT_RW			PORTB
		#define PinPort_RW		PORTB5
	#endif
	#if (RW == 6)
		#define DDR_RW			DDRB
		#define DD_RW			DDB6
		#define PORT_RW			PORTB
		#define PinPort_RW		PORTB6
	#endif
	#if (RW == 7)
		#define DDR_RW			DDRB
		#define DD_RW			DDB7
		#define PORT_RW			PORTB
		#define PinPort_RW		PORTB7
	#endif

#endif



#if (Port_Data_RW == 3)

	#if (RW == 0)
		#define DDR_RW			DDRC
		#define DD_RW			DDC0
		#define PORT_RW			PORTC
		#define PinPort_RW		PORTC0
	#endif
	#if (RW == 1)
		#define DDR_RW			DDRC
		#define DD_RW			DDC1
		#define PORT_RW			PORTC
		#define PinPort_RW		PORTC1
	#endif
	#if (RW == 2)
		#define DDR_RW			DDRC
		#define DD_RW			DDC2
		#define PORT_RW			PORTC
		#define PinPort_RW		PORTC2
	#endif
	#if (RW == 3)
		#define DDR_RW			DDRC
		#define DD_RW			DDC3
		#define PORT_RW			PORTC
		#define PinPort_RW		PORTC3
	#endif
	#if (RW == 4)
		#define DDR_RW			DDRC
		#define DD_RW			DDC4
		#define PORT_RW			PORTC
		#define PinPort_RW		PORTC4
	#endif
	#if (RW == 5)
		#define DDR_RW			DDRC
		#define DD_RW			DDC5
		#define PORT_RW			PORTC
		#define PinPort_RW		PORTC5
	#endif
	#if (RW == 6)
		#define DDR_RW			DDRC
		#define DD_RW			DDC6
		#define PORT_RW			PORTC
		#define PinPort_RW		PORTC6
	#endif
	#if (RW == 7)
		#define DDR_RW			DDRC
		#define DD_RW			DDC7
		#define PORT_RW			PORTC
		#define PinPort_RW		PORTC7
	#endif

#endif



#if (Port_Data_RW == 4)

	#if (RW == 0)
		#define DDR_RW			DDRD
		#define DD_RW			DDD0
		#define PORT_RW			PORTD
		#define PinPort_RW		PORTD0
	#endif
	#if (RW == 1)
		#define DDR_RW			DDRD
		#define DD_RW			DDD1
		#define PORT_RW			PORTD
		#define PinPort_RW		PORTD1
	#endif
	#if (RW == 2)
		#define DDR_RW			DDRD
		#define DD_RW			DDD2
		#define PORT_RW			PORTD
		#define PinPort_RW		PORTD2
	#endif
	#if (RW == 3)
		#define DDR_RW			DDRD
		#define DD_RW			DDD3
		#define PORT_RW			PORTD
		#define PinPort_RW		PORTD3
	#endif
	#if (RW == 4)
		#define DDR_RW			DDRD
		#define DD_RW			DDD4
		#define PORT_RW			PORTD
		#define PinPort_RW		PORTD4
	#endif
	#if (RW == 5)
		#define DDR_RW			DDRD
		#define DD_RW			DDD5
		#define PORT_RW			PORTD
		#define PinPort_RW		PORTD5
	#endif
	#if (RW == 6)
		#define DDR_RW			DDRD
		#define DD_RW			DDD6
		#define PORT_RW			PORTD
		#define PinPort_RW		PORTD6
	#endif
	#if (RW == 7)
		#define DDR_RW			DDRD
		#define DD_RW			DDD7
		#define PORT_RW			PORTD
		#define PinPort_RW		PORTD7
	#endif

#endif

///////////////////////////////////////////////////// E ///////////////////////////////////////////////////////



#if (Port_Data_E == 1)

	#if (E == 0)
		#define DDR_E			DDRA
		#define DD_E			DDA0
		#define PORT_E			PORTA
		#define PinPort_E		PORTA0
	#endif
	#if (E == 1)
		#define DDR_E			DDRA
		#define DD_E			DDA1
		#define PORT_E			PORTA
		#define PinPort_E		PORTA1
	#endif
	#if (E == 2)
		#define DDR_E			DDRA
		#define DD_E			DDA2
		#define PORT_E			PORTA
		#define PinPort_E		PORTA2
	#endif
	#if (E == 3)
		#define DDR_E			DDRA
		#define DD_E			DDA3
		#define PORT_E			PORTA
		#define PinPort_E		PORTA3
	#endif
	#if (E == 4)
		#define DDR_E			DDRA
		#define DD_E			DDA4
		#define PORT_E			PORTA
		#define PinPort_E		PORTA4
	#endif
	#if (E == 5)
		#define DDR_E			DDRA
		#define DD_E			DDA5
		#define PORT_E			PORTA
		#define PinPort_E		PORTA5
	#endif
	#if (E == 6)
		#define DDR_E			DDRA
		#define DD_E			DDA6
		#define PORT_E			PORTA
		#define PinPort_E		PORTA6
	#endif
	#if (E == 7)
		#define DDR_E			DDRA
		#define DD_E			DDA7
		#define PORT_E			PORTA
		#define PinPort_E		PORTA7
	#endif

#endif


#if (Port_Data_E == 2)

	#if (E == 0)
		#define DDR_E			DDRB
		#define DD_E			DDB0
		#define PORT_E			PORTB
		#define PinPort_E		PORTB0
	#endif
	#if (E == 1)
		#define DDR_E			DDRB
		#define DD_E			DDB1
		#define PORT_E			PORTB
		#define PinPort_E		PORTB1
	#endif
	#if (E == 2)
		#define DDR_E			DDRB
		#define DD_E			DDB2
		#define PORT_E			PORTB
		#define PinPort_E		PORTB2
	#endif
	#if (E == 3)
		#define DDR_E			DDRB
		#define DD_E			DDB3
		#define PORT_E			PORTB
		#define PinPort_E		PORTB3
	#endif
	#if (E == 4)
		#define DDR_E			DDRB
		#define DD_E			DDB4
		#define PORT_E			PORTB
		#define PinPort_E		PORTB4
	#endif
	#if (E == 5)
		#define DDR_E			DDRB
		#define DD_E			DDB5
		#define PORT_E			PORTB
		#define PinPort_E		PORTB5
	#endif
	#if (E == 6)
		#define DDR_E			DDRB
		#define DD_E			DDB6
		#define PORT_E			PORTB
		#define PinPort_E		PORTB6
	#endif
	#if (E == 7)
		#define DDR_E			DDRB
		#define DD_E			DDB7
		#define PORT_E			PORTB
		#define PinPort_E		PORTB7
	#endif

#endif


#if (Port_Data_E == 3)

	#if (E == 0)
		#define DDR_E			DDRC
		#define DD_E			DDC0
		#define PORT_E			PORTC
		#define PinPort_E		PORTC0
	#endif
	#if (E == 1)
		#define DDR_E			DDRC
		#define DD_E			DDC1
		#define PORT_E			PORTC
		#define PinPort_E		PORTC1
	#endif
	#if (E == 2)
		#define DDR_E			DDRC
		#define DD_E			DDC2
		#define PORT_E			PORTC
		#define PinPort_E		PORTC2
	#endif
	#if (E == 3)
		#define DDR_E			DDRC
		#define DD_E			DDC3
		#define PORT_E			PORTC
		#define PinPort_E		PORTC3
	#endif
	#if (E == 4)
		#define DDR_E			DDRC
		#define DD_E			DDC4
		#define PORT_E			PORTC
		#define PinPort_E		PORTC4
	#endif
	#if (E == 5)
		#define DDR_E			DDRC
		#define DD_E			DDC5
		#define PORT_E			PORTC
		#define PinPort_E		PORTC5
	#endif
	#if (E == 6)
		#define DDR_E			DDRC
		#define DD_E			DDC6
		#define PORT_E			PORTC
		#define PinPort_E		PORTC6
	#endif
	#if (E == 7)
		#define DDR_E			DDRC
		#define DD_E			DDC7
		#define PORT_E			PORTC
		#define PinPort_E		PORTC7
	#endif

#endif


#if (Port_Data_E == 4)

	#if (E == 0)
		#define DDR_E			DDRD
		#define DD_E			DDD0
		#define PORT_E			PORTD
		#define PinPort_E		PORTD0
	#endif
	#if (E == 1)
		#define DDR_E			DDRD
		#define DD_E			DDD1
		#define PORT_E			PORTD
		#define PinPort_E		PORTD1
	#endif
	#if (E == 2)
		#define DDR_E			DDRD
		#define DD_E			DDD2
		#define PORT_E			PORTD
		#define PinPort_E		PORTD2
	#endif
	#if (E == 3)
		#define DDR_E			DDRD
		#define DD_E			DDD3
		#define PORT_E			PORTD
		#define PinPort_E		PORTD3
	#endif
	#if (E == 4)
		#define DDR_E			DDRD
		#define DD_E			DDD4
		#define PORT_E			PORTD
		#define PinPort_E		PORTD4
	#endif
	#if (E == 5)
		#define DDR_E			DDRD
		#define DD_E			DDD5
		#define PORT_E			PORTD
		#define PinPort_E		PORTD5
	#endif
	#if (E == 6)
		#define DDR_E			DDRD
		#define DD_E			DDD6
		#define PORT_E			PORTD
		#define PinPort_E		PORTD6
	#endif
	#if (E == 7)
		#define DDR_E			DDRD
		#define DD_E			DDD7
		#define PORT_E			PORTD
		#define PinPort_E		PORTD7
	#endif


#endif
