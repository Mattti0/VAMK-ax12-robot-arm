/*
 * USART_driver.c
 *
 * Created: 21.9.2015 12:04:02
 *  Author: e1100983
 */
#include "USART_driver.h"

Err_t USART_Transmit(uint8_t port, uint8_t data)
{
  Err_t err = ERROR;

  switch(port)
  {
    case 0:
      while (!(UCSR0A & (1 << UDRE0)));
      UDR0 = data;
      err = ERROR_OK;
      break;

    case 1:
      while (!(UCSR1A & (1 << UDRE1)));
      UDR1 = data;
      err = ERROR_OK;
      break;

    default:
      err = INVALID_PORT;
      break;
  }
  return err;
}

void USART_Init()
{

  UBRR0H = 0x00;
  UBRR0L = ((XTAL / 16) / BAUD_SERVO) - 1;
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
  UCSR1C |= (1 << UCSZ00)| (1 << UCSZ01);

  UBRR1H = 0x00;
  UBRR1L = ((XTAL / 16) / BAUD_MODBUS) - 1;
  UCSR1B |= (1 << RXEN1) | (1 << TXEN1);
  UCSR1C |= (1 << UCSZ10)| (1 << UCSZ11);
  
  //DDRE  |= (1 << PINE2 | 1 << PINE3); /* Set TX and control pins to out */
  //PORTE |= (1 << PINE2 | 1 << PINE3); /* Enable pul-up resistors */
  //PORTE = 0xFE;
}

uint8_t USART_Receive(uint8_t port)
{
  uint8_t data;

  switch(port)
  {
    case 0:
      while( !(UCSR0A & (1<<RXC)) );
      return UDR0;
      break;

    case 1:
      while( !(UCSR1A & (1<<RXC)) );
      return UDR1;
      break;
    
    default:
      break;
  }

  return 0;
}
