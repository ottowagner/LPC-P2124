#include "Headers/GPIO.h"

void checkPin(uint16_t *pinNr){
  uint8_t returnStr[300] = "\r\nFunktion: ";
  int16_t cleanPINSEL;

  if(*pinNr <=15){
    cleanPINSEL = PINSEL0 & ((1<<(uint16_t)(*pinNr*2))|1<<(uint16_t)((*pinNr*2)+1));
    cleanPINSEL = cleanPINSEL>>(*pinNr*2);
  }
  else if(*pinNr>15 && *pinNr<=31){
    cleanPINSEL = PINSEL1 & ((1<<(uint16_t)((*pinNr-16)*2))|1<<(uint16_t)(((*pinNr-16)*2)+1));
    cleanPINSEL = cleanPINSEL>>((*pinNr-16)*2);
  }
  else{
    strcpy(returnStr, "\r\nFalsche Eingabe!");
    sendMessage(returnStr);
    return;
  }

  if(cleanPINSEL == ((1<<1)|(1<<0))){
    strcat(returnStr, F11[*pinNr]);
  }else if(cleanPINSEL == ((0<<1)|(1<<0))){
    strcat(returnStr, F01[*pinNr]);
  }else if(cleanPINSEL == ((1<<1)|(0<<0))){
    strcat(returnStr, F10[*pinNr]);
  }
  else{
    strcat(returnStr, "GPIO (");
    if (readDirection(pinNr) == 1){
      uint8_t dirMessage[] = "Der Ausgang";
      strcat(returnStr, dirMessage);
    }
    else{
      uint8_t dirMessage[] = "Der Eingang";
      strcat(returnStr, dirMessage);
    }
    if (readState(pinNr) == 1){
      uint8_t stateMessage[] = " ist aktiviert)";
      strcat(returnStr, stateMessage);
    }
    else{
      uint8_t stateMessage[] = " ist deaktiviert)";
      strcat(returnStr, stateMessage);
    }
  }

  sendMessage(returnStr);
}

bool readDirection(uint16_t *pinNr){
  bool direction = false;

  if(*pinNr<=31){
    if((IO0DIR & (1<<*pinNr))==(1<<*pinNr)){
      direction = true;
    }
    else{
      direction = false;
    }
  
  }
  return direction;
}

bool readState(uint16_t *pinNr){
  bool status = 0;

  if(*pinNr<=31){
    if((IO0PIN & (1<<*pinNr))==(1<<*pinNr)){
      status = 1;
    }
    else{
      status = 0;
    }
  
  }
  return status;
}

bool setIO(IO_params *paramset){
  
  if(paramset->pinNr <=15 & paramset->pinNr >1){
    PINSEL0 &= ~((1<<(paramset->pinNr*2))|(1<<((paramset->pinNr*2)+1))); 
  }
  else if(paramset->pinNr>15 && paramset->pinNr<=31){
    PINSEL1 &= ~((1<<((paramset->pinNr-16)*2))|(1<<(((paramset->pinNr-16)*2)+1)));
  }
  else{
    uint8_t error[] = "\r\nFalsche Eingabe!\r\n";
    sendMessage(error);
    return(true);
  }
  
  if(paramset->pinNr<31 & paramset->pinNr>1){
    if(paramset->direction==1){
      IO0DIR|=(1<<paramset->pinNr);
    }
    else{
      IO0DIR&=~(1<<paramset->pinNr);
    }

    if(paramset->state==0){
      IO0CLR|=(1<<paramset->pinNr);
    }
    else{
      IO0SET|=(1<<paramset->pinNr);
    }
  }
  return(true);
}