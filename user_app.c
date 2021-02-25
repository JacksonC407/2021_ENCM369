/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
#define _XTAL_FREQ 64000000
void UserAppInitialize(void)
{
    

} /* end UserAppInitialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- 

Promises:
- 

*/
void UserAppRun(void)
{
    
static u32 u32counter;

for( u32counter = 0x00 ; u32counter <= 0x40 ; u32counter) // counts from 0-63 counting by 1
    {
    __delay_ms(100);
    if(RB5==1)
    {
     u32counter=u32counter+1;   
          if((0x01 & u32counter) != 0x00) // sets RA0 to on if the counter and 0x01 are not equal to 0
        {
            RA0=0x01;
        }
        else
        {
            RA0=0x00;
        }
        if((0x02 & u32counter) != 0x00)
        {
            RA1=0x01;
        }
        else
        {
            RA1=0x00;
        }
         if((0x04 & u32counter) != 0x00)
        {
            RA2=0x01;
        }
        else
        {
            RA2=0x00;
        }
         if((0x08 & u32counter) != 0x00)
        {
            RA3=0x01;
        }
        else
        {
            RA3=0x00;
        }
         if((0x10 & u32counter) != 0x00)
        {
            RA4=0x01;
        }
        else
        {
            RA4=0x00;
        }
         if((0x20 & u32counter) != 0x00)
        {
            RA5=0x01;
        }
        else
        {
            RA5=0x00;
        }
      __delay_ms(250);
    }
    }
        
    
} /* end UserAppRun */



/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
