/**
*
**/ 

#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "at32f4xx.h"

typedef enum
{
    LED2 = 2,
    LED3,
    LED4
}LED_Type;

#define LED_NUM     4

#ifdef AT32F403Rx_HD

#define LED2_PIN                GPIO_Pins_13
#define LED2_GPIO               GPIOC
#define LED2_GPIO_RCC_CLK       RCC_APB2PERIPH_GPIOC

#define LED3_PIN                GPIO_Pins_14
#define LED3_GPIO               GPIOC
#define LED3_GPIO_RCC_CLK       RCC_APB2PERIPH_GPIOC

#define LED4_PIN                GPIO_Pins_15
#define LED4_GPIO               GPIOC
#define LED4_GPIO_RCC_CLK       RCC_APB2PERIPH_GPIOC

#define POWER_PIN              GPIO_Pins_5
#define POWER_GPIO             GPIOA
#define POWER_RCC_CLK          RCC_APB2PERIPH_GPIOA

#define BUZZER_PIN             GPIO_Pins_4
#define BUZZER_GPIO            GPIOA
#define BUZZER_GPIO_RCC_CLK    RCC_APB2PERIPH_GPIOA

#endif
/*End LED define*/

#ifdef __cplusplus
extern "C"
{
#endif

void bsp_InitLed(void);
void bsp_LedOn(uint8_t _no);
void bsp_LedOff(uint8_t _no);
void bsp_LedToggle(uint8_t _no);
int bsp_LedState(uint8_t _no);
void sound_buzzer(void);

#ifdef __cplusplus
}
#endif

#endif /* END of __BSP_LED_H */