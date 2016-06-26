#ifndef __TIMER_h__
#define __TIMER_h__
#include "Typedefs.h"
#include "stdint.h"

/** 
 *  Konfiguriert und startet einen Timer mit der uebergebenen Zeit (in Sekunden)
 */
void start_Timer(uint16_t duration);

#define TIMER0_ENABLE 0		/**< TIMER0 aktivieren */
#define TIMER0_DISABLE 1	/**< TIMER0 deaktivieren */
#define MR0_INTERRUPT_RESET 0	/**< MR0 Interrupt zuruecksetzen */
#define MR0_ENABLE 0		/**< MR0 aktivieren */
#define MR0_RESET 1		/**< MR0 zuruecksetzen */
#define kHz_10 2949		/**< 10kHz */

#endif