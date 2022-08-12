/*
 * Keypad.h
 *
 * Created: 8/5/2022 10:57:50 AM
 *  Author: mahdy
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "Dio.h"
#include "Keypad_Cfg.h"
#include "StdTypes.h"
#define F_CPU   16000000UL
#include <util/delay.h>


#define KEYPAD_RELEASED  1
#define KEYPAD_PRESSED   0

void H_Keypad_Init(void);
u8   H_Keypad_Read(void);

#endif /* KEYPAD_H_ */