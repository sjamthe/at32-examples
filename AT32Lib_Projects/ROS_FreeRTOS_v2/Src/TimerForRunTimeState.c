/**
  ******************************************************************************
  * @file    FreeRTOS/Src/TimerForRunTimeState.c
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
  
/* Includes ------------------------------------------------------------------*/  
#include "bsp.h"

/** @addtogroup AT32F403_StdPeriph_Examples
  * @{
  */

/** @addtogroup FreeRTOS_ResManagement_SafelyPrint
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define  timerINTERRUPT_FREQUENCY	20000 //50us
#define  timerHIGHEST_PRIORITY		1

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//the time base for gathering task statistics  
volatile uint32_t ulHighFrequencyTimerTicks = 0UL;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
void vTimerInitForRunTimeState(void);
#ifdef __cplusplus
}
#endif

/**
  * @brief  Configure timer6 for gather task statistcs
  * @param  None
  * @retval None
  */
void vTimerInitForRunTimeState(void)
{
	bsp_SetTMRforInt(TMR6, timerINTERRUPT_FREQUENCY, timerHIGHEST_PRIORITY, 0);
}

/**
  * @brief  Interrupt handler for timer 6
  * @param  None
  * @retval None
  */
void TMR6_GLOBAL_IRQHandler( void )
{
	if(TMR_GetINTStatus(TMR6, TMR_INT_Overflow) != RESET)
	{
		ulHighFrequencyTimerTicks++;
		TMR_ClearITPendingBit(TMR6, TMR_INT_Overflow);
	}
}


/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2018 ArteryTek *****END OF FILE****/
