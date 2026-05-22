#include "ErrorMonitorTask.h"
#include "main.h"
#include "cmsis_os.h"
#include "SensorTask.h" //ReadRegister için
#include "main.h"

void ErrorMonitorTask1(void const * argument)
{
  /* USER CODE BEGIN ErrorMonitorTask1 */
  /* Infinite loop */
  for(;;)
  {
	  uint8_t error = 0x00;
	  uint16_t diag_status = ADIS_ReadRegister(0x02);  // IMUDAKİ HATAYI VERECEK REGİSTER
	          int16_t temp = imu_data.temperature;
	          float temp_c = temp / 100.0f;

	          if (diag_status != 0x0000 && (temp_c < -40.0f || temp_c > 125.0f))
	          {
	              error = 0x11;  // İkisi birden hata varsa
	          }
	          else if (diag_status != 0x0000)
	          {
	              error = 0x01;  // Sadece IMU SPI hatası
	          }
	          else if (temp_c < -40.0f || temp_c > 125.0f)
	          {
	              error = 0x10;  // Sadece sıcaklık hatası
	          }
	          else
	          {
	              error = 0x00;  // Hata yok
	          }

	          imu_data.error_flags = error;
    osDelay(1);
  }
  /* USER CODE END ErrorMonitorTask1 */
}
