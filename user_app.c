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
static u8 UserApp_au8SineTable[]=
{
    0x80,0x83,0x86,0x89,0x8d,0x90,0x93,0x96,0x99,0x9c,0x9f,0xa2,0xa5,0xa8,0xab,0xae,
0xb1,0xb4,0xb7,0xba,0xbc,0xbf,0xc2,0xc4,0xc7,0xca,0xcc,0xcf,0xd1,0xd4,0xd6,0xd8,
0xdb,0xdd,0xdf,0xe1,0xe3,0xe5,0xe7,0xe9,0xea,0xec,0xee,0xef,0xf1,0xf2,0xf4,0xf5,
0xf6,0xf7,0xf9,0xfa,0xfa,0xfb,0xfc,0xfd,0xfe,0xfe,0xff,0xff,0xff,0x100,0x100,0x100,
0x100,0x100,0x100,0x100,0xff,0xff,0xff,0xfe,0xfe,0xfd,0xfc,0xfb,0xfa,0xfa,0xf9,0xf7,
0xf6,0xf5,0xf4,0xf2,0xf1,0xef,0xee,0xec,0xea,0xe9,0xe7,0xe5,0xe3,0xe1,0xdf,0xdd,
0xdb,0xd8,0xd6,0xd4,0xd1,0xcf,0xcc,0xca,0xc7,0xc4,0xc2,0xbf,0xbc,0xba,0xb7,0xb4,
0xb1,0xae,0xab,0xa8,0xa5,0xa2,0x9f,0x9c,0x99,0x96,0x93,0x90,0x8d,0x89,0x86,0x83,
0x80,0x7d,0x7a,0x77,0x73,0x70,0x6d,0x6a,0x67,0x64,0x61,0x5e,0x5b,0x58,0x55,0x52,
0x4f,0x4c,0x49,0x46,0x44,0x41,0x3e,0x3c,0x39,0x36,0x34,0x31,0x2f,0x2c,0x2a,0x28,
0x25,0x23,0x21,0x1f,0x1d,0x1b,0x19,0x17,0x16,0x14,0x12,0x11,0xf,0xe,0xc,0xb,
0xa,0x9,0x7,0x6,0x6,0x5,0x4,0x3,0x2,0x2,0x1,0x1,0x1,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x2,0x2,0x3,0x4,0x5,0x6,0x6,0x7,0x9,
0xa,0xb,0xc,0xe,0xf,0x11,0x12,0x14,0x16,0x17,0x19,0x1b,0x1d,0x1f,0x21,0x23,
0x25,0x28,0x2a,0x2c,0x2f,0x31,0x34,0x36,0x39,0x3c,0x3e,0x41,0x44,0x46,0x49,0x4c,
0x4f,0x52,0x55,0x58,0x5b,0x5e,0x61,0x64,0x67,0x6a,0x6d,0x70,0x73,0x77,0x7a,0x7d
    
};

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

void UserAppInitialize(void)
{
    LATA = 0x80;
    
    T0CON0 = 0x90;
    T0CON1 = 0x54;
    
    DAC1CON=0xA0;
    
    DAC1DATL=0;

} /* end UserAppInitialize() */

  /*---------------------------------------------------------------------------------------------------------------------
 void TimeXus(u16 u16Microseconds)
 Sets Timer0 to count u16Microseconds
 
 Requires:
 - Timer0 configured such that each timer tick is 1 microsecond
 - u16Microseconds is the value in microseconds to time from 1 to 65535
 
 Promises:
 - Pre-loads TMr0H:L to clock out desired period
 - TMR0IF cleared
 - Timer0 enabled
 */
void TimeXus(u16 u16micros)
{
    T0CON0 &= 0x7f;
    
    u16 u16Time = 0xffff-u16micros;
    TMR0L = u16Time & 0x00ff;
    TMR0H = (u8)((u16Time & 0xff00)>>8);
            
    PIR3 &= 0x7f;
    
    T0CON0|=0x80;
    
}
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
    static u8 u8Index=0;
    
     static bool  bUp=true;
    
    if(DAC1DATL==255)// check for direction switch
    {
        bUp=false;
    }
     if(DAC1DATL==0)
    {
        bUp=true;
    }
    //increment or go down based on if 
    if(bUp)
    {
        DAC1DATL=UserApp_au8SineTable[u8Index];
    u8Index+=4;
    }
    else
    {
        DAC1DATL=UserApp_au8SineTable[u8Index];
    u8Index-=4;
    }
    
#if 0//triangle wave code
    static bool  bUp=true;
    
    if(DAC1DATL==255)// check for direction switch
    {
        bUp=false;
    }
     if(DAC1DATL==0)
    {
        bUp=true;
    }
    //increment or go down based on if 
    if(bUp)
    {
        DAC1DATL ++;
    }
    else
    {
        DAC1DATL--;
    }
#endif
    
} /* end UserAppRun */



/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
