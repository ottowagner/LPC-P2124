#include "Headers/calculations.h"

uint16_t measureFrequenz(uint16_t pinNr){
  IO_params set;
  set.pinNr = pinNr;
  set.direction = 0;
  set.state = 0;
  setIO(&set);

  uint16_t freq = 0;
  bool oscillation = false;
  uint16_t pin = pinNr;

  start_Timer(1);
  while(!(T0IR&(1<<0))==(1<<0)){
    bool state = readState(&pin);
    if(state == 1 & oscillation == true){
      freq++;
      oscillation = false;
    }else if(state == 0 & oscillation == false){
      oscillation = true;
    }
  }
  return freq;
}

float calcAngVelocity(uint16_t pinNr, uint16_t lines){
  uint16_t freq = measureFrequenz(pinNr);
  float aVelocity = (float)((2 * M_PI * ((float)freq))/lines);  //Winkelgeschwindigkeit [ 1/s ] 
  return aVelocity;
}

float calcVelocity(uint16_t pinNr, uint16_t lines, float radius){
  float aVelocity = calcAngVelocity(pinNr, lines);
  float velocity = (float)(radius /100 * aVelocity);            //Bahngeschwindigkeit [ m/s ] 
  return velocity;                                      
}