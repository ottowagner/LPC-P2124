#ifndef __PWM_h__
#define __PWM_h__
#include "stdint.h"
#include "Headers/UART.h"

typedef struct{
  uint16_t pinNr;       /**< PinNr der PWM */
  uint16_t frequenz;    /**< Frequenz der PWM */
  uint16_t impDuration; /**< Impulsdauer */
}PWM_params;            /**< Parameter für die Konfiguration einer PWM */

/** 
 *  Konfiguriert und startet die uebergebene PWM mit der uebergebenen Frequenz und der Impulsdauer
 */
void start_PWM(PWM_params *paramset);

#define PWM_2_PIN 7             /**< PinNr von PWM2 */
#define PWM_4_PIN 8		/**< PinNr von PWM4 */
#define PWM_6_PIN 9		/**< PinNr von PWM6 */
#define PWM_5_PIN 21		/**< PinNr von PWM5 */
#define PWM_COUNTER_RESET 1	/**< Setzt PWM Counter zurueck */
#define PWM_COUNTER_ENABLE 0	/**< Aktiviert PWM Counter */
#define PWM_ENABLE 3		/**< Aktiviert PWM's */
#define PWM_RESET_ON_PWMMR0 1	/**< PWM's werden bei erreichen von PWMMR0 zurueckgesetzt */
#define kHz_10 2949		/**< 10kHz */
#define PWM_2_ENABLE_14 14	/**< PINSEL PWM2 Setzen */
#define PWM_2_ENABLE_15 15	/**< PINSEL PWM2 Setzen */
#define PWM_4_ENABLE_16 16	/**< PINSEL PWM4 Setzen */
#define PWM_4_ENABLE_17 17	/**< PINSEL PWM4 Setzen */
#define PWM_6_ENABLE_18 18	/**< PINSEL PWM6 Setzen */
#define PWM_6_ENABLE_19 19	/**< PINSEL PWM6 Setzen */
#define PWM_5_ENABLE_10 10	/**< PINSEL PWM5 Setzen */
#define PWM_5_ENABLE_11 11	/**< PINSEL PWM5 Setzen */
#define PWM_2_OUTPUT_ENABLE 10	/**< PWM2 Output aktivieren */
#define PWM_4_OUTPUT_ENABLE 12	/**< PWM4 Output aktivieren */
#define PWM_5_OUTPUT_ENABLE 13	/**< PWM5 Output aktivieren */
#define PWM_6_OUTPUT_ENABLE 14	/**< PWM6 Output aktivieren */
#define PWM_2_LATCH_ENABLE 2	/**< PWM2 Latch aktivieren */
#define PWM_4_LATCH_ENABLE 4	/**< PWM4 Latch aktivieren */
#define PWM_5_LATCH_ENABLE 5	/**< PWM5 Latch aktivieren */
#define PWM_6_LATCH_ENABLE 6	/**< PWM6 Latch aktivieren */

#endif