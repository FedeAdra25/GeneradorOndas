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
static const uint32_t BASE_FRQ = SGEN_BASE_FREQ;
//turns on generator
static void SGEN_TurnOn();
//turns off generator
static void SGEN_TurnOff();
//restarts program
static void SGEN_RST();
//sets the frequency
static void SGEN_SetFreq(uint16_t frequency);


//Function for cleaning string
static void SGEN_Cleanup(char*);

void SGEN_Init(){
	//Inicializar signal generator
	
	//Inicializo timer
	TIMERCONFIG_Init(TIMERCONFIG_CTC,TIMERCONFIG_PRESCALER_8); //inicializo timer en modo ctc y con preescalador N=8
	SGEN_SetFreq(100); //seteo la frecuencia inicial
	//SGEN_TurnOff();
}


uint8_t SGEN_Decode(char* command){
	
	SGEN_Cleanup(command); //Limpio los backslash por si el usuario se confundio al escribir (ej: "OM\bN" se ve como un ON)
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
	//TO DO
	//UART_PrintString("La maquina se prendio bien culiado");
	TIMERCONFIG_ActivateToggle(); //activo el toggle
}

//turns off generator
static void SGEN_TurnOff(){
	//TO DO
	//UART_PrintString("La maquina se apago bien culiado");
	TIMERCONFIG_DeactivateToggle();
}

//restarts program
static void SGEN_RST(){
	//TO DO
	//UART_PrintString("La maquina se reseteo bien culiados");
	SGEN_Init();
	SGEN_TurnOff();
	
}

//sets the frequency
static void SGEN_SetFreq(uint16_t frequency){
	frq = frequency;
	TIMERCONFIG_SetOCR1A( (BASE_FRQ/frq) + 0.5 ); //seteo el OCR1A fancy
	//TODO
}

//Cleans backspaces
static void SGEN_Cleanup(char* str){
	//TODO
}