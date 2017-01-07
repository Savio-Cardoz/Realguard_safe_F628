#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000
#endif 
#include <xc.h>
#include <htc.h>
#include "Keypad4x4.h"

enum button buttonPressed;

struct keypadStatus currentKeypadStatus;        // define a structure to return the state of keypad of structure type keypadStatus

/**************************************************************************************/
/*          Function to Initialize the controller port to which the 4X4 keypad is connected
 *          Rows are set as outputs and columns as inputs           
            Arguments Taken: None
            Returns:    None
 */
void initKeypad(void)
{
	KEYPAD_PORT_DIR = 0xF0;	// Last 4 pins (Column) input, First 4 pins (Rows) output
    KEYPAD_PORT	    = 0xFF;	// Set Keypad port pin values zero

	OPTION_REG = 0x7F;
}

/**************************************************************************************/
/*          Function to check key pressed           
            Arguments Taken: None
            Returns:    Key pressed indicator bit   member of structure keypadStatus
                        Key pressed value           member of structure keypadStatus
 */
struct keypadStatus getKey(void)                
{	
/****   Make ROW 2 LOW and check for columns 1,2,3,4    *****/    
    PORTB = 0xFE;
    if ((PORTB & 0x10) == 0x00)
    { 
        __delay_ms(100);
        while ((PORTB & 0x10) == 0x00);
        buttonPressed = SP_FUNC_ON;
        currentKeypadStatus.keyPressIndicator = True;
        currentKeypadStatus.keyPressed = buttonPressed;
        return currentKeypadStatus;
    }
    
    else if ((PORTB & 0x20) == 0x00)
    { 
        __delay_ms(100);
        while ((PORTB & 0x20) == 0x00);
        buttonPressed = button_0;
        currentKeypadStatus.keyPressIndicator = True;
        currentKeypadStatus.keyPressed = buttonPressed;
        return currentKeypadStatus;
    }
    
    else if ((PORTB & 0x40) == 0x00)
    { 
        __delay_ms(100);
        while ((PORTB & 0x40) == 0x00);
        buttonPressed = SP_FUNC_ENTER;
        currentKeypadStatus.keyPressIndicator = True;
        currentKeypadStatus.keyPressed = buttonPressed;
        return currentKeypadStatus;
    }
    
    else if ((PORTB & 0x80) == 0x00)
    { 
        __delay_ms(100);
//        RA7 = 1;                                // For Debugging on board
        while ((PORTB & 0x80) == 0x00);
  //      RA7 = 0;                                // For Debugging on board
        buttonPressed = SP_FUNC_OFF;
        currentKeypadStatus.keyPressIndicator = True;
        currentKeypadStatus.keyPressed = buttonPressed;
        return currentKeypadStatus;
    }
/****   Make ROW 2 LOW and check for columns 1,2,3,4    *****/
    PORTB = 0xFD;
    if ((PORTB & 0x10) == 0x00)
    { 
        __delay_ms(100);
//        RA1 = 1;                                // For Debugging on board
        while ((PORTB & 0x10) == 0x00);
//        RA1 = 0;                                // For Debugging on board
        buttonPressed = button_7;
        currentKeypadStatus.keyPressIndicator = True;
        currentKeypadStatus.keyPressed = buttonPressed;
        return currentKeypadStatus;
    }
    
    else if ((PORTB & 0x20) == 0x00)
    { 
        __delay_ms(100);
 //       RA2 = 1;                                // For Debugging on board
        while ((PORTB & 0x20) == 0x00);
 //////       RA2 = 0;                                // For Debugging on board
        buttonPressed = button_8;
        currentKeypadStatus.keyPressIndicator = True;
        currentKeypadStatus.keyPressed = buttonPressed;
        return currentKeypadStatus;
    }
    
    else if ((PORTB & 0x40) == 0x00)
    { 
        __delay_ms(100);
 //       RA0 = 1;                                // For Debugging on board
        while ((PORTB & 0x40) == 0x00);
 ////////       RA0 = 0;                                // For Debugging on board
        buttonPressed = button_9;
        currentKeypadStatus.keyPressIndicator = True;
        currentKeypadStatus.keyPressed = buttonPressed;
        return currentKeypadStatus;
    }
    
    else if ((PORTB & 0x80) == 0x00)
    { 
        __delay_ms(100);
//        RA7 = 1;                                // For Debugging on board
        while ((PORTB & 0x80) == 0x00);
 //       RA7 = 0;                                // For Debugging on board
        buttonPressed = SP_FUNC_B;
        currentKeypadStatus.keyPressIndicator = True;
        currentKeypadStatus.keyPressed = buttonPressed;
        return currentKeypadStatus;
    }
/****   Make ROW 3 LOW and check for columns 1,2,3,4    *****/
    PORTB = 0xFB;
    if ((PORTB & 0x10) == 0x00)
    { 
        __delay_ms(100);
 //       RA1 = 1;                                // For Debugging on board
        while ((PORTB & 0x10) == 0x00);
 //       RA1 = 0;                                // For Debugging on board
        buttonPressed = button_4;
        currentKeypadStatus.keyPressIndicator = True;
        currentKeypadStatus.keyPressed = buttonPressed;
        return currentKeypadStatus;
    }
    
    else if ((PORTB & 0x20) == 0x00)
    { 
        __delay_ms(100);
//        RA2 = 1;                                // For Debugging on board
        while ((PORTB & 0x20) == 0x00);
 //////       RA2 = 0;                                // For Debugging on board
        buttonPressed = button_5;
        currentKeypadStatus.keyPressIndicator = True;
        currentKeypadStatus.keyPressed = buttonPressed;
        return currentKeypadStatus;
    }
    
    else if ((PORTB & 0x40) == 0x00)
    { 
        __delay_ms(100);
//        RA0 = 1;                                // For Debugging on board
        while ((PORTB & 0x40) == 0x00);
 ////////       RA0 = 0;                                // For Debugging on board
        buttonPressed = button_6;
        currentKeypadStatus.keyPressIndicator = True;
        currentKeypadStatus.keyPressed = buttonPressed;
        return currentKeypadStatus;
    }
    
    else if ((PORTB & 0x80) == 0x00)
    { 
        __delay_ms(100);
//        RA7 = 1;                                // For Debugging on board
        while ((PORTB & 0x80) == 0x00);
//        RA7 = 0;                                // For Debugging on board
        buttonPressed = SP_FUNC_A;
        currentKeypadStatus.keyPressIndicator = True;
        currentKeypadStatus.keyPressed = buttonPressed;
        return currentKeypadStatus;
    }
/****   Make ROW 4 LOW and check for columns 1,2,3,4    *****/
    PORTB = 0xF7;
    if ((PORTB & 0x10) == 0x00)
    { 
        __delay_ms(100);
//        RA1 = 1;                                // For Debugging on board
        while ((PORTB & 0x10) == 0x00);
//        RA1 = 0;                                // For Debugging on board
        buttonPressed = button_1;
        currentKeypadStatus.keyPressIndicator = True;
        currentKeypadStatus.keyPressed = buttonPressed;
        return currentKeypadStatus;
    }
    
    else if ((PORTB & 0x20) == 0x00)
    { 
        __delay_ms(100);
 //       RA2 = 1;                                // For Debugging on board
        while ((PORTB & 0x20) == 0x00);
 //////       RA2 = 0;                                // For Debugging on board
        buttonPressed = button_2;
        currentKeypadStatus.keyPressIndicator = True;
        currentKeypadStatus.keyPressed = buttonPressed;
        return currentKeypadStatus;
    }
    
    else if ((PORTB & 0x40) == 0x00)
    { 
        __delay_ms(100);
 //       RA0 = 1;                                // For Debugging on board
        while ((PORTB & 0x40) == 0x00);
 //////       RA0 = 0;                                // For Debugging on board
        buttonPressed = button_3;
        currentKeypadStatus.keyPressIndicator = True;
        currentKeypadStatus.keyPressed = buttonPressed;
        return currentKeypadStatus;
    }
    
    else if ((PORTB & 0x80) == 0x00)
    { 
        __delay_ms(100);
 //       RA7 = 1;                                // For Debugging on board
        while ((PORTB & 0x80) == 0x00);
 //       RA7 = 0;                                // For Debugging on board
        buttonPressed = NO_KEY_TUNE;
        currentKeypadStatus.keyPressIndicator = True;
        currentKeypadStatus.keyPressed = buttonPressed;
        return currentKeypadStatus;
    }
    
    else {
            currentKeypadStatus.keyPressIndicator = False;
            return currentKeypadStatus;
    }
    
}
