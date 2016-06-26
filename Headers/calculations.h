#ifndef __CALCULATIONS_h__
#define __CALCULATIONS_h__
#include "stdint.h"
#include "GPIO.h"
#include "TIMER.h"

#define M_PI 3.14159265358979323846 /**< Zahl PI */

/** 
 *  Berechnet die anliegende Frequenz eines Pins
 */
uint16_t measureFrequenz(uint16_t pinNr);

/** 
 *  Ermittelt aus der Frequenz die entsprechende Winkelgeschwindigkeit
 */
float calcAngVelocity(uint16_t pinNr, uint16_t lines);

/** 
 *  Ermittelt aus der Winkelgeschwindigkeit die entsprechende Bahngeschwindigkeit
 */
float calcVelocity(uint16_t pinNr, uint16_t lines, float radius);

#endif