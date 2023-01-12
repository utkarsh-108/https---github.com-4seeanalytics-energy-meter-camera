#ifndef ATOM_DISPLAY_H /* include guards */
#define ATOM_DISPLAY_H
#include <Arduino.h>
#include <FastLED.h>
#include <WiFi.h>

#ifdef HW_M5STICK_C
#include <M5StickC.h>
#endif

#ifdef HW_M5STICK_PLUS
#include <M5StickCPlus.h>

#endif

#ifdef HW_M5STACK_PM
#include <M5Stack.h>
#include "Free_Fonts.h" // Include the header file attached to this sketch
#endif

#ifdef HW_M5STICK_ATOM
#include <M5StickC.h>
#endif

#define Neopixel_PIN 27

// CRGB leds[1];
// uint8_t gHue = 0;

#define DEFAULT_ARRAYSIZE 100
#define DISPLAY_MODE_DEFAULT 0
#define DISPLAY_MODE_WIFI 1
#define DISPLAY_MODE_COUNT 2
#define DISPLAY_MODE_ID 3
#define DISPLAY_MODE_QR 4
#define DISPLAY_MODE_AP 5
#define DISPLAY_MODE_NONE 6

#define BLINK_TINY 50
#define BLINK_SHORT 100
#define BLINK_LONG 250
#define BLINK_EXTRA_LONG 500

#ifdef HW_M5STICK_ATOM
class ATOM_Display
{
public:
  ATOM_Display();
  bool init(String sw_ver, String deviceCode);
  void wifi_setup_screen(String tssid, String tpass);
  void display_occupancy(int occupancy);
  void connection_status(bool wstatus, bool mstatus);
  void show_device_id();
  void show_on_demand_screen();
  void show_reset_screen();
  void show_first_time_screen();
  void show_error_screen(int errorcode);
  void switch_display_mode(int modeID);
  void blink(int duration);
  void show_setup_mode(bool network, bool wifi, bool code);
  void set_display_color(CRGB color);
  void show_ota_screen();

  void blue_slow_flashing();
  void blue_fast_flashing();
  void white_fast_flashing();
  void red_constant_updating_software();
  void green_beacon();
  void red_beacon();
  void black_led();
  void green_fast_flashing();
  void red_fast_flashing();

private:
  CRGB leds[1];
  int __display_mode;
  CRGB _my_led_color = CRGB::Black;
};
#endif

#ifdef HW_M5STACK_PM
class Air_Quality_Display
{
public:
  Air_Quality_Display();

  bool init(String sw_ver, String deviceCode);
  void wifi_setup_screen(String tssid, String tpass);
  void display_occupancy(int occupancy, int sr, int sy, int sg);
  void display_air_quality(int pm1, int pm2_5, int pm10, int temp, int humi, int voc, int co2, byte Screen_number);
  void connection_status(bool wstatus, bool mstatus);
  void show_device_id();
  void show_on_demand_screen();
  void show_reset_screen();
  void show_first_time_screen();
  void show_ota_screen();
  void show_error_screen(int errorcode);
  void switch_display_mode(int modeID);
  void show_setup_mode(bool network, bool wifi, bool code);
  void set_display_color(CRGB color);
  void blink(int duration);

private:
  CRGB leds[1];
  int QR_CODE_WIDTH = 320;
  int SCREEN_WIDTH = 320;
  int SCREEN_HEIGHT = 240;
  int OCCUPANCY_FONT_SIZE = 10;
  // Imported from M5 Display
  int X_LOCAL = 100;
  int Y_LOCAL = 30;
  int X_OFFSET = 160;
  int Y_OFFSET = 20;
  int FRONT = 2;
  int PIN_LED = 10;
  int __display_mode;
  char __deviceCode[5];
};
#endif

class M5Stick_Display
{
public:
  M5Stick_Display();

  bool init(String sw_ver, String deviceCode);
  void wifi_setup_screen(String tssid, String tpass);
  void display_occupancy(int occupancy, int sr, int sy, int sg);
  void display_air_quality(int pm1, int pm2_5, int pm10, int temp, int humi, int voc, int co2);
  void connection_status(bool wstatus, bool mstatus);
  void show_device_id();
  void show_on_demand_screen();
  void show_reset_screen();
  void show_first_time_screen();
  void show_ota_screen();
  void show_error_screen(int errorcode);
  void switch_display_mode(int modeID);
  void show_setup_mode(bool network, bool wifi, bool code);
  void set_display_color(CRGB color);
  void blink(int duration);

private:
  CRGB leds[1];
#ifdef HW_M5STACK_PM
  int QR_CODE_WIDTH = 80;
  int SCREEN_WIDTH = 160;
  int SCREEN_HEIGHT = 80;
  int OCCUPANCY_FONT_SIZE = 8;
#endif

#ifdef HW_M5STICK_C
  int QR_CODE_WIDTH = 80;
  int SCREEN_WIDTH = 160;
  int SCREEN_HEIGHT = 80;
  int OCCUPANCY_FONT_SIZE = 8;
#endif

#ifdef HW_M5STICK_PLUS
  int QR_CODE_WIDTH = 135;
  int SCREEN_WIDTH = 135;
  int SCREEN_HEIGHT = 240;
  int OCCUPANCY_FONT_SIZE = 10;
#endif

  // Imported from M5 Display
  int X_LOCAL = 100;
  int Y_LOCAL = 30;
  int X_OFFSET = 160;
  int Y_OFFSET = 20;
  int FRONT = 2;
  int PIN_LED = 10;
  int __display_mode;
  char __deviceCode[5];
};

#define FontB18 FSSB18
#define FontB12 FSSB12
#define Font12 FSS12

#define Button_Colour 0xA5C7 // olive (161, 177, 58) RGB

/* declaration of the funcitons */
void Display_Page_0(void);
void Display_Page_1(void);
void Display_Page_2(void);
void Display_Page_3(void);
void Display_Page_4(void);
void Display_Page_5(void);
void Display_Page_6(void);
void Display_Page_7(void);
void Display_Page_8(void);
void Display_Page_9(void);

void bottom_left(const char *string);
void bottom_right(const char *string);
void bottom_center(const char *string);
void Clear_Button(char button);

#endif