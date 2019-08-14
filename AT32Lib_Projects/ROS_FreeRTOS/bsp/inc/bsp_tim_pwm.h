/**
  ******************************************************************************
  * @file    Project/bsp/bsp_tim_pwm.h
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

#ifndef __BSP_TMR_PWM_H
#define __BSP_TMR_PWM_H

void bsp_SetTIMOutPWM(GPIO_Type* GPIOx, uint16_t GPIO_Pin, TMR_Type* TIMx, uint8_t _ucChannel,
	 uint32_t _ulFreq, uint32_t _ulDutyCycle);

void bsp_SetTIMOutPWM_N(GPIO_Type* GPIOx, uint16_t GPIO_Pin, TMR_Type* TIMx, uint8_t _ucChannel,
	 uint32_t _ulFreq, uint32_t _ulDutyCycle);
	 
void bsp_SetTMRforInt(TMR_Type* TIMx, uint32_t _ulFreq, uint8_t _PreemptionPriority, uint8_t _SubPriority);

#endif


/******************* (C) COPYRIGHT 2018 ArteryTek *****END OF FILE****/
