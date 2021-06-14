/*
 * sgen.c
 *
 * Created: 06-Jun-21 7:11:01 PM
 *  Author: fedea
 */ 

#include <string.h>
#include <stdlib.h>
#include <avr/io.h>
#include "sgen.h"



//Decoder, receives command string
//Returns 0 on success
//Returns 69 on error
//Returns 42 on restart
static unsigned short frq = SGEN_STARTUP_FREQ;
//turns on generator
static void SGEN_TurnOn();
//turns off generator
static void SGEN_TurnOff();
//restarts program
static void SGEN_RST();
//sets the frequency
static void SGEN_SetFreq(uint16_t frequency);




void SGEN_Init(){
	//Inicializar signal generator
	
	//Inicializo timer
	TIMERCONFIG_Init(TIMERCONFIG_CTC,TIMERCONFIG_PRESCALER_8); //inicializo timer en modo ctc y con preescalador N=8
	SGEN_SetFreq(100); //seteo la frecuencia inicial
	//SGEN_TurnOff();
}


uint8_t SGEN_Decode(char* command){
	
	if(strcmp(command,"ON")==0){
		SGEN_TurnOn();
	}
	else if(strcmp(command,"OFF")==0) {
		SGEN_TurnOff();
	}
	else if(strcmp(command,"RST")==0){
		SGEN_RST();
		return SGEN_RESET;
	}
	else if(atoi(command)>=100 && atoi(command)<=10000){
		SGEN_SetFreq(atoi(command));
	}
	else{
		return SGEN_ERROR;
	}
	return SGEN_SUCCESS;
}



//Private library methods

//turns on generator
static void SGEN_TurnOn(){
	//UART_PrintString("La maquina se prendio bien");
	TIMERCONFIG_ActivateToggle(); //activo el toggle
}

//turns off generator
static void SGEN_TurnOff(){
	//UART_PrintString("La maquina se apago bien");
	TIMERCONFIG_DeactivateToggle();
}

//restarts program
static void SGEN_RST(){
	//UART_PrintString("La maquina se reseteo bien");
	SGEN_Init();
	SGEN_TurnOff();	
}

//sets the frequency
static void SGEN_SetFreq(uint16_t frequency){
	frq = frequency;
	TIMERCONFIG_SetTopOnCTC((uint16_t)((float)SGEN_BASE_FREQ/frq) + 0.5 - 1); //seteo el OCR1A fancy
}
