
#ifndef MAIN_H // défini une seul fois le main.h
#define MAIN_H

#include <Arduino.h>
#include "SD.h"
#include "DFRobot_GDL.h"
#include "DFRobot_Touch.h"
#include "DFRobot_UI.h"
#include "time.h"

/* Pin definition */
#define TFT_DC D2
#define TFT_CS D6
#define TFT_RST D3

#define MAX_ALARM 5

/* AlarmClock structure */
struct AlarmClock
{
    int hours = 0;
    int minutes = 0;
    bool active = false;
    bool repeat = false;
};

/* Global variables */
extern volatile tm time_clock;
extern volatile bool alarm_ring;
extern volatile bool update_time;
extern volatile bool clock_update;
extern volatile AlarmClock alarm_clock[MAX_ALARM]; // 5 alarmes possibles

extern DFRobot_Touch_GT911 touch;
extern DFRobot_ILI9488_320x480_HW_SPI screen;
extern DFRobot_UI ui;

#endif // MAIN_H
