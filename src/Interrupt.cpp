#include "Interrupt.h"

void IRAM_ATTR Timer_Clock_IT(void)
{
    time_clock.secondes++;
    if (time_clock.secondes == 60)
    {
        time_clock.secondes = 0;
        time_clock.minutes++;
        if (time_clock.minutes == 60)
        {
            time_clock.minutes = 0;
            time_clock.hours++;
            if (time_clock.hours == 24)
            {
                time_clock.hours = 0;
            }
        }
    }

    for (int i = 0; i < MAX_ALARM; i++)
    {
        if (alarm_clock[i].active)
        {
            if (alarm_clock[i].hours == time_clock.hours && alarm_clock[i].minutes == time_clock.minutes)
            {
                alarm_ring = true;
                if (!alarm_clock[i].repeat)
                {
                    alarm_clock[i].active = false;
                }
            }
        }
    }
}