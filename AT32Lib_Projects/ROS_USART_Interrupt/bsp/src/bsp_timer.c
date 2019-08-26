/**
  ******************************************************************************
  * @file    FreeRTOS/bsp.c/bsp_timer.c 
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
#include "bsp_timer.h"

/** @addtogroup AT32F403_StdPeriph_Examples
  * @{
  */

/** @addtogroup FreeRTOS_ResManagement_SafelyPrint
  * @{
  */ 
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/  
//#define USE_TMR2
#define USE_TMR3
//#define USE_TMR4
//#define USE_TMR5

#ifdef USE_TMR2
	#define TMR_HARD		TMR2
	#define TMR_HARD_IRQn	TMR2_GLOBAL_IRQn
	#define TMR_HARD_RCC	RCC_APB1PERIPH_TMR2
#endif

#ifdef USE_TMR3
	#define TMR_HARD		TMR3
	#define TMR_HARD_IRQn	TMR3_GLOBAL_IRQn
	#define TMR_HARD_RCC	RCC_APB1PERIPH_TMR3
#endif

#ifdef USE_TMR4
	#define TMR_HARD		TMR4
	#define TMR_HARD_IRQn	TMR4_GLOBAL_IRQn
	#define TMR_HARD_RCC	RCC_APB1PERIPH_TMR4
#endif

#ifdef USE_TMR5
	#define TMR_HARD		TMR5
	#define TMR_HARD_IRQn	TMR5_GLOBAL_IRQn
	#define TMR_HARD_RCC	RCC_APB1PERIPH_TMR5
#endif

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void (*s_TMR_CallBack1)(void);
static void (*s_TMR_CallBack2)(void);
static void (*s_TMR_CallBack3)(void);
static void (*s_TMR_CallBack4)(void);

/*
* Use ticks from TMR_CallBack1 to keep milli second clock needed by ROS _hardware.time().
*/
static volatile uint32_t ticks;

static void TMR_CallBack1(void)
{
  ticks++;
}

// return the system clock as milliseconds
inline uint32_t millis(void) {
  return ticks;
  //return TMR_GetCounter(TMR3);
}

void delay_ms(uint32_t t) {
  uint32_t elapsed;
  uint32_t start = millis();
  do {
    elapsed = millis() - start;
  } while (elapsed < t) ;
}

/* Private functions ---------------------------------------------------------*/
#if defined (USE_TMR2) || defined (USE_TMR3)  || defined (USE_TMR4)	|| defined (USE_TMR5)

/**
  * @brief  Initialize hard timer
  * @param  None
  * @retval None
  */
void bsp_InitHardTimer(void)
{
	TMR_TimerBaseInitType  TMR_TimeBaseStructure;
	uint32_t usPeriod;
	uint16_t usPrescaler;
	//uint32_t uiTMRxCLK;

	RCC_APB1PeriphClockCmd(TMR_HARD_RCC, ENABLE);
	
	//uiTMRxCLK = SystemCoreClock ; /// 2;

	//usPrescaler = uiTMRxCLK / 1000000 ;	//1us
  usPrescaler = 8000000 / 1000000 ;	
	usPeriod = 1000;

	/* Time base configuration */
	TMR_TimeBaseStructure.TMR_Period            = usPeriod;
	TMR_TimeBaseStructure.TMR_DIV               = usPrescaler-1;
	TMR_TimeBaseStructure.TMR_ClockDivision     = 0;
	TMR_TimeBaseStructure.TMR_CounterMode       = TMR_CounterDIR_Up;

	TMR_TimeBaseInit(TMR_HARD, &TMR_TimeBaseStructure);

	TMR_ARPreloadConfig(TMR_HARD, ENABLE);

	/* TMRx enable counter */
	TMR_Cmd(TMR_HARD, ENABLE);

    NVIC_InitType NVIC_InitStructure;	

	NVIC_InitStructure.NVIC_IRQChannel = TMR_HARD_IRQn;

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = 4;	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority           = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

  /* Initialize TMR3 with 1ms timer, needed by ROS */
  bsp_StartHardTimer(1, 1000, (void*)TMR_CallBack1);
}

/**
  * @brief  Set interrupt
  * @param  _CC:Compare channel
  * @param  _uiTimeOut:Timeout value
  * @param  _pCallBack:Callback function
  * @retval None
  */
void bsp_StartHardTimer(uint8_t _CC, uint32_t _uiTimeOut, void * _pCallBack)
{
    uint32_t cnt_now;
    uint32_t cnt_tar;

    if (_uiTimeOut < 5)
    {
        ;
    }
    else
    {
        _uiTimeOut -= 5;
    }

    cnt_now = TMR_GetCounter(TMR_HARD);    	
    cnt_tar = cnt_now + _uiTimeOut;			
    if (_CC == 1)
    {
        s_TMR_CallBack1 = (void (*)(void))_pCallBack;

        TMR_SetCompare1(TMR_HARD, cnt_tar);      	
        TMR_ClearITPendingBit(TMR_HARD, TMR_INT_CC1);
		    TMR_INTConfig(TMR_HARD, TMR_INT_CC1, ENABLE);	

    }
    else if (_CC == 2)
    {
		  s_TMR_CallBack2 = (void (*)(void))_pCallBack;

      TMR_SetCompare2(TMR_HARD, cnt_tar);      	
		  TMR_ClearITPendingBit(TMR_HARD, TMR_INT_CC2);
		  TMR_INTConfig(TMR_HARD, TMR_INT_CC2, ENABLE);	
    }
    else if (_CC == 3)
    {
        s_TMR_CallBack3 = (void (*)(void))_pCallBack;

        TMR_SetCompare3(TMR_HARD, cnt_tar);      	
        TMR_ClearITPendingBit(TMR_HARD, TMR_INT_CC3);
	    	TMR_INTConfig(TMR_HARD, TMR_INT_CC3, ENABLE);	
    }
    else if (_CC == 4)
    {
        s_TMR_CallBack4 = (void (*)(void))_pCallBack;

        TMR_SetCompare4(TMR_HARD, cnt_tar);      	
		TMR_ClearITPendingBit(TMR_HARD, TMR_INT_CC4);
		TMR_INTConfig(TMR_HARD, TMR_INT_CC4, ENABLE);	
    }
	else
    {
        return;
    }
}
#endif

/**
  * @brief  Interrupt handler
  * @param  None
  * @retval None
  */
#ifdef USE_TMR2
void TMR2_GLOBAL_IRQHandler(void)
#endif

#ifdef USE_TMR3
void TMR3_GLOBAL_IRQHandler(void)
#endif

#ifdef USE_TMR4
void TMR4_GLOBAL_IRQHandler(void)
#endif

#ifdef USE_TMR5
void TMR5_GLOBAL_IRQHandler(void)
#endif
{
    if (TMR_GetINTStatus(TMR_HARD, TMR_INT_CC1))
    {
        TMR_ClearITPendingBit(TMR_HARD, TMR_INT_CC1);
        //TMR_INTConfig(TMR_HARD, TMR_INT_CC1, DISABLE);
        
        s_TMR_CallBack1();
    }

    if (TMR_GetINTStatus(TMR_HARD, TMR_INT_CC2))
    {
        TMR_ClearITPendingBit(TMR_HARD, TMR_INT_CC2);
        TMR_INTConfig(TMR_HARD, TMR_INT_CC2, DISABLE);	

        s_TMR_CallBack2();
    }

    if (TMR_GetINTStatus(TMR_HARD, TMR_INT_CC3))
    {
        TMR_ClearITPendingBit(TMR_HARD, TMR_INT_CC3);
        TMR_INTConfig(TMR_HARD, TMR_INT_CC3, DISABLE);	

        s_TMR_CallBack3();
    }

    if (TMR_GetINTStatus(TMR_HARD, TMR_INT_CC4))
    {
        TMR_ClearITPendingBit(TMR_HARD, TMR_INT_CC4);
        TMR_INTConfig(TMR_HARD, TMR_INT_CC4, DISABLE);	

        s_TMR_CallBack4();
    }
}

/**
  * @}
  */ 

/**
  * @}
  */ 
  
/******************* (C) COPYRIGHT 2018 ArteryTek *****END OF FILE****/ 
