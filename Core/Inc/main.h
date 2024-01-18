/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CAM_D0_Pin GPIO_PIN_0
#define CAM_D0_GPIO_Port GPIOF
#define CAM_D1_Pin GPIO_PIN_1
#define CAM_D1_GPIO_Port GPIOF
#define CAM_D2_Pin GPIO_PIN_2
#define CAM_D2_GPIO_Port GPIOF
#define CAM_D3_Pin GPIO_PIN_3
#define CAM_D3_GPIO_Port GPIOF
#define CAM_D4_Pin GPIO_PIN_4
#define CAM_D4_GPIO_Port GPIOF
#define CAM_D5_Pin GPIO_PIN_5
#define CAM_D5_GPIO_Port GPIOF
#define CAM_D6_Pin GPIO_PIN_6
#define CAM_D6_GPIO_Port GPIOF
#define CAM_D7_Pin GPIO_PIN_7
#define CAM_D7_GPIO_Port GPIOF
#define SPI1_CS_Pin GPIO_PIN_3
#define SPI1_CS_GPIO_Port GPIOA
#define SPI1_DC_Pin GPIO_PIN_4
#define SPI1_DC_GPIO_Port GPIOA
#define SPI1_RST_Pin GPIO_PIN_6
#define SPI1_RST_GPIO_Port GPIOA
#define CAM_VSYNC_Pin GPIO_PIN_4
#define CAM_VSYNC_GPIO_Port GPIOC
#define CAM_VSYNC_EXTI_IRQn EXTI4_IRQn
#define CAM_RRST_Pin GPIO_PIN_0
#define CAM_RRST_GPIO_Port GPIOD
#define CAM_WRST_Pin GPIO_PIN_1
#define CAM_WRST_GPIO_Port GPIOD
#define CAM_WEN_Pin GPIO_PIN_2
#define CAM_WEN_GPIO_Port GPIOD
#define CAM_RCLK_Pin GPIO_PIN_3
#define CAM_RCLK_GPIO_Port GPIOD
#define CAM_RST_Pin GPIO_PIN_4
#define CAM_RST_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
