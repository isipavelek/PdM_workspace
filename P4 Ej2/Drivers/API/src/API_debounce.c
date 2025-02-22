/*
 * API_debounce.c
 *
 *  Created on: 5 mar. 2023
 *      Author: ipave
 */

#include "API_debounce.h"
#include "API_delay.h"


static uint8_t estado=BUTTON_UP;
static delay_t estructura_tiempo;
static bool_t tecla=0;


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
	tecla=true;
}
void buttonReleased(){
	tecla=false;
}


bool_t readKey(void){

	if(tecla==true){
		tecla=false;
		return true;
	}
	return false;

}

