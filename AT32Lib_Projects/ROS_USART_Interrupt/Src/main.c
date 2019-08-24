/**
 * UART read/write on two cop ports, with one used for ROS
 **/ 
  
/* Includes ------------------------------------------------------------------*/
//#include "comms.h"

#include "bsp_uart_fifo.h"
#include <stdio.h>
#include <string.h>

 /*delay macros*/
#define STEP_DELAY_MS	500
/*delay variable*/
static __IO float fac_us;
static __IO float fac_ms;
void Delay_ms(u16 nms);
void Delay_init();
void uart_write(char *buf);

int main(void)
{  

  Delay_init();
  /* Setup USART */
  bsp_InitUart();

  int i=0;
  char buf[512];
  uint8_t ch;
  while (1)
  {
    Delay_ms(1000);
    i++;
    sprintf(buf,"Testing %d\n",i);
    comSendBuf(COM2, buf, strlen(buf));
    while(comGetChar(COM2, &ch) == 1) {
      comSendChar(COM2, ch);
    }

    comSendChar(COM2,'\n');
  }

}

void Delay_init()
{
    /*Config Systick*/
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    fac_us=(float)SystemCoreClock/(192 * 1000000);
    fac_ms=fac_us*1000;
}


/**
  * @brief  Inserts a delay time.
  * @param  nus: specifies the delay time length, in microsecond.
  * @retval None
  */
void Delay_us(u32 nus)
{
    u32 temp;
    SysTick->LOAD = nus*fac_us;
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;
    do
    {
        temp = SysTick->CTRL;
    }while((temp & 0x01) &&! (temp & (1<<16)));

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0X00;
}

/**
  * @brief  Inserts a delay time.
  * @param  nms: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay_ms(u16 nms)
{
    u32 temp;
    while(nms)
    {
        if(nms > STEP_DELAY_MS)
        {
            SysTick->LOAD = (u32)STEP_DELAY_MS * fac_ms;
            nms -= STEP_DELAY_MS;
        }
        else
        {
            SysTick->LOAD = (u32)nms * fac_ms;
            nms = 0;
        }
        SysTick->VAL = 0x00;
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
        do
        {
            temp = SysTick->CTRL;
        }while( (temp & 0x01) && !(temp & (1<<16)) );

        SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
        SysTick->VAL = 0X00;
    }
}

/**
  * @brief  Inserts a delay time.
  * @param  sec: specifies the delay time length, in seconds.
  * @retval None
  */
void Delay_sec(u16 sec)
{
    u16 i;
    for(i=0; i<sec; i++)
    {
        Delay_ms(500);
        Delay_ms(500);
    }
}