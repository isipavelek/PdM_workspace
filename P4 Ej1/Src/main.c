
#include "main.h"
#include "API_init.h"
/* Private typedef -----------------------------------------------------------*/

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;


/* Private define ------------------------------------------------------------*/
#define LIM_SEC 3
const char LEDS[LIM_SEC]={LED1,LED2,LED3};
#define OFF 0
#define ON 1
#define DEMORA_BASE 40

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t estado;
static delay_t estructura;

/* Private function prototypes -----------------------------------------------*/

void debounceFSM_init();		// debe cargar el estado inicial
void debounceFSM_update();	// debe leer las entradas, resolver la lógica de
					// transición de estados y actualizar las salidas
void buttonPressed();			// debe togglear el LED1
void buttonReleased();		// debe togglear el LED3

int main(void){
  HAL_Init();

  /* Configure the system clock to 180 MHz */
  SystemClock_Config();

  /* Initialize BSP Led for LED2 */
  BSP_LED_Init(LED1);

  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

  debounceFSM_init();
  /* Infinite loop */
  while (1){
	  debounceFSM_update();
  }
}

void debounceFSM_init(){
    estado=BUTTON_UP;


}
void debounceFSM_update(){
	switch (estado){
	case (BUTTON_UP): if(BSP_PB_GetState(BUTTON_USER)){
						estado=BUTTON_FALLING;
						delayInit(&estructura,DEMORA_BASE);
					}
					  break;
	case (BUTTON_FALLING): if(delayRead(&estructura)){
							 if(!BSP_PB_GetState(BUTTON_USER))estado=BUTTON_UP;
							 else {
								 buttonPressed();
								 estado=BUTTON_DOWN;
							 }
						 	}
						break;
	case (BUTTON_DOWN):if(!BSP_PB_GetState(BUTTON_USER)){
							estado=BUTTON_RAISING;
							delayInit(&estructura,DEMORA_BASE);
						}

						break;
	case (BUTTON_RAISING):
						if(delayRead(&estructura)){
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
	  BSP_LED_On(LED1);

}
void buttonReleased(){
	  BSP_LED_Off(LED1);

}



#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

