/**
 **************************************************************************
 * File Name    : at32_hoverboard.h
 * Description  : at32_hoverboard configuration file
 * Date         : 2019-08-10
 * Version      : V1.0.0
 **************************************************************************
 */

/* PINS specific for hoverboard */

#ifndef __AT32_HOVERBOARD_H
#define __AT32_HOVERBOARD_H
#include <at32f4xx.h>
#include <at32f4xx_gpio.h>
#include <at32f4xx_rcc.h>
#include <at32f4xx_usart.h>

/*
* This header include define support list:
* 	1. AT32F403 based Hoverboard
*/
//#define AT32F403Rx_HD 

#if !defined (AT32F403Rx_HD)
#error "Please compile with -DAT32F403Rx_HD for hoverboard support"
#endif


/*define usb pin*/
#define USB_DP_PIN          GPIO_Pins_12
#define USB_DM_PIN          GPIO_Pins_11

#define USB_GPIO            GPIOA
#define USB_GPIO_RCC_CLK    RCC_APB2PERIPH_GPIOA

/*AT_START LED*/
typedef enum
{
    LED1 = 0,
    LED2,
    LED3,
    LED4
}LED_Type;

#define LED_NUM     4

#ifdef AT32F403Rx_HD
/*have no LED1*/
#define LED1_PIN                0
#define LED1_GPIO               NULL
#define LED1_GPIO_RCC_CLK       0

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
#endif
/*End LED define*/


/*define button*/
typedef enum
{
    BUTTON_WAKEUP = 0,
    BUTTON_USER_KEY,
    BUTTON_KEY1_DOWN,
    BUTTON_KEY2_LEFT,
    NO_BUTTON
}BUTTON_Type;

#define BUTTON_NUM  2

#define BUTTON_WAKEUP_PIN              GPIO_Pins_0
#define BUTTON_WAKEUP_GPIO             GPIOA
#define BUTTON_WAKEUP_RCC_CLK          RCC_APB2PERIPH_GPIOA

#define BUTTON_USER_KEY_PIN            GPIO_Pins_9
#define BUTTON_USER_KEY_GPIO           GPIOB
#define BUTTON_USER_KEY_RCC_CLK       RCC_APB2PERIPH_GPIOB

/*end define button*/
#ifdef AT_START_F403_V1_2
/*Audio DAC OUTPUT GPIO Pin*/
#define F403_AUDIO_DAC_OUTPIN      GPIO_Pins_4
#endif

/**************** UART printf ****************/
// #define AT32_PRINT_UART                USART2
// #define USARTx_IRQn                    USART2_IRQn
// #define USARTx_IRQ_Handler             USART2_IRQHandler
// #define AT32_PRINT_UART_RCC            RCC_APB1PERIPH_USART2

// /*Tx*/
// #define AT32_PRINT_UARTTX_PIN          GPIO_Pins_2
// #define AT32_PRINT_UARTTX_GPIO         GPIOA
// #define AT32_PRINT_UARTTX_GPIO_RCC     RCC_APB2PERIPH_GPIOA

// /*Rx*/
// #define AT32_PRINT_UARTRX_PIN          GPIO_Pins_3
// #define AT32_PRINT_UARTRX_GPIO         GPIOA
// #define AT32_PRINT_UARTRX_GPIO_RCC     RCC_APB2PERIPH_GPIOA
/**************** End UART printf ****************/

/**************** UART printf ****************/
#define AT32_PRINT_UART                USART3
#define USARTx_IRQn                    USART3_IRQn
#define USARTx_IRQ_Handler             USART3_IRQHandler
#define AT32_PRINT_UART_RCC            RCC_APB1PERIPH_USART3

/*Tx*/
#define AT32_PRINT_UARTTX_PIN          GPIO_Pins_10
#define AT32_PRINT_UARTTX_GPIO         GPIOB
#define AT32_PRINT_UARTTX_GPIO_RCC     RCC_APB2PERIPH_GPIOB

/*Rx*/
#define AT32_PRINT_UARTRX_PIN          GPIO_Pins_11
#define AT32_PRINT_UARTRX_GPIO         GPIOB
#define AT32_PRINT_UARTRX_GPIO_RCC     RCC_APB2PERIPH_GPIOB
/**************** End UART printf ****************/

void AT32_Hoverboard_Init(void);
void AT32_USB_GPIO_init(void);
void Board_Init(void);

/*Led Operation function*/
void AT32_LEDn_Init(LED_Type led);
void AT32_LEDn_ON(LED_Type led);
void AT32_LEDn_OFF(LED_Type led);
void AT32_LEDn_Toggle(LED_Type led);

/*Button Operation function*/
void AT32_BUTTON_Init(BUTTON_Type button);
BUTTON_Type AT32_BUTTON_Press(void);
uint8_t AT32_BUTTON_State(BUTTON_Type button);

void UART_Print_Init(uint32_t bound);

/*Delay function*/
void Delay_init(void);
void Delay_us(u32 nus);
void Delay_ms(u16 nms);
void Delay_sec(u16 sec);
#endif