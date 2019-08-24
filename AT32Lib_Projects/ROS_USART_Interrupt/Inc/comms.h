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

typedef struct
{
	USART_Type *uart;		            /* Device */
	uint8_t *pTxBuf;			        /* point to transmit buffer */
	uint8_t *pRxBuf;			        /* point to receive buffer */
	uint16_t usTxBufSize;		        /* size of transmit buffer */
	uint16_t usRxBufSize;		        /* size of receive buffer */
	__IO uint16_t usTxWrite;		    /* index for write */
	__IO uint16_t usTxRead;			    /* index for read */
	__IO uint16_t usTxCount;		    /* the remain number of waiting */

	__IO uint16_t usRxWrite;		    /* index for write */
	__IO uint16_t usRxRead;			    /* index for read */
	__IO uint16_t usRxCount;		    /* the remain number for reading */

	void (*SendBefor)(void); 	        /* callback function for before starting transmit��used to change to transmit mode for RS485�� */
	void (*SendOver)(void); 	        /* callback function for after transmit complete��used to change to receive mode for RS485�� */
	void (*ReciveNew)(uint8_t _byte);	/* callback function while some data arrived */
}UART_T;

#endif