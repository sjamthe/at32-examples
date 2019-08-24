/**
* Modified from default example of AT32
* Contains USART2 & USART3 wrappers for Hoverboard
**/ 

/* Includes ------------------------------------------------------------------*/  
#include "bsp_uart_fifo.h"
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/  
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static UART_T g_tUart1;
static uint8_t g_TxBuf1[UART1_TX_BUF_SIZE];		/* transmit buffer */
static uint8_t g_RxBuf1[UART1_RX_BUF_SIZE];		/* receive buffer */

static UART_T g_tUart2;
static uint8_t g_TxBuf2[UART2_TX_BUF_SIZE];		/* transmit buffer */
static uint8_t g_RxBuf2[UART2_RX_BUF_SIZE];		/* receive buffer */

/* Private function prototypes -----------------------------------------------*/
static void UartVarInit(void);
static void InitHardUart2(void);
static void InitHardUart3(void);

static void EnableUart(COM_PORT_E _ucPort);
static void UartSend(UART_T *_pUart, uint8_t *_ucaBuf, uint16_t _usLen);
static uint8_t UartGetChar(UART_T *_pUart, uint8_t *_pByte);
static void UartIRQ(UART_T *_pUart);
static void ConfigUartNVIC(void);

#define ENABLE_COM2
#define ENABLE_COM3

/* Private functions ---------------------------------------------------------*/

/**
 * @brief   Initialize all hardware included on the AT-STRAT-F403 board
 * @param   None
 * @retval  None
 */
void bsp_InitUart(void)
{
	UartVarInit();		/* initialize all global parameters */

	//UART2_Init();

#ifdef ENABLE_COM2
	InitHardUart2();	/* initialize USART */
#endif
#ifdef ENABLE_COM3
	InitHardUart3();	/* initialize USART */
#endif

	ConfigUartNVIC();	/* configurate USART interrupts */

#ifdef ENABLE_COM2
	EnableUart(COM2);
#endif
#ifdef ENABLE_COM3
	EnableUart(COM3);
#endif
}


/**
 * @brief   change serial number to USART device
 * @param   _ucPort: serial number
            COM2
            COM3
 * @retval  USART device
 */

UART_T *ComToUart(COM_PORT_E _ucPort)
{
	if (_ucPort == COM2)
	{
		return &g_tUart1;
	}
	else if (_ucPort == COM3)
	{
		return &g_tUart2;
	}
	return 0;
}

/**
 * @brief   send data to TX FIFO,and in fact send out data by ISR
 * @param   _ucPort: serial number that send the data           
                COM2
                COM3
            _ucaBuf: buffer contain data that will be sent
            _usLen : length of sent data
 * @retval  None
 */
void comSendBuf(COM_PORT_E _ucPort, uint8_t *_ucaBuf, uint16_t _usLen)
{
	UART_T *pUart;

	pUart = ComToUart(_ucPort);
	if (pUart == 0)
	{
		return;
	}

	if (pUart->SendBefor != 0)
	{
		pUart->SendBefor(); /* changed to TX mode when used as RS485 communication */
	}

	UartSend(pUart, _ucaBuf, _usLen);
}

/**
 * @brief   send one byte data to TX FIFO,and in fact send out data by ISR
 * @param   _ucPort: serial number that send the data
                COM2
                COM3
            _ucByte: the sent data
 * @retval  None
 */

void comSendChar(COM_PORT_E _ucPort, uint8_t _ucByte)
{
	comSendBuf(_ucPort, &_ucByte, 1);
}

/**
 * @brief   obtain one byte data from receive FIFO, none blocked mode
 * @param   _ucPort: serial number that send the data
                COM2
                COM3
            _ucByte: the received data
 * @retval  0: no data 1:obtain the data
 */

uint8_t comGetChar(COM_PORT_E _ucPort, uint8_t *_pByte)
{
	UART_T *pUart;

	pUart = ComToUart(_ucPort);
	if (pUart == 0)
	{
		return 0;
	}

	return UartGetChar(pUart, _pByte);
}

/**
  * @brief  Clear TX fifo data
  * @param  _ucPort: serial number that send the data
                COM2
                COM3
  * @retval None
  */
void comClearTxFifo(COM_PORT_E _ucPort)
{
	UART_T *pUart;

	pUart = ComToUart(_ucPort);
	if (pUart == 0)
	{
		return;
	}

	pUart->usTxWrite = 0;
	pUart->usTxRead = 0;
	pUart->usTxCount = 0;
}

/**
  * @brief  Clear RX fifo data
  * @param  _ucPort: serial number that send the data
                COM2
                COM3
  * @retval None
  */
void comClearRxFifo(COM_PORT_E _ucPort)
{
	UART_T *pUart;

	pUart = ComToUart(_ucPort);
	if (pUart == 0)
	{
		return;
	}

	pUart->usRxWrite = 0;
	pUart->usRxRead = 0;
	pUart->usRxCount = 0;
}

/**
 * @brief   reconfigurate the baudrate
 * @param   None
 * @retval  None
 */

void bsp_SetUartBaud(COM_PORT_E _ucPort, uint32_t _baud)
{
	UART_T *pUart;

	pUart = ComToUart(_ucPort);
	if (pUart == 0)
	{
		return;
	}

	USART_InitType USART_InitStructure;

	USART_InitStructure.USART_BaudRate      = _baud;	
	USART_InitStructure.USART_WordLength    = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits      = USART_StopBits_1;
	USART_InitStructure.USART_Parity        = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode          = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(pUart->uart, &USART_InitStructure);
	
}

/**
  * @brief  Uart parameter initialization
  * @param  None
  * @retval None
  */
static void UartVarInit()
{
#ifdef ENABLE_COM2 
		g_tUart1.uart           = USART2;
		g_tUart1.pTxBuf         = g_TxBuf1;					
		g_tUart1.pRxBuf         = g_RxBuf1;					
		g_tUart1.usTxBufSize    = UART1_TX_BUF_SIZE;	
		g_tUart1.usRxBufSize    = UART1_RX_BUF_SIZE;	
		g_tUart1.usTxWrite      = 0;						
		g_tUart1.usTxRead       = 0;						
		g_tUart1.usRxWrite      = 0;						
		g_tUart1.usRxRead       = 0;						
		g_tUart1.usRxCount      = 0;						
		g_tUart1.usTxCount      = 0;						
		g_tUart1.SendBefor      = 0;						
		g_tUart1.SendOver       = 0;						
		g_tUart1.ReciveNew      = 0;						
#endif
#ifdef ENABLE_COM3
		g_tUart2.uart           = USART3;
		g_tUart2.pTxBuf         = g_TxBuf2;					
		g_tUart2.pRxBuf         = g_RxBuf2;					
		g_tUart2.usTxBufSize    = UART2_TX_BUF_SIZE;	
		g_tUart2.usRxBufSize    = UART2_RX_BUF_SIZE;	
		g_tUart2.usTxWrite      = 0;						
		g_tUart2.usTxRead       = 0;						
		g_tUart2.usRxWrite      = 0;						
		g_tUart2.usRxRead       = 0;						
		g_tUart2.usRxCount      = 0;						
		g_tUart2.usTxCount      = 0;						
		g_tUart2.SendBefor      = 0;						
		g_tUart2.SendOver       = 0;						
		g_tUart2.ReciveNew      = 0;						
#endif
}

/**
  * @brief  Hard uart2 initialization
  * Enable pin and usart interrupt clocks and config pins
  * @param  None
  * @retval None
  */
static void InitHardUart2(void)
{
	/* ------ CLOCK CONFIGURATION ------*/
    /* Enable GPIOA clock as we need TX pin PA2 and Rx pin PA3 enabled */
    RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOA, ENABLE);

    /* Enable USART2 Clock */
    RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_USART2, ENABLE); 


    /*------ GPIO CONFIGURATION ------*/
    GPIO_InitType GPIO_InitStructure;

    /* Configure USART2 Rx as input floating */
    GPIO_InitStructure.GPIO_Pins = GPIO_Pins_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure USART2 Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pins = GPIO_Pins_2;
    GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Initialize baud etc */
	bsp_SetUartBaud(COM2, UART1_BAUD);
}

/**
  * @brief  Hard uart2 initialization
  * Enable pin and usart interrupt clocks and config pins
  * @param  None
  * @retval None
  */
static void InitHardUart3(void)
{
	/* ------ CLOCK CONFIGURATION ------*/
    /* Enable GPIOA clock as we need TX pin PB10 and Rx pin PB11 enabled */
    RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOB, ENABLE);

    /* Enable USART2 Clock */
    RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_USART3, ENABLE); 


    /*------ GPIO CONFIGURATION ------*/
    GPIO_InitType GPIO_InitStructure;

    /* Configure USART2 Rx as input floating */
    GPIO_InitStructure.GPIO_Pins = GPIO_Pins_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* Configure USART2 Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pins = GPIO_Pins_10;
    GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Initialize baud etc */
	bsp_SetUartBaud(COM3, UART2_BAUD);
}

/**
  * @brief  Uart interrupt config
  * @param  None
  * @retval None
  */
static void ConfigUartNVIC(void)
{
	/* Configure the NVIC Preemption Priority Bits */  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	NVIC_InitType NVIC_InitStructure;

#ifdef ENABLE_COM2
    NVIC_InitStructure.NVIC_IRQChannel                      = USART2_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority           = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif
#ifdef ENABLE_COM3
    NVIC_InitStructure.NVIC_IRQChannel                      = USART3_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority           = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif
}

/**
 * @brief   Enable Uart
 * @param   _ucPort: serial number
            COM2
            COM3
 * @retval  USART device
 */
void EnableUart(COM_PORT_E _ucPort)
{
	UART_T *pUart;

	pUart = ComToUart(_ucPort);
	if (pUart == 0)
	{
		return;
	}
    /*------ ENABLE USART ------*/

    /* Enable USART2 Receive and Transmit interrupts */
    USART_INTConfig(pUart->uart, USART_INT_RDNE, ENABLE);
    USART_INTConfig(pUart->uart, USART_INT_TDE, ENABLE);

    /* Enable the USART2 Peripheral */
    USART_Cmd(pUart->uart, ENABLE);
}

/**
  * @brief  Uart interrupt config
  * @param  _pUart:Uart to use
  * @param  _ucaBuf:buffer contain data that will be sent
  * @param  _usLen:length of sent data
  * @retval None
  */
static void UartSend(UART_T *_pUart, uint8_t *_ucaBuf, uint16_t _usLen)
{
	uint16_t i;

	for (i = 0; i < _usLen; i++)
	{
		while (1)//wait forever until tx buffer has space
		{
			__IO uint16_t usCount;

			DISABLE_INT();
			usCount = _pUart->usTxCount;
			ENABLE_INT();

			if (usCount < _pUart->usTxBufSize)
			{
				break;
			}
		}

		/* copy data to tx buffer*/
		_pUart->pTxBuf[_pUart->usTxWrite] = _ucaBuf[i];

		DISABLE_INT();
		if (++_pUart->usTxWrite >= _pUart->usTxBufSize)//the tx write point return to the start while reach to the bottom
		{
			_pUart->usTxWrite = 0;
		}
		_pUart->usTxCount++;
		ENABLE_INT();
	}

	USART_INTConfig(_pUart->uart, USART_INT_TDE, ENABLE);//enable transmit empty interrupt
}

/**
  * @brief  Uart interrupt config
  * @param  _pUart:Uart to use
  * @param  _pByte:buffer to receive data
  * @retval 0:No data received
            1:Data read complete
  */
static uint8_t UartGetChar(UART_T *_pUart, uint8_t *_pByte)
{
	uint16_t usCount;

	DISABLE_INT();
	usCount = _pUart->usRxCount;
	ENABLE_INT();

	
	if (usCount == 0)	
	{
		return 0;
	}
	else
	{
		*_pByte = _pUart->pRxBuf[_pUart->usRxRead];		
		
		DISABLE_INT();
		if (++_pUart->usRxRead >= _pUart->usRxBufSize)
		{
			_pUart->usRxRead = 0;
		}
		_pUart->usRxCount--;
		ENABLE_INT();
		return 1;
	}
}

/**
  * @brief  Uart interrupt config
  * @param  _pUart:Uart to use
  * @retval None
  */
static void UartIRQ(UART_T *_pUart)
{
	//receive data process
	if (USART_GetITStatus(_pUart->uart, USART_INT_RDNE) != RESET)
	{
		uint8_t ch;

		ch = USART_ReceiveData(_pUart->uart);
		_pUart->pRxBuf[_pUart->usRxWrite] = ch;
		if (++_pUart->usRxWrite >= _pUart->usRxBufSize)
		{
			_pUart->usRxWrite = 0;
		}
		if (_pUart->usRxCount < _pUart->usRxBufSize)
		{
			_pUart->usRxCount++;
		}

		//if (_pUart->usRxWrite == _pUart->usRxRead)
		//if (_pUart->usRxCount == 1)
		{
			if (_pUart->ReciveNew)
			{
				_pUart->ReciveNew(ch);
			}
		}
	}

    //transmit data process
	if (USART_GetITStatus(_pUart->uart, USART_INT_TDE) != RESET)
	{
		//if (_pUart->usTxRead == _pUart->usTxWrite)
		if (_pUart->usTxCount == 0)
		{
			USART_INTConfig(_pUart->uart, USART_INT_TDE, DISABLE);
			USART_INTConfig(_pUart->uart, USART_INT_TRAC, ENABLE);
		}
		else
		{
			USART_SendData(_pUart->uart, _pUart->pTxBuf[_pUart->usTxRead]);
			if (++_pUart->usTxRead >= _pUart->usTxBufSize)
			{
				_pUart->usTxRead = 0;
			}
			_pUart->usTxCount--;
		}

	}
	else if (USART_GetITStatus(_pUart->uart, USART_INT_TRAC) != RESET)
	{
		//if (_pUart->usTxRead == _pUart->usTxWrite)
		if (_pUart->usTxCount == 0)
		{
		
			USART_INTConfig(_pUart->uart, USART_INT_TRAC, DISABLE);

			if (_pUart->SendOver)
			{
				_pUart->SendOver();
			}
		}
		else
		{
			USART_SendData(_pUart->uart, _pUart->pTxBuf[_pUart->usTxRead]);
			if (++_pUart->usTxRead >= _pUart->usTxBufSize)
			{
				_pUart->usTxRead = 0;
			}
			_pUart->usTxCount--;
		}
	}
}

/**
 * @brief   This function handles USART2 exception
 * @param   None
 * @retval  None
 */

void USART2_IRQHandler(void)
{
	UartIRQ(&g_tUart1);
}

/**
 * @brief   This function handles USART2 exception
 * @param   None
 * @retval  None
 */

void USART3_IRQHandler(void)
{
	UartIRQ(&g_tUart2);
}


//int fputc(int ch, FILE *f)
//{
//#if 0	
//	comSendChar(COM1, ch);

//	return ch;
//#else	
//	USART_SendData(AT32_PRINT_UART, (uint8_t) ch);

//	while (USART_GetFlagStatus(AT32_PRINT_UART, USART_FLAG_TRAC) == RESET)
//	{}

//	return ch;
//#endif
//}

// int fgetc(FILE *f)
// {
// #if 1	
// 	uint8_t ucData;

// 	while(comGetChar(COM1, &ucData) == 0);

// 	return ucData;
// #else
// 	while (USART_GetFlagStatus(AT32_PRINT_UART, USART_FLAG_RXNE) == RESET);

// 	return (int)USART_ReceiveData(AT32_PRINT_UART);
// #endif
// }

/**
  * @}
  */ 

/**
  * @}
  */ 
  