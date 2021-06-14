/*
 * IncFile1.h
 *
 * Created: 25-May-21 8:25:39 PM
 *  Author: fedea
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#define TX_BUFFER_LENGTH 230
#define RX_BUFFER_LENGTH 20


typedef enum {ERROR_UART_FULL_BUFF, ERROR_UART_PARITY, ERROR_UART_NONE} ERROR_CODES; //verque hacemo con esto


unsigned char UART_HayString();
char* UART_GetString();
void UART_PrintString(const char*); //Prints String
void UART_Write_Char_To_Buffer(const char); //Adds char to buffer
unsigned char UART_Error_Full_Buffer(); //No la usamos en nuestra implementación.

//Encapsulan hardware (reimplementar si se cambia el mcu)
void UART_Init(unsigned char,unsigned char,unsigned char);	

#endif /* INCFILE1_H_ */