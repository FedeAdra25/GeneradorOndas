/*
 * sgen.h
 *
 * Created: 06-Jun-21 7:18:48 PM
 *  Author: fedea
 */ 


#ifndef SGEN_H_
#define SGEN_H_

#define SGEN_ERROR 53
#define SGEN_RESET 69
#define SGEN_STARTUP_FREQ 100


void SGEN_Init();


uint8_t SGEN_Decode(char* command);



#endif /* SGEN_H_ */