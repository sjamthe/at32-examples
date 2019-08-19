/**
  ******************************************************************************
  * @file    FreeRTOS/bsp/bsp_uart_fifo.h
  * @author  Artery Technology
  * @version V1.1.2
  * @date    2019-01-04
  * @brief   Bsp Service Routines.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, ARTERYTEK SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2018 ArteryTek</center></h2>
  ******************************************************************************
  */
  

#ifndef _BSP_USART_FIFO_H_
#define _BSP_USART_FIFO_H_

/*
 * function configuration:
 *
 * (1)USART1 -----> RS232
	  PA9/USART1_TX	 
	  PA10/USART1_RX
	  
 * (2)USART2 -----> GPRS
	  PA2/USART2_TX
	  PA3/USART2_RX 

 * (3)USART3 -----> RS485
	  PB10/USART3_TX
	  PB11/USART3_RX
	  PB2/BOOT1/RS485_TX_EN
 */
 
#define	UART1_FIFO_EN	1

typedef enum
{
	COM1 = 0,	/* USART1  PA9, PA10 */
	COM2 = 1,	/* USART2, PA2, PA3 */
	COM3 = 2,	/* USART3, PB10, PB11 */
	COM4 = 3,	/* UART4, PC10, PC11 */
	COM5 = 4,	/* UART5, PC12, PD2 */
}COM_PORT_E;

/* define baudrate, the size of FIFO buffer, support full-duplex transmission */
#if UART1_FIFO_EN == 1
	#define UART1_BAUD			115200
	#define UART1_TX_BUF_SIZE	2*1024
	#define UART1_RX_BUF_SIZE	2*1024

#ifndef UART2_PRINT_PORT //use port different from print_port

	#define UART1_PORT         		USART2
	#define UART1_IRQ             	USART2_IRQn
	#define USARTx_IRQ_Handler      USART2_IRQHandler
	#define UART1_RCC         		RCC_APB1PERIPH_USART2

	/*Tx*/
	#define UART1_TX_PIN          	GPIO_Pins_2
	#define UART1_TX_GPIO         	GPIOA
	#define UART1_TX_GPIO_RCC     	RCC_APB2PERIPH_GPIOA

	/*Rx*/
	#define UART1_RX_PIN          	GPIO_Pins_3
	#define UART1_RX_GPIO         	GPIOA
	#define UART1_RX_GPIO_RCC     	RCC_APB2PERIPH_GPIOA
#else

	#define UART1_PORT         		USART3
	#define UART1_IRQ             	USART3_IRQn
	#define USARTx_IRQ_Handler      USART3_IRQHandler
	#define UART1_RCC         		RCC_APB1PERIPH_USART3

	/*Tx*/
	#define UART1_TX_PIN          	GPIO_Pins_10
	#define UART1_TX_GPIO         	GPIOB
	#define UART1_TX_GPIO_RCC     	RCC_APB2PERIPH_GPIOB

	/*Rx*/
	#define UART1_RX_PIN          	GPIO_Pins_11
	#define UART1_RX_GPIO         	GPIOB
	#define UART1_RX_GPIO_RCC     	RCC_APB2PERIPH_GPIOB
#endif
#endif

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

void bsp_SetUart1Baud(uint32_t _baud);
#ifdef __cplusplus
}
#endif

#endif



/******************* (C) COPYRIGHT 2018 ArteryTek *****END OF FILE****/
