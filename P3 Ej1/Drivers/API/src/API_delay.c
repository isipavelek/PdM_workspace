/*
 * API_delay.c
 *
 *  Created on: 5 mar. 2023
 *      Author: ipave
 */

#include "API_delay.h"


void delayInit( delay_t * delay, tick_t duration ){
	delay->duration=duration;
	delay->running=FALSE;

}
bool_t delayRead( delay_t * delay ){
	if((delay->running)==FALSE){
		delay->running=TRUE;
		delay->startTime=HAL_GetTick();

	}
	else{
		if(HAL_GetTick()-delay->startTime>=delay->duration){
			delay->running=FALSE;
			return TRUE;
		}
	}
	return FALSE;
}


void delayWrite( delay_t * delay, tick_t duration ){
	delay->duration=duration;
}

