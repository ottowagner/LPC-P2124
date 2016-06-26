#ifndef __ADC_h__
#define __ADC_h__
#include "stdint.h"
#include "TIMER.h"
#include "GPIO.h"

/** 
 *  Initialisiert den entsprechenden ADC
 */
void init_ADC(uint16_t pinNr);

/** 
 *  Berechnet die anliegende Gleichspannung eines ADC
 */
float measureDCVoltage(uint16_t pinNr);

/** 
 *  Berechnet die anliegende Wechselspannung eines ADC
 */
float measureACVoltage(uint16_t pinNr);

#define AIN0_PIN 27   /**< PinNr von AIN0 */
#define AIN1_PIN 28   /**< PinNr von AIN1 */
#define AIN2_PIN 29   /**< PinNr von AIN2 */
#define AIN3_PIN 30   /**< PinNr von AIN3 */
#define AIN0_22 22    /**< PINSEL AIN0 Setzen */
#define AIN0_23 23    /**< PINSEL AIN0 Setzen */
#define AIN1_24 24    /**< PINSEL AIN1 Setzen */
#define AIN1_25 25    /**< PINSEL AIN1 Setzen */
#define AIN2_26 26    /**< PINSEL AIN2 Setzen */
#define AIN2_27 27    /**< PINSEL AIN2 Setzen */
#define AIN3_28 28    /**< PINSEL AIN3 Setzen */
#define AIN3_29 29    /**< PINSEL AIN3 Setzen */
#define AIN0_SEL 0    /**< AIN0 auswaehlen */
#define AIN1_SEL 1    /**< AIN1 auswaehlen */
#define AIN2_SEL 2    /**< AIN2 auswaehlen */
#define AIN3_SEL 3    /**< AIN3 auswaehlen */
#define CLKDIV_9 9    /**< CLKDIV 4,28 MHz Setzen*/
#define CLKDIV_10 10  /**< CLKDIV 4,28 MHz Setzen*/
#define BURST_MODE 16 /**< BURST MODE aktivieren */
#define ADC_ENABLE 21 /**< ADC Aktivieren */

#endif