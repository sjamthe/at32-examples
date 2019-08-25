/**
 * UART read/write on two cop ports, with one used for ROS
 **/ 
  
/* Includes ------------------------------------------------------------------*/
#include "bsp_uart_fifo.h"
//#include "bsp_delay.h"
#include "bsp_timer.h"
#include "ros.h"
#include <stdio.h>
#include <string.h>

ros::NodeHandle nh; /* ROS node handle */

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

  /* ROS init, we can start UART hear in not in bsp */ 
  nh.initNode();
}

int main(void)
{  

  init();

  char buf[512];
  while (1)
  {
    
    nh.spinOnce1(); 

    // sprintf(buf,"Millis %d\n",millis());
    // printf(buf);
    delay_ms(1000);

  }

}

