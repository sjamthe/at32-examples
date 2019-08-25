/**
 * UART read/write on two cop ports, with one used for ROS
 **/ 
  
/* Includes ------------------------------------------------------------------*/
#include "bsp_uart_fifo.h"
#include "bsp_timer.h"
#include <stdio.h>
#include <string.h>

void ros_init(void);
void ros_run(void);

/*
* Initialize all functionslity needed
*/ 
void init() 
{
  /* It is recommended to assign all the priority bits to be preempt 
  * priority bits, leaving no priority bits as subpriority bits
  */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

  bsp_InitHardTimer();/* initialize TMR */
  /* Setup USART */
  bsp_InitUart();

  ros_init();
}

int main(void)
{  

  init();

  char buf[512];
  while (1)
  {
    ros_run();

    // sprintf(buf,"Millis %d\n",millis());
    // printf(buf);
    delay_ms(1000);

  }

}

