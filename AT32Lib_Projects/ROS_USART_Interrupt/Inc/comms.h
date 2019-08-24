/**
 * comms.h: All USART defines
 **/

#ifndef __COMMS_H
#define __COMMS_H

#include "at32f4xx.h"

/* Private define ------------------------------------------------------------*/
#define BAUD_RATE 115200
#define TxBufferSize   (countof(TxBuffer) - 1)
#define RxBufferSize   0x20

/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))
 
void UART2_Init();

#endif