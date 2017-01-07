/* 
 * File:   main.c
 * Author: Cardoz
 *
 * Created on December 13, 2016, 11:40 PM
 */
#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000
#endif
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <htc.h>
#include "Keypad4x4.h"
#include "timer.h"
#include "eeprom_routines.h"

#pragma config FOSC = INTOSCIO
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config MCLRE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config CP = OFF

#define DOOR_SW_OPEN 1
#define DOOR_SW_CLOSED 0

typedef struct			// Using to access individual bits/pins of a register/port
{
	unsigned char bit0:1;
	unsigned char bit1:1;
	unsigned char bit2:1;
	unsigned char bit3:1;
	unsigned char bit4:1;
	unsigned char bit5:1;
	unsigned char bit6:1;
	unsigned char bit7:1;
} _io_reg;

#define REGISTER_BIT(rg,bt) ((volatile _io_reg*)&rg)->bit##bt

#define SETBIT(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT))
#define CHECKBIT(ADDRESS,BIT) (ADDRESS & (1<<BIT))
#define BIT_FLIP(ADDRESS,BIT) ((ADDRESS)^=(BIT))

#define SET_LED REGISTER_BIT(PORTA, 0)
#define POWER_LED REGISTER_BIT(PORTA, 1)
#define ACCESS_LED REGISTER_BIT(PORTA, 2)
#define BUZZER REGISTER_BIT(PORTA, 3)
#define DOORSWITCH REGISTER_BIT(PORTA, 5)
#define ERROR_LED REGISTER_BIT(PORTA, 7)

static unsigned char keyPressCount;
static unsigned char keyBuffer[25];     // Buffer that will hold the values of the keys pressed

unsigned char *eepromCode;
//extern enum timerType currentTimerState;

const unsigned char defaultPassCode[9] = {9,8,7,6,5,4,3,2,1};
const unsigned char defaultPassCode2[3] = {1,2,3};
const unsigned char defaultPassCodeLenght = 9;

void ackKeyPress();
void passcodeCompare(char *keybuffer1, char *keybuffer2, char compareLenght);

void initControllerIO()
{
    TRISA0 = 0;      // Output for the SET LED
    TRISA1 = 0;      // Output for the POWER LED
    TRISA2 = 0;      // Output for the ACCESS LED and Solenoid
    TRISA3 = 0;      // Output for the Buzzer
//    TRISA4 = 
    TRISA5 = 1;     // Input for Door Sense Switch
    TRISA7 = 0;     // Output for the power indication LED
    
    CMCON = 0x07;
    
    SET_LED = 0;
    POWER_LED = 0;
    ACCESS_LED = 0;
    ERROR_LED = 0;
}

int main() 
{   
    struct keypadStatus currentKeypadStatus;
    initControllerIO();
    initKeypad();
    initTimer();
    INTCONbits.PEIE = 1;    // Enable peripheral interrupts
    ei();                   // Enable global interrupts

    static unsigned char i = 0;

/****************    Testing eeprom routines ***************/
//    eepromWriteCode(defaultPassCodeLenght, defaultPassCode);
//    eepromWriteCode(defaultPassCodeLenght, defaultPassCode2);
//    eepromCode = eepromReadCode(2);
//    
//    for(unsigned char i=0; i<9; i++)
//    {
//        keyBuffer[i] = *(eepromCode + i);
//    }
//    eepromWriteCode(defaultPassCodeLenght, defaultPassCode);

    while(1)
    {
        currentKeypadStatus = getKey();
        if(currentKeypadStatus.keyPressIndicator)
        {
            if(currentKeypadStatus.keyPressed == SP_FUNC_ON)
            {
                if(DOORSWITCH == DOOR_SW_OPEN)    // iF DOOR IS CLOSED ENTER ACCESS MODE
                {
                    passcodeCompare(keyBuffer, defaultPassCode, keyPressCount);
                    keyPressCount = 0;
                    i = 0;          // Flushing of buffer to be better implemented
                }
            }
            
            else if(currentKeypadStatus.keyPressed == SP_FUNC_B)
            {
                
            }
            
            else if(currentKeypadStatus.keyPressed == SP_FUNC_ENTER)
            {
                
            }
            else{
                keyBuffer[i] = currentKeypadStatus.keyPressed;
                ackKeyPress();
                keyPressCount++;
                if(++i == 26)             // Incrementing the buffer and checking overflow
                i = 0;
            }
            
            currentKeypadStatus.keyPressIndicator = False;
        }
    }
    return (EXIT_SUCCESS);
}

void passcodeCompare(char *keybuffer1, char *keybuffer2, char compareLenght)
{
    if(compareLenght == defaultPassCodeLenght)      // if it is equal to default passcode size
    {
        for(unsigned char i=0; i <= (compareLenght-1); i++)
        {
            if(*keybuffer1 == *keybuffer2)
            {
                *keybuffer1++; 
                *keybuffer2++;
            }
            else {
                ERROR_LED = 1;
                errorTimerTone();
                __delay_ms(1000);
                ERROR_LED = 0;
                T1CON = 0x00;
                return;
            };
        }
        ACCESS_LED = 1;
        okTimerTone();
        __delay_ms(3800);
        ACCESS_LED = 0;
    }
    
    else {
        ERROR_LED = 1;
        errorTimerTone();
        __delay_ms(1000);
        ERROR_LED = 0;
        T1CON = 0x00;
        return;
    };
}

/**************************************************************************************/
/*          Function to give a visual feedback of a key pressed           
            Arguments Taken: None
            Returns: None
 */
void ackKeyPress()
{
    SET_LED = 1;
    ackKeyPressTimerTone();
    __delay_ms(100);
    T1CON = 0;              // Stop timer PWM for Buzzer
    SET_LED = 0;
}


