#include "TempTask.h"
#include "FreeRTOS.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include "cmsis_os.h"
#include "main.h"


void TempTask1(void const * argument)
{
  /* USER CODE BEGIN TempTask1 */
  /* Infinite loop */
  for(;;)
  {
	  HAL_ADC_Start(&hadc1);

	          if (HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)
	          {
	              uint16_t adc_raw_value = HAL_ADC_GetValue(&hadc1);

	              float Vsense = (adc_raw_value * 3.3f) / 4095.0f;
	              float temperature_celsius = ((0.76f - Vsense) / 0.0025f) + 25.0f;

	              imu_data.temperature = (int16_t)(temperature_celsius * 100);
	          }

	          HAL_ADC_Stop(&hadc1);
    osDelay(1);
  }
  /* USER CODE END TempTask1 */
}
