## These examples are to test the HAL port for AT32 based hoverboard

All examples start with code on bluepill (STM32) then the code is ported to AT32 and tested

1. bluepill-blink-at32port - Working
2. bluepill_uart_simple-at32port - Working on AT32

## Examples based on Artery's BSP (Board Support Package)
While I was working on above examples a new BSP was released by Artery Tech.
I decided to switch to that as it may have better support!

1. AT32Lib_Projects/LED_Toggle working on hoverboard
2. AT32Lib_Projects/USART_Interrupt works on hoverboard
3. AT32Lib_Projects/USART_Printf works on hoverboard
4. FreeRTOS_SafelyPrint works on hoverboard

