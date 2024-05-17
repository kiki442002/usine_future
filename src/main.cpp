#include "main.h"
#include "Interrupt.h"

DFRobot_Touch_GT911 touch;
DFRobot_ILI9488_320x480_HW_SPI screen(/*dc=*/TFT_DC, /*cs=*/TFT_CS, /*rst=*/TFT_RST);
DFRobot_UI ui(&screen, &touch);

volatile TimeClock time_clock;
volatile bool alarm_ring = false;
volatile AlarmClock alarm_clock[MAX_ALARM]; // 5 alarmes possibles

void setup()
{
    /*Initilisation du Timer pour l'horloge*/
    hw_timer_t *timer_clock = NULL;
    timer_clock = timerBegin(0, 40, true);                    // Initialise le timer 0, diviseur 40 (donc fréquence de 1MHz), comptage ascendant
    timerAttachInterrupt(timer_clock, &Timer_Clock_IT, true); // Attache la fonction onTimer à notre timer
    timerAlarmWrite(timer_clock, 1000000, true);              // Déclenche l'alarme toutes les secondes, répétition automatique
    timerAlarmEnable(timer_clock);                            // Active l'alarme
}

void loop()
{
    if (alarm_ring)
    {
        // sonner le réveil
    }

    ui.refresh(); // Rafraichir l'écran
}
