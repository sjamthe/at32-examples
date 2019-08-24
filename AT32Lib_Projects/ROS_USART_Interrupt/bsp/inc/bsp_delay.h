/**
* bsp_delay.h
* Contains functions to support delay timers
**/

#ifndef _BSP_USART_FIFO_H_
#define _BSP_USART_FIFO_H_

/* Includes ------------------------------------------------------------------*/  
#include "at32f4xx.h"

 /*delay macros*/
#define STEP_DELAY_MS	500
/*delay variable*/
static __IO float fac_us;
static __IO float fac_ms;


void Delay_init();
void Delay_ms(u16 nms);
void Delay_us(u32 nus);
void Delay_sec(u16 sec);

#endif /* _BSP_USART_FIFO_H_ */