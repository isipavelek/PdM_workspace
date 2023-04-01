#include "main.h"
#include "API_debounce.h"
#include "API_delay.h"
#include "API_init.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define DEMORA_100 100
#define DEMORA_500 500
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
bool_t demora=false;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

int main(void){
  delay_t estructura;
  HAL_Init();
  /* Configure the system clock to 180 MHz */
  SystemClock_Config();
  /* Initialize BSP Led for LED2 */
  BSP_LED_Init(LED2);
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
  debounceFSM_init();
  delayInit(&estructura,DEMORA_100);
  /* Infinite loop */
  while (1){
	  debounceFSM_update();
	  if(delayRead(&estructura)==true)BSP_LED_Toggle(LED2);
	  if(readKey()==true){
		  if(!demora)delayWrite(&estructura,DEMORA_100);
		  else delayWrite(&estructura,DEMORA_500);
		  demora^=true;


	  }
  }
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


