#ifndef MyTypes_h
#define MyTypes_h

#include <WiFi.h>
#include <Arduino.h>

#define SSID_MAX_LEN 32
//From v1.0.10, WPA2 passwords can be up to 63 characters long.
#define PASS_MAX_LEN 64

typedef struct
{
  char wifi_ssid[SSID_MAX_LEN];
  char wifi_pw[PASS_MAX_LEN];
  bool useStaticIP;
  IPAddress staticIP;
  IPAddress gatewayIP;
  IPAddress subnetIP;
  char reserved[32];
} WiFi_Credentials;

typedef struct
{
  char primary_mqtt_server[24];
  int primary_mqtt_port;
  char secondary_mqtt_server[24];
  int secondary_mqtt_port;
  char topic_prefix[10];
  char device_code[4];
  int data_frequency;
  int timeZone;
  int default_unit_C;
  int blue_distance_max;
  int blue_distance_min;
  int blue_scan_time;
  int blue_interval;
  bool blue_active_scan;
  int blue_window;
  int scan_zone;
  int calibrateRssi;
  int setupMode;
  IPAddress primaryDNS;
  IPAddress secondaryDNS;
  int calibrate_temperature_a;
  int calibrate_temperature_b;
  int calibrate_humidity_a;
  int calibrate_humidity_b;
  char reserved[48];
} device_config_data;

#define NUM_WIFI_CREDENTIALS 3

typedef struct
{
  WiFi_Credentials WiFi_Creds[NUM_WIFI_CREDENTIALS];
  device_config_data device_config;

} data_config;

struct iButton
{
  const uint8_t PIN;
  uint32_t numberKeyPresses;
  bool pressed;
};

#endif