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
    struct Pair
  {
    uint32_t time;
    bool state;
  };
  extern Pair array[SIZE - 1];
  extern uint32_t lenght;
  extern uint32_t countSend;
  extern uint16_t ARR; /*autoreload*/
  extern uint16_t RR;  /*repetition register*/
  extern uint16_t PR;  /*prescaler*/
  extern uint16_t autoreload, repeat, prescale;
  extern bool new_state;
  extern bool processed;
  extern bool most_value;
extern void Init(const uint32_t& new_lenght, const Pair& pair);
extern void getTIM(void);
 /* class Buff
  {
  private:
    Pair array[SIZE - 1];
    uint32_t lenght;
    uint32_t countSend;
    uint16_t ARR; 
    uint16_t RR;
    uint16_t PR;
    uint16_t part_of_val;

  public:
    inline void Increment(void){
      if(countSend < lenght - 0x01U){
        ++countSend;
      }
      else{
        countSend = 0x00U;
    }
    }
    inline Buff(void)
    {
      lenght = 0x00U;
      countSend = 0x00U;
      part_of_val = 0x00U;
      ARR = 0x01U;
      RR = 0x00U;
      PR = 71U;
      //lenght = new_lenght;
    }
    inline void addPair(const Pair &pair)
    {
      array[lenght++] = pair;
    }
    inline void getTIM(void)
    {
      if (array[countSend].time < 2)
      {
        if(array[countSend].time == 0x00U){
          processed = false;
          Increment();
        }
        autoreload = 1;
        repeat = 0;
        prescale = 35;
        new_state = array[countSend].state;
        processed = false;
      }
      else if (array[countSend].time > 1 && array[countSend].time < 65535U)
      {
        autoreload = (uint32_t)array[countSend].time - 1U;
        repeat = 0;
        prescale = 71;
        new_state = array[countSend].state;
        most_value = true;
        processed = false;
        Increment();
      }
      else if((array[countSend].time > 0xFFFFU)&&(!most_value))

      {
        autoreload = 0xFFFFU;
        repeat = array[countSend].time/65535U;
        prescale = 71U;
        new_state = array[countSend].state;
        processed = false;
        most_value = true;
      }
    else if (array[countSend].time > 0xFFFFU&&most_value)
      {
        //ARR = array[countSend].time%0xFFFFU;;
        //RR = 0x00U;
        //ARR = ((array[countSend].time)%65535U) - 1U;
        //Increment();
        //++countSend;
        //asm("nop");
        autoreload = array[countSend].time%0xFFFFU;
        prescale = 71U;
        repeat = 0x00U;
        processed = false;
        most_value = false;
        Increment();
      }
    }
  };

  extern Buff buff;*/
  /* Exported functions prototypes ---------------------------------------------*/
  void Error_Handler(void);
  
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
