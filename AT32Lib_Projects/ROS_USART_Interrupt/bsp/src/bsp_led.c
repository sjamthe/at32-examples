/**
*   Functions to operate test LEDs on some hoverboard pins.
**/ 
  
/* Includes ------------------------------------------------------------------*/
#include "bsp_led.h"
#include "bsp_timer.h"  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/ 
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initialize led io port
  * @param  None
  * @retval None
  */
 static int ledState[5];

void bsp_InitLed(void)
{
	GPIO_InitType GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(LED2_GPIO_RCC_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(LED3_GPIO_RCC_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(LED4_GPIO_RCC_CLK, ENABLE); 
    RCC_APB2PeriphClockCmd(BUZZER_GPIO_RCC_CLK, ENABLE);  
 
	GPIO_InitStructure.GPIO_MaxSpeed    = GPIO_MaxSpeed_50MHz;
	GPIO_InitStructure.GPIO_Mode        = GPIO_Mode_OUT_PP;	

	GPIO_InitStructure.GPIO_Pins = LED2_PIN;
	GPIO_Init(LED2_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pins = LED3_PIN;
	GPIO_Init(LED3_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pins = LED4_PIN;
	GPIO_Init(LED4_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pins = BUZZER_PIN;
	GPIO_Init(BUZZER_GPIO, &GPIO_InitStructure);

	bsp_LedOff(2);
	bsp_LedOff(3);
	bsp_LedOff(4);
	ledState[2] = 0;
	ledState[3] = 0;
	ledState[4] = 0;
}

/**
  * @brief  Turn on led
  * @param  _no:Led number
  * @retval None
  */
void bsp_LedOn(uint8_t _no)
{
	switch(_no)
	{
	    case 2:
		    LED2_GPIO->BSRE = LED2_PIN;
			ledState[_no] = 1;
		    break;
		case 3:
		    LED3_GPIO->BSRE = LED3_PIN;
			ledState[_no] = 1;
		    break;
		case 4:
		    LED4_GPIO->BSRE = LED4_PIN;
			ledState[_no] = 1;
		    break;
		default:
		    break;
	}

}

/**
  * @brief  Turn off led
  * @param  _no:Led number
  * @retval None
  */
void bsp_LedOff(uint8_t _no)
{
	switch(_no)
	{
	  case 2:
		    LED2_GPIO->BRE = LED2_PIN;
			ledState[_no] = 0;
		    break;
		case 3:
		    LED3_GPIO->BRE = LED3_PIN;
			ledState[_no] = 0;
		    break;
		case 4:
		    LED4_GPIO->BRE = LED4_PIN;
			ledState[_no] = 0;
		    break;
		default:
		    break;
	}
}

/**
  * @brief  Toggle led
  * @param  _no:Led number
  * @retval None
  */
void bsp_LedToggle(uint8_t _no)
{	
	switch(_no)
	{
	    case 2:
		    LED2_GPIO->OPTDT ^= LED2_PIN;
			ledState[_no] = (ledState[_no]) ? 0:1;
		    break;
		case 3:
		    LED3_GPIO->OPTDT ^= LED3_PIN;
			ledState[_no] = (ledState[_no]) ? 0:1;
		    break;
		case 4:
		    LED4_GPIO->OPTDT ^= LED4_PIN;
			ledState[_no] = (ledState[_no]) ? 0:1;
		    break;
		default:
		    break;
	}

}

int bsp_LedState(uint8_t _no)
{
	return ledState[_no];
}

void sound_buzzer()
{
  uint8_t buzzerFreq = 0;
  uint8_t buzzerPattern = 0;

  buzzerPattern = 15;
  for (int i = 10; i >= 0; i--) {
    buzzerFreq = i;
    uint32_t buzzerTimer = 0;
    while (buzzerTimer < 5000 )
    {
        //create square wave for buzzer
        buzzerTimer++;
        if (buzzerFreq != 0 && (buzzerTimer / 20) % (buzzerPattern + 1) == 0) {
        if (buzzerTimer % buzzerFreq == 0) {
            BUZZER_GPIO->BSRE = BUZZER_PIN;
        }
        } else {
            BUZZER_GPIO->BRE = BUZZER_PIN;
        }
    }
    delay_ms(40);
  }

}
/**
  * @}
  */ 

/**
  * @}
  */ 

