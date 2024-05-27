
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

/* Pin definition for rotating encoder */
#define CLK_ROTATIF D9  // clock event trigger when rotation made
#define DATA_ROTATIF D7 // data to know if rotation is clockwise or  not
#define SW_ROTATIF D5   // switch button integrated to encoder

/* Pin definition for snooze button */
#define SW_SNOOZE D10

/* Pin definition for buzzer button */
#define BUZZER_OUT D13

/* Number max of alarm */
#define MAX_ALARM 5

/* Screen coordinate */
#define X_CLOCK 10
#define Y_CLOCK 120

#define X_ACTIVE_ALARM 5
#define Y_ACTIVE_ALARM 265

#define X_REPEAT_ALARM 5
#define Y_REPEAT_ALARM 205

// used to know in which edit alarm mode we are
enum AlarmEditState
{
    NO_EDIT,
    HOUR_EDIT,
    MINUTE_EDIT
};

/* AlarmClock structure */
struct AlarmClock
{
    unsigned short hours = 12;
    unsigned short minutes = 30;
    bool active = false;
    bool repeat = false;
};

/* Global variables */
extern volatile tm time_clock;
extern volatile bool alarm_ring;
extern volatile bool update_time;
extern volatile bool clock_update;
extern volatile AlarmClock alarm_clock[MAX_ALARM]; // 5 alarmes possibles

extern volatile AlarmEditState state;

extern DFRobot_Touch_GT911 touch;
extern DFRobot_ILI9488_320x480_HW_SPI screen;
extern DFRobot_UI ui;

#endif // MAIN_H
