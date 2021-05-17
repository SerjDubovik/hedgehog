



// прототипы функций
/*
void pause_disp(unsigned int time_ms);
void strob(unsigned int time_strob);
void set_bus_disp(unsigned int set);
void read_write(unsigned int set);
void send_byte(unsigned int virtbyte);
void init_display();
void clear_disp();
void setCursor (int line_cursor,int position_cursor);
	void nomb_to_digit (char *pointMas, unsigned int value, unsigned int position);
void DBG_SendValue( unsigned int value );
void LCD_SendStr(char *str);
void LCD_SendStr_NN(char *str,int coun1, int count2);
void LCD_SendStr_Quant(char *str, int count);
int LCD_SendStr_mark (char *str, int count);
*/

 void init_display();
 void copy_video_mem(char *in_mas, char *out_mas);
 void display(char *pt_video_memory);
 void send_byte(unsigned int virtbyte);
 void pause_disp(unsigned int time_ms);
 void strob(unsigned int time_strob);
 void set_bus_disp(unsigned int set);
 void read_write(unsigned int set);
 void clear_disp();
 void setCursor (int line_cursor,int position_cursor);
 void nomb_to_digit (char *pointMas, unsigned int value, unsigned int position);
 void LCD_SendStr_NN(char *str,int coun1, int count2);
