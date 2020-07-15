/* 
 *
 * Author: Mohamed Ebead
 *
 * Created on July , 2020 .
 * 
 */



#ifndef CONFIG_H
#define	CONFIG_H

// [ PIC16F877A ] Configuration Bit Settings
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
// CONFIG

#pragma config FOSC = XT  // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF  // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit
                          // (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF  // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF  // Flash Program Memory Write Enable bits 
                          // (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF   // Flash Program Memory Code Protection bit (Code protection off)



#include <xc.h>

#endif	/* CONFIG_H */

