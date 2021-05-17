#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000L

#define adrr_devise 	2						// адрес этого устройства в сети модбас
#define leth_array		29						// длинна массива для принятых/отправленых данных. служит для проверки возможности записи по адресу




// прототипы функций

static unsigned short CRC16(int *puchMsg, unsigned short usDataLen); // функция вычисления контрольной суммы






// инициализация переменных
volatile 	unsigned int 	var_1 					= 0;	// переменные для хранения значений АЦП
volatile 	unsigned int 	var_2 					= 0;	// переменные для хранения значений АЦП
volatile 	unsigned int 	var_3 					= 0;	// переменные для хранения значений АЦП
volatile 	unsigned int 	var_4 					= 0;	// переменные для хранения значений АЦП
volatile 	unsigned int 	var_5 					= 0;	// переменные для хранения значений АЦП
volatile 	unsigned int 	var_6 					= 0;	// переменные для хранения значений АЦП
volatile 	unsigned int 	var_7 					= 0;	// переменные для хранения значений АЦП
volatile 	unsigned int 	var_8 					= 0;	// переменные для хранения значений АЦП

volatile 	unsigned int 	switch_var				= 0;	// переменная для организации пересчёта сканирования под ряд

volatile	char 			flag_UART_in 			= 0;	// флаг начала приёма посылки по UART
volatile	char 			count_timer0 			= 0;	// таймер для расчёта пауз при приёме сообщений
volatile	char			swith_modbas 			= 0;	// переменная переключатель для разбора посылки
	

volatile	int 			buf_UART_RXC 			= 0;	// переменная буфер для хранения принятого байта
volatile	int 			buf_UART_TXC 			= 0;	// переменная буфер для хранения файла для отправки


volatile	int 			array_modbas_in[60];			// буфер для приёма из уарта
volatile	int 			count_modbas_in 		= 0;	// счётчик кол-ва принятых байт
volatile	int 			array_modbas_out[60];			// буфер для передачи из уарта
volatile	int 			count_modbas_out 		= 0;	// счётчик кол-ва переданных байт
volatile	int 			buffer_index			= 0;	// счётчик для отправки
volatile	int 			count_transf_array 		= 0;	// счётчик для перегрузки массивов

volatile	int 			array_storage[59] 		= {};	// массив для принятых/переданных данных


volatile	unsigned long 	crc_calc 				= 0;	// расчётная контрольная сумма
volatile	unsigned long 	adrr_var 				= 0;	// собраный адрес из массива принятого по сети. для сравнения.
volatile	unsigned long 	quantity_byte 			= 0;	// кол-во байт которое необходимо записать или считать по сети из памяти
	
volatile	unsigned int 	crc_read_low 			= 0;	// буферные переменные для сравнение контрольной суммы
volatile	unsigned int 	crc_read_high 			= 0;	//
volatile	unsigned int 	crc_calc_low 			= 0;	//
volatile	unsigned int 	crc_calc_high 			= 0;	//

volatile	unsigned int 	buf_probe	 			= 0;	// для отстройки передачи слова а не байта





// обработчики прерываний UART.

ISR(USART_RXC_vect)								// UART. Завершение приема
{
	array_modbas_in[count_modbas_in] = UDR;		// забираем принятый байт
	count_modbas_in++;							// адрес на следующий элемент массива
	count_timer0 = 0;							// обнулили счётчик приёма.
	flag_UART_in = 1;							// флаг старта приёма посылки
}






ISR(USART_UDRE_vect)							// Прерывание по опустошению приёмного буфера UART. 
{
	buffer_index++;								// Увеличиваем индекс
 	
	if(buffer_index == count_modbas_out)  		// Вывели весь буффер? 
		{
			UCSRB &=~(1<<UDRIE);				// Запрещаем прерывание по опустошению - передача закончена
		}
		else 
		{
			UDR = array_modbas_out[buffer_index];			// Берем данные из буффера. 
		}

}







ISR(USART_TXC_vect)								// Прерывание по завершению отправки байта UART.
{

}



// обработчики прерываний Timer0.

ISR (TIMER0_OVF_vect)
{
	count_timer0++;								// при 16 мгц и предделителе на 8, каждое переполнение 	
}												// это 0,0001275 с. 



////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

int main()
{
asm volatile("sei"); //разрешаем глобальное прерывание

// инициализация переферии


// инициализация UART

#define baudrate 9600L
#define bauddivider (F_CPU/(16*baudrate)-1)
#define HI(x) ((x)>>8)
#define LO(x) ((x)& 0xFF)

UBRRL = LO(bauddivider);
UBRRH = HI(bauddivider);
UCSRA = 0;										// тут флаги состояния
UCSRB = 1<<RXEN|1<<TXEN|1<<RXCIE|0<<TXCIE;		// тут флаги управления 
UCSRC = 1<<URSEL|1<<UCSZ0|1<<UCSZ1;				// 8 бит



// инициализация таймера 0

TIMSK = 1 << TOIE0; 							// запускаем нулевой таймер
TCCR0 = (0<<CS02)|(1<<CS01)|(0<<CS00); 			// делитель частоты на 8.
/*
	; итак что тут у нас:
	; 000 - не тикает
	; 001 - тикает, но без делителя
	; 010 - делим тикание на 8
	; 011 - делим тикание на 64
	; 100 - делим тикание на 256
	; 101 - делим тикание на 1024						!!!
	; 110 - тикаем со входа Т0 по переднему фронту
	; 111 - тикаем со входа Т0 по заднему фронту
*/


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




// инициализация GPIO

DDRA = 0x0;										// PortA на вход. Тут значения АЦП

DDRD |= 1 << DDD2;								// управление импульсом и светодиодом на плате.
PORTD &= ~(0 << PORTD2);						// зажгли для наглядности и отладки.
DDRD |= 1 << DDD3;								// управление импульсом и светодиодом на плате.
PORTD &= ~(0 << PORTD3);						// зажгли для наглядности и отладки.



//PORTD |= 1 << PORTD2;							// зажигаем светодиод
//PORTD |= 1 << PORTD3;							// зажигаем светодиод

//PORTD &= ~(1 << PORTD2); 						// тушим светодиод
//PORTD &= ~(1 << PORTD3); 						// тушим светодиод







	for(;;) // бесконечный цикл
	{


		if (flag_UART_in == 1)					// проверка флага начала приёма. истина когда пришёл первый байт.
			{
				if (count_timer0 >= 20)			// проверка на таймаут приёма. пока время не вышло ждём байты
				{								// пока что тестовые 16 по 0,001041с каждый
					flag_UART_in = 0;			// сбрасываем флаг начала приема, переходим к анализу принятого	
					count_timer0 = 0;			// сбрасываем счётчик, чтоб знать сколько времени прошло после приёма
					swith_modbas = 1;			// свич разбора полётов. что пришло, правильно и как жить дальше.
					buffer_index = 0;				
				} // скобка проверки таймаута

				
			} // скобка проверки флага начала приёма




		switch (swith_modbas)
			{

				case 1:																// первый кейс разбирает принятый пакет по модбасу
				{	
					if (array_modbas_in[0] == adrr_devise) 							// проверка адреса устройства
					{																// если адрес совпал, то смотрим что в пакете дальше
						crc_calc = CRC16(array_modbas_in, (count_modbas_in-2));		// считаем CRC принятого пакета

						crc_read_high = array_modbas_in[count_modbas_in-2]; 		// старший
						crc_read_low = array_modbas_in[count_modbas_in-1];			// младший

						crc_calc_low = ((crc_calc >> 8) & 0x00FF);					// младший (count_modbas_in+2)
						crc_calc_high = (crc_calc & 0x00FF);						// старший (count_modbas_in+1)
						
						
						if((crc_read_low == crc_calc_low)&&(crc_read_high == crc_calc_high))// проверка соответствия контрольной суммы.
						{															
							
							switch (array_modbas_in[1]) 	// свич определяет какая команда кроется в пакете.
								{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
									case 0x06:				// запись значения в один регистр хранения (Preset Single Register).
									{
										adrr_var = array_modbas_in[2];								// собераем адрес из массива в одну переменную
										adrr_var = ((adrr_var << 8) | array_modbas_in[3]);

										if (adrr_var <= leth_array)									// проверка возможности записи по указанному адресу
										{
											array_storage[adrr_var * 2] = array_modbas_in[4];		// пишем в массив для хранения полученое по сети слово
											array_storage[(adrr_var * 2)+1] = array_modbas_in[5];

											for(int i = 0; i<= count_modbas_in; i++)				// скопируем масивы. так как ответ должен быть таким же как приёмный пакет.
											{
												array_modbas_out[i] = array_modbas_in[i];
											}
											
											count_modbas_out = count_modbas_in;
											count_modbas_in = 0;
											swith_modbas = 2; 										// переключаем на выполнение второго кейса
											

										} // скобка проверки адреса переменной
										else 														// если адрес выходит за диапазон доступних, нужно записать код ошибки
										{
											count_modbas_in = 0;
											swith_modbas = 0;
										} // else скобка 

									} // скобка команды 0х06
									break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
									case 0x10:	// запись значений в несколько регистров хранения (Preset Multiple Registers)
									{
										adrr_var = array_modbas_in[2];								// собераем адрес из массива в одну переменную
										adrr_var = ((adrr_var << 8) | array_modbas_in[3]);

										if (array_modbas_in[5] == 2) 								// проверка кол-ва байт в слове. если не 2, то в лес такие пакеты, я не знаю как их обрабатывать, выходим с ошибкой
										{
											if (adrr_var + (array_modbas_in[6]/2) <= leth_array)	// проверка возможности записи по указанному адресу
											{
												adrr_var *= 2;

												for (int i =0; array_modbas_in[6] > i ; i++)
												{
													array_storage[adrr_var] = array_modbas_in[(7+i)];	//
													adrr_var++;
												} // скобка цикла


												array_modbas_out[0] = array_modbas_in[0];
												array_modbas_out[1] = array_modbas_in[1];
												array_modbas_out[2] = array_modbas_in[2];
												array_modbas_out[3] = array_modbas_in[3];
												array_modbas_out[4] = array_modbas_in[4];
												array_modbas_out[5] = array_modbas_in[5];


												crc_calc = CRC16(array_modbas_out, 6);				// считаем CRC отправляемого пакета, 3 точно известных байта и байты считанные , зависит от колва в переменной

												crc_calc_low = ((crc_calc >> 8) & 0x00FF);			// младший (count_modbas_in+2)
												crc_calc_high = (crc_calc & 0x00FF);				// старший (count_modbas_in+1)

												array_modbas_out[6] = crc_calc_high;				// посчитаная контролька, пишем в массив для отправки
												array_modbas_out[7] = crc_calc_low;													
												

												count_modbas_out = 8;								// ответ всегда равен 8 байт
												count_modbas_in = 0;
												swith_modbas = 2; 	
											} // скобка проверки адреса переменных
											else
											{
												count_modbas_in = 0;
												swith_modbas = 0;
											} // else скобка проверки адреса переменных
										} // скобочка проверки сколько байт в слове.
										else
										{
											count_modbas_in = 0;
											swith_modbas = 0;
										} // скобочка else проверки сколько байт в слове

									} // скобка команды 0х10
									break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
									case 0x03:				// чтение значений из нескольких регистров хранения (Read Holding Registers).
									{
										adrr_var = array_modbas_in[2];										// собераем адрес из массива в одну переменную
										adrr_var = ((adrr_var << 8) | array_modbas_in[3]);

										quantity_byte = array_modbas_in[4];
										quantity_byte = ((quantity_byte << 8) | array_modbas_in[5]);		// соберём кол-во байт, которое нужно прочитать


										if ((adrr_var <= leth_array) || ((adrr_var + quantity_byte) <= leth_array))	// проверка возможности чтения данных по указанному адресу.
										{
											array_modbas_out[0] = array_modbas_in[0];						// адрес слейва, который отвечает на запрос
											array_modbas_out[1] = array_modbas_in[1];						// код команды, на которую отвечает слейв (0х3 конкретно в этом случае)
											array_modbas_out[2] = quantity_byte * 2;						// колличество байт, которые передаём. переменная 2 байта, верх срежется, поэтому не можем разом в один пакет записать более 255-ти байт

											adrr_var *= 2;													// слова у нас двух байтные, чтобы указать на адрес в массиве, умножаем на два (для счётчика)
											quantity_byte *= 2;

											for (int i = 0; i <= quantity_byte; i++)
											{
												array_modbas_out[i+3] = array_storage[adrr_var];			// читаем из массива хранения в сеть по указанному адресу
												adrr_var++;
											}

																											// в слове по два байта

											crc_calc = CRC16(array_modbas_out, (quantity_byte + 3));		// считаем CRC отправляемого пакета, 3 точно известных байта и байты считанные , зависит от колва в переменной

											crc_calc_low = ((crc_calc >> 8) & 0x00FF);						// младший (count_modbas_in+2)
											crc_calc_high = (crc_calc & 0x00FF);							// старший (count_modbas_in+1)

											array_modbas_out[(quantity_byte + 3)] = crc_calc_high;			// посчитаная контролька, пишем в массив для отправки
											array_modbas_out[(quantity_byte + 3)+1] = crc_calc_low;			// 

											count_modbas_out = (quantity_byte + 3)+2;
											count_modbas_in = 0;
											swith_modbas = 2; 			// переключаем на выполнение второго кейса

										} // скобка проверки адреса переменной
										else // если адрес выходит за диапазон доступних, нужно записать код ошибки
										{
											count_modbas_in = 0;
											swith_modbas = 0;
										} // else скобка
									} // скобка команды 0х03
									break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
									case 0x04:				// чтение значений из нескольких регистров ввода (Read Input Registers).
									{

									} // скобка команды 0х04
									break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								} // скобка свича разбора пакета на команды. 



							PORTD &= ~(1 << PORTD3); 								// тушим светодиод. тестово. показывает что контрольная сумма соответствует.
						} // скобка проверки совпадения принятого crc

						else
						{
							swith_modbas = 0; 										// улетаем в кейс обработки ошибочных ситуаций.
							count_modbas_in = 0;
							PORTD |= 1 << PORTD3;									// зажигаем светодиод. тестово. показывает что контрольная сумма не совпала
						} // else скобка проверки совпадения принятого crc

/*						

						// тестовый блок кода. пишет в масив на вывод посчитаный и принятый контрольный код
						array_modbas_out[0] =  (crc_calc & 0x00FF);					// старший (count_modbas_in+1)
						array_modbas_out[1] =  ((crc_calc >> 8) & 0x00FF);			// младший (count_modbas_in+2)

						array_modbas_out[2] =	array_modbas_in[count_modbas_in-2]; // старший
						array_modbas_out[3] =	array_modbas_in[count_modbas_in-1];	// младший


						count_modbas_out = 4;		// тут важно указать именно кол-во байт в массиве

*/


					} // скобка проверки адреса


					else
					{
						swith_modbas = 0; 		// если адрес не совпадает, то дальше даже не проверяем пакет, выходим из кейса
						count_modbas_in = 0;
					} // else скобка проверки адреса



				} // скобочка первого кейса
				break;
				case 2:							// второй кейс формирует ответ на принятый пакет
				{

					
					buffer_index=0;				// Сбрасываем индекс
					UDR = array_modbas_out[0];	// Отправляем первый байт из массива для отправки
					UCSRB|=(1<<UDRIE);			// Разрешаем прерывание UDRE

					swith_modbas = 0; 			// сбрасываем свич в дефолт и не заходим сюда
				} // скобочка второго кейса
				break;
				case 3: // кейс ошибок, сюда попадаем при обнаружении ошибок. доработать!!!!
				{
					//swith_modbas = 0;
				}
				break;

				default:
				{
				}
			
			} // скобка свича

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// тут заканчивается обработка модбас связи

/*
array_storage[30] =	array_storage[0];
array_storage[31] =	array_storage[1];							// записываем переменные для проверки передачи на компе
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
array_storage[46] =	array_storage[16];							// записываем переменные для проверки передачи на компе
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



		if (count_timer0 > 127)					// тестовый блок, показывает что таймер 0 считает
			{
				PORTD |= 1 << PORTD2;			// зажигаем светодиод
			}
		else
			{
				PORTD &= ~(1 << PORTD2); 		// тушим светодиод
			}
			


	}	//скобка безконечного цикла





	return 0;
}// скобка мейна

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


// функция для расчёта контрольной суммы
static unsigned short CRC16(int *puchMsg,  /* Сообщение       */
                            unsigned short usDataLen /* Длина сообщения */)
{
    unsigned short crc = 0xFFFF;
    unsigned short uIndex;
    int i;
    for (uIndex = 0; uIndex < usDataLen; uIndex += 1) {
        crc ^= (unsigned short)*(puchMsg + uIndex);
        for (i = 8; i != 0; i -= 1) {
          if ((crc & 0x0001) == 0) { crc >>= 1; }
          else { crc >>= 1; crc ^= 0xA001; }			// полином задаём здесь
        }
    }
    // Изменим порядок следования байт
 //   crc = ((crc >> 8) & 0x00FF) | ((crc << 8) & 0xFF00);
    return crc;
}





// обработчик прерывания сканирования АЦП
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
	}	// скобочка кейса

switch_var++;

} //скобочка ифа

else
{
	switch_var = 0;
}

// а тут выбор канала нужно организовать автоматически.
ADCSRA = (1<<ADEN)|(1<<ADIE)|(1<<ADSC)|(0<<ADATE)|(5<<ADPS0)	; //Запустили

}


