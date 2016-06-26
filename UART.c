#include "Headers/UART.h"

bool init_UART(){
  // UART
  UART_Config CFG_UART;
  CFG_UART.baud = 9600;
  CFG_UART.parityEnable = true;
  CFG_UART.EvenParity = true;
  CFG_UART.Stopbits = 1;
  CFG_UART.wordLength = 8;
  uint32_t PLK = 29491200;

  //Channel 0
  PINSEL0|=(1<<0);
  PINSEL0&=~(1<<1);
  PINSEL0|=(1<<2);
  PINSEL0&=~(1<<3);   

  //Wortlänge
  switch(CFG_UART.wordLength){
  case 5: U0LCR&=~((1<<0)|(1<<1));break;
  case 6: U0LCR&=~(1<<1);U0LCR|=(1<<0);break;
  case 7: U0LCR|=(1<<1);U0LCR&=~(1<<0);break;
  case 8: U0LCR|=(1<<0)|(1<<1);break;
  default:U0LCR|=(1<<0)|(1<<1);break;
  }

  //Stopbit
  if(CFG_UART.Stopbits == 1){
  U0LCR&=~(1<<STOPBIT_SELECT);
  }
  else{
  U0LCR|=(1<<PARITY_ENABLE);
  }

  //EvenParity
  if(CFG_UART.EvenParity==true){
  U0LCR|=(1<<4);
  U0LCR&=~(1<<5);;
  }
  else{
  U0LCR&=~(1<<4);
  U0LCR&=~(1<<5);
  }

  //parityEnable
  if(CFG_UART.parityEnable==true){
  U0LCR|=(1<<PARITY_ENABLE);
  }
  else{
  U0LCR&=~(1<<PARITY_ENABLE);
  }

  // Configure baudrate
  U0LCR|=(1<<DIVISOR_LATCH_ACCESS_BIT);

  int16_t divisor = PLK/(16*CFG_UART.baud);
  uint8_t LSB = divisor;
  uint8_t MSB = divisor>>8;
  U0DLL = LSB;
  U0DLM = MSB;

  // DLAB zugriff wieder löschen
  U0LCR&=~(1<<DIVISOR_LATCH_ACCESS_BIT);

  // reset FIFO
  U0FCR|=(1<<FIFO_ENABLE)|(1<<FIFO_RESET_Rx)|(1<<FIFO_RESET_Tx);

  return(false);
}

bool sendCharacter(uint8_t character){
  while(!(U0LSR &(1<<TRANSMITTER_HOLDING_REGISTER_EMPTY))) continue;
  U0THR=character;
  return(true);
}

bool sendMessage(uint8_t *message){
  uint16_t lenght =  strlen(message);
  for(uint16_t i = 0; i<lenght;i++){
    sendCharacter(message[i]);
  }
  return(true);
}

uint16_t readCharacter(){
    while((U0LSR & 0x1)==0){}   // warten bis Zeichen verfuegbar
    return U0RBR;               // Zeichen aus UDR zurueckgeben
}
 
void readMessage(uint8_t* Message, uint16_t MaxLen){
  uint16_t NextChar;
  uint16_t StringLen = 0;

  NextChar = readCharacter();
  while( NextChar != ';' && StringLen < MaxLen - 1 ) {
    *Message++ = NextChar;
    StringLen++;
    NextChar = readCharacter();
  }

  *Message = '\0';
}