/**
  ******************************************************************************
  * @file    FreeRTOS/bsp/bsp_timer.h
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

#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H

  
#define TMR_COUNT	4	

typedef enum
{
	TMR_ONCE_MODE = 0,
	TMR_AUTO_MODE = 1		
}TMR_MODE_E;


typedef struct
{
	volatile uint8_t Mode;	
	volatile uint8_t Flag;	
	volatile uint32_t Count;	
	volatile uint32_t PreLoad;	
}SOFT_TMR;


void bsp_InitTimer(void);
void bsp_DelayMS(uint32_t n);
void bsp_DelayUS(uint32_t n);
void bsp_StartTimer(uint8_t _id, uint32_t _period);
void bsp_StartAutoTimer(uint8_t _id, uint32_t _period);
void bsp_StopTimer(uint8_t _id);
uint8_t bsp_CheckTimer(uint8_t _id);
int32_t bsp_GetRunTime(void);
int32_t bsp_CheckRunTime(int32_t _LastTime);

void bsp_InitHardTimer(void);
void bsp_StartHardTimer(uint8_t _CC, uint32_t _uiTimeOut, void * _pCallBack);

#endif

  
  
/******************* (C) COPYRIGHT 2018 ArteryTek *****END OF FILE****/
