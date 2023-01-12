#include <Arduino.h>

#ifdef HW_M5STACK_PM
#include <M5Stack.h>
#endif

#include "EEPROM.h"
#define EEPROM_SIZE 128

#include <WiFi.h>
#include <ESP32Ping.h>

#define modeAddr 0
#define wifiAddr 0

void erase_eeprom(void);
String Get_BLE_Name(void);
String Get_Device_code(void);
void WiFi_Setup_Using_BLE();
void BLE_Stop(void);
void wifiConnectTask();
void OTA_Update(void);

