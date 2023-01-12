#include "display.h"

#include "AQI_Calculation.h"

#ifdef HW_M5STICK_ATOM
ATOM_Display::ATOM_Display()
{
}

bool ATOM_Display::init(String sw_ver, String deviceCode)
{
  FastLED.addLeds<WS2811, Neopixel_PIN, GRB>(leds, 1).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(10);

  leds[0] = _my_led_color;
  FastLED.show();
  return true;
}

void ATOM_Display::show_ota_screen()
{
}

void ATOM_Display::wifi_setup_screen(String tssid, String tpass)
{
}

void ATOM_Display::show_device_id()
{
}

void ATOM_Display::display_occupancy(int occupancy)
{
}

void ATOM_Display::connection_status(bool wstatus, bool mstatus)
{
  if (wstatus == true)
  {
    leds[0] = CRGB::Blue;
  }
  else
  {
    leds[0] = CRGB::Red;
    //  FastLED.show();
  }
  // if (wstatus && mstatus)
  // {
  //   green_beacon();
  // }
  // else if (!wstatus || !mstatus)
  // {
  //   red_beacon();
  // }
}

void ATOM_Display::show_reset_screen()
{
}

void ATOM_Display::show_on_demand_screen()
{
}

void ATOM_Display::show_first_time_screen()
{
}

void ATOM_Display::show_error_screen(int errorcode)
{
}

void ATOM_Display::set_display_color(CRGB color)
{
  _my_led_color = color;
  leds[0] = _my_led_color;
  FastLED.show();
}

void ATOM_Display::show_setup_mode(bool network, bool wifi, bool code)
{
  leds[0] = CRGB::Red;

  if (network == true)
  {
    leds[0] = CRGB::Green;
  }

  if (wifi == true)
  {
    leds[0] = CRGB::Blue;
  }

  if (code == true)
  {
    leds[0] = CRGB::White;
  }

  FastLED.show();
  delay(BLINK_TINY);
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(BLINK_TINY);
}

void ATOM_Display::blink(int duration)
{

  leds[0] = CRGB::Black;
  FastLED.show();
  delay(duration);
  leds[0] = _my_led_color;
  FastLED.show();
}

/****************************************************************
 * void blue_slow_flashing()
 * function Flashes Blue LED for On time of 1s and off time of 1s
 * Author : Utkarsh Chitte
 * Last Modified : 22-04-01
 ****************************************************************/
void ATOM_Display::blue_slow_flashing()
{
  // Serial.println("blue_slow");
  leds[0] = CRGB::Blue;
  FastLED.show();
  delay(1000);
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(1000);
}

/**********************************************************************
 * void blue_fast_flashing()
 * function Flashes Blue LED for On time of 100ms and off time of 100ms
 * Author : Utkarsh Chitte
 * Last Modified : 22-04-01
 **********************************************************************/
void ATOM_Display::blue_fast_flashing()
{
  // Serial.println("blue_fast");
  leds[0] = CRGB::Blue;
  FastLED.show();
  delay(100);
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(100);
}

/***********************************************************************
 * void white_fast_flashing()
 * function Flashes White LED for On time of 100ms and off time of 100ms
 * Author : Utkarsh Chitte
 * Last Modified : 22-04-01
 **********************************************************************/
void ATOM_Display::white_fast_flashing()
{
  // Serial.println("white_fast");
  leds[0] = CRGB::White;
  FastLED.show();
  delay(100);
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(100);
}

/****************************************************************
 * void red_constant_updating_software()
 * function keeps Red LED on until the flow exits the function
 * Author : Utkarsh Chitte
 * Last Modified : 22-04-01
 ****************************************************************/
void ATOM_Display::red_constant_updating_software()
{
  // Serial.println("red");
  leds[0] = CRGB::Red;
  FastLED.show();
}

/********************************************************************
 * void green_beacon()
 * function Flashes Green LED for On time of 200ms and off time of 5s
 * Author : Utkarsh Chitte
 * Last Modified : 22-04-01
 ********************************************************************/

void ATOM_Display::green_beacon()
{
  //  Serial.println("green_beacon");
  leds[0] = CRGB::Green;
  FastLED.show();
  delay(200);
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(5000);
}

/********************************************************************
 * void red_beacon()
 * function Flashes Red LED for On time of 200ms and off time of 5s
 * Author : Utkarsh Chitte
 * Last Modified : 22-04-01
 ********************************************************************/
void ATOM_Display::red_beacon()
{
  // Serial.println("red_beacon");
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(200);
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(5000);
}

/********************************************************************
 * void black_led()
 * makes LED Black
 * Author : Utkarsh Chitte
 * Last Modified : 22-04-01
 ********************************************************************/
void ATOM_Display::black_led()
{
  // Serial.println("black");
  leds[0] = CRGB::Black;
  FastLED.show();
}

/****************************************************************
 * void green_fast_flashing()
 * function Flashes green LED for On time of 100ms and off time of 100ms
 * Author : Utkarsh Chitte
 * Last Modified : 22-04-01
 ****************************************************************/
void ATOM_Display::green_fast_flashing()
{
  // Serial.println("green_fast");
  leds[0] = CRGB::Green;
  FastLED.show();
  delay(100);
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(100);
}

/**********************************************************************
 * void red_fast_flashing()
 * function Flashes Blue LED for On time of 100ms and off time of 100ms
 * Author : Utkarsh Chitte
 * Last Modified : 22-04-01
 **********************************************************************/
void ATOM_Display::red_fast_flashing()
{
  // Serial.println("red_fast");
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(100);
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(100);
}

#endif

/*****************************************************************************/
/*****************************************************************************/
/*****************          AIR QUALITY SENSOR         ***********************/
/*****************************************************************************/
/*****************************************************************************/

#ifdef HW_M5STACK_PM
Air_Quality_Display::Air_Quality_Display()
{
}

void Air_Quality_Display::set_display_color(CRGB color)
{
}

bool Air_Quality_Display::init(String sw_ver, String deviceCode)
{
  __display_mode = DISPLAY_MODE_DEFAULT;

  M5.Lcd.fillScreen(TFT_BLACK); // Black screen fill
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setTextSize(2);

  deviceCode.toCharArray(__deviceCode, 4);

  M5.Lcd.fillScreen(TFT_BLACK); // Black screen fill
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setTextSize(3);

  M5.Lcd.setCursor(90, 5);
  M5.Lcd.print(sw_ver);

  M5.Lcd.setTextSize(6);
  M5.Lcd.setCursor(110, 120);

  M5.Lcd.print(__deviceCode);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(80, 40);
  M5.Lcd.print("www.secure.live");

  delay(2000);
  return true;
}

void Air_Quality_Display::wifi_setup_screen(String tssid, String tpass)
{

  M5.Lcd.setTextColor(TFT_BLUE);

  M5.Lcd.print("www.secure.live");
}

void Air_Quality_Display::show_device_id()
{
  M5.Lcd.fillScreen(TFT_WHITE); // Black screen fill
  String bid = WiFi.macAddress();
  bid.replace(":", "");

  /*M5.Lcd.qrcode(bid, 0, 0, 200, 6);
  delay(2000);
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setTextSize(2);
  //delay(2000);
  M5.Lcd.setCursor(20, 190);
  M5.Lcd.print(bid.substring(0,6));
  //delay(2000);
  M5.Lcd.setCursor(100, 190);
  M5.Lcd.print(bid.substring(6,12));*/
}

void Air_Quality_Display::display_occupancy(int occupancy, int sr, int sy, int sg)
{

  int ocolor = 0;
  if (occupancy >= sr)
    ocolor = 3;
  else if (occupancy >= sy)
    ocolor = 2;
  else if (occupancy >= sg)
    ocolor = 1;
  else
    ocolor = 0;

  if (ocolor == 0)
  {
    M5.Lcd.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TFT_BLACK);
  }
  else if (ocolor == 1)
  {
    M5.Lcd.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TFT_DARKGREEN);
  }
  else if (ocolor == 2)
  {
    M5.Lcd.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TFT_YELLOW);
  }
  else if (ocolor == 3)
  {
    M5.Lcd.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TFT_RED);
  }

  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setTextSize(OCCUPANCY_FONT_SIZE);
  M5.Lcd.print(occupancy);
}

uint32_t get_colour(byte scale_value)
{
  switch (scale_value)
  {
  case 0:
    return TFT_GREEN;
    break;
  case 1:
    return TFT_GREENYELLOW;
    break;
  case 2:
    return TFT_YELLOW;
    break;
  case 3:
    return TFT_ORANGE;
    break;
  case 4:
    return TFT_RED;
    break;
  default:
    return TFT_TRANSPARENT;
    break;
  }
  /*
  if (scale_value == 0)
    return TFT_GREEN;
  else if (scale_value == 1)
    return TFT_GREENYELLOW;
  else if (scale_value == 2)
    return TFT_YELLOW;
  else if (scale_value == 3)
    return TFT_ORANGE;
  else if (scale_value == 4)
    return TFT_RED;
  else
    return TFT_TRANSPARENT;*/
}

uint32_t Background_colour(byte aq_int)
{
  /*int aq_int;
  aq_int = (int)aq;*/

  if ((aq_int <= 100) && (aq_int >= 61))
  {
    // return TFT_DARKGREEN;
    return 0xaf50;
  }
  if ((aq_int <= 60) && (aq_int >= 21))
  {
    // return 0xffc107;
    // return TFT_ORANGE;
    return 0xD407;
  }
  if ((aq_int <= 20) && (aq_int >= 1))
  {
    // return TFT_RED;
    // return 0xf44336;
    return 0xF206;
  }
}

uint32_t temperature_colour(byte T)
{
  if (T >= 77)
  {
    return 0xF206; // red
  }
  if ((T <= 76) & (T >= 64))
  {
    return 0xaf50; // green
  }
  if ((T <= 63) & (T >= 51))
  {
    return 0xD407; // orange
  }
  if (T <= 50)
  {
    return 0x340F; // blue
  }
}

uint32_t humidity_colour(byte H)
{
  if (H >= 61)
  {
    return 0xF206; // red
  }
  if ((H <= 60) & (H >= 41))
  {
    return 0xD407; // orange
  }
  if (H <= 40)
  {
    return 0xaf50; // green
  }
}

// uint32_t text_colour(float aq)
// {
//   int aq_int;
//   aq_int = (int)aq;
//   /*
//   if((aq_int <= 80)&(aq_int >= 21))
//   {
//     return TFT_BLACK;
//   }
//   else
//   {
//     return TFT_WHITE;
//   }*/
//   return TFT_BLACK;
// }

void Air_Quality_Display::display_air_quality(int pm1, int pm2_5, int pm10, int temp, int humi, int voc, int co2, byte main_screen)
{

  M5.Lcd.fillScreen(TFT_BLACK); // Black screen fill

  byte bar_count = 5; // Number of bars on display
  byte dot_count = 5; // Number of dots for each bar

  byte dot_gapx = 19;    // Gap between Dots
  byte dot_gapy = 20;    // Gap between Colums
  byte dot_offsetX = 18; // Screen offset X pos
  byte dot_offsetY = 30; // Screen offset Y Pos
  byte dot_radius = 10;  // Raidus of the dot

  uint16_t aqi_circle_x = 240;
  uint16_t aqi_circle_y = 90;
  uint16_t aqi_circle_radius = 70;
  /*
  float tmax = 95;   //Maximum Temperature
  float tmin = 68;   // Minimum Temperature
  float tgood = 78;  //Ideal Temperature
  float hmax = 60;   //Maximum Humidity
  float hmin = 10;   // Minimum Humidity
  float hgood = 45;  //Ideal Humidity
  float cmax = 2000; //Maximum CO2
  float cmin = 400;  // Minimum CO2
  float cgood = 600; //Ideal CO2
  float pmax = 1000; //Maximum PM2.5
  float pmin = 0;    // Minimum PM2.5
  float pgood = 5;   //Ideal PM2.5
  float vmax = 50;   //Maximum VOC
  float vmin = 0;    // Minimum VOC
  float vgood = 0;   //Ideal VOC
  */
  // Calculate the number of dots to show
  /*float tdots = abs((temp - tgood)) / (tmax - tmin) * 5;
  float hdots = abs((humi - hgood)) / (hmax - hmin) * 5;
  float cdots = abs((co2 - cgood)) / (cmax - cmin) * 5;
  float pdots = abs((pm2_5 - pgood)) / (pmax - pmin) * 5;
  float vdots = abs((voc - vgood)) / (vmax - vmin) * 5;*/

  float AQI_PM25 = 0, AQI_CO2 = 0, AQI_VOC = 0, AQI_TEMP = 0, AQI_HUMI = 0;
  Get_All_AQI_Values(&AQI_PM25, &AQI_VOC, &AQI_CO2, &AQI_TEMP, &AQI_HUMI);

  float tdots = 0, hdots = 0, cdots = 0, pdots = 0, vdots = 0;
  if (AQI_TEMP > 0)
    tdots = AQI_TEMP / 100;
  if (AQI_HUMI > 0)
    hdots = AQI_HUMI / 100;
  if (AQI_CO2 > 0)
    cdots = AQI_CO2 / 100;
  if (AQI_PM25 > 0)
    pdots = AQI_PM25 / 100;
  if (AQI_VOC > 0)
    vdots = AQI_VOC / 100;

  float AQI = (100 - (vdots + cdots + tdots + hdots + pdots) * 4);
  Serial.print("AQI = ");
  Serial.println(AQI);
  // float AQI = ((vdots + cdots + tdots + hdots + pdots) * 4);

  //----------------------------------------------------------------------
  /*int main_screen = Screen_number;
  Serial.println(main_screen);*/
  Serial.println("Screen No :" + String(main_screen));
  /*---------------------------Display screens bifurcation-------------------------*/

  if (main_screen == 0)
  {
    Serial.println("Home Screen active");
    M5.Lcd.fillScreen(TFT_BLACK); // Black screen fill
    aqi_circle_x = 160;
    aqi_circle_y = 90;

    M5.Lcd.setFreeFont(FF24);
    M5.Lcd.setTextSize(2);

    M5.Lcd.setTextColor(TFT_BLACK);
    M5.Lcd.setCursor(aqi_circle_x - 52, aqi_circle_y + 35, FRONT);
    M5.Lcd.drawCircle(aqi_circle_x, aqi_circle_y, aqi_circle_radius + 1, TFT_WHITE);

    if (AQI < 0)
    {
      M5.Lcd.fillCircle(aqi_circle_x, aqi_circle_y, aqi_circle_radius, 0xaf50);
      M5.Lcd.print("0");
    }
    else if (AQI > 100)
    {
      M5.Lcd.fillCircle(aqi_circle_x, aqi_circle_y, aqi_circle_radius, 0xaf50);
      M5.Lcd.print("99");
    }
    else
    {
      M5.Lcd.fillCircle(aqi_circle_x, aqi_circle_y, aqi_circle_radius, Background_colour(AQI));
      M5.Lcd.print(int(AQI));
    }

    M5.Lcd.setFreeFont(FF18);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(TFT_LIGHTGREY);
    M5.Lcd.setCursor(110, 190, FRONT);
    M5.lcd.print("AQ Score");

    // M5.Lcd.setTextSize(1);
    // M5.Lcd.setFreeFont(FSS12);
    // M5.Lcd.setTextColor(TFT_LIGHTGREY);
    // M5.Lcd.setTextDatum(TC_DATUM); // Centre text on x,y position
    // M5.Lcd.drawString("AQ Score",160,180);

    // M5.Lcd.fillRoundRect(230, 200, 80, 30, 10, TFT_OLIVE); // 0x340F
    // M5.Lcd.setCursor(239, 222, FRONT);
    // M5.lcd.print("NEXT");

    bottom_right("NEXT");
  }
  else if (main_screen == 1)
  {
    Serial.println("Temperature screen active");
    M5.Lcd.fillScreen(TFT_BLACK); // Black screen fill
    aqi_circle_x = 160;
    aqi_circle_y = 90;

    M5.Lcd.setFreeFont(FF24);

    M5.Lcd.setTextColor(TFT_BLACK);

    M5.Lcd.setCursor(aqi_circle_x - 52, aqi_circle_y + 35, FRONT);
    M5.Lcd.drawCircle(aqi_circle_x, aqi_circle_y, aqi_circle_radius + 1, TFT_WHITE);

    M5.Lcd.fillCircle(aqi_circle_x, aqi_circle_y, aqi_circle_radius, temperature_colour(temp));
    if (temp > 99)
    {
      M5.Lcd.setCursor(aqi_circle_x - 40, aqi_circle_y + 15, FRONT);
      M5.Lcd.setTextSize(1);
    }
    else
      M5.Lcd.setTextSize(2);
    M5.Lcd.print(int(temp));

    M5.Lcd.setFreeFont(FF18);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(TFT_LIGHTGREY);
    M5.Lcd.setCursor(65, 190, FRONT);
    M5.lcd.print("TEMPERATURE  F");
    M5.Lcd.drawCircle(250, 175, 3, TFT_WHITE); // degree

    // M5.Lcd.fillRoundRect(120, 200, 80, 30, 10, TFT_OLIVE); // 0x340F
    // M5.Lcd.setTextColor(TFT_WHITE);
    // M5.Lcd.setCursor(123, 222, FRONT);
    // M5.lcd.print("HOME");

    // M5.Lcd.fillRoundRect(230, 200, 80, 30, 10, TFT_OLIVE); // 0x340F
    // M5.Lcd.setCursor(239, 222, FRONT);
    // M5.lcd.print("NEXT");

    bottom_center("HOME");
    bottom_right("NEXT");
  }
  else if (main_screen == 2)
  {
    Serial.println("Humidity Screen active");
    M5.Lcd.fillScreen(TFT_BLACK); // Black screen fill
    aqi_circle_x = 160;
    aqi_circle_y = 90;

    M5.Lcd.setFreeFont(FF24);
    M5.Lcd.setTextSize(2);

    M5.Lcd.setTextColor(TFT_BLACK);

    M5.Lcd.setCursor(aqi_circle_x - 52, aqi_circle_y + 35, FRONT);
    M5.Lcd.drawCircle(aqi_circle_x, aqi_circle_y, aqi_circle_radius + 1, TFT_WHITE);

    M5.Lcd.fillCircle(aqi_circle_x, aqi_circle_y, aqi_circle_radius, humidity_colour(humi));
    M5.Lcd.print(int(humi));

    M5.Lcd.setFreeFont(FF18);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(TFT_LIGHTGREY);
    M5.Lcd.setCursor(100, 190, FRONT);
    M5.lcd.print("HUMIDITY %");

    // M5.Lcd.fillRoundRect(120, 200, 80, 30, 10, TFT_OLIVE); // 0x340F
    // M5.Lcd.setTextColor(TFT_WHITE);
    // M5.Lcd.setCursor(123, 222, FRONT);
    // M5.lcd.print("HOME");

    // M5.Lcd.fillRoundRect(230, 200, 80, 30, 10, TFT_OLIVE); // 0x340F
    // M5.Lcd.setCursor(239, 222, FRONT);
    // M5.lcd.print("NEXT");

    bottom_center("HOME");
    bottom_right("NEXT");
  }
  else if (main_screen == 3)
  {
    M5.Lcd.fillScreen(TFT_BLACK); // Black screen fill
    Serial.println("Details Screen active");
    // Draw background empty circles
    for (int i = 0; i < bar_count; i++)
    {
      for (int y = 0; y < dot_count; y++)
      {
        M5.lcd.drawCircle(dot_offsetX + (dot_radius + dot_gapx) * i, dot_offsetY + (dot_radius + dot_gapy) * y, dot_radius, TFT_DARKGREY);
      }
    }

    M5.Lcd.setFreeFont(FF18);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(TFT_DARKGREY);
    M5.Lcd.setCursor(12, 190, FRONT);
    M5.lcd.print("T  H  C  P  V");

    M5.Lcd.setFreeFont(FF18);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(TFT_LIGHTGREY);
    M5.Lcd.setCursor(193, 190, FRONT);
    M5.lcd.print("AQ Score");

    // Display The Dots
    for (int y = 0; y < dot_count; y++)
    {
      if (y < round(tdots))
      {
        M5.lcd.fillCircle(dot_offsetX + (dot_radius + dot_gapx) * 0, dot_offsetY + (dot_radius + dot_gapy) * (4 - y), dot_radius, get_colour(y));
        // Serial.println(dot_offsetY + (dot_radius + dot_gapy) * (4 - y));
      }

      if (y < round(hdots))
        M5.lcd.fillCircle(dot_offsetX + (dot_radius + dot_gapx) * 1, dot_offsetY + (dot_radius + dot_gapy) * (4 - y), dot_radius, get_colour(y));
      if (y < round(cdots))
        M5.lcd.fillCircle(dot_offsetX + (dot_radius + dot_gapx) * 2, dot_offsetY + (dot_radius + dot_gapy) * (4 - y), dot_radius, get_colour(y));
      if (y < round(pdots))
        M5.lcd.fillCircle(dot_offsetX + (dot_radius + dot_gapx) * 3, dot_offsetY + (dot_radius + dot_gapy) * (4 - y), dot_radius, get_colour(y));
      if (y < round(vdots))
        M5.lcd.fillCircle(dot_offsetX + (dot_radius + dot_gapx) * 4, dot_offsetY + (dot_radius + dot_gapy) * (4 - y), dot_radius, get_colour(y));
    }

    Serial.println(String(tdots) + " " + String(hdots) + " " + String(cdots) + " " + String(pdots) + " " + String(vdots) + " ");
    M5.Lcd.setFreeFont(FF24);
    M5.Lcd.setTextSize(2);
    // M5.Lcd.setTextColor(TFT_LIGHTGREY);
    M5.Lcd.setTextColor(TFT_BLACK /*text_colour(AQI)*/);
    M5.Lcd.setCursor(aqi_circle_x - 52, aqi_circle_y + 35, FRONT);
    M5.Lcd.drawCircle(aqi_circle_x, aqi_circle_y, aqi_circle_radius + 1, TFT_WHITE);
    // M5.Lcd.fillCircle(aqi_circle_x, aqi_circle_y, aqi_circle_radius, TFT_DARKGREEN);
    if (AQI < 0)
    {
      M5.Lcd.fillCircle(aqi_circle_x, aqi_circle_y, aqi_circle_radius, 0xaf50);

      M5.Lcd.print("0");
    }
    else if ((AQI > 100))
    {
      M5.Lcd.fillCircle(aqi_circle_x, aqi_circle_y, aqi_circle_radius, 0xF206);

      M5.Lcd.print("99");
    }
    else
    {
      M5.Lcd.fillCircle(aqi_circle_x, aqi_circle_y, aqi_circle_radius, Background_colour(AQI));

      M5.Lcd.print(int(AQI));
    }

    // M5.Lcd.fillRoundRect(120, 200, 80, 30, 10, TFT_OLIVE); // 0x340F
    // M5.Lcd.setFreeFont(FF18);
    // M5.Lcd.setTextSize(1);
    // M5.Lcd.setTextColor(TFT_WHITE);
    // M5.Lcd.setCursor(123, 222, FRONT);
    // M5.lcd.print("HOME");

    // M5.Lcd.fillRoundRect(230, 200, 80, 30, 10, TFT_OLIVE); // 0x340F
    // M5.Lcd.setCursor(239, 222, FRONT);
    // M5.lcd.print("NEXT");

    bottom_center("HOME");
    bottom_right("NEXT");
  }
  else if (main_screen == 4)
  {
    Serial.println("factory Screen active");

    // M5.Lcd.fillScreen(TFT_BLACK); // Black screen fill

    // M5.Lcd.setFreeFont(FF18);
    // M5.Lcd.setTextSize(1);
    // M5.Lcd.setTextColor(TFT_LIGHTGREY);

    // M5.Lcd.setCursor(65, 60, FRONT);
    // M5.lcd.print("FACTORY RESET");

    // M5.Lcd.setFreeFont(FF17);
    // M5.Lcd.setTextSize(1);
    // M5.Lcd.setTextColor(TFT_LIGHTGREY);

    // M5.Lcd.setCursor(10, 90, FRONT);
    // M5.lcd.print("factory reset will remove all the setup");

    // M5.Lcd.setCursor(90, 110, FRONT);
    // M5.lcd.print("and configurations");

    // M5.Lcd.setCursor(65, 150, FRONT);
    // M5.lcd.print("Do you want to continue?");

    // M5.Lcd.setTextSize(1);
    M5.Lcd.fillScreen(TFT_BLACK); // Black screen fill
    M5.Lcd.setTextColor(TFT_LIGHTGREY);
    M5.Lcd.setTextDatum(TC_DATUM);
    M5.Lcd.setFreeFont(FontB12); // Select Free Serif 18 point font
    M5.Lcd.drawString("FACTORY RESET", 160, 30);
    M5.Lcd.setFreeFont(FSS9);
    M5.Lcd.drawString("Factory reset will remove all the setup", 160, 80);
    M5.Lcd.drawString("and configurations", 160, 110);
    M5.Lcd.drawString("Do you want to continue?", 160, 150);

    // M5.Lcd.setFreeFont(FF18);
    // M5.Lcd.fillRoundRect(120, 200, 80, 30, 10, TFT_OLIVE); // 0x340F
    // M5.Lcd.setTextColor(TFT_WHITE);
    // M5.Lcd.setCursor(140, 222, FRONT);
    // M5.lcd.print("NO");

    // M5.Lcd.fillRoundRect(230, 200, 80, 30, 10, TFT_OLIVE); // 0x340F
    // M5.Lcd.setCursor(243, 222, FRONT);
    // M5.lcd.print("YES");
    bottom_center("ON");
    bottom_right("YES");
  }
}
void Air_Quality_Display::connection_status(bool wstatus, bool mstatus)
{
  M5.Lcd.setFreeFont(FF1);
  M5.Lcd.setTextSize(1);

  if (wstatus)
  {
    M5.Lcd.setTextColor(TFT_DARKGREY);
    M5.Lcd.setCursor(2, 10);
    M5.Lcd.print("Wifi");
  }
  else
  {
    M5.Lcd.setTextColor(TFT_RED);
    M5.Lcd.setCursor(2, 10);
    M5.Lcd.print("Wifi");
  }

  if (mstatus)
  {
    M5.Lcd.setTextColor(TFT_DARKGREY);
    M5.Lcd.print(" | Online | ");
    M5.Lcd.print(__deviceCode);
  }
  else
  {
    M5.Lcd.setTextColor(TFT_RED);
    M5.Lcd.print(" | Offline | ");
    M5.Lcd.print(__deviceCode);
  }
}

void Air_Quality_Display::show_ota_screen()
{
  M5.Lcd.fillScreen(TFT_RED); // Black screen fill
  M5.Lcd.setTextSize(4);
  M5.Lcd.setCursor(15, 100);
  M5.Lcd.print("Updating...");
  // delay(2000);
}

void Air_Quality_Display::show_reset_screen()
{
  M5.Lcd.fillScreen(TFT_DARKGREY); // Black screen fill
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(2, 2);
  M5.Lcd.print("RESET");
  delay(2000);
}

void Air_Quality_Display::show_on_demand_screen()
{
  M5.Lcd.fillScreen(TFT_WHITE); // Black screen fill

  M5.Lcd.setTextSize(2);

  M5.Lcd.setCursor(2, 2);
  M5.Lcd.print("WIFI SETUP");
  delay(2000);
}

void Air_Quality_Display::show_first_time_screen()
{
  M5.Lcd.fillScreen(TFT_BLUE); // Black screen fill
  M5.Lcd.setTextColor(TFT_WHITE);
}

void Air_Quality_Display::show_error_screen(int errorcode)
{
  M5.Lcd.fillScreen(TFT_RED); // Black screen fill

  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(2, 2);
  M5.Lcd.print("ERR " + errorcode);
  delay(1000);
}

void Air_Quality_Display::blink(int duration)
{
  digitalWrite(PIN_LED, LOW);
  delay(duration);
  digitalWrite(PIN_LED, HIGH);
  delay(duration);
}

void Air_Quality_Display::show_setup_mode(bool network, bool wifi, bool code)
{
}

#endif

/*****************************************************************************/
/*****************************************************************************/
/*********************          M5STICK         ******************************/
/*****************************************************************************/
/*****************************************************************************/

#ifdef HW_M5STICK_C
M5Stick_Display::M5Stick_Display()
{
}

void M5Stick_Display::set_display_color(CRGB color)
{
}

bool M5Stick_Display::init(String sw_ver, String deviceCode)
{
  __display_mode = DISPLAY_MODE_DEFAULT;

  M5.Lcd.fillScreen(TFT_BLACK); // Black screen fill
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setTextSize(2);

  deviceCode.toCharArray(__deviceCode, 4);

  M5.Lcd.fillScreen(TFT_BLACK); // Black screen fill
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setTextSize(3);

  M5.Lcd.setCursor(90, 5);
  M5.Lcd.print(sw_ver);

  M5.Lcd.setTextSize(6);
  M5.Lcd.setCursor(110, 120);

  M5.Lcd.print(__deviceCode);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(80, 40);
  M5.Lcd.print("www.secure.live");

  delay(2000);
  return true;
}

void M5Stick_Display::wifi_setup_screen(String tssid, String tpass)
{

#ifdef HW_M5STICK_C
  M5.Lcd.fillScreen(TFT_WHITE);
  M5.Lcd.qrcode("WIFI:S:" + tssid + ";T:WPA;P:" + tpass + ";", 0, 0, QR_CODE_WIDTH, 3);

  M5.Lcd.setTextColor(TFT_DARKGREY);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(40, 20);
  M5.Lcd.print("WiFi: " + tssid);
  M5.Lcd.setCursor(40, 40);
  M5.Lcd.print("Pass: " + tpass);

#endif

#ifdef HW_M5STICK_PLUS
  M5.Lcd.setCursor(15, SCREEN_HEIGHT - 60);
  M5.Lcd.print("WiFi : " + tssid);
  M5.Lcd.setCursor(15, SCREEN_HEIGHT - 50);
  M5.Lcd.print("Pass : " + tpass);

  M5.Lcd.fillScreen(TFT_WHITE);
  M5.Lcd.qrcode("WIFI:S:" + tssid + ";T:WPA;P:" + tpass + ";", (SCREEN_WIDTH - QR_CODE_WIDTH) / 2, 0, QR_CODE_WIDTH, 3);

  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_DARKGREY);

#endif

  M5.Lcd.setTextColor(TFT_BLUE);

#ifdef HW_M5STICK_C
  M5.Lcd.setCursor(20, SCREEN_HEIGHT - 10);
#endif

#ifdef HW_M5STICK_PLUS
  M5.Lcd.setCursor(25, SCREEN_HEIGHT - 20);
#endif

  M5.Lcd.print("www.secure.live");
}

void M5Stick_Display::show_device_id()
{

  M5.Lcd.fillScreen(TFT_WHITE); // Black screen fill

  String bid = WiFi.macAddress();
  bid.replace(":", "");

  // M5.Lcd.qrcode(bid, 160, 10, QR_CODE_WIDTH, 1);

#ifdef HW_M5STICK_C
  M5.Lcd.setTextColor(TFT_LIGHTGREY);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(80, 20);
  M5.Lcd.print(bid.substring(0, 6));
  M5.Lcd.setCursor(80, 45);
  M5.Lcd.print(bid.substring(6, 12));

#endif

#ifdef HW_M5STICK_PLUS
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(15, QR_CODE_WIDTH + 20);
  M5.Lcd.print(bid.substring(0, 6));

  M5.Lcd.setCursor(15, QR_CODE_WIDTH + 50);
  M5.Lcd.print(bid.substring(6, 12));

  M5.Lcd.setTextColor(TFT_BLUE);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(25, SCREEN_HEIGHT - 20);
  M5.Lcd.print("www.secure.live");
#endif
}

void M5Stick_Display::display_occupancy(int occupancy, int sr, int sy, int sg)
{

  int ocolor = 0;
  if (occupancy >= sr)
    ocolor = 3;
  else if (occupancy >= sy)
    ocolor = 2;
  else if (occupancy >= sg)
    ocolor = 1;
  else
    ocolor = 0;

  if (ocolor == 0)
  {
    M5.Lcd.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TFT_BLACK);
  }
  else if (ocolor == 1)
  {
    M5.Lcd.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TFT_DARKGREEN);
  }
  else if (ocolor == 2)
  {
    M5.Lcd.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TFT_YELLOW);
  }
  else if (ocolor == 3)
  {
    M5.Lcd.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TFT_RED);
  }

#ifdef HW_M5STICK_C

  if (occupancy < 10)
    M5.Lcd.setCursor((SCREEN_WIDTH / 2) - 20, 20);
  else
    M5.Lcd.setCursor((SCREEN_WIDTH / 2) - 45, 20);
#endif

#ifdef HW_M5STICK_PLUS

  if (occupancy < 10)
    M5.Lcd.setCursor((SCREEN_WIDTH / 2) - 20, 100);
  else
    M5.Lcd.setCursor((SCREEN_WIDTH / 2) - 45, 100);
#endif

  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setTextSize(OCCUPANCY_FONT_SIZE);
  M5.Lcd.print(occupancy);
}

void M5Stick_Display::display_air_quality(int pm1, int pm2_5, int pm10, int temp, int humi, int voc, int co2)
{
  M5.Lcd.setTextSize(1);
  M5.Lcd.fillScreen(TFT_BLACK); // Black screen fill

  M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  M5.Lcd.setCursor(X_LOCAL, Y_LOCAL + Y_OFFSET, FRONT);
  M5.Lcd.print("                     ");
  M5.Lcd.setCursor(X_LOCAL, Y_LOCAL + Y_OFFSET, FRONT);
  M5.Lcd.print("PM1.0 : ");
  M5.Lcd.print(pm1);
  M5.Lcd.print(" uf/m3");

  M5.Lcd.setCursor(X_LOCAL, Y_LOCAL + Y_OFFSET * 2, FRONT);
  M5.Lcd.print("                     ");
  M5.Lcd.setCursor(X_LOCAL, Y_LOCAL + Y_OFFSET * 2, FRONT);
  M5.Lcd.print("PM2.5 : ");
  M5.Lcd.print(pm2_5);
  M5.Lcd.print(" uf/m3");

  M5.Lcd.setCursor(X_LOCAL, Y_LOCAL + Y_OFFSET * 3, FRONT);
  M5.Lcd.print("                     ");
  M5.Lcd.setCursor(X_LOCAL, Y_LOCAL + Y_OFFSET * 3, FRONT);
  M5.Lcd.print("PM10  : ");
  M5.Lcd.print(pm10);
  M5.Lcd.print(" uf/m3");

  M5.Lcd.setCursor(X_LOCAL, Y_LOCAL + Y_OFFSET * 4, FRONT);
  M5.Lcd.print("                     ");
  M5.Lcd.setCursor(X_LOCAL, Y_LOCAL + Y_OFFSET * 4, FRONT);
  M5.Lcd.print("TEMP  : ");
  M5.Lcd.print(temp);
  M5.Lcd.print(" ");
  Serial.print(char(176));
  M5.Lcd.print("F");

  M5.Lcd.setCursor(X_LOCAL, Y_LOCAL + Y_OFFSET * 5, FRONT);
  M5.Lcd.print("                     ");
  M5.Lcd.setCursor(X_LOCAL, Y_LOCAL + Y_OFFSET * 5, FRONT);
  M5.Lcd.print("HUMI  : ");
  M5.Lcd.print(humi);
  M5.Lcd.print(" %");

  M5.Lcd.setCursor(X_LOCAL, Y_LOCAL + Y_OFFSET * 6, FRONT);
  M5.Lcd.print("                     ");
  M5.Lcd.setCursor(X_LOCAL, Y_LOCAL + Y_OFFSET * 6, FRONT);
  M5.Lcd.print("TVOC  : ");
  M5.Lcd.print(voc);
  M5.Lcd.print(" ppb");

  M5.Lcd.setCursor(X_LOCAL, Y_LOCAL + Y_OFFSET * 7, FRONT);
  M5.Lcd.print("                     ");
  M5.Lcd.setCursor(X_LOCAL, Y_LOCAL + Y_OFFSET * 7, FRONT);
  M5.Lcd.print("eCO2  : ");
  M5.Lcd.print(co2);
  M5.Lcd.print(" ppm");
}

void M5Stick_Display::connection_status(bool wstatus, bool mstatus)
{

  M5.Lcd.setTextSize(1);

  if (wstatus)
    M5.Lcd.setTextColor(TFT_WHITE);
  else
    M5.Lcd.setTextColor(TFT_DARKGREY);

  M5.Lcd.setCursor(2, 2);
  M5.Lcd.print("Wifi");

#ifdef HW_M5STICK_C
  if (WiFi.SSID() == "SECURE_SETUP")
  {
    M5.Lcd.setCursor(SCREEN_WIDTH - 100, 2);
    M5.Lcd.print("(SETUP)");
  }

#endif

#ifdef HW_M5STICK_PLUS
  if (WiFi.SSID() == "SECURE_SETUP")
  {
    M5.Lcd.setCursor(SCREEN_WIDTH - 90, 2);
    M5.Lcd.print("(SETUP)");
  }

#endif

  if (mstatus)
    M5.Lcd.setTextColor(TFT_WHITE);
  else
    M5.Lcd.setTextColor(TFT_DARKGREY);

#ifdef HW_M5STICK_C
  M5.Lcd.setCursor(SCREEN_WIDTH - 25, 2);
#endif

#ifdef HW_M5STICK_PLUS
  M5.Lcd.setCursor(SCREEN_WIDTH - 25, 2);
#endif

  M5.Lcd.print(" | Live | ");
  M5.Lcd.print(__deviceCode);
}

void M5Stick_Display::show_ota_screen()
{
  M5.Lcd.fillScreen(TFT_RED); // Black screen fill
  M5.Lcd.setTextSize(4);
  M5.Lcd.setCursor(15, 100);
  M5.Lcd.print("Updating...");
  // delay(2000);
}

void M5Stick_Display::show_reset_screen()
{
  M5.Lcd.fillScreen(TFT_DARKGREY); // Black screen fill
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(2, 2);
  M5.Lcd.print("RESET");
  delay(2000);
}

void M5Stick_Display::show_on_demand_screen()
{
  M5.Lcd.fillScreen(TFT_WHITE); // Black screen fill

  M5.Lcd.setTextSize(2);

  M5.Lcd.setCursor(2, 2);
  M5.Lcd.print("WIFI SETUP");
  delay(2000);
}

void M5Stick_Display::show_first_time_screen()
{
  M5.Lcd.fillScreen(TFT_BLUE); // Black screen fill

  M5.Lcd.setTextColor(TFT_WHITE);

#ifdef HW_M5STICK_C

  M5.Lcd.setRotation(3);

  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(15, 10);
  M5.Lcd.print("NEW DEVICE");

  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(15, 40);
  M5.Lcd.print("Wait for reboot...");
  M5.Lcd.setCursor(15, 55);
  M5.Lcd.print("(Approx 2 minutes)");

#endif

#ifdef HW_M5STICK_PLUS

  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(40, SCREEN_HEIGHT - 170);
  M5.Lcd.print("FIRST");

  M5.Lcd.setCursor(45, SCREEN_HEIGHT - 150);
  M5.Lcd.print("TIME");

  M5.Lcd.setCursor(40, SCREEN_HEIGHT - 130);
  M5.Lcd.print("SETUP");

  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(30, SCREEN_HEIGHT - 55);
  M5.Lcd.print("Rebooting...");
  M5.Lcd.setCursor(35, SCREEN_HEIGHT - 30);
  M5.Lcd.print("(2 minutes)");

#endif

  // delay(2000);
}

void M5Stick_Display::show_error_screen(int errorcode)
{
  M5.Lcd.fillScreen(TFT_RED); // Black screen fill

  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(2, 2);
  M5.Lcd.print("ERR " + errorcode);
  delay(1000);
}

void M5Stick_Display::blink(int duration)
{
  digitalWrite(PIN_LED, LOW);
  delay(duration);
  digitalWrite(PIN_LED, HIGH);
  delay(duration);
}

void M5Stick_Display::show_setup_mode(bool network, bool wifi, bool code)
{
}

#endif

#ifdef HW_M5STACK_PM

#include "Wifi_BLE_config.h"

/* variables have been externed from main.cpp */
extern volatile bool Button_A_valid;
extern volatile bool Button_B_valid;
extern volatile bool Button_C_valid;
extern volatile bool Reboot_button;

extern volatile int wifi_connected;

/******************************************
 * void bottom_left(const char *string)
 * displays the button icon on bottom left screen with name given in string as argument
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 *******************************************/
void bottom_left(const char *string)
{
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_WHITE, Button_Colour);
  M5.Lcd.setTextDatum(TC_DATUM);
  M5.Lcd.fillRoundRect(5, 200, 100, 30, 10, Button_Colour);
  M5.Lcd.drawString(string, 55, 204, 4); // Font 4 for fast drawing with background
  Button_A_valid = true;
}

/******************************************
 * void bottom_right(const char *string)
 * displays the button icon on bottom right screen with name given in string as argument
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 *******************************************/
void bottom_right(const char *string)
{
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_WHITE, Button_Colour);
  M5.Lcd.setTextDatum(TC_DATUM);
  M5.Lcd.fillRoundRect(225, 200, 90, 30, 10, Button_Colour);
  M5.Lcd.drawString(string, 270, 204, 4); // Font 4 for fast drawing with background
  Button_C_valid = true;
}

/******************************************
 * void bottom_center(const char *string)
 * displays the button icon on bottom center screen with name given in string as argument
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 *******************************************/
void bottom_center(const char *string)
{
  int xpos = M5.Lcd.width() / 2; // Half the screen width
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_WHITE, Button_Colour);
  M5.Lcd.setTextDatum(TC_DATUM);
  if (strcmp(string, "RESTART") == 0)
  {
    Reboot_button = true;
    M5.Lcd.fillRoundRect(100, 200, 120, 30, 10, Button_Colour);
  }
  else
  {
    Reboot_button = false;
    M5.Lcd.fillRoundRect(115, 200, 90, 30, 10, Button_Colour);
  }
  M5.Lcd.drawString(string, xpos, 204, 4); // Font 4 for fast drawing with background
  Button_B_valid = true;
}

void display_heading(String str_heading)
{
  M5.Lcd.fillScreen(TFT_WHITE); // Black screen fill
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setFreeFont(FontB12);   // Select Free Serif 12 point font
  M5.Lcd.setTextDatum(TC_DATUM); // Centre text on x,y position
  M5.Lcd.drawString(str_heading, 160, 10);
}

/******************************************
 * void Display_Page_0(void)
 * function displays the page and also the button if it as
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 *******************************************/
void Display_Page_0(void)
{
  int xpos = M5.Lcd.width() / 2; // Half the screen width
  // int ypos = 10;

  /*M5.Lcd.fillScreen(TFT_WHITE); // Black screen fill
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setFreeFont(FontB12);   // Select Free Serif 12 point font
  M5.Lcd.setTextDatum(TC_DATUM); // Centre text on x,y position
  M5.Lcd.drawString("Welcome to Secure", xpos, ypos);*/
  display_heading("Welcome to Secure");

  M5.Lcd.setFreeFont(Font12);
  M5.Lcd.drawString("Ready to setup your new", xpos, 100);
  M5.Lcd.drawString("Air Quality Monitor", xpos, 130);

  bottom_right("NEXT");
}

/******************************************
 * void Display_Page_1(void)
 * function displays the page and also the buttons if it as in it
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 *******************************************/
void Display_Page_1(void)
{
  int xpos = M5.Lcd.width() / 2; // Half the screen width
  int ypos = 10;

  /*M5.Lcd.fillScreen(TFT_WHITE); // Black screen fill
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setFreeFont(FontB12);   // Select Free Serif 12 point font
  M5.Lcd.setTextDatum(TC_DATUM); // Centre text on x,y position
  M5.Lcd.drawString("Setup", xpos, ypos);*/

  display_heading("Setup");

  M5.Lcd.setFreeFont(Font12);
  M5.Lcd.drawString("Do you have a phone", xpos, 70);
  M5.Lcd.drawString("with Secure app", xpos, 100);
  M5.Lcd.drawString("installed?", xpos, 130);
  bottom_left("NO");
  bottom_right("YES");
}

/******************************************
 * void Display_Page_2(void)
 * function displays the page and also the buttons if it as in it
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 *******************************************/
void Display_Page_2(void)
{
  int xpos = M5.Lcd.width() / 2; // Half the screen width

  M5.Lcd.fillScreen(TFT_WHITE); // Black screen fill
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setFreeFont(Font12);    // Select Free Sans-Serif 12 point font
  M5.Lcd.setTextDatum(TC_DATUM); // Centre text on x,y position
  M5.Lcd.qrcode("http://192.168.4.1/", 80, 5, 165, 3);

  M5.Lcd.drawString("Scan to download app", xpos, 170);
  bottom_center("DONE");
}

/******************************************
 * void Display_Page_3(void)
 * function displays the page and also the buttons if it as in it
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 *******************************************/
void Display_Page_3(void)
{
  int xpos = M5.Lcd.width() / 2; // Half the screen width
  int ypos = 10;

  /*M5.Lcd.fillScreen(TFT_WHITE); // Black screen fill
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setFreeFont(FontB12);   // Select Free Serif 12 point font
  M5.Lcd.setTextDatum(TC_DATUM); // Centre text on x,y position
  M5.Lcd.drawString("Setup", xpos, ypos);*/

  display_heading("Setup");

  M5.Lcd.setFreeFont(Font12); // Select Free Serif 12 point font
  M5.Lcd.drawString("Use Secure app on your", xpos, 70);
  M5.Lcd.drawString("phone to search for", xpos, 100);
  String Ble_name = Get_BLE_Name();
  Ble_name = "\"" + Ble_name + "\"";
  M5.Lcd.drawString(Ble_name, xpos, 130);
}

/******************************************
 * void Display_Page_4(void)
 * function displays the page and also the buttons if it as in it
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 *******************************************/
void Display_Page_4(void)
{
  int xpos = M5.Lcd.width() / 2; // Half the screen width
  int ypos = 10;

  /*M5.Lcd.fillScreen(TFT_WHITE); // Black screen fill
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setFreeFont(FontB12);   // Select Free Serif 12 point font
  M5.Lcd.setTextDatum(TC_DATUM); // Centre text on x,y position
  M5.Lcd.drawString("Connected!", xpos, ypos);*/

  display_heading("Connected!");

  M5.Lcd.setFreeFont(Font12); // Select Free Serif 12 point font
  M5.Lcd.drawString("Continue to setup", xpos, 70);
  M5.Lcd.drawString("on Secure app", xpos, 100);

  M5.Lcd.setTextColor(TFT_LIGHTGREY);
  M5.Lcd.setFreeFont(FSS9); // Select Free Serif 12 point font
  M5.Lcd.drawString("5:00 mins remaining...", xpos, 140);
}

/******************************************
 * void Display_Page_5(void)
 * function displays the page and also the buttons if it as in it
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 *******************************************/
void Display_Page_5(void)
{
  int xpos = M5.Lcd.width() / 2; // Half the screen width
  int ypos = 10;

  /*M5.Lcd.fillScreen(TFT_WHITE); // Black screen fill
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setFreeFont(FontB12);   // Select Free Serif 12 point font
  M5.Lcd.setTextDatum(TC_DATUM); // Centre text on x,y position
  M5.Lcd.drawString("Connecting to....", xpos, ypos);*/

  display_heading("Connecting to....");

  M5.Lcd.setFreeFont(Font12); // Select Free Serif 12 point font
  M5.Lcd.drawString("My WiFi", xpos, 100);
}

/******************************************
 * void Display_Page_6(void)
 * function displays the page and also the buttons if it as in it
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 *******************************************/
void Display_Page_6(void)
{
  int xpos = M5.Lcd.width() / 2; // Half the screen width
  int ypos = 10;

  /*M5.Lcd.fillScreen(TFT_WHITE); // Black screen fill
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setFreeFont(FontB12);   // Select Free Serif 12 point font
  M5.Lcd.setTextDatum(TC_DATUM); // Centre text on x,y position
  M5.Lcd.drawString("You are all set!", xpos, ypos);*/

  display_heading("You are all set!");

  M5.Lcd.setFreeFont(Font12); // Select Free Serif 12 point font
  M5.Lcd.drawString("Your Device code is:", xpos, 70);
  M5.Lcd.setFreeFont(FSS24); // Select Free Serif 12 point font
  String Device_code = Get_Device_code();
  M5.Lcd.drawString(Device_code, xpos, 110);
  bottom_right("OK");
}

/******************************************
 * void Display_Page_7(void)
 * function displays the page and also the buttons if it as in it
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 *******************************************/
void Display_Page_7(void)
{
  int xpos = M5.Lcd.width() / 2; // Half the screen width
  int ypos = 10;
  /*M5.Lcd.fillScreen(TFT_WHITE); // Black screen fill
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setTextDatum(TC_DATUM);
  M5.Lcd.setFreeFont(FontB18); // Select Free Serif 18 point font
  M5.Lcd.drawString("THANK YOU", xpos, ypos);*/

  display_heading("THANK YOU");

  M5.Lcd.setFreeFont(Font12); // Select Free Serif 18 point font
  M5.Lcd.drawString("Updating", xpos, 70);
  M5.Lcd.drawString("Please wait, it takes less", xpos, 100);
  M5.Lcd.drawString("than 5 minutes to complete", xpos, 130);
  M5.Lcd.drawString("the setup.", xpos, 160);
}

/******************************************
 * void Display_Page_8(void)
 * function displays the page and also the buttons if it as in it
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 *******************************************/
void Display_Page_8(void)
{
  int xpos = M5.Lcd.width() / 2; // Half the screen width
  int ypos = 10;

  /*M5.Lcd.fillScreen(TFT_WHITE); // Black screen fill
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setFreeFont(FontB12);   // Select Free Serif 18 point font
  M5.Lcd.setTextDatum(TC_DATUM); // Centre text on x,y position
  M5.Lcd.drawString("Failed!", xpos, ypos);*/

  display_heading("Failed!");

  M5.Lcd.setFreeFont(Font12); // Select Free Serif 12 point font
  M5.Lcd.drawString("Unable to complete", xpos, 70);
  M5.Lcd.drawString("the setup.Please", xpos, 100);
  M5.Lcd.drawString("restart and try", xpos, 130);
  M5.Lcd.drawString("again.", xpos, 160);
  bottom_center("RESTART");
  Reboot_button = true;
}

/******************************************
 * void Display_Page_9(void)
 * function displays the page and also the buttons if it as in it
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 *******************************************/
void Display_Page_9(void)
{
  int xpos = M5.Lcd.width() / 2; // Half the screen width
  int ypos = 100;

  M5.Lcd.fillScreen(TFT_WHITE); // Black screen fill
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setFreeFont(Font12);    // Select Free Serif 12 point font
  M5.Lcd.setTextDatum(TC_DATUM); // Centre text on x,y position
  M5.Lcd.drawString("Device Rebooting...", xpos, ypos);
}

/*void display_factory_reset_screen(void)
{
  Serial.println("factory Screen active");
  M5.Lcd.fillScreen(TFT_BLACK); // Black screen fill

  M5.Lcd.setFreeFont(FF18);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_LIGHTGREY);

  M5.Lcd.setCursor(65, 60, 2);
  M5.lcd.print("FACTORY RESET");

  M5.Lcd.setFreeFont(FF17);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_LIGHTGREY);

  M5.Lcd.setCursor(10, 90, 2);
  M5.lcd.print("factory reset will remove all the setup");

  M5.Lcd.setCursor(90, 110, 2);
  M5.lcd.print("and configurations");

  M5.Lcd.setCursor(65, 150, 2);
  M5.lcd.print("Do you want to continue?");

  M5.Lcd.setFreeFont(FF18);

  M5.Lcd.fillRoundRect(120, 200, 80, 30, 10, TFT_OLIVE); // 0x340F
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setCursor(140, 222, 2);
  M5.lcd.print("NO");

  M5.Lcd.fillRoundRect(230, 200, 80, 30, 10, TFT_OLIVE); // 0x340F
  M5.Lcd.setCursor(243, 222, 2);
  M5.lcd.print("YES");
}*/

#endif