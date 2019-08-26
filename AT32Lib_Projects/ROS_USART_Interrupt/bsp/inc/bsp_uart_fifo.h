/**
* Modified from default example of AT32
* Contains USART2 & USART3 wrappers for Hoverboard
**/

#ifndef _BSP_USART_FIFO_H_
#define _BSP_USART_FIFO_H_

/* Includes ------------------------------------------------------------------*/  
#include "at32f4xx.h"


#ifndef USE_FreeRTOS
	#define ENABLE_INT()	__set_PRIMASK(0)	/* enable global interrupt */
	#define DISABLE_INT()	__set_PRIMASK(1)	/* disable global interrupt */
#endif
/*
 * function configuration:
 *
 * (2)USART2 
	  PA2/USART2_TX
	  PA3/USART2_RX 

 * (3)USART3 
	  PB10/USART3_TX
	  PB11/USART3_RX
 */
 
typedef enum
{
	COM2 = 1,	/* USART2, PA2, PA3 */
	COM3 = 2,	/* USART3, PB10, PB11 */
}COM_PORT_E;

/* define baudrate, the size of FIFO buffer, support full-duplex transmission */
#define UART1_BAUD			115200
#define UART1_TX_BUF_SIZE	512
#define UART1_RX_BUF_SIZE	512

#define UART2_BAUD			115200
#define UART2_TX_BUF_SIZE	10 // DEBUG, default should be 512
#define UART2_RX_BUF_SIZE	512

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

#ifdef __cplusplus
extern "C"
{
#endif
void bsp_InitUart(void);
void comSendBuf(COM_PORT_E _ucPort, uint8_t *_ucaBuf, uint16_t _usLen);
void comSendChar(COM_PORT_E _ucPort, uint8_t _ucByte);
uint8_t comGetChar(COM_PORT_E _ucPort, uint8_t *_pByte);

void comClearTxFifo(COM_PORT_E _ucPort);
void comClearRxFifo(COM_PORT_E _ucPort);

void bsp_SetUartBaud(COM_PORT_E _ucPort, uint32_t _baud);
#ifdef __cplusplus
}
#endif

#endif

