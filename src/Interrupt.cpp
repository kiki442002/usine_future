#include "Interrupt.h"

void IRAM_ATTR Timer_Clock_IT(void)
{
    /* Mise a jour du temps et de la date */
    time_clock.tm_sec++;
    if (time_clock.tm_sec == 60)
    {
        time_clock.tm_sec = 0;
        time_clock.tm_min++;
        if (time_clock.tm_min == 60)
        {
            time_clock.tm_min = 0;
            time_clock.tm_hour++;
            if (time_clock.tm_hour == 24)
            {
                time_clock.tm_hour = 0;
                time_clock.tm_mday++;

                if (time_clock.tm_mday > 28)
                {
                    bool leap_year = time_clock.tm_year % 4 == 0 && (time_clock.tm_year % 100 != 0 || time_clock.tm_year % 400 == 0);
                    if (time_clock.tm_mon == 1 || time_clock.tm_mon == 3 || time_clock.tm_mon == 5 || time_clock.tm_mon == 7 || time_clock.tm_mon == 8 || time_clock.tm_mon == 10 || time_clock.tm_mon == 12)
                    {
                        if (time_clock.tm_mday == 32)
                        {
                            time_clock.tm_mday = 1;
                            time_clock.tm_mon++;
                            if (time_clock.tm_mon == 13)
                            {
                                time_clock.tm_mon = 1;
                                time_clock.tm_year++;
                            }
                        }
                    }
                    else if (time_clock.tm_mon == 4 || time_clock.tm_mon == 6 || time_clock.tm_mon == 9 || time_clock.tm_mon == 11)
                    {
                        if (time_clock.tm_mday == 31)
                        {
                            time_clock.tm_mday = 1;
                            time_clock.tm_mon++;
                        }
                    }
                    else if (time_clock.tm_mon == 2)
                    {
                        if ((time_clock.tm_mday == 29 && !leap_year) || time_clock.tm_mday == 30)
                        {
                            time_clock.tm_mday = 1;
                            time_clock.tm_mon++;
                        }
                    }
                }
            }
        }
    }

    /* MAJ par NTP */
    if (time_clock.tm_hour == 3 && time_clock.tm_min == 0 && time_clock.tm_sec == 0)
    {
        update_time = true;
    }

    /* Vérification des alarmes */
    for (int i = 0; i < MAX_ALARM; i++)
    {
        if (alarm_clock[i].active)
        {
            if (alarm_clock[i].hours == time_clock.tm_hour && alarm_clock[i].minutes == time_clock.tm_min && time_clock.tm_sec == 0)
            {
                alarm_ring = true;
                if (!alarm_clock[i].repeat)
                {
                    alarm_clock[i].active = false;
                }
            }
        }
    }
    clock_update = true;
}