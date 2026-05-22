#ifndef SensorTask_H
#define SensorTask_H
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "main.h"

// Chip Select pini kontrol makroları
#define CS_LOW()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET)  // örnek pin
#define CS_HIGH() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET)
//////////////////////////////////7
float convert_gyro(int32_t raw, float scale);
float convert_accel(int32_t raw);

void SensorTask1(void const * argument);
uint16_t ADIS_ReadRegister(uint8_t reg_addr);
float convert_gyro(int32_t raw, float scale);
float convert_accel(int32_t raw);



#endif
