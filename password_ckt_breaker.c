#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "lcd.h"

char PW[10] = "12344321";

int main()
{
	DDRD = 0xFF;
	DDRC |= 1<<PC0 | 1<<PC1 | 1<<PC2;
	PORTB |= 1<<PB0 | 1<<PB1 | 1<<PB2 | 1<<PB3;
	
	DDRB |= 1<<PB4;
	PORTB |= 1<<PB4;

	uint8_t c = 1;
	char s[10] = "\0";
	
	lcd_init();
	
	while(1){
	lcd_cmd(0x01);
	lcd_print("Password?");
	lcd_cmd(0xC0);
	strcpy(s,"");
	while (1)
	{
		if (bit_is_clear(PINB, PINB0))
		{
			if (c != 0){
			lcd_print("1");
			c = 0;
			strcat(s,"1");
			if (strlen(s) == strlen(PW))
			break;
			}
		}
		else if (bit_is_clear(PINB, PINB1))
		{
			if (c != 0){
			c = 0;
			lcd_print("2");
			strcat(s,"2");
			if (strlen(s) == strlen(PW))
			break;}
		}
		else if (bit_is_clear(PINB, PINB2))
		{
			if (c != 0){
			c = 0;
			lcd_print("3");
			strcat(s,"3");
			if (strlen(s) == strlen(PW))
			break;}
		}
		else if (bit_is_clear(PINB, PINB3))
		{
			if (c != 0){
			c = 0;
			lcd_print("4");
			strcat(s,"4");
			if (strlen(s) == strlen(PW))
			break;
			}
		}
		else 
		{
			c = 1;
		}
	}
	_delay_ms(500);
	if (strcmp(s, PW) == 0)
	{
		lcd_cmd(0x01);
		lcd_print("Successfull");
		PORTB ^= 1<<PB4;
		break;
	}
	else 
	{
		lcd_cmd(0x01);
		lcd_print("Unsuccessfull");
		_delay_ms(1000);
	}	}
	return 0;
}