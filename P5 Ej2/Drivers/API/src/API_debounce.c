/*
 * API_debounce.c
 *
 *  Created on: 5 mar. 2023
 *      Author: ipave
 */

#include "API_debounce.h"
#include "API_uart.h"


static uint8_t estado=BUTTON_UP;
static delay_t estructura_tiempo;


void debounceFSM_init(){
	delayInit(&estructura_tiempo,DEMORA_BASE);
	estado=BUTTON_UP;
}
void debounceFSM_update(){
	switch (estado){
			case (BUTTON_UP): if(BSP_PB_GetState(BUTTON_USER)){
								estado=BUTTON_FALLING;
								delayRead(&estructura_tiempo);
							}
							  break;
			case (BUTTON_FALLING): if(delayRead(&estructura_tiempo)){
									 if(!BSP_PB_GetState(BUTTON_USER))estado=BUTTON_UP;
									 else {
										 buttonPressed();
										 estado=BUTTON_DOWN;
									 }
									}
								break;
			case (BUTTON_DOWN):if(!BSP_PB_GetState(BUTTON_USER)){
									estado=BUTTON_RAISING;
									delayRead(&estructura_tiempo);
								}

								break;
			case (BUTTON_RAISING):
								if(delayRead(&estructura_tiempo)){
									 if(BSP_PB_GetState(BUTTON_USER))estado=BUTTON_DOWN;
									 else {
										 buttonReleased();
										 estado=BUTTON_UP;
									 }
								 }
								break;


	}
}

void buttonPressed(){
	 uartSendString((uint8_t * )"Flanco Descendente detectado");
}
void buttonReleased(){

	 uartSendString((uint8_t * )"Flanco Ascendente detectado");

}


