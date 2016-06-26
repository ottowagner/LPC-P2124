#include "Headers/PWM.h"

void start_PWM(PWM_params *paramset){
  if(paramset->pinNr != PWM_2_PIN & paramset->pinNr != PWM_4_PIN & paramset->pinNr != PWM_6_PIN & paramset->pinNr != PWM_5_PIN){
    uint8_t error[] = "\r\nFalsche Eingabe!\r\n";
    sendMessage(error);
    return;
  }

  PWMTCR = (1<<PWM_COUNTER_RESET);
  PWMMCR = (1<<PWM_RESET_ON_PWMMR0);
  PWMPR = kHz_10;
  PWMMR0 = (10000/ paramset->frequenz);   //freq=PWMPR/PWMMR0  => PWMMR0=10000Hz/freq

  if(paramset->pinNr == PWM_2_PIN){
    PINSEL0&=~(1<<PWM_2_ENABLE_14);
    PINSEL0|=(1<<PWM_2_ENABLE_15);
    PWMMR2 = paramset->impDuration;
    PWMPCR = (1<<PWM_2_OUTPUT_ENABLE);
    PWMLER = (1<<PWM_2_LATCH_ENABLE);
  }
  else if(paramset->pinNr == PWM_4_PIN){
    PINSEL0&=~(1<<PWM_4_ENABLE_16);
    PINSEL0|=(1<<PWM_4_ENABLE_17);
    PWMMR4 = paramset->impDuration;
    PWMPCR = (1<<PWM_4_OUTPUT_ENABLE);
    PWMLER = (1<<PWM_4_LATCH_ENABLE);
  }
  else if(paramset->pinNr == PWM_5_PIN){
    PINSEL1|=(1<<PWM_5_ENABLE_10);
    PINSEL1&=~(1<<PWM_5_ENABLE_11);
    PWMMR5 = paramset->impDuration;
    PWMPCR = (1<<PWM_5_OUTPUT_ENABLE);
    PWMLER = (1<<PWM_5_LATCH_ENABLE);
  }
  else if(paramset->pinNr == PWM_6_PIN){
    PINSEL0&=~(1<<PWM_6_ENABLE_18);
    PINSEL0|=(1<<PWM_6_ENABLE_19);
    PWMMR6 = paramset->impDuration;
    PWMPCR = (1<<PWM_6_OUTPUT_ENABLE);
    PWMLER = (1<<PWM_6_LATCH_ENABLE);
  }

  PWMTCR = (1<<PWM_COUNTER_ENABLE)|(1<<PWM_ENABLE);
}