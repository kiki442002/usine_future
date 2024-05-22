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
volatile bool clock_update = false;

void setup()
{
    Serial.begin(115200);
    Serial.println("Début programme");
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
    Serial.println("Wifi connecter");

    configTime(3600 * 2, 1, "pool.ntp.org");

    getLocalTime((tm *)&time_clock, 10000);
    Serial.println("Temps récupérer");
    /*Initilisation du Timer pour l'horloge*/
    hw_timer_t *timer_clock = NULL;
    timer_clock = timerBegin(0, 80, true);                    // Initialise le timer 0, diviseur 80 (donc fréquence de 1MHz), comptage ascendant
    timerAttachInterrupt(timer_clock, &Timer_Clock_IT, true); // Attache la fonction Timer_Clock_IT à notre timer
    timerAlarmWrite(timer_clock, 1000000, true);              // Déclenche l'interruption toutes les secondes
    timerAlarmEnable(timer_clock);                            // Active l'interruption
    Serial.println("Setup Fini");
}

void loop()
{

    if (alarm_ring)
    {

        Serial.println("Réveil Sonne");
        // sonner le réveil
    }

    ui.refresh(); // Rafraichir l'écran

    if (update_time)
    {
        getLocalTime((tm *)&time_clock, 10000);
        update_time = false;
    }

    if (clock_update)
    {
        Serial.println("Heure : " + String(time_clock.tm_hour) + " Minutes : " + String(time_clock.tm_min) + " Secondes : " + String(time_clock.tm_sec));
        Serial.println("Jour : " + String(time_clock.tm_mday) + " Mois : " + String(time_clock.tm_mon) + " Année : " + String(time_clock.tm_year));
        clock_update = false;
    }
}
