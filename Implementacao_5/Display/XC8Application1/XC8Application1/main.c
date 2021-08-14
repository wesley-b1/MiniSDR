
#define F_CPU 8000000UL
//
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
//
//#define LCD_Dir_00 DDRB
//#define LCDER_Port PORTB
//#define RSel PB0
//#define ENable PB1
//
//void LCD_Commandgiver( unsigned char comand){
//	LCDER_Port = (LCDER_Port & 0x0F) | (comand & 0xF0);
//	LCDER_Port &= ~(1<<RSel);
//	LCDER_Port |= (1<<ENable);
//	_delay_ms(2);
//	LCDER_Port &= ~(1<<ENable);
//	
//	_delay_us(200);
//	
//	LCDER_Port =(LCDER_Port & 0x0F)| (comand << 4);
//	LCDER_Port |= (1<<ENable);
//	_delay_us(2);
//	LCDER_Port &= ~(1<<ENable);
//	_delay_ms(2);
//}
//
//void LCD_Initializer (void){
//	LCD_Dir_00 = 0xFF;
//	_delay_ms(20);
//	
//	LCD_Commandgiver(0x02);
//	LCD_Commandgiver(0x28);
//	LCD_Commandgiver(0x0c);
//	LCD_Commandgiver(0x06);
//	LCD_Commandgiver(0x01);
//	_delay_ms(2);
//}
//
//void LCD_String (char *string_00){
//	int ci;
//	for(ci=0;string_00[ci]!=0;ci++){
//		LCD_Character(string_00[ci]);
//	}
//	
//}
//
//void LCD_Character(unsigned char data_00){
//	LCDER_Port = (LCDER_Port & 0x0F) | (data_00 & 0xF0);
//	LCDER_Port |= (1<<RSel);
//	LCDER_Port |= (1<<ENable);
//	_delay_us(1);
//	LCDER_Port &= ~(1<<ENable);
//	
//	_delay_us(200);
//	
//	LCDER_Port =(LCDER_Port & 0x0F)| (comand << 4);
//	LCDER_Port |= (1<<ENable);
//	_delay_us(2);
//	LCDER_Port &= ~(1<<ENable);
//	_delay_ms(2);
//	
//}
//
//----------------------------------------------------------------------------------------------------
//#include <xc.h>
//void lcd_cmd(unsigned char cmd){
//
//	PORTB = cmd;
//	PORTC &=~ (0x01);
//	PORTC &=~ (0x02);
//	PORTC |=  (0x04);
//	for(int i = 0;i<255;i++){}//Delay
//	PORTC &=~ (0x04);
//
//}
//
//void lcd_data(unsigned char data){
//
//	PORTB = data;
//	PORTC |= (0x01);
//	PORTC &=~ (0x02);
//	PORTC |=  (0x04);
//	for(int i = 0;i<255;i++){}//Delay
//	PORTC &=~ (0x04);
//
//}
//
//void lcd_init(){
//
//	lcd_cmd(0x38);
//	lcd_cmd(0x0e);
//	lcd_cmd(0x06);
//	lcd_cmd(0x01);
//	lcd_cmd(0x80);
//
//}
//int main(void)
//{
//	DDRB = 0xff;
//	DDRC = 0xff;
//	lcd_init();
//	while(1)
//	{
//		lcd_data('a');
//		for(int i = 0;i<255;i++){}//Delay
//		//TODO:: Please write your application code
//	}
//}
//--------------------------------------------------------------------------------------
/*
 * main.c
 *
 * Created: 8/13/2021 7:15:26 PM
 *  Author: joaom
 */ 


#define AUXPORTB PORTB

#include <xc.h>
void lcd_cmd(unsigned char cmd){
	
	PORTB &= 0xF0;
	PORTB |= cmd;
	
	//PORTC &= 0xFC;
	//PORTC |= 0x01;
	PORTB |= (1<<PORTB4); //SETANDO O ENABLE
	PORTB &= ~(1<<PORTB5);//RESETANDO O RS
	for(int i = 0;i<255;i++){}//Delay
	//PORTC &=~ 0x01;
	PORTB &= ~(1<<PORTB4); //RESETANDO O ENABLE

}

void lcd_data(unsigned char data){
	//PORTC &= 0xFC;
	//PORTC |= 0x02;
	PORTB |= (1<<PORTB5); //SETANDO O RS
	
	
	for(int i=0; i<2 ;i++){
		PORTB &= 0xF0;
		PORTB |= data;
		
		//PORTC &= 0xFC;
		//PORTC |= 0x03;
		PORTB |= (1<<PORTB4);//ENABLE EM 1
		for(int j = 0;j<255;j++){}//Delay
		//PORTC &=~ 0x01;	
		PORTB &= ~(1<<PORTB4);//ENABLE EM 0
	}
	//PORTC &=~ 0x02;	
	PORTB &= ~(1<<PORTB5);//RESETANDO O RS

}
/*void lcd_adress(unsigned char data){
	lcd_cmd(data[0]);
	lcd_cmd(data[4]);
}*/
void lcd_init(){
	//RS = 0 D7:D4 = 0010
	//RS = 0 D7:D4 = 1000
	lcd_cmd(0x02);
	lcd_cmd(0x08);
}

void lcd_off_cursor(){
	//RS = 0 D7:D4 = 0000
	//RS = 0 D7:D4 = 1100
	lcd_cmd(0x00);
	lcd_cmd(0x0C);
}

void lcd_on_cursor(){
	//RS = 0 D7:D4 = 0000
	//RS = 0 D7:D4 = 1100
	lcd_cmd(0x00);
	lcd_cmd(0x0F);
}




int main(void)
{
	DDRB = 0xff;
	DDRC = 0xff;
	PORTB = 0xF8;
	PORTC = 0xAF;
	lcd_init();
	lcd_off_cursor();
	lcd_cmd(0x87);
	lcd_cmd(0x87);
	lcd_on_cursor();
	lcd_data(0x14);
    
}


