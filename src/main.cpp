#include "main.h"
#include "Interrupt.h"
#include "WiFiManager.h"
#include "ArduinoOTA.h"
#include "Screen.h"

DFRobot_Touch_GT911 touch;
DFRobot_ILI9488_320x480_HW_SPI screen(/*dc=*/TFT_DC, /*cs=*/TFT_CS, /*rst=*/TFT_RST);
DFRobot_UI ui(&screen, &touch);

volatile tm time_clock;
volatile AlarmEditState state = NO_EDIT;
volatile bool alarm_ring = false;
// TODO: généraliser pour 5 alarmes
volatile AlarmClock alarm_clock[MAX_ALARM]; // 5 alarmes possibles, seul la première utilisé pour l'instant

volatile bool update_time = false;
volatile bool clock_update = false;

void setup()
{
    WiFiManager wm;
    wm.resetSettings();
    bool res;

    Serial.begin(115200);
    Serial.println("Début programme");

    /*Initialisation du wifi*/
    WiFi.mode(WIFI_STA);

    res = wm.autoConnect("Clock_AP_FALLBACK", "12345678");
    while (!res)
    {
        Serial.print(".");
    }
    Serial.println();
    Serial.println("Wifi connecter");

    /*MAJ OTA*/
    ArduinoOTA.setHostname("clock"); // upload with clock.local
    ArduinoOTA
        .onStart([]()
                 {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH) {
        type = "sketch";
      } else {  // U_SPIFFS
        type = "filesystem";
      }

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type); })
        .onEnd([]()
               { Serial.println("\nEnd"); })
        .onProgress([](unsigned int progress, unsigned int total)
                    { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); })
        .onError([](ota_error_t error)
                 {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) {
        Serial.println("Auth Failed");
      } else if (error == OTA_BEGIN_ERROR) {
        Serial.println("Begin Failed");
      } else if (error == OTA_CONNECT_ERROR) {
        Serial.println("Connect Failed");
      } else if (error == OTA_RECEIVE_ERROR) {
        Serial.println("Receive Failed");
      } else if (error == OTA_END_ERROR) {
        Serial.println("End Failed");
      } });
    ArduinoOTA.begin();

    Serial.println("Maj OTA configuré");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    configTime(3600 * 2, 1, "pool.ntp.org");

    getLocalTime((tm *)&time_clock, 10000);
    Serial.println("Temps récupéré");

    /*Screen Initialisation*/
    screen_init();
    Serial.println("Setup screen Fini");

    /* setup of rotating encoder */
    pinMode(CLK_ROTATIF, INPUT);
    pinMode(DATA_ROTATIF, INPUT);
    attachInterrupt(SW_ROTATIF, changeEditState, FALLING);
    attachInterrupt(CLK_ROTATIF, rotatingInterrupt, CHANGE);
    Serial.println("Setup Encodeur Fini");

    /* setup of snoozing switch button */
    pinMode(SW_SNOOZE, INPUT);
    attachInterrupt(SW_SNOOZE, snoozeInterrupt, RISING);
    Serial.println("Setup Snoozing Fini");

    /*Initilisation du Timer pour l'horloge*/
    hw_timer_t *timer_clock = NULL;
    timer_clock = timerBegin(0, 80, true);                    // Initialise le timer 0, diviseur 80 (donc fréquence de 1MHz), comptage ascendant
    timerAttachInterrupt(timer_clock, &Timer_Clock_IT, true); // Attache la fonction Timer_Clock_IT à notre timer
    timerAlarmWrite(timer_clock, 1000000, true);              // Déclenche l'interruption toutes les secondes
    timerAlarmEnable(timer_clock);                            // Active l'interruption
    Serial.println("Setup NTP Fini");
}

void loop()
{

    if (alarm_ring)
    {
        Serial.println("Réveil Sonne");
        // TODO: sonner le réveil
    } else
    {
        // TODO: disable buzzer
    }

    if (update_time)
    {
        getLocalTime((tm *)&time_clock, 10000);
        screen_updateTime();
        update_time = false;
    }

    if (clock_update)
    {
        Serial.println((tm *)&time_clock, "%A, %B %d %Y %H:%M:%S");
        screen_updateTime();
        clock_update = false;
    }
    ArduinoOTA.handle(); // OTA
}
