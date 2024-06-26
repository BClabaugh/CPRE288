/*
*
*   uart.c
*
*
*
*   @author
*   @date
*/
//
//#include <inc/tm4c123gh6pm.h>
//#include <stdint.h>
//#include "uart.h"
//
////#define SYSCTL_RCGCGPIO_R (*((volatile unsigned long *) 0x400FE608))
////#define SYSCTL_PRGPIO_R (*((volatile unsigned long *) 0x400FEA08))
////#define SYSCTL_RCGCUART_R (*((volatile unsigned long *) 0x400FE618))
////#define SYSCTL_PRUART_R (*((volatile unsigned long *) 0x400FEA18))
////#define GPIO_PORTB_AFSEL_R (*((volatile unsigned long *) 0x40005420))
////#define GPIO_PORTB_DEN_R (*((volatile unsigned long *) 0x4000551C))
////#define GPIO_PORTB_PCTL_R (*((volatile unsigned long *) 0x4000552C))
////#define UART1_CTL_R (*((volatile unsigned long *) 0x4000D030))
////#define UART1_IBRD_R (*((volatile unsigned long *) 0x4000D024))
////#define UART1_FBRD_R (*((volatile unsigned long *) 0x4000D028))
////#define UART1_LCRH_R (*((volatile unsigned long *) 0x4000D02C))
////#define UART1_CC_R (*((volatile unsigned long *) 0x4000DFC8))
////
////#define UART1_DR_R (*((volatile unsigned long *) 0x4000D000))
//
//
//void uart_init(void){
//	//TODO
//  //enable clock to GPIO port B
//  SYSCTL_RCGCGPIO_R |= 0b000010;
//
//  //enable clock to UART1
//  SYSCTL_RCGCUART_R |= 0x02;
//
//  //wait for GPIOB and UART1 peripherals to be ready
//  while ((SYSCTL_PRGPIO_R & 0x02) == 0) {};
//  while ((SYSCTL_PRUART_R & 0x02) == 0) {};
//
//  //enable alternate functions on port B pins
//  GPIO_PORTB_AFSEL_R |= 0x03;
//
//  //enable digital functionality on port B pins
//  GPIO_PORTB_DEN_R |= 0x03;
//
//  //enable UART1 Rx and Tx on port B pins
//  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFFFFFF00) + 0x00000011;
//
//  //calculate baud rate
//  uint16_t iBRD = (int)(16000000 / (16 * 115200)); //use equations
//  uint16_t fBRD = (int)(0.6808 * 64 + 0.5); //use equations
//
//  //turn off UART1 while setting it up
//  UART1_CTL_R &= 0xFFFFFFFE;
//
//  //set baud rate
//  //note: to take effect, there must be a write to LCRH after these assignments
//  UART1_IBRD_R = iBRD;
//  UART1_FBRD_R = fBRD;
//
//  //set frame, 8 data bits, 1 stop bit, no parity, no FIFO
//  //note: this write to LCRH must be after the BRD assignments
//  UART1_LCRH_R = 0x00000060;
//
//  //use system clock as source
//  //note from the datasheet UARTCCC register description:
//  //field is 0 (system clock) by default on reset
//  //Good to be explicit in your code
//  UART1_CC_R = 0x00;
//
//  //re-enable UART1 and also enable RX, TX (three bits)
//  //note from the datasheet UARTCTL register description:
//  //RX and TX are enabled by default on reset
//  //Good to be explicit in your code
//  //Be careful to not clear RX and TX enable bits
//  //(either preserve if already set or set them)
//  UART1_CTL_R |= 0x301;
//
//}
//
//void uart_sendChar(char data){
//	while(UART1_FR_R & 0x20)
//  {
//  }
//
//  UART1_DR_R = data;
//}
//
//char uart_receive(void){
//	char data = 0;
//
//  while(UART1_FR_R & UART_FR_RXFE)
//  {
//  }
//
//  data = (char)(UART1_DR_R & 0xFF);
//
//  return data;
//}
//
//char uart_receive_nonblocking(void){
//	char data = 0;
//
//  if((UART1_FR_R | UART_FR_RXFE))
//  {
//    data = (char)(UART1_DR_R & 0xFF);
//    return data;
//  }
//
//  return '0';
//}
//
//void uart_sendStr(const char *data){
//	//TODO for reference see lcd_puts from lcd.c file
//
//  while(*data != '\0')
//  {
//    uart_sendChar(*data);
//    data++;
//  }
//}


