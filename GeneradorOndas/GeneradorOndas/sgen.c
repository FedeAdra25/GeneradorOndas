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
//Returns 0 if error
//Returns 1 on success
//Returns 5 if restart

static uint16_t frq = SGEN_STARTUP_FREQ;

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
}


uint8_t SGEN_Decode(char* command){
	
	SGEN_Cleanup(command); //Limpio los backslash por si el usuario se confundio al escribir (ej: "OM\bN" se ve como un ON)
	
	if(strcmp(command,"ON\0") ==0){
		SGEN_TurnOn();
	}
	else if(strcmp(command,"OFF\0") ==0) {
		SGEN_TurnOff();
	}
	else if(strcmp(command,"RST\0") ==0){
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
	UART_PrintString("La maquina se prendio bien culiado");
}

//turns off generator
static void SGEN_TurnOff(){
	//TO DO
	UART_PrintString("La maquina se apago bien culiado");
}

//restarts program
static void SGEN_RST(){
	//TO DO
	UART_PrintString("La maquina se reseteo bien culiado");
}

//sets the frequency
static void SGEN_SetFreq(uint16_t frequency){
	frq = frequency;
	//TODO
}


//Cleans backspaces
static void SGEN_Cleanup(char* str){
	//TODO
}