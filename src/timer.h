#include <Arduino.h>

#ifdef HW_M5STACK_PM
#include <M5Stack.h>
#endif

void timer_enable(int Time);
void timer_disable(void);
void Timer(void);

void clock_enable(uint8_t mins, uint8_t secs);
void clock_disable(void);
void display_clock(void);

void dots_enable(void);
void Delay_Dots(void);
void dots_disable(void);