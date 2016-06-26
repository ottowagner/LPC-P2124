#ifndef __GPIO_h__
#define __GPIO_h__
#include "stdint.h"
#include "UART.h"

static const uint8_t *F01[32] = {"TxD (UART0)", "RxD (UART0)", "SCL (I2C)", "SDA (I2C)", "SCK (SPI0)", "MISO (SPI0)", "MOSI (SPI0)", 
  "SSEL (SPI0)", "TxD UART1", "RxD (UART1)", "RTS (UART1)", "CTS (UART1)", "DSR (UART1)", "DTR (UART1)", "CD (UART1)", "RI (UART1)", "EINT0",
  "Capture 1.2 (TIMER1)", "Capture 1.3 (TIMER1)", "Match 1.2 (TIMER1)", "Match 1.3 (TIMER1)", "PWM5", "Reserved", "Reserved", "Reserved", 
  "Reserved", "Reserved", "AIN0 (A/D Converter)", "AIN1 (A/D Converter)", "AIN2 (A/D Converter)", "AIN3 (A/D Converter)", "Reserved"};/**< LPC2124 Funktionen 01  */

static const uint8_t *F10[32] = {"PWM1", "PWM3", "Capture 0.0 (TIMER0)", "Match 0.0 (TIMER0)", "Capture 0.1 (TIMER0)", "Match 0.1 (TIMER0)", 
  "Capture 0.2 (TIMER0)", "PWM2", "PWM4", "PWM6", "Capture 1.0 (TIMER1)", "Capture 1.1 (TIMER1)", "Match 1.0 (TIMER1)", "Match 1.1 (TIMER1)",
  "EINT1", "EINT2", "Match 0.2 (TIMER0)", "SCK (SPI1)", "MISO (SPI1)", "MOSI (SPI1)", "SSEL (SPI1)", "Reserved", "Capture 0.0 (TIMER0)", "Reserved", 
  "Reserved", "Reserved", "Reserved", "Capture 0.1 (TIMER0)", "Capture 0.2 (TIMER0)", "Capture 0.3 (TIMER0)", "EINT3", "Reserved"};/**< LPC2124 Funktionen 10 */

static const uint8_t *F11[32] = {"Reserved", "EINT0", "Reserved", "EINT1", "Reserved", "Reserved", "Reserved", "EINT2", "Reserved", "EINT3", "Reserved", 
  "Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Capture 0.2 (TIMER0)", "Match 1.2 (TIMER1)", "Match 1.3 (TIMER1)", "Match 1.3 (TIMER1)", 
  "EINT3", "Capture 1.3 (TIMER1)", "Match 0.0 (TIMER0)", "Reserved", "Reserved", "Reserved", "Reserved", "Match 0.1 (TIMER0)", "Match 0.2 (TIMER0)", 
  "Match 0.3 (TIMER0)", "Capture 0.0 (TIMER0)", "Reserved"};/**< LPC2124 Funktionen 11 */

typedef struct{
  uint16_t state;       /**< Status des Pins */
  uint16_t pinNr;       /**< Nummer des Pins */
  uint16_t direction;   /**< Richtung des Pins */
}IO_params;             /**< Parameter für die Konfiguration eines GPIO */

/** 
 *  Ueberprueft welche Funktion beim Pin gerade aktiviert ist.
 *  Wenn die Funktion GPIO aktiv ist, dann wird ausgegeben ob der PIN ein Eingang oder Ausgang ist
 *    sowie ob gerade 3.3V (aktiviert) oder 0V (deaktiviert) anliegt.
 */
void checkPin(uint16_t *pinNr);

/** 
 *  Ueberprueft ob der PIN ein Eingang oder Ausgang ist
 */
bool readDirection(uint16_t *pinNr);

/** 
 *  Ueberprueft ob 0V (Status 0) oder 3.3V (Status 1) anliegt
 */
bool readState(uint16_t *pinNr);

/** 
 *  Setzt einen PIN als Eingang oder Ausgang und kann den PIN aktivieren (3.3V) oder deaktivieren (0V)
 */
bool setIO(IO_params *paramset);

#endif