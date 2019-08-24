/**
 * UART read/write on two cop ports, with one used for ROS
 **/ 
  
/* Includes ------------------------------------------------------------------*/
//#include "comms.h"

#include "bsp_uart_fifo.h"
#include "bsp_delay.h"
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

void uart_write(char *buf);

int main(void)
{  

  Delay_init();
  /* Setup USART */
  bsp_InitUart();

#define TESTCOM COM3

  int i=0;
  char buf[512];
  uint8_t ch;
  int written = 0;
  while (1)
  {
    Delay_ms(5000);
    i++;
    if(written == 0) {
      sprintf(buf,"Testing %d\n",i);
    }
    comSendBuf(TESTCOM, buf, strlen(buf));

    written = 0;
    int j=0;
    while(comGetChar(COM2, &ch) == 1) {
      comSendChar(COM2, ch);
      buf[j++] = ch;
      written = 1;
    }

    if(written) {
      buf[j++] = '\0';
      comSendChar(COM2,'\n');
    }
  }

}