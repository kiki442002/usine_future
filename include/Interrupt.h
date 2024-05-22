#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "main.h"


void IRAM_ATTR Timer_Clock_IT(void);
void ARDUINO_ISR_ATTR rotatingInterrupt(void);
void ARDUINO_ISR_ATTR changeEditState(void);
void ARDUINO_ISR_ATTR snoozeInterrupt(void);

#endif // INTERRUPT_H