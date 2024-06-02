#include "main.h"
#include "Interrupt.h"
#include "WiFiManager.h"
#include "ArduinoOTA.h"
#include "Screen.h"
#include "pitches.h"
#include "anyrtttl.h"

DFRobot_Touch_GT911 touch;
DFRobot_ILI9488_320x480_HW_SPI screen(/*dc=*/TFT_DC, /*cs=*/TFT_CS, /*rst=*/TFT_RST);
DFRobot_UI ui(&screen, &touch);

volatile tm time_clock;
volatile AlarmEditState state;
volatile bool alarm_ring = false;
// TODO: généraliser pour 5 alarmes
volatile AlarmClock alarm_clock[MAX_ALARM]; // 5 alarmes possibles, seul la première utilisé pour l'instant

char tetris_melody_alarm[] PROGMEM = "tetris:d=4,o=5,b=160:e6,8b,8c6,8d6,16e6,16d6,8c6,8b,a,8a,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,2a,8p,d6,8f6,a6,8g6,8f6,e6,8e6,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,a";
char mario_melody_alarm[] PROGMEM = "mario:d=4,o=5,b=100:16e6,16e6,32p,8e6,16c6,8e6,8g6,8p,8g,8p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16c7,16p,16c7,16c7,p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16d#6,8p,16d6,8p,16c6";

volatile bool update_time;
volatile bool clock_update;
volatile bool edit_screen_update;
volatile bool init_home_screen_needed;

void setup()
{
  WiFiManager wm;
  // wm.resetSettings();
  bool res;

  Serial.begin(115200);
  Serial.println("Début programme");

  pinMode(TFT_BL,OUTPUT);
  digitalWrite(TFT_BL,HIGH);

  /*Initialisation du wifi*/
  WiFi.mode(WIFI_STA);

  // wifi name and password
  res = wm.autoConnect("Clock_AP_FALLBACK", "12345678");
  while (!res)
  {
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Wifi connected");

  /*MAJ OTA*/
  ArduinoOTA.setHostname("clock"); // upload with clock.local
  ArduinoOTA
      .onStart([]() {
        String type;

        if (U_FLASH == ArduinoOTA.getCommand()) {
          type = "sketch";
        } else {  // U_SPIFFS
          type = "filesystem";
        }

        // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
        Serial.println("Start updating " + type); 
      })
      .onEnd([]() { 
        Serial.println("\nEnd");
      })
      .onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
      })
      .onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        switch(error) {
          case OTA_AUTH_ERROR:
            Serial.println("Auth Failed");
            break;
          case OTA_BEGIN_ERROR:
            Serial.println("Begin Failed");
            break;
          case OTA_CONNECT_ERROR:
            Serial.println("Connect Failed");
            break;
          case OTA_RECEIVE_ERROR:
            Serial.println("Receive Failed");
            break;
          case OTA_END_ERROR:
            Serial.println("End Failed");
            break;
        }
      });
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
  pinMode(CLK_ROTATIF, INPUT_PULLUP);
  pinMode(DATA_ROTATIF, INPUT_PULLUP);
  attachInterrupt(SW_ROTATIF, changeEditState, RISING);
  attachInterrupt(CLK_ROTATIF, rotatingInterrupt, RISING);
  Serial.println("Setup Encodeur Fini");

  /* setup of snoozing switch button */
  pinMode(SW_SNOOZE, INPUT_PULLUP);
  attachInterrupt(SW_SNOOZE, snoozeInterrupt, FALLING); // when button is pressed, SW_SNOOZE will be dropping to GND, so falling is first
  Serial.println("Setup Snoozing Fini");

  /* setup of buzzer */
  pinMode(BUZZER_OUT, OUTPUT);
  Serial.println("Setup Buzzer Fini");

  /*Initilisation du Timer pour l'horloge*/
  hw_timer_t *timer_clock = NULL;
  timer_clock = timerBegin(0, 80, true);                    // Initialise le timer 0, diviseur 80 (donc fréquence de 1MHz), comptage ascendant
  timerAttachInterrupt(timer_clock, &Timer_Clock_IT, true); // Attache la fonction Timer_Clock_IT à notre timer
  timerAlarmWrite(timer_clock, 1000000, true);              // Déclenche l'interruption toutes les minutes
  timerAlarmEnable(timer_clock);                            // Active l'interruption
  Serial.println("Setup NTP Fini");

  // FIXME: corriger le fichier ../.pio/libdeps/dfrobot_.../anyrtttl.cpp avec DelayFuncPtr _delay = (void (*)(long unsigned int))(&delay);
  ledcAttachPin(BUZZER_OUT, 0);
  
  state = NO_EDIT;
  update_time = false;
  clock_update = false;
  init_home_screen_needed = false;
}
  

void loop()
{
  // Serial.println("loop beginned");
  if (alarm_ring)
  { // alarm should go ringing, and you are not editing it
    // Serial.println("Réveil Sonne");
    if(!anyrtttl::nonblocking::isPlaying())
    {
      anyrtttl::nonblocking::begin(BUZZER_OUT, mario_melody_alarm);
    }
    anyrtttl::nonblocking::play();
  }
  else
  {
    anyrtttl::nonblocking::stop();
  }

  if(init_home_screen_needed) {
    screen_display_hour();
    init_home_screen_needed = false;
  }

  if (update_time)
  {
    getLocalTime((tm *)&time_clock, 10000);
    if(NO_EDIT == state) {
      Serial.println("Updating time by ntp!");
      screen_updateTime();
    }
    update_time = false;
  }

  if (clock_update)
  {
    Serial.println((tm *)&time_clock, "%A, %B %d %Y %H:%M:%S");
    if(NO_EDIT == state) {
      Serial.println("Updating time by clock!");
      screen_updateTime();
    }
    // TODO: leave edit mode automatically after 20 secs
    clock_update = false;
  }

  if(edit_screen_update && NO_EDIT != state)
  {
    Serial.println("Editing mode!");
    edit_screen_update = false;
    screen_edit_alarm();
    
  }
  if(edit_screen_update) {
    Serial.println("edit screen update asked!");
  }

  Serial.printf("Alarme : %dh%d\n", alarm_clock[0].hours, alarm_clock[0].minutes);
  if(alarm_clock[0].repeat) {
    Serial.println("alarm à répet");
  }
  if(alarm_clock[0].active) {
    Serial.println("alarm active");
  }
  switch(state) {
    case NO_EDIT:
      Serial.println("NO_EDIT mode");
      break;
    case HOUR_EDIT:
      Serial.println("HOUR_EDIT mode");
      break;
    case MINUTE_EDIT:
      Serial.println("MINUTE_EDIT mode");
      break;
  }

  delay(300);

  ArduinoOTA.handle(); // OTA
}
