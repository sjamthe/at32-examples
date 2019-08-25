/**
 * UART read/write on two cop ports, with one used for ROS
 **/ 
  
/* Includes ------------------------------------------------------------------*/
//#include "comms.h"

#include "bsp_uart_fifo.h"
//#include "bsp_delay.h"
#include "bsp_timer.h"
//#include "ros.h"
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif
void Delay_init();
void Delay_ms(u16 nms);
void Delay_us(u32 nus);
void Delay_sec(u16 sec);
#ifdef __cplusplus
}
#endif

static volatile uint32_t ticks;

//void uart_write(char *buf);

#define TESTCOM COM3

//ros::NodeHandle nh; /* ROS node handle */

// return the system clock as milliseconds
inline uint32_t millis(void) {
  return ticks;
  //return TMR_GetCounter(TMR3);
}

void my_delay_ms(uint32_t t) {
  uint32_t elapsed;
  uint32_t start = millis();
  do {
    elapsed = millis() - start;
  } while (elapsed < t) ;
}

static void TMR_CallBack1(void)
{
  ticks++;
  
  //char buf[512];
  //sprintf(buf,"In callback %d\n",ticks);
  //comSendBuf(TESTCOM, buf, strlen(buf));
}

void init() 
{
  /* It is recommended to assign all the priority bits to be preempt 
  * priority bits, leaving no priority bits as subpriority bits
  */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

  bsp_InitHardTimer();/* initialize TMR */
  //Delay_init();
  /* Setup USART */
  bsp_InitUart();

  bsp_StartHardTimer(1, 1000, (void*)TMR_CallBack1);//after 1ms to execute ISR
  /* ROS init, we can start UART hear in not in bsp */ 
  //nh.initNode();
}

int main(void)
{  

  init();

  // int i=0;
  char buf[512];
  // uint8_t ch;
  // int written = 0;
  while (1)
  {
    
    //nh_->spinOnce1(); 

    sprintf(buf,"Millis %d, %d\n",millis(),TMR_GetCounter(TMR3));
    comSendBuf(TESTCOM, buf, strlen(buf));
    my_delay_ms(1000);
    // Delay_ms(5000);
    // i+
    // if(written == 0) {
    //   sprintf(buf,"Testing %d\n",i);
    // }
    // comSendBuf(TESTCOM, buf, strlen(buf));

    // written = 0;
    // int j=0;
    // while(comGetChar(COM2, &ch) == 1) {
    //   comSendChar(COM2, ch);
    //   buf[j++] = ch;
    //   written = 1;
    // }

    // if(written) {
    //   buf[j++] = '\0';
    //   comSendChar(COM2,'\n');
    // }
  }

}

