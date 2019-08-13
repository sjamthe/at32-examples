/**
  ******************************************************************************
  * @file    FreeRTOS/ResManagement_SafelyPrint/at32f4xx_assert.c
  * @author  Artery Technology 
  * @version V1.1.2
  * @date    2019-01-04
  * @brief   Assert Service Routines.
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
#include "at32f4xx.h"	
#include <stdio.h>

/** @addtogroup AT32F403_StdPeriph_Examples
  * @{
  */

/** @addtogroup FreeRTOS_ResManagement_SafelyPrint
  * @{
  */ 
#ifdef USE_FULL_ASSERT

/**
 * @brief   assert failed 
 * @param   file:file name
 * @param   line:line number 
 * @retval  None
 */
void assert_failed(uint8_t* file, uint32_t line)
{ 

	while (1)
	{
	}
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 
/******************* (C) COPYRIGHT 2018 ArteryTek *****END OF FILE****/ 
