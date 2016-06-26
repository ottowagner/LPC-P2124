#include "Headers/TIMER.h"

void start_Timer(uint16_t duration){
  T0TCR|=(1<<TIMER0_DISABLE);
  T0PR=kHz_10;
  T0MR0=duration*10000;             // Timer0 in Sekunden
  T0MCR|=(1<<MR0_ENABLE);
  T0MCR|=(1<<MR0_RESET);
  T0IR|=(1<<MR0_INTERRUPT_RESET);
  T0TCR=(1<<TIMER0_ENABLE);
}