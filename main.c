#include "Headers/main.h"

int main(void){
  init_UART();
  uint8_t error[] = "\r\nFalsche Eingabe!\r\n";

  uint8_t todo[] = "Antworten bitte mit ';' bestaetigen!";
  sendMessage(todo);
  while (true){
    uint8_t introQ[] = "\r\n\r\nWas moechten Sie tun?\r\n";
    uint8_t one[] = "(1) PIN einrichten\r\n";
    strcat(introQ, one);
    uint8_t two[] = "(2) PIN auslesen\r\n";
    strcat(introQ, two);
    uint8_t three[] = "(3) PWM einrichten\r\n";
    strcat(introQ, three);
    uint8_t four[] = "(4) Frequenz messen\r\n";
    strcat(introQ, four);
    uint8_t five[] = "(5) Winkelgeschwindigkeit messen\r\n";
    strcat(introQ, five);
    uint8_t six[] = "(6) Bahngeschwindigkeit messen \r\n";
    strcat(introQ, six);
    uint8_t seven[] = "(7) Gleichspannung messen\r\n";
    strcat(introQ, seven);
    uint8_t eight[] = "(8) Wechselspannung messen\r\n";
    strcat(introQ, eight);
    uint8_t chosen[] = "Ihre Auswahl: ";
    strcat(introQ, chosen);
    uint16_t selected = question(introQ);
 
    switch(selected) {
      case 1: setPin();
                break;
      case 2: readPin();
                break;
      case 3: setPWM();
                break;
      case 4: measureFreq();
                break;
      case 5: measureAngVelo();
                break; 
      case 6: measureVelo();
                break; 
      case 7: measureDC();
                break;
      case 8: measureAC();
                break;
      default: sendMessage(error);
                break;
    }
  }
}

uint16_t question(uint8_t *question){
  sendMessage(question);
  uint8_t answer[10];
  readMessage(answer, sizeof(answer));
  sendMessage(answer);
  uint16_t answerInt = atoi(answer);
  return answerInt;
}

void setPin(){
  IO_params paramset;
  uint8_t pinQ[] = "\r\nBitte geben Sie den Pin an: ";
  paramset.pinNr = question(pinQ);

  uint8_t directionQ[] = "\r\nSoll es ein Eingang (0) oder Ausgang (1) sein? ";
  paramset.direction = question(directionQ);

  if(paramset.direction == 1){
    uint8_t stateQ[] = "\r\nSoll der Pin Deaktiviert (0) oder Aktiviert (1)  werden? ";
    paramset.state = question(stateQ);;
  }
  setIO(&paramset);
}

void readPin(){
  uint8_t pinQ[] = "\r\nWelchen Pin moechten Sie auslesen? ";
  uint16_t pinNr = question(pinQ);
  checkPin(&pinNr);
}

void setPWM(){
  PWM_params paramset;
  uint8_t pwmQ[] = "\r\nWelche PWM moechten Sie einrichten (PWM2 (7) PWM4 (8) PWM6 (9) PWM5 (21))? ";
  paramset.pinNr = question(pwmQ);

  uint8_t freqQ[] = "\r\nWelche Frequenz moechten Sie einstellen (in Hz)? ";
  paramset.frequenz = question(freqQ);

  uint8_t impLQ[] = "\r\nWie lange soll der Impuls sein (max. ";
  uint16_t taktL = (10000/paramset.frequenz)-1;
  uint8_t taktLS[10];
  sprintf(taktLS, "%d", taktL);
  strcat(impLQ, taktLS);
  uint8_t impLQEnd[] = ")? ";
  strcat(impLQ, impLQEnd);  
  paramset.impDuration = question(impLQ);

  start_PWM(&paramset);
}

void measureFreq(){
  uint8_t pinQ[] = "\r\nWelchen Pin moechten Sie messen? ";
  uint16_t pinNr =  question(pinQ);
  uint16_t freq = measureFrequenz(pinNr);

  uint8_t sFreq[5];
  uint8_t freqMessage[] = "\r\nDie Frequenz betraegt: ";
  itoa(freq, sFreq, 10);
  strcat(freqMessage, sFreq);
  uint8_t HzMessage[] = "Hertz.\r\n";
  strcat(freqMessage, HzMessage);
  sendMessage(freqMessage);
}

void measureAngVelo(){
  uint8_t pinQ[] = "\r\nWelchen Pin moechten Sie messen? ";
  uint16_t pinNr =  question(pinQ);

  uint8_t linesQ[] = "\r\nWie viele Signale pro Umdrehung? ";
  sendMessage(linesQ);
  uint8_t answerL[10];
  readMessage(answerL, sizeof(answerL));
  sendMessage(answerL);
  uint16_t lines = atoi(answerL);

  float velo = calcAngVelocity(pinNr, lines);
  uint8_t sVelo[20];
  uint8_t veloMessage[] = "\r\nDie Winkelgeschwindigkeit betraegt: ";
  sprintf(sVelo,"%01.2f",velo);
  strcat(veloMessage, sVelo);
  uint8_t msMessage[] = " 1/s.\r\n";
  strcat(veloMessage, msMessage);
  sendMessage(veloMessage);
}

void measureVelo(){
  uint8_t pinQ[] = "\r\nWelchen Pin moechten Sie messen? ";
  uint16_t pinNr =  question(pinQ);

  uint8_t linesQ[] = "\r\nWie viele Signale pro Umdrehung? ";
  sendMessage(linesQ);
  uint8_t answerL[10];
  readMessage(answerL, sizeof(answerL));
  sendMessage(answerL);
  uint16_t lines = atoi(answerL);

  uint8_t radiusQ[] = "\r\nWelchen Radius hat die Bahn (in cm)? ";
  sendMessage(radiusQ);
  uint8_t answerR[10];
  readMessage(answerR, sizeof(answerR));
  sendMessage(answerR);
  float radius = atof(answerR);

  float velo = calcVelocity(pinNr, lines, radius);
  uint8_t sVelo[20];
  uint8_t veloMessage[] = "\r\nDie Bahngeschwindigkeit betraegt: ";
  sprintf(sVelo,"%01.2f",velo);
  strcat(veloMessage, sVelo);
  uint8_t msMessage[] = "m/s.\r\n";
  strcat(veloMessage, msMessage);
  sendMessage(veloMessage);
}

void measureDC(){
  uint8_t adQ[] = "\r\nWelchen AD-Wandler möchten Sie nutzen (AIN0 (27) AIN1(28) AIN2(29) AIN3(30))? ";
  uint16_t pinNr =  question(adQ);
  float dc = measureDCVoltage(pinNr);

  uint8_t vMessage[] = "\r\nDie Gleichspannung betraegt: ";
  uint8_t sDC[20];
  sprintf(sDC,"%01.3f",dc);
  strcat(vMessage, sDC);
  uint8_t voltMessage[] = "V.\r\n";
  strcat(vMessage, voltMessage);
  sendMessage(vMessage);
}

void measureAC(){
  uint8_t adQ[] = "\r\nWelchen AD-Wandler möchten Sie nutzen (AIN0 (27) AIN1(28) AIN2(29) AIN3(30))? ";
  uint16_t pinNr =  question(adQ);
  float ac = measureACVoltage(pinNr);

  uint8_t vMessage[] = "\r\nDie Wechselspannung betraegt: ";
  uint8_t sAC[20];
  sprintf(sAC,"%01.3f",ac);
  strcat(vMessage, sAC);
  uint8_t voltMessage[] = "V.\r\n";
  strcat(vMessage, voltMessage);
  sendMessage(vMessage);
}