/*
 * timerconfig.c
 *
 * Created: 12-Jun-21 12:47:08 PM
 *  Author: fedea
 */ 


#include "timerconfig.h"



void TIMERCONFIG_Init(uint8_t mode, uint8_t prescaler){
	
	DDRB = (1<<PORTB1); //Configuro el puerto PB1 como salida
	switch(mode)
	{
		case TIMERCONFIG_CTC:
			TCCR1B |= (1<<WGM12);
			break;
		default:
			break; //normal mode
	}
	switch(prescaler)
	{
		case TIMERCONFIG_PRESCALER_8:
			TCCR1B |= (1<<CS11);
			break;
		default:
			break; //deactivate timer1
	}
	OCR1A=BASE_FREQ; //La librería setea el registro OCR1A base
}

void TIMERCONFIG_SetTopOnCTC(uint16_t value){
	OCR1A = value;
}

void TIMERCONFIG_ActivateToggle(){
	TCCR1A |= (1<<COM1A0); //Activo toggle de OC1A
}
void TIMERCONFIG_DeactivateToggle(){
	TCCR1A &= ~(1<<COM1A0); //Desactivo toggle de OC1A
}