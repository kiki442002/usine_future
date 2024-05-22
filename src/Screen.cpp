#include "Screen.h"

void screen_init()
{
    ui.begin();
    ui.setTheme(DFRobot_UI::MODERN);

    screen.begin();
    screen.fillScreen(COLOR_RGB565_BLACK);
    screen.setFont(&FreeMonoBold12pt7b);
    screen.setTextSize(3);
    screen.setTextColor(COLOR_RGB565_WHITE);
}

void screen_updateTime()
{
    screen.setCursor(10, 120);
    screen.print((tm *)&time_clock, "%A, %B %d %Y \n %H:%M:%S");
}

void screen_indicate_alarm() {
    return;
}
