#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "main.h"


void IRAM_ATTR Timer_Clock_IT(void);
void ARDUINO_ISR_ATTR rotatingInterrupt(void);
void ARDUINO_ISR_ATTR changeState(void);

#endif // INTERRUPT_H