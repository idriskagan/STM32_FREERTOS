#include "CommsTask.h"
#include "main.h"
#include "cmsis_os.h"

void CommsTask1(void const * argument)
{
  /* USER CODE BEGIN CommsTask1 */
  /* Infinite loop */
  for(;;)
  { // --- CAN GÖNDERİMİ ---
	    CAN_TxHeaderTypeDef TxHeader;
	    uint32_t TxMailbox;
	    uint8_t TxData[8];

	    TxHeader.DLC = 8;
	    TxHeader.IDE = CAN_ID_STD;
	    TxHeader.RTR = CAN_RTR_DATA;
	    TxHeader.StdId = 0x123;
	    TxHeader.TransmitGlobalTime = DISABLE;

	    uint8_t* data_ptr = (uint8_t*)&imu_data;

	    // 31 byte → 4 frame (8+8+8+7)
	    for (uint8_t i = 0; i < 31; i += 8)
	    {
	        uint8_t size = (i + 8 <= 30) ? 8 : (30 - i);  // son parça 6 byte olabilir
	        memset(TxData, 0, 8);  // kalan byte'ları sıfırla
	        memcpy(TxData, data_ptr + i, size);
	        HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
	        HAL_Delay(1);  // MCP2551 gibi transceiver'lar için gerekli olabilir
	    }

	    // --- UART GÖNDERİMİ ---
	    char uart_buf[150];
	    int len = snprintf(uart_buf, sizeof(uart_buf),
	        "T:%u E:%u P:%u GX:%ld GY:%ld GZ:%ld AX:%ld AY:%ld AZ:%ld TEMP:%d\r\n",
	        imu_data.timestamp,
	        imu_data.error_flags,
	        imu_data.port_id,
	        imu_data.gyro_x,
	        imu_data.gyro_y,
	        imu_data.gyro_z,
	        imu_data.accel_x,
	        imu_data.accel_y,
	        imu_data.accel_z,
	        imu_data.temperature
	    );
	    HAL_UART_Transmit(&huart4, (uint8_t*)uart_buf, len, HAL_MAX_DELAY);
	}

    osDelay(1);
  }
  /* USER CODE END CommsTask1 */
