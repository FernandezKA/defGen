#include"main.h"
inline void Increment(void){
      if(countSend < lenght - 0x01U){
        ++countSend;
      }
      else{
        countSend = 0x00U;
    }
    }
void Init(const uint32_t& new_lenght)
    {
      lenght = new_lenght;
      countSend = 0x00U;
      autoreload = 0x01U;
      repeat = 0x00U;
      prescale = 71U;
    }
void getTIM(void)
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
        most_value = false;
        processed = false;
        Increment();
      }
      else if((array[countSend].time > 0xFFFFU)&&(!most_value))/*if value more than 0xFFFF
*make two part of value for loading, first part is integer of div value at 0xFFFF
*second part is part at divide appendix
*/
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