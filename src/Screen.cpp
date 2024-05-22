#include "Screen.h"
const unsigned char alarm_repeat_icon[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfc,
    0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xc0, 0x00,
    0x00, 0x00, 0x7f, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x03,
    0xff, 0x80, 0x1f, 0xf8, 0x00, 0x00, 0x03, 0xfe, 0x00, 0x07, 0xfc, 0x00, 0x00, 0x07, 0xf8, 0x00,
    0x01, 0xfe, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0xff, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x7f,
    0x80, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x3f, 0x80, 0x00, 0x3f, 0x80, 0x00, 0x00, 0x1f, 0xc0, 0x00,
    0x3f, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x7e, 0x00,
    0x00, 0x00, 0x07, 0xe0, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0xfc, 0x00, 0x00, 0x00,
    0x03, 0xe0, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x3f, 0xff,
    0x00, 0xfc, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xc0, 0xfc, 0x00, 0x00, 0x00, 0xff, 0xff, 0xc0, 0xfc,
    0x00, 0x00, 0x00, 0xff, 0xff, 0xc0, 0xfc, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xc0, 0xfc, 0x00, 0x00,
    0x00, 0x7f, 0xff, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x3f, 0xff, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x1f,
    0xfe, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x0f, 0xfc, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x07, 0xf8, 0x00,
    0x7e, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x3f, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00,
    0x60, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x07, 0xf8, 0x00, 0x01, 0xf8, 0x00,
    0x00, 0x03, 0xfe, 0x00, 0x07, 0xfc, 0x00, 0x00, 0x03, 0xff, 0x80, 0x1f, 0xf8, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x3f, 0xff,
    0xff, 0xc0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfc, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const unsigned char alarm_active_icon[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e,
    0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00,
    0x1f, 0xc0, 0x00, 0x01, 0xf8, 0x00, 0xc0, 0x07, 0xe0, 0x00, 0x03, 0xe0, 0x01, 0xe0, 0x01, 0xf0,
    0x00, 0x07, 0xc0, 0x03, 0xf0, 0x00, 0xf8, 0x00, 0x0f, 0x83, 0xc3, 0xf0, 0xf0, 0x7c, 0x00, 0x1f,
    0x0f, 0xc3, 0xf0, 0xfc, 0x3e, 0x00, 0x1e, 0x1f, 0xc3, 0xf0, 0xfe, 0x1e, 0x00, 0x3c, 0x3f, 0x03,
    0xf0, 0x3f, 0x0f, 0x00, 0x3c, 0x7c, 0x0f, 0xfc, 0x0f, 0x87, 0x00, 0x78, 0x78, 0x3f, 0xff, 0x07,
    0x87, 0x80, 0x78, 0xf0, 0x7f, 0xff, 0x83, 0xc7, 0x80, 0x70, 0xf0, 0xf8, 0x07, 0xc3, 0xc3, 0x80,
    0x71, 0xe1, 0xf0, 0x03, 0xe1, 0xe3, 0xc0, 0xf1, 0xe1, 0xe0, 0x01, 0xe1, 0xe3, 0xc0, 0xf1, 0xc3,
    0xc0, 0x00, 0xf0, 0xe3, 0xc0, 0xe1, 0xc3, 0x80, 0x00, 0x70, 0xe1, 0xc0, 0xe1, 0xc3, 0x80, 0x00,
    0x70, 0xe1, 0xc0, 0xe1, 0xc3, 0x80, 0x00, 0x78, 0xe1, 0xc0, 0xe1, 0xc7, 0x80, 0x00, 0x78, 0xe1,
    0xc0, 0xf1, 0xe7, 0x80, 0x00, 0x79, 0xe3, 0xc0, 0xf1, 0xe7, 0x80, 0x00, 0x79, 0xe3, 0xc0, 0x70,
    0xc7, 0x80, 0x00, 0x78, 0xc3, 0x80, 0x70, 0x07, 0x80, 0x00, 0x78, 0x03, 0x80, 0x70, 0x07, 0x80,
    0x00, 0x78, 0x03, 0x80, 0x00, 0x07, 0x80, 0x00, 0x78, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x38,
    0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x3c, 0x00, 0x00,
    0x00, 0x0f, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x1e,
    0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00,
    0x07, 0x80, 0x00, 0x00, 0x70, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x03, 0xc0,
    0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00,
    0x3f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e,
    0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfc, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

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
