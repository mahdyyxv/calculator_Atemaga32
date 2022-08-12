/*
 * Calculator.c
 *
 * Created: 8/5/2022 10:46:24 AM
 * Author : mahdy
 */ 

#include "Keypad.h"
#include "Lcd.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define F_CPU   16000000UL
#include <util/delay.h>

u8 flag = 1;
s64 result = 0;
u8 String[16] = "";
u8 i = 0;
u8 c = '\0';
s64 Number1 = 0;
s64 Number2 = 0;
f64 result2 = 0.0;
u8 cnt = 0;
u8 operation = '\0';
u8 str[20]; 

void _convert(u8* , u64* );
u64 power(u64 ,u64 );
void convertToString(s64 , u8 *);

int main(void)
{
	SetBit(_DDRD, 0);
	H_Lcd_Init();
	H_Keypad_Init();
	H_Lcd_WriteString("Hi :)");
	H_Lcd_GoTo(1,0);
	H_Lcd_WriteString("Simple Calculator ;)");
	for (cnt = 0; cnt<5; cnt++)
	{
		H_Lcd_ShiftLeft();
		_delay_ms(500);
	}
	cnt = 0;
	_delay_ms(100);
	H_Lcd_Clr();
	memset(String, 0, 16);
    while (1) 
    {
		label:
		H_Lcd_GoTo(0,i);
		c = H_Keypad_Read();
		
		if(c != '\0')
		{
			flag = 1;
			if(i > 16)
			{
				memset(String, 0, 16);
				i = 0;
				H_Lcd_Clr();
			}

			if(c != '=') H_Lcd_WriteCharacter(c);
			else if(c == '=')
			{
				_convert(String, &Number2);
				
				switch(operation)
				{
					case '+' : result = (Number1 + Number2); break;
					case '-' : result = (Number1 - Number2); break;
					case '*' : result = (Number1 * Number2); break;
					case '/' : result2 = ((f64)Number1 / (f64)Number2); break;
					default  :					                  break;
				}
				H_Lcd_GoTo(1,0);
				H_Lcd_WriteCharacter('=');

				if(operation == '/') H_Lcd_WriteNumberflt(result2);
				else convertToString(result, str);
				H_Lcd_WriteString(str);
				_delay_ms(10);
				while(c != 'C') c = H_Keypad_Read();
				i = 0;
				result = 0;
				result2 =0.0;
				cnt = 0;
				operation = '\0';
				c='\0';
				H_Lcd_Clr();
				memset(String, 0, 16);
				memset(str, 0, 16);
				Number1 = 0;
				Number2 = 0;
				goto label;
			}
			if ((c == '+') || (c == '-' )|| (c == '/' )|| (c == '*'))
			{
				operation = c;
				_convert(String, &Number1);
				c = '\0';
				flag = 0; 
				i++;
				cnt=0;
				memset(String, 0, 16);
			}		
			if(flag == 1)
			{
				String[cnt] = c;
				String[cnt+1] = '\0';
				cnt++;
				i++;
			}
		}
		
    }
}


u64 power(u64 number ,u64 power_times)
{
	u64 nn = 1;
	for (int x = 1; x <= power_times; x++)
	nn *= number;
	return nn;
}

void _convert(u8* str, u64 *number)
{
	u8 length = strlen(str);
	u8 cnt = 0;
	s8 z = 0;
	if((length == 0 ) || (str[cnt]-48 == 0)) *number = 0;
	else
	{
		for( z = (length - 1) ; z > -1 ; z--)
		{
			*number += ( ((u64) (str[cnt]-48) ) * power(10, z) );
			cnt++;
		}
	}
}

void convertToString(s64 Number, u8 *String)
{
	u8 Arr[20] = {0};
	u8 Cnt = 0;
	u8 Digit = 0;
	u8 sign[2]= "+\0";
	label:
	while ((Number != 0) && (Number > 0))
	{
		Digit             = (u64)Number % 10;
		Arr[Cnt]          = Digit +48;
		Cnt ++;
		Number            = (u64)(Number / 10);
	}
	if(Number < 0)
	{
		memset(sign, 0, 2);
		strcat(sign, "-\0");
		Number *= -1;
		goto label;
	}
	if (sign[0] == '+')
	{
		strrev(Arr);
	}
	else
	{
		strcat(Arr, sign);
		strrev(Arr);
	}
	strcat(String, Arr);
}

