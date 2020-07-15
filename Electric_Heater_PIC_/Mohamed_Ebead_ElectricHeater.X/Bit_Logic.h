/*
 * Author: Mohamed  Ebead
 *
 * Created on July , 2020 .
 */

#ifndef BIT_LOGIC_H
#define	BIT_LOGIC_H

#define SET_BIT(VAR,BITNO) (VAR) |=  (1 << (BITNO))
#define CLR_BIT(VAR,BITNO) (VAR) &= ~(1 << (BITNO))
#define TOG_BIT(VAR,BITNO) (VAR) ^=  (1 << (BITNO))
#define GET_BIT(VAR,BITNO) (((VAR) >> (BITNO)) & 0x01)



#endif	/* BIT_LOGIC_H */

