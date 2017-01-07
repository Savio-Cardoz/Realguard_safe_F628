#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000
#endif
#include<htc.h>
#include<xc.h>
#include"timer.h"

enum timerType currentTimerState;

void initTimer();
void startTimer(unsigned int time_val);

void interrupt ISR(void)
{
    if(TMR1IF)
    {
        if(timerOVFcount == 0)
        {
            PORTAbits.RA3 = 1;
            timerOVFcount = 1;
        }
        if(timerOVFcount == 1)
        {
            PORTAbits.RA3 = 0;
            timerOVFcount = 0;
        }
        
        
        switch(currentTimerState)
        {
            case 0: TMR1 = ackTimerVal;
            break;
            
            case 1: TMR1 = errorTimerVal;
            break;
            
            case 2: TMR1 = okTimerVal;
            break;
        }
        TMR1IF = 0;
    }
}

void ackKeyPressTimerTone()
{
    currentTimerState = ackTimer;
    TMR1 = ackTimerVal;
    T1CON = 0x01;
}

void errorTimerTone()
{
    currentTimerState = errorTimer;
    TMR1 = errorTimerVal;
    T1CON = 0x01;
    __delay_ms(200);
    T1CON = 0x00;
    __delay_ms(100);
    T1CON = 0x01;
    __delay_ms(200);
    T1CON = 0x00;
}

void okTimerTone()
{
    currentTimerState = okTimer;
    TMR1 = okTimerVal;
    T1CON = 0x01;
    __delay_ms(200);
    T1CON = 0x00;
}

void initTimer()
{
    //TMR1 = okTimerVal;
    PIE1 = 0x01;
   // T1CON = 0x01;
    
}

