#include <Arduino.h>

#include "display.h"

int Display_page(int cur_page, char button);
void perform_task(int page);
void Failure_action(void);

bool enable_timer = false;
bool enable_long_timer = false;
uint32_t time_in_secs = 0;

unsigned long curr_millis = 0, prev_millis = 0;

bool clk_display = false;

uint8_t _sec = 0;
uint8_t _min = 0;
String clock_str = "";

unsigned long dot_prev_millis = 0, dot_curr_millis = 0;
uint8_t dots_num = 1;
bool display_dots = false;

extern volatile int page_ptr;

#ifndef HW_ESP32_CAM
/******************************************
 * void timer_enable(int Time)
 * function enables the timer and argument passed is timeout time in sec
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 *******************************************/
void timer_enable(int Time)
{
  enable_timer = true;
  time_in_secs = Time;
  prev_millis = millis();
}

/******************************************
 * void timer_disable(void)
 * function disables the timer.
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 *******************************************/
void timer_disable(void)
{
  enable_timer = false;
}

/******************************************
 * void Timer(void)
 * function if timeout reaches goes to failure page or displays restart button.
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 *******************************************/
void Timer(void)
{
  if (enable_timer)
  {
    curr_millis = millis();

    if (curr_millis - prev_millis >= (1000 * time_in_secs))
    {
      if (page_ptr == 4)
      {
        timer_disable();
        Failure_action();
        Serial.println("5 min timeout --fail");
      }
      else
      {
        timer_disable();
        bottom_center("RESTART");
        Serial.println("1 min timeout --fail");
      }
    }
  }
}

void clock_enable(uint8_t mins, uint8_t secs)
{
  clk_display = true;
  _min = mins;
  _sec = secs;
}

void clock_disable(void)
{
  clk_display = false;
  _min = 0;
  _sec = 0;
}

void display_clock(void)
{
  if (_min >= 0)
  {
    if (_sec <= 9)
    {
      clock_str = String(_min) + ":0" + String(_sec);
    }
    else
    {
      clock_str = String(_min) + ":" + String(_sec);
    }

    M5.Lcd.fillRect(70, 140, 40, 20, TFT_WHITE);
    M5.Lcd.drawString(clock_str, 90, 140);

    if (_sec != 0)
    {
      _sec--;
    }
    else
    {
      _sec = 59;
      _min--;
    }
  }
}

/******************************************
 * void dots_enable(void)
 * function enables the display dots for waiting screen.
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 *******************************************/
void dots_enable(void)
{
  display_dots = true;
  dots_num = 1;
  dot_prev_millis = millis();
}

/******************************************
 * void dots_disable(void)
 * function disables the display dots for waiting screen.
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 *******************************************/
void dots_disable(void)
{
  display_dots = false;
  dots_num = 1;
}

/******************************************
 * void Delay_Dots(void)
 * function display dots for waiting screen.
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 *******************************************/
void Delay_Dots(void)
{
  if (display_dots)
  {
    dot_curr_millis = millis();
    if (dot_curr_millis - dot_prev_millis >= 1000)
    {
      uint8_t xpos = 100;
      uint8_t ypos = 180;
      if (dots_num == 6)
      {
        M5.Lcd.fillRect(0, 170, 320, 30, TFT_WHITE);
        dots_num = 1;
      }

      M5.Lcd.fillCircle((dots_num * 20) + xpos, ypos, 5, TFT_LIGHTGREY);
      dots_num++;

      dot_prev_millis = dot_curr_millis;

      if (clk_display)
      {
        display_clock();
      }
    }
  }
}
#endif