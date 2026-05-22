#include "SensorTask.h"
#include "FreeRTOS.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include "cmsis_os.h"
#include "SensorTask.h"

void SensorTask1(void const * argument)
{
  /* USER CODE BEGIN SensorTask1 */
  /* Infinite loop */
  for(;;)
  {
	  // IMU verilerini oku
	  imu_data.gyro_x  = ((int32_t)ADIS_ReadRegister(0x06) << 16) | ADIS_ReadRegister(0x04);
	  imu_data.gyro_y  = ((int32_t)ADIS_ReadRegister(0x0A) << 16) | ADIS_ReadRegister(0x08);
	  imu_data.gyro_z  = ((int32_t)ADIS_ReadRegister(0x0E) << 16) | ADIS_ReadRegister(0x0C);

	  imu_data.accel_x = ((int32_t)ADIS_ReadRegister(0x12) << 16) | ADIS_ReadRegister(0x10);
	  imu_data.accel_y = ((int32_t)ADIS_ReadRegister(0x16) << 16) | ADIS_ReadRegister(0x14);
	  imu_data.accel_z = ((int32_t)ADIS_ReadRegister(0x1A) << 16) | ADIS_ReadRegister(0x18);
    osDelay(1000);
  }
  /* USER CODE END SensorTask1 */
}


// IMU veri okuma kısmı için okunan veriler
uint16_t ADIS_ReadRegister(uint8_t reg_addr) {
    uint8_t tx[2] = { reg_addr & 0x7F, 0x00 };
    uint8_t rx[2] = { 0 };

    CS_LOW();
    HAL_SPI_Transmit(&hspi3, tx, 2, HAL_MAX_DELAY); //Hangi sensörü okmak istediğimizi söylüyoz
    CS_HIGH();
    HAL_Delay(1); // gerekli olabilir

    CS_LOW();
    HAL_SPI_Receive(&hspi3, rx, 2, HAL_MAX_DELAY);
    CS_HIGH();

    return (rx[0] << 8) | rx[1];
}
float convert_gyro(int32_t raw, float scale) {
    return raw / scale;
}

float convert_accel(int32_t raw) {
    return raw / 262144000.0f;
}
/////////////////////////////////////////

