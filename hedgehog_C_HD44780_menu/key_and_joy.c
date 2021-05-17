

//#include <avr/io.h>






/*
struct joy_type {						// вот такой должна быть объявлена структура для обработки джойстика

	int button;
	int joy_up, joy_down, joy_left, joy_right;

	int axis_X;
	int axis_Y;

} joy_1, joy_2
*/


/*
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



*/






