/*
 * uart.c
 *
 * Created: 25-May-21 8:24:15 PM
 *  Author: fedea
 */ 

#include "uart.h"
#include "serialPort.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>

static unsigned char TXindice_lectura=0, TXindice_escritura=0;
static unsigned char RX_Index=0;
static unsigned char TX_Buffer[TX_BUFFER_LENGTH];
static  unsigned char RX_Buffer[RX_BUFFER_LENGTH];

#ifdef ECO_DEBUG
volatile unsigned char eco=0;
#endif

volatile unsigned char imprimiendoMensaje=0;
volatile unsigned char flag_hayString=0;
static ERROR_CODES Error_code;

/*
Compilacion condicional


#ifdef ECO_DEBUG
	printEcho(); -> solo si esta definido ECO_DEBUG
#else
	//nada
#endif

*/

void UART_Init(uint8_t baud_rate,uint8_t TxEnable,uint8_t RxEnable){
	// config = 0x33 ==> Configuro UART 9600bps, 8 bit data, 1 stop @ F_CPU = 8MHz.
	// config = 0x25 ==> Configuro UART 9600bps, 8 bit data, 1 stop @ F_CPU = 4Hz.
	//Utilizo las funciones de la librería que encapsula el hardware
	SerialPort_Init(baud_rate);
	if(TxEnable){
		SerialPort_TX_Enable();
	}
	if(RxEnable){
		SerialPort_RX_Enable();
	}
	SerialPort_RX_Interrupt_Enable();
}

/*
//Prints str on terminal
void UART_PrintString(const char* str){
	
	//TO DO
	TXindice_lectura=0;
	TXindice_escritura=0;
	for(uint8_t i=str;i!='\0';i++){
		*i=TX_Buffer[TXindice_lectura++];
	}
	imprimiendoMensaje=1;
	SerialPort_TX_Interrupt_Enable();
	
	return 0;
}
*/

void UART_PrintString( const char* STR_PTR )
{
	unsigned char i = 0;
	while(STR_PTR[i]!='\0')
	{
		UART_Write_Char_To_Buffer(STR_PTR[i]);
		i++;
	}
	imprimiendoMensaje=1;
	SerialPort_TX_Interrupt_Enable();
	//SerialPort_RX_Interrupt_Disable(); //podria deshabilitar la escritura mientras
}

void UART_Write_Char_To_Buffer(const char data)
{
	if(TXindice_escritura < TX_BUFFER_LENGTH)
	{
		TX_Buffer[TXindice_escritura] = data;
		TXindice_escritura++;
	}
	else
	{
		// Write buffer is full --> TO-DO checkeo del error
		Error_code= ERROR_UART_FULL_BUFF;
	}
}

 char* UART_GetString(){
	char* ret = (char*) malloc(strlen(RX_Buffer)* sizeof(char));
	strcpy(ret,RX_Buffer);
	return ret;
}

unsigned char UART_HayString(){
	if(flag_hayString){
		flag_hayString=0;
		return 1;
	}
	else{
		return 0;
	}
}

ISR (USART_RX_vect){
	volatile unsigned char dato=UDR0;
	if(dato!='\r'){
		RX_Buffer[RX_Index++%RX_BUFFER_LENGTH] = dato;
		#ifdef ECO_DEBUG
		eco=1;
		SerialPort_TX_Interrupt_Enable();
		#endif
	}
	else{
		RX_Buffer[RX_Index++]='\0';
		RX_Index=0;
		UART_PrintString("\n\r");
		flag_hayString=1;
	}
}

ISR(USART_UDRE_vect){
	#ifdef ECO_DEBUG
	if(eco){
		SerialPort_Send_Data(RX_Buffer[(RX_Index-1)%RX_BUFFER_LENGTH]);
		eco=0;
		SerialPort_TX_Interrupt_Disable();
	}
	#endif
	if(imprimiendoMensaje){
		if(TXindice_lectura<TXindice_escritura){
			SerialPort_Send_Data(TX_Buffer[TXindice_lectura++]);		
		}
		else{
			//ya no tengo mas para escribir
			imprimiendoMensaje=0;
			TXindice_lectura=0;
			TXindice_escritura=0;
			SerialPort_TX_Interrupt_Disable();
			//SerialPort_RX_Interrupt_Enable(); //podriamos deshabilitar y habilitar lectura de teclado mientras se escribe msj
		}
	}
}