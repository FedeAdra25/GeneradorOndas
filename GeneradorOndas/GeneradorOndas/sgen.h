/*
 * sgen.h
 *
 * Created: 06-Jun-21 7:18:48 PM
 *  Author: fedea
 */ 


#ifndef SGEN_H_
#define SGEN_H_
#include <string.h>
#include <stdlib.h>
#include <avr/io.h>
#define SGEN_SUCCESS 0
#define SGEN_ERROR 69
#define SGEN_RESET 42
#define SGEN_STARTUP_FREQ 100
#define SGEN_BASE_FREQ 1000000
#include "uart.h"
#include "timerconfig.h"
void SGEN_Init();
uint8_t SGEN_Decode(char* command);



#endif /* SGEN_H_ */