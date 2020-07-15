/*
 * File:   DIO_Prog.c
 * Author: Mohamed  Ebead
 *
 * Created on July , 2020 .
 */

// shared libraries 
#include "Std_Types.h"
#include "Bit_Logic.h"

// MCAL

// HAL
#include "DIO_Interface.h"
#include "DIO_Reg.h"



/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : DIO_SetPinDirection                                          *
 * @breif       : this function sets the pin direction (INPUT/OUTPUT)          *
 * @param[in]   : Macro PORT ID (PORTA_DIO/PORTB_DIO/PORTC_DIO/PORTD_DIO)      *                                        
 * @param[in]   : Macro PIN ID  (PIN0/PIN1/PIN2/PIN3/PIN4/PIN5/PIN6/PIN7)      *                                                 
 * @param[in]   : Macro Direction ( INPUT / OUTPUT )                           *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void DIO_SetPinDirection (u8 u8PortIdCopy, u8 u8PinIdCopy, u8 u8PinDirCopy)
{
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= PORTD_DIO) && (u8PinIdCopy <= PIN7))
	{
		if ( u8PinDirCopy == OUTPUT )
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
				case PORTA_DIO: CLR_BIT(TRISA_Register,u8PinIdCopy); break;
				case PORTB_DIO: CLR_BIT(TRISB_Register,u8PinIdCopy); break;
				case PORTC_DIO: CLR_BIT(TRISC_Register,u8PinIdCopy); break;
				case PORTD_DIO: CLR_BIT(TRISD_Register,u8PinIdCopy); break;
			}
		}
		
		else if ( u8PinDirCopy == INPUT )
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
				case PORTA_DIO: SET_BIT(TRISA_Register,u8PinIdCopy); break;
				case PORTB_DIO: SET_BIT(TRISB_Register,u8PinIdCopy); break;
				case PORTC_DIO: SET_BIT(TRISC_Register,u8PinIdCopy); break;
				case PORTD_DIO: SET_BIT(TRISD_Register,u8PinIdCopy); break;
			}
		}
		
		else
		{
			/* Do nothing, Wrong Direction Required */
		}
	}
	
	else
	{
		/* Do nothing, Error in the Pin ID or PORT ID */
	}
}


/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : DIO_SetPinValue                                          *
 * @breif       : this function sets the pin Value (LOW/HIGH)                  *
 * @param[in]   : Macro PORT ID (PORTA_DIO/PORTB_DIO/PORTC_DIO/PORTD_DIO)      *                                         
 * @param[in]   : Macro PIN ID  (PIN0/PIN1/PIN2/PIN3/PIN4/PIN5/PIN6/PIN7)      *                                                  
 * @param[in]   : Macro Value ( LOW / HIGH )                                   *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/

void DIO_SetPinValue(u8 u8PortIdCopy , u8 u8PinIdCopy, u8 u8PinValCopy)
{
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= PORTD_DIO) && (u8PinIdCopy <= PIN7))
	{
		if (u8PinValCopy == HIGH)
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
				case PORTA_DIO: SET_BIT(PORTA_Register,u8PinIdCopy); break;
				case PORTB_DIO: SET_BIT(PORTB_Register,u8PinIdCopy); break;
				case PORTC_DIO: SET_BIT(PORTC_Register,u8PinIdCopy); break;
				case PORTD_DIO: SET_BIT(PORTD_Register,u8PinIdCopy); break;
			}
		
		}
		
		else if (u8PinValCopy == LOW)
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
				case PORTA_DIO: CLR_BIT(PORTA_Register,u8PinIdCopy); break;
				case PORTB_DIO: CLR_BIT(PORTB_Register,u8PinIdCopy); break;
				case PORTC_DIO: CLR_BIT(PORTC_Register,u8PinIdCopy); break;
				case PORTD_DIO: CLR_BIT(PORTD_Register,u8PinIdCopy); break;
			}
		}
	
		else
		{
			/* Do nothing, Wrong value to set */
		}
	}
	
	else
	{
		/* Do nothing, Error in the Pin ID or PORT ID */
	}
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : DIO_GetPinValue                                              *
 * @breif       : this function Gets the pin Value (0/1)                       *
 * @param[in]   : Macro PORT ID (PORTA_DIO/PORTB_DIO/PORTC_DIO/PORTD_DIO)      *                                       
 * @param[in]   : Macro PIN ID  (PIN0/PIN1/PIN2/PIN3/PIN4/PIN5/PIN6/PIN7)      *                                                
 * @return      : u8 ( 0 == LOW ) or ( 1 == HIGH )                             *
 * @note        : this fun returns 0xFF if there is an error in parameters sent* 
 ******************************************************************************/
u8 DIO_GetPinValue(u8 u8PortIdCopy, u8 u8PinIdCopy)
{
	/* Define Local Variable to get the BIT Value */
	u8 u8ResultLocal;
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= PORTD_DIO) && (u8PinIdCopy <= PIN7))
	{
		/* Check on the Required PORT Number */
		switch (u8PortIdCopy)
		{
			case PORTA_DIO: u8ResultLocal= GET_BIT(PORTA_Register,u8PinIdCopy); break;
			case PORTB_DIO: u8ResultLocal= GET_BIT(PORTB_Register,u8PinIdCopy); break;
			case PORTC_DIO: u8ResultLocal= GET_BIT(PORTC_Register,u8PinIdCopy); break;
			case PORTD_DIO: u8ResultLocal= GET_BIT(PORTD_Register,u8PinIdCopy); break;
		}
	}
	
	else
	{
		/* return 0xff in case of error in the Pin ID or PORT ID */
		u8ResultLocal = 0xFF;
	}
	
	return u8ResultLocal;
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : DIO_SetPortDirection                                         *
 * @breif       : this function Sets the PORT Direction                        *
 * @param[in]   : Macro PORT ID (PORTA_DIO/PORTB_DIO/PORTC_DIO/PORTD_DIO)      *                                         
 * @return      : u8 direction value corresponds to 7 bits                     *
 * @note        : for each PIN : 0 == OUTPUT , 1 == INPUT                      *
 ******************************************************************************/
void DIO_SetPortDirection (u8 u8PortId, u8 u8PortDir)
{
	/* Check on the Required PORT Number */
	switch (u8PortId)
	{
			case PORTA_DIO: TRISA_Register = u8PortDir; break;
			case PORTB_DIO: TRISB_Register = u8PortDir; break;
			case PORTC_DIO: TRISC_Register = u8PortDir; break;
			case PORTD_DIO: TRISD_Register = u8PortDir; break;
		default: /* Wrong Port ID */       break;
	}
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : DIO_SetPortValue                                         *
 * @breif       : this function Sets the PORT Value                        *
 * @param[in]   : Macro PORT ID (PORTA_DIO/PORTB_DIO/PORTC_DIO/PORTD_DIO)      *                                         
 * @return      : u8 value corresponds to 7 bits                               *
 * @note        :                                                              *
 ******************************************************************************/
void DIO_SetPortValue (u8 u8PortId, u8 u8PortVal)
{
	/* Check on the Required PORT Number */
	switch (u8PortId)
	{
			case PORTA_DIO: PORTA_Register = u8PortVal; break;
			case PORTB_DIO: PORTB_Register = u8PortVal; break;
			case PORTC_DIO: PORTC_Register = u8PortVal; break;
			case PORTD_DIO: PORTD_Register = u8PortVal; break;
		default: /* Wrong Port ID */        break;
	}
}
/******************************************************************************/