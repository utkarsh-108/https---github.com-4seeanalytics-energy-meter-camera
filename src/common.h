#ifndef COMMON_H /* include guards */
#define COMMON_H

#include <Arduino.h>
#include <config.h>
#include <EEPROM.h>
#include <esp_wifi.h>
#include <ArduinoJson.h>

#include "FS.h"

#include <LITTLEFS.h> // https://github.com/lorol/LITTLEFS
#include "types.h"

extern int previousDiagnosticsMillis;
extern int previousDataMillis;
extern int previousSystemMillis;

extern unsigned long packetsSentPM; // MQTT packets sent
extern unsigned long packetsFailPM; // MQTT packet sent failure
extern unsigned long dataLoopsPM;   // Loops with data
extern unsigned long loopsPM;       // Counter to track executions
extern unsigned long lastpacketsSentPM;
extern unsigned long wifiErrors;       // Wifi Connectivity Errors
extern unsigned long mqttErrors;       // MQTT Error
extern unsigned long sensorReadErrors; // Sensor read errors

extern bool debugMode;           // Is device in DebugMode ? when in debug mode, all serial messages are sent to MQTT
extern bool wifiOnline;          // Is wifi connected and device is online?
extern bool hasWiFi1Credentials; // Does EEPROM has stored wifi 1 credentials?
extern bool hasWiFi2Credentials; // Does EEPROM has stored wifi 2 credentials?

extern String chipID;

// IPAddress DEFAULT_DNS_PRIMARY(8, 8, 8, 8);
// IPAddress DEFAULT_DNS_SECONDARY(8, 8, 4, 4);

extern String Router_SSID;
extern String Router_Pass;
#define CONFIG_PORTAL_TIMEOUT 60

// From v1.1.0
#define MIN_AP_PASSWORD_SIZE 8

extern bool w;
extern bool m;
extern bool isSetupMode;     // Newly flashed devices default to setup Mode. When in setup mode, it conencts to mqtt.secure.live else to mqtts.secure.live
extern bool deviceHasConfig; // Set to true if device EEPROM has stored configuration
extern bool deviceHasWifiCreds;
extern bool newRun;
extern bool resetButtonPressed;
extern bool portalOnDemand; // Check for On demand Config Portal

extern bool iswifiSet;
extern bool isCodeSet;

extern String device_mac;

enum status
{
    Non = 2,
    Ok = 1,
    Fail = 0
};

#endif