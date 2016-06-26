#ifndef __MAIN_h__
#define __MAIN_h__
#include "stdio.h"
#include "stdint.h"
#include "libarm.h"
#include "Typedefs.h"
#include "ADC.h"
#include "calculations.h"
#include "GPIO.h"
#include "PWM.h"
#include "TIMER.h"
#include "UART.h"

/** 
 *  \brief     LPC2124 Testtool
 *  \details   Das Programm kann diverse Funktionen des Boards LPC2124 ausfuehren.
 *  \author    Otto Wagner
 *  \author    Johan Ahrens
 *  \version   1
 *  \date      08.03.2016
 *  \copyright GNU Public License.
 */
int main(void);

/** 
 *  Nimmt eine Frage entgegen und gibt die entsprechende Antwort zurueck
 */
uint16_t question(uint8_t *question);

/** 
 * Fuehrt die Funktion zum Setzen eines GPIO-Pins aus
 */
void setPin();

/** 
 * Fuehrt die Funktion zum Lesen eines Pins aus
 */
void readPin();

/** 
 * Fuehrt die Funktion zum Konfigurieren einer PWM aus
 */
void setPWM();

/** 
 * Fuehrt die Funktion zum Messen der Frequenz aus
 */
void measureFreq();

/** 
 * Fuehrt die Funktion zum Messen der Winkelgeschwindigkeit aus
 */
void measureAngVelo();

/** 
 * Fuehrt die Funktion zum Messen der Bahngeschwindigkeit aus
 */
void measureVelo();

/** 
 * Fuehrt die Funktion zum Messen der Gleichspannung aus
 */
void measureDC();

/** 
 * Fuehrt die Funktion zum Messen der Wechselspannung aus
 */
void measureAC();

#endif