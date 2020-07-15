/*
 * File:   Interrupts_Handler.c
 * Author: Mohamed  Ebead
 *
 * Created on July , 2020 .
 */


//shared libraries 
#include "Std_Types.h"
#include "Bit_Logic.h"
#include "Configurations.h"

// MCAL


// HAL
#include "DIO_Interface.h"
#include "INT_Reg.h"
#include "Timer1_Reg.h"


// extern used variables 
extern u8 u8_Temp_Set ;
extern u8 ON_OFF_Status ; 
extern u8 Set_Temp_Flag ;
extern u8 TempChange_Status ; 
extern u16 ms_Counter ; 


void (*GptrToFun_Timer1) (void) ;
void (*GptrToFun_RB0) (void) ;
void (*GptrToFun_RB4) (void) ;
void (*GptrToFun_RB5) (void) ;


/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : Timer1_SetCallBack                                           *
 * @breif       : To avoid calling upper layer from the lower layer            *
 *                which opposes the layered architecture                       *
 *                this function takes the address of the function that         *
 *                is wanted be called from the ISR and assigns it to the       *
 *                global pointer to function witch will be called from ISR     *
 * @param[in]   : pFun which will be the address of                            *
 *                Temp_ControlWaterTemp function                               *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void Timer1_SetCallBack (void (*pFun) (void)) 
{
    GptrToFun_Timer1 = pFun ; 
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : RB0_SetCallBack                                              *
 * @breif       : To avoid calling upper layer from the lower layer            *
 *                which opposes the layered architecture                       *
 *                this function takes the address of the function that         *
 *                is wanted be called from the ISR and assigns it to the       *
 *                global pointer to function witch will be called from ISR     *
 * @param[in]   : pFun which will be the address of                            *
 *                RB0_Handler function                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void RB0_SetCallBack (void (*pFun) (void)) 
{
    GptrToFun_RB0 = pFun ; 
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : RB4_SetCallBack                                              *
 * @breif       : To avoid calling upper layer from the lower layer            *
 *                which opposes the layered architecture                       *
 *                this function takes the address of the function that         *
 *                is wanted be called from the ISR and assigns it to the       *
 *                global pointer to function witch will be called from ISR     *
 * @param[in]   : pFun which will be the address of                            *
 *                RB4_Handler function                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void RB4_SetCallBack (void (*pFun) (void)) 
{
    GptrToFun_RB4 = pFun ; 
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : RB5_SetCallBack                                              *
 * @breif       : To avoid calling upper layer from the lower layer            *
 *                which opposes the layered architecture                       *
 *                this function takes the address of the function that         *
 *                is wanted be called from the ISR and assigns it to the       *
 *                global pointer to function witch will be called from ISR     *
 * @param[in]   : pFun which will be the address of                            *
 *                RB5_Handler function                                         *
 * @return      : void                                                         *
 * @note        :                                                              *
 ******************************************************************************/
void RB5_SetCallBack (void (*pFun) (void)) 
{
    GptrToFun_RB5 = pFun ; 
}

/*----------------------------------------------------------------------------*/
/*******************************************************************************
 * @fn          : ISR ( Interrupt Service Routine )                            *
 * @breif       : this function is entered only by the hardware                *
 * @param[in]   : void                                                         *
 * @return      : void                                                         *
 * @note        : this function checks which flag is set , then it handles     *
 *                the interrupt associated with this flag by calling the       *
 *                callback functions to avoid opposing the layered architecture*
 *                and finally clears this flag .                               *
 ******************************************************************************/
void __interrupt () ISR (void) 
{   
   
    if (GET_BIT(INTCON_REGISTER,INTCON_INTF))      // ON/OFF button ( RB0 )
    {        
       GptrToFun_RB0 ();
       CLR_BIT(INTCON_REGISTER,INTCON_INTF) ; 

    }
    else if ( GET_BIT(INTCON_REGISTER,INTCON_RBIF) ) // UP or DOWN button ( RB4 , RB5 )
    {
        // UP button is pressed 
        if ( ! DIO_GetPinValue(PORTB_DIO,up_BUTTON) )
        {
            GptrToFun_RB4 () ;
        }
        // DOWN button is pressed 
        else if ( ! DIO_GetPinValue(PORTB_DIO,DOWN_BUTTON) )
        {
            GptrToFun_RB5 () ;
            
        }
        else
        {
            // pressed wrong button 
        }
        CLR_BIT(INTCON_REGISTER,INTCON_RBIF) ;  // clear PORT change  interrupt flag
        
    }
    else if (GET_BIT(PIR1_REGISTER , CCP1IF_BIT))
    {
        ms_Counter ++ ;
        if (ms_Counter==100)
        {
           // TOG_BIT(PORTB_Register , 1) ;
             GptrToFun_Timer1 () ;
            ms_Counter=0 ;
        }
        CLR_BIT(PIR1_REGISTER , CCP1IF_BIT) ;
        
    }
    else 
    {
       // other interrupt flag
    }
}
/******************************************************************************/