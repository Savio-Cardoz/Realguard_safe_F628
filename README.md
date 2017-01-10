# Realguard_safe_F628
Firmware for the PIC16F628 for the Realguard safe project

Features implemented:
1. Factory default entery codes are 987654321 and 123
2. User can change the code to one of their own(max. 25 chars limit)
    To do this, a factory code should be entered and while DOORSWITCH is CLOSED, new code is entered.
*Bug note: Because default codes are written to EEPROM at the start of the 'main', every time system is restarted, the user code is overwritten with the default codes again.
