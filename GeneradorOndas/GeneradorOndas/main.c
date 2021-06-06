/*
 * GeneradorOndas.c
 *
 * Created: 05-Jun-21 3:26:02 PM
 * Author : fedea
 */ 


#include "main.h"
int main(void)
{
    char welcomeMsj[] = "Bienvenidx al generador de señales digitales programable\r Por favor, ingrese una frecuencia entre 100 y 10000Hz o un comando\r ON: encender generador(frecuencia por defecto: 100Hz), OFF: apagar generador, RST: reiniciar\r\n";
	char errorMsj[] = "Lo siento, no he entendido el comando\r\n";
	unsigned char command = 0;
	
	UART_Init(BAUD_RATE,1,1); //inicializo la uart
	SGEN_Init(); //inicializo generadora de señales
	sei();
	
	UART_PrintString(welcomeMsj); //Imprimo mensaje de bienvenida
	
    while (1) 
    {
		if(UART_HayString()){
			command = SGEN_Decode(UART_GetString()); //returns number
		}
		//Comportamiento si dio error o se reinicio
		if(command==SGEN_ERROR){
			UART_PrintString(errorMsj);
			//print error msj
		}
		else if (command==SGEN_RESET){
			//restart and print welcome msj
		}
		
		
    }
}