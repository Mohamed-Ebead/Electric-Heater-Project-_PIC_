
/* 
 *
 * Author: Mohamed Ebead
 *
 * Created on July , 2020 .
 */


#ifndef INT_REG_H
#define	INT_REG_H


#define OPTION_REGISTER  (*((volatile u8*)0x81))
#define OPTION_RBPU    7  // PORTB  pull up enable 
#define OPTION_INTEDG  6  // Interrupt edge select 





#define INTCON_REGISTER  (*((volatile u8*)0x0B))
#define INTCON_GIE   7   // global interrupt enable
#define INTCON_PEIE  6   // peripheral interrupt enable 
#define INTCON_INTE  4   // RB0 external interrupt enable 
#define INTCON_RBIE  3   // PORT change  interrupt enable 
#define INTCON_INTF  1   // RB0 external interrupt flag 
#define INTCON_RBIF  0   // PORT change  interrupt flag









#endif	/* INT_REG_H */

