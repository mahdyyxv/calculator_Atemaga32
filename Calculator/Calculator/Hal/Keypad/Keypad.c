/*
 * Keypad.c
 *
 * Created: 8/5/2022 10:58:01 AM
 *  Author: mahdy
 */ 

#include "Keypad.h"

void H_Keypad_Init(void)
{
	M_Dio_PinMode(KEYPAD_R0_PIN, OUTPUT);
	M_Dio_PinMode(KEYPAD_R1_PIN, OUTPUT);
	M_Dio_PinMode(KEYPAD_R2_PIN, OUTPUT);
	M_Dio_PinMode(KEYPAD_R3_PIN, OUTPUT);
	
	M_Dio_PinMode(KEYPAD_C0_PIN, INPUT);
	M_Dio_PinMode(KEYPAD_C1_PIN, INPUT);
	M_Dio_PinMode(KEYPAD_C2_PIN, INPUT);
	M_Dio_PinMode(KEYPAD_C3_PIN, INPUT);
	
	M_Dio_PinPullUpRes(KEYPAD_C0_PIN, ENABLE);
	M_Dio_PinPullUpRes(KEYPAD_C1_PIN, ENABLE);
	M_Dio_PinPullUpRes(KEYPAD_C2_PIN, ENABLE);
	M_Dio_PinPullUpRes(KEYPAD_C3_PIN, ENABLE);\
	
	M_Dio_PinWrite(KEYPAD_R0_PIN, HIGH);
	M_Dio_PinWrite(KEYPAD_R1_PIN, HIGH);
	M_Dio_PinWrite(KEYPAD_R2_PIN, HIGH);
	M_Dio_PinWrite(KEYPAD_R3_PIN, HIGH);
}

u8   H_Keypad_Read(void)
{
	u8 Keypad[4][4] = 
	{
		{'7', '8', '9', '/'},
		{'4', '5', '6', '*'},
		{'1', '2', '3', '-'},
		{'C', '0', '=', '+'}
	};
	
	u8 local_Row_cnt = 0;
	u8 local_Column_cnt = 0;
	u8 local_u8_value = '\0';
	u8 local_u8_Reading = KEYPAD_RELEASED;
	
	for(local_Row_cnt = KEYPAD_R0_PIN; local_Row_cnt <= KEYPAD_R3_PIN; local_Row_cnt++)
	{
		M_Dio_PinWrite(local_Row_cnt, LOW);
		
		for (local_Column_cnt = KEYPAD_C0_PIN; local_Column_cnt <= KEYPAD_C3_PIN; local_Column_cnt++)
		{
			local_u8_Reading = M_Dio_PinRead(local_Column_cnt);
			if(local_u8_Reading == KEYPAD_PRESSED)
			{
				_delay_ms(10);
				if ( M_Dio_PinRead(local_Column_cnt) == KEYPAD_PRESSED)
				{
					
					while (M_Dio_PinRead(local_Column_cnt) == KEYPAD_PRESSED);
					local_u8_value = Keypad[local_Row_cnt - KEYPAD_R0_PIN ][local_Column_cnt - KEYPAD_C0_PIN];
					
				
				}
			}
		}
		
		M_Dio_PinWrite(local_Row_cnt, HIGH);
	}
	
	return local_u8_value;
}