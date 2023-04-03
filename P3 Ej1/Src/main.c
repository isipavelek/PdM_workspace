#include "main.h"
#include "API_init.h"

/* Private define ------------------------------------------------------------*/
#define LIM_SEC 3
const char LEDS[LIM_SEC]={LED1,LED2,LED3};
#define OFF 0
#define ON 1
#define DEMORA_BASE 200

/* Private variables ---------------------------------------------------------*/
bool estado=OFF;
/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void){
  uint8_t i=0;
  HAL_Init();
  delay_t estructura;

  /* Configure the system clock to 180 MHz */
  SystemClock_Config();

  /* Initialize BSP Led for LED2 */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);
  delayInit(&estructura,DEMORA_BASE);

  /* Infinite loop */
  while (1){

	  if(delayRead(&estructura)==true){
		  BSP_LED_Toggle(LEDS[i]);
  		  if(estado==ON){
  			  i++;
  			  if(i==sizeof(LEDS))i=0;
  		  }
  		  estado^=true;

	  }

  }
}

