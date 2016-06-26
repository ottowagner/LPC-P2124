#ifndef __UART_h__
#define __UART_h__
#include "Typedefs.h"
#include "String.h"
#include "stdint.h"

typedef struct{
  uint16_t wordLength;  /**< Wortlaenge */
  uint16_t baud;        /**< Schrittgeschwindigkeit (Baudrate) */
  bool parityEnable;    /**< parity aktivieren */
  bool EvenParity;      /**< EvenParity */
  uint16_t Stopbits;    /**< Stopbits */
}UART_Config;           /**< Parameter für die Konfiguration des UART */

/** 
 *  Konfiguriert und startet den UART0
 */
bool init_UART();

/** 
 *  Sendet ein Zeichen an den UART
 */
bool sendCharacter(uint8_t character);

/** 
 *  Sendet eine Zeichenkette an den UART
 */
bool sendMessage(uint8_t *message);

/** 
 *  Empfaengt ein Zeichen vom UART
 */
uint16_t readCharacter();

/** 
 *  Empfaengt eine Zeichenkette vom UART
 */
void readMessage(uint8_t* message, uint16_t MaxLen);

#define FIFO_ENABLE 0				/**< FIFO aktivieren */
#define FIFO_RESET_Rx 1				/**< FIFO Rx zuruecksetzen */
#define FIFO_RESET_Tx 2				/**< FIFO Tx zuruecksetzen */
#define PARITY_ENABLE 3				/**< Parity aktivieren */
#define STOPBIT_SELECT 2			/**< STOPBIT auswaehlen */
#define DIVISOR_LATCH_ACCESS_BIT 7		/**< Zugriff auf Divisor Latch */
#define TRANSMITTER_HOLDING_REGISTER_EMPTY 5	/**< Holding Register leer */

#endif