#include "Headers/ADC.h"

void init_ADC(uint16_t pinNr){
  switch(pinNr) {
    case 27:  PINSEL1|=(1<<AIN0_22);
              PINSEL1&=~(1<<AIN0_23);
              //Select AIN0
              ADCR|=(1<<AIN0_SEL);
              ADCR&=~((1<<AIN1_SEL)|(1<<AIN2_SEL)|(1<<AIN3_SEL));
              break;
    case 28:  PINSEL1|=(1<<AIN1_24);
              PINSEL1&=~(1<<AIN1_25);
              //Select AIN1
              ADCR|=(1<<AIN1_SEL);   
              ADCR&=~((1<<AIN0_SEL)|(1<<AIN2_SEL)|(1<<AIN3_SEL));
              break;
    case 29:  PINSEL1|=(1<<AIN2_26);
              PINSEL1&=~(1<<AIN2_27);
              //Select AIN2
              ADCR|=(1<<AIN2_SEL);        
              ADCR&=~((1<<AIN0_SEL)|(1<<AIN1_SEL)|(1<<AIN3_SEL));
              break;
    case 30:  PINSEL1|=(1<<AIN3_28);
              PINSEL1&=~(1<<AIN3_29);
              //Select AIN3
              ADCR|=(1<<AIN3_SEL);               
              ADCR&=~((1<<AIN0_SEL)|(1<<AIN1_SEL)|(1<<AIN2_SEL));
              break;
  }

  ADCR|=(1<<CLKDIV_9)|(1<<CLKDIV_10); //4,28 MHz
  ADCR|=(1<<BURST_MODE);
  ADCR|=(1<<ADC_ENABLE);
}

float measureDCVoltage(uint16_t pinNr){
  if(pinNr != AIN0_PIN & pinNr != AIN1_PIN & pinNr != AIN2_PIN & pinNr != AIN3_PIN){
    int8_t error[] = "\r\nFalsche Eingabe!\r\n";
    sendMessage(error);
    return(true);
  }
  init_ADC(pinNr);

  while(!(ADDR&(0x80000000)));
  int16_t wert=(ADDR>>6);
  float calcDC = (3.0/1024*wert);

  return calcDC;
}

float measureACVoltage(uint16_t pinNr){
  if(pinNr != AIN0_PIN & pinNr != AIN1_PIN & pinNr != AIN2_PIN & pinNr != AIN3_PIN){
    int8_t error[] = "\r\nFalsche Eingabe!\r\n";
    sendMessage(error);
    return(true);
  }

  IO_params paramset;
  paramset.pinNr = pinNr;
  paramset.direction = 0;
  setIO(&paramset);

  float upTime = 0;
  float downTime = 0;
  start_Timer(1);
  while(!(T0IR&(1<<0))==(1<<0)){
    bool state = readState(&pinNr);
    if(state == 1){
      upTime++;
    }else{
      downTime++;
    }
  }
  float dutycycle = upTime/(upTime + downTime); //Tastverhältnis = Pulsdauer / Periodendauer

  int16_t adcWert=0;
  float adValue=0;
  float adMax=0;

  init_ADC(pinNr);
  start_Timer(1);
  while(!(T0IR&(1<<0))==(1<<0)){
    while(!(ADDR&(0x80000000)));
    adcWert=(ADDR>>6);

    adValue=((3.312/1024)*adcWert); //http://www.mikrocontroller.net/articles/AVR-Tutorial:_ADC
    if(adMax<adValue){
      adMax = adValue;
    }
  }

  float calcAC = adMax*dutycycle;

  return calcAC;
}