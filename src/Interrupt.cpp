#include "Interrupt.h"

void IRAM_ATTR Timer_Clock_IT(void)
{
    /* Mise a jour du temps et de la date */
    time_clock.tm_sec++;
    if (time_clock.tm_sec == 60)
    {
        clock_update = true;
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
    if(NO_EDIT == state) {
        /* Vérification des alarmes */
        for (int i = 0; i < MAX_ALARM; i++)
        {
            if (alarm_clock[i].active)
            {
                if (alarm_clock[i].hours == time_clock.tm_hour &&
                    alarm_clock[i].minutes == time_clock.tm_min &&
                    time_clock.tm_sec == 0)
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
}

void IRAM_ATTR rotatingInterrupt()
{
    // Interrupt processing function
    if(NO_EDIT != state) {
        if (digitalRead(CLK_ROTATIF) != digitalRead(DATA_ROTATIF))
        { // if A change before B, clockwise rotation
            switch (state)
            {
                case HOUR_EDIT:
                    alarm_clock[0].hours = (alarm_clock[0].hours + 1) % 24;
                    break;
                case MINUTE_EDIT:
                    alarm_clock[0].minutes = (alarm_clock[0].minutes + 1) % 60;
                    break;
            }
        }
        else
        {
            // if B change before A, rotation is anticlockwise
            switch (state)
            {
                case HOUR_EDIT:
                    alarm_clock[0].hours = (1 == alarm_clock[0].hours) ? 24 : alarm_clock[0].hours - 1;
                    break;
                case MINUTE_EDIT:
                    alarm_clock[0].minutes = ((unsigned short)-1 == alarm_clock[0].minutes) ? 59 : alarm_clock[0].minutes - 1;
            }
        }
        alarm_clock[0].active = true; // user just edited the clock to use it
        edit_screen_update = true;
    }    
}

void IRAM_ATTR changeEditState()
{
    // TODO: search for an improved way to do incremental on enum
    // state = (AlarmEditState)(((int)state) + 1) % (((int)MINUTE_EDIT) + 1);
    switch (state)
    {
        case NO_EDIT:
            state = HOUR_EDIT;
            edit_screen_update = true;
            break;
        case HOUR_EDIT:
            state = MINUTE_EDIT;
            edit_screen_update = true;
            break;
        case MINUTE_EDIT:
            state = NO_EDIT;
            init_home_screen_needed = true;
            break;
    }
}

void IRAM_ATTR snoozeInterrupt(void)
{
    if (NO_EDIT == state)
    { // the snooze action either interrupt the ringing alarm or enable/disable programmed alarm
        if (alarm_ring)
        { // alarm is ringing, stop it
            alarm_ring = false;
            alarm_clock[0].active = alarm_clock[0].repeat; // stay on if reapat mode, else go back to no activity         
        }
        else
        { // alarm is not ringing, enable / disable programmed alarm is asked
            alarm_clock[0].active = !alarm_clock[0].active;
        }
        init_home_screen_needed = true;
    }
    else
    { // edition of alarm params, action is to set or not set repeat mode
        alarm_clock[0].repeat = !alarm_clock[0].repeat;
        edit_screen_update = true;
    }
}