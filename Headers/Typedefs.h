#ifndef __TYPEDEFS_h__
#define __TYPEDEFS_h__
#include "targets/lpc2000.h"

#define ADDR (*(volatile unsigned long *)0xE0034004) /**< Adresse von ADDR */

/** 
 * Aus stdint.h 
 * int8_t   8   -128 bis 127
 * int16_t  16 	-32768 bis 32767
 * int32_t  32  -2147483648 bis 2147483647
 * int64_t  64 	-9223372036854775808  bis 9223372036854775807
 * uint8_t  8 	0 bis 255
 * uint16_t 16 	0 bis 65535
 * uint32_t 32 	0 bis 4294967295
 * uint64_t 64 	0 bis 18446744073709551615
*/

typedef unsigned short int bool;  /**< bool */
#define false 0                   /**< false */
#define true  1                   /**< true */

#endif