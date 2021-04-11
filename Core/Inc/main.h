/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_pwr.h"
#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_gpio.h"
#include <stdint.h>
#define SIZE 34
#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

  /* Private includes ----------------------------------------------------------*/
  /* USER CODE BEGIN Includes */
  extern uint16_t autoreload, repeat, prescale;
  extern bool new_state, processed;
  struct Pair
  {
    uint32_t time;
    bool state;
  };
  class Buff
  {
  private:
    Pair array[SIZE - 1];
    uint32_t lenght;
    uint32_t countSend;
    uint16_t ARR; /*autoreload*/
    uint16_t RR;  /*repetition register*/
    uint16_t PR;  /*prescaler*/
    bool most_value = false;
    uint16_t part_of_val;

  public:
    inline void Increment(void){
      if(countSend < lenght - 0x01U){
        ++countSend;
      }
      else{
        countSend = 0x04U;
    }
    }
    inline Buff(Pair *pair, uint32_t new_lenght)
    {
      lenght = 0x00U;
      countSend = 0x00U;
      part_of_val = 0x00U;
      ARR = 0x00U;
      RR = 0x00U;
      PR = 0x00U;
      for (uint32_t i = 0U; i < lenght - 1U; ++i)
      {
        array[i] = pair[i];
      }
      lenght = new_lenght;
    }
    inline void addPair(const Pair &pair)
    {
      array[lenght++] = pair;
    }
    inline void getTIM(void)
    {
      if (most_value)
      {
        ARR = (array[countSend].time)%65535U;
        most_value = false;
        Increment();
        //++countSend;
      }
      if (array[countSend].time < 2)
      {
        if(array[countSend].time == 0x00U){
          Increment();
          //++countSend;
        }
        ARR = 1;
        RR = 0;
        PR = 35;
        new_state = array[countSend].state;
        ++countSend;
      }
      else if (array[countSend].time > 1 && array[countSend].time < 0xFFFF)
      {
        ARR = (uint32_t)array[countSend].time;
        RR = 0;
        PR = 71;
        new_state = array[countSend].state;
        Increment();
        //++countSend;
      }
      else
      {
        ARR = 65535U;
        RR = array[countSend].time/65535;
        new_state = array[countSend].state;
        most_value = true;
      }
    }
  };

  extern Buff buff;
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
#define Led_Pin LL_GPIO_PIN_13
#define Led_GPIO_Port GPIOC
#define Out_Pin LL_GPIO_PIN_8
#define Out_GPIO_Port GPIOA
#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0 ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority, \
                                                         4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1 ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority, \
                                                         3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2 ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority, \
                                                         2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3 ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority, \
                                                         1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4 ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority, \
                                                         0 bit  for subpriority */
#endif
  /* USER CODE BEGIN Private defines */

  /* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
