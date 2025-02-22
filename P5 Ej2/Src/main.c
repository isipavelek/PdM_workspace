/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_debounce.h"
#include "API_uart.h"
#include "API_init.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* UART handler declaration */
UART_HandleTypeDef UartHandle;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

int main(void){
  HAL_Init();
  /* Configure the system clock to 180 MHz */
  SystemClock_Config();

  /* Initialize BSP Led for LED2 */
  BSP_LED_Init(LED2);
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
  //BSP_LED_On(LED1);
  debounceFSM_init();
  /* Infinite loop */
  if(!uartInit())BSP_LED_On(LED2);
  while (1){
	  debounceFSM_update();
  }
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

