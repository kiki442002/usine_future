#include "main.h"
#include "Interrupt.h"
#include "WiFiManager.h"

DFRobot_Touch_GT911 touch;
DFRobot_ILI9488_320x480_HW_SPI screen(/*dc=*/TFT_DC, /*cs=*/TFT_CS, /*rst=*/TFT_RST);
DFRobot_UI ui(&screen, &touch);

volatile tm time_clock;
volatile bool alarm_ring = false;
volatile AlarmClock alarm_clock[MAX_ALARM]; // 5 alarmes possibles

volatile bool update_time = false;

void setup()
{
    /*Initialisation du wifi*/
    WiFi.mode(WIFI_STA);
    WiFiManager wm;
    bool res;
    res = wm.autoConnect("Clock_AP_FALLBACK", "12345678");
    if (!res)
    {
        Serial.println("Failed to connect");
        ESP.restart();
    }

    configTime(3600, 1, "pool.ntp.org");

    getLocalTime((tm *)&time_clock, 10000);

    /*Initilisation du Timer pour l'horloge*/
    hw_timer_t *timer_clock = NULL;
    timer_clock = timerBegin(0, 40, true);                    // Initialise le timer 0, diviseur 40 (donc fréquence de 1MHz), comptage ascendant
    timerAttachInterrupt(timer_clock, &Timer_Clock_IT, true); // Attache la fonction Timer_Clock_IT à notre timer
    timerAlarmWrite(timer_clock, 1000000, true);              // Déclenche l'interruption toutes les secondes
    timerAlarmEnable(timer_clock);                            // Active l'interruption
}

void loop()
{

    if (alarm_ring)
    {
        // sonner le réveil
    }

    ui.refresh(); // Rafraichir l'écran

    if (update_time)
    {
        getLocalTime((tm *)&time_clock, 10000);
        update_time = false;
    }
}
