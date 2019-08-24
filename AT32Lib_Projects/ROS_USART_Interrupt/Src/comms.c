/**
 * comms.c: All USART setup functions
 **/

/* Includes ------------------------------------------------------------------*/
#include "comms.h"

/* Private variables ---------------------------------------------------------*/
uint8_t TxBuffer[] = "\n\rUSART Hyperterminal Interrupts Example: USART-Hyperterminal\
 communication using Interrupt\n\r";
uint8_t RxBuffer[RxBufferSize];
uint8_t NbrOfDataToTransfer = TxBufferSize;
uint8_t NbrOfDataToRead = RxBufferSize;
uint8_t TxCounter = 0; 
uint16_t RxCounter = 0;

void UART2_Init()
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


    /*------ NVIC CONFIGURATION ------*/
    
    /* Configure the NVIC Preemption Priority Bits */  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    
    /* Enable the USART2 Interrupt */
    NVIC_InitType NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);


    /*------ BAUD AND OTHER CONFIGURATION ------*/
    USART_InitType USART_InitStructure;

    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.USART_BaudRate = BAUD_RATE;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);

    /*------ ENABLE USART2 ------*/

    /* Enable USART2 Receive and Transmit interrupts */
    USART_INTConfig(USART2, USART_INT_RDNE, ENABLE);
    USART_INTConfig(USART2, USART_INT_TDE, ENABLE);

    /* Enable the USART2 Peripheral */
    USART_Cmd(USART2, ENABLE);
}

/**
  * @brief  This function handles USART1 global interrupt request.
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
  if(USART_GetITStatus(USART2, USART_INT_RDNE) != RESET)
  {
    /* Read one byte from the receive data register */
    RxBuffer[RxCounter++] = (USART_ReceiveData(USART2) & 0x7F);

    if(RxCounter == NbrOfDataToRead)
    {
      /* Disable the USART Receive interrupt */
      USART_INTConfig(USART2, USART_INT_RDNE, DISABLE);
    }
  }

  if(USART_GetITStatus(USART2, USART_INT_TDE) != RESET)
  {   
    /* Write one byte to the transmit data register */
    USART_SendData(USART2, TxBuffer[TxCounter++]);

    if(TxCounter == NbrOfDataToTransfer)
    {
      /* Disable the USART Transmit interrupt */
      USART_INTConfig(USART2, USART_INT_TDE, DISABLE);
      TxCounter = 0;
    }
  }
}