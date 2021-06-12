/*
 * timerconfig.h
 *
 * Created: 12-Jun-21 12:47:18 PM
 *  Author: fedea
 */ 


#ifndef TIMERCONFIG_H_
#define TIMERCONFIG_H_
#include <avr/io.h>

#define TIMERCONFIG_CTC 4
#define TIMERCONFIG_PRESCALER_8 8
#define BASE_FREQ 65535

void TIMERCONFIG_Init(uint8_t,uint8_t);
void TIMERCONFIG_ActivateToggle();
void TIMERCONFIG_DeactivateToggle();
void TIMERCONFIG_SetOCR1A(uint16_t);

#endif /* TIMERCONFIG_H_ */