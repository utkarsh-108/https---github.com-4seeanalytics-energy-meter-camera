/****************************************************************************************************************************
  
  ESP_WiFiManager is a library for the ESP8266/ESP32 platform (https://github.com/esp8266/Arduino) to enable easy
  
  Built by Khoi Hoang https://github.com/khoih-prog/ESP_WiFiManager

 *****************************************************************************************************************************/
#include <common.h>

extern data_config WM_config;

extern IPAddress DEFAULT_DNS_PRIMARY/*(8, 8, 8, 8)*/;
extern IPAddress DEFAULT_DNS_SECONDARY/*(8, 8, 4, 4)*/;

#if !(defined(ESP8266) || defined(ESP32))
#error This code is intended to run on the ESP8266 or ESP32 platform! Please check your Tools->Board setting.
#endif

// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _WIFIMGR_LOGLEVEL_ 1

#include <FS.h>

#include <esp_wifi.h>
#include <WiFi.h>
#include <WiFiClient.h>

// From v1.1.0
#include <WiFiMulti.h>
WiFiMulti wifiMulti;

#define LED_BUILTIN 2
#define LED_ON HIGH
#define LED_OFF LOW

// Now support ArduinoJson 6.0.0+ ( tested with v6.14.1 )
#include <ArduinoJson.h> //https://github.com/bblanchon/ArduinoJson

// Indicates whether ESP has WiFi credentials saved from previous session, or double reset detected
bool initialConfig = false;
//////

// SSID and PW for Config Portal
String AP_SSID;
String AP_PASS;

#define USE_AVAILABLE_PAGES false
#define USE_STATIC_IP_CONFIG_IN_CP false
#define USE_ESP_WIFIMANAGER_NTP false
#define USE_CLOUDFLARE_NTP false

#define USING_CORS_FEATURE true

#if (defined(USE_STATIC_IP_CONFIG_IN_CP) && !USE_STATIC_IP_CONFIG_IN_CP)
// Force DHCP to be true
#if defined(USE_DHCP_IP)
#undef USE_DHCP_IP
#endif
#define USE_DHCP_IP true
#else
// You can select DHCP or Static IP here
//#define USE_DHCP_IP     true
#define USE_DHCP_IP false
#endif

#include <ESP_WiFiManager.h> //https://github.com/khoih-prog/ESP_WiFiManager

// Function Prototypes
uint8_t connectMultiWiFi(bool fastmode);

void check_WiFi(void)
{
  if ((WiFi.status() != WL_CONNECTED))
  {

    debug_string("WiFi lost. Call connectMultiWiFi in loop", true);
    wifiOnline = false;
    connectMultiWiFi(true);
  }
}

void check_wifi_status()
{
  static ulong checkstatus_timeout = 0;
  static ulong LEDstatus_timeout = 0;
  static ulong checkwifi_timeout = 0;

  static ulong currentMillis;

#define HEARTBEAT_INTERVAL 10000L
#define LED_INTERVAL 2000L
#define WIFICHECK_INTERVAL 1000L

  currentMillis = millis();

  // Check WiFi every WIFICHECK_INTERVAL (1) seconds.
  if ((currentMillis > checkwifi_timeout) || (checkwifi_timeout == 0))
  {
    check_WiFi();
    checkwifi_timeout = currentMillis + WIFICHECK_INTERVAL;
  }

  if ((currentMillis > LEDstatus_timeout) || (LEDstatus_timeout == 0))
  {
    // Toggle LED at LED_INTERVAL = 2s

    LEDstatus_timeout = currentMillis + LED_INTERVAL;
  }

  // Print hearbeat every HEARTBEAT_INTERVAL (10) seconds.
  if ((currentMillis > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    // heartBeatPrint();
    checkstatus_timeout = currentMillis + HEARTBEAT_INTERVAL;
  }
}

uint8_t connectMultiWiFi(bool fastmode)
{
#if ESP32
// For ESP32, this better be 0 to shorten the connect time
#define WIFI_MULTI_1ST_CONNECT_WAITING_MS 0
#else
// For ESP8266, this better be 2200 to enable connect the 1st time
#define WIFI_MULTI_1ST_CONNECT_WAITING_MS 2200L
#endif

#define WIFI_MULTI_CONNECT_WAITING_MS 100L

  uint8_t status;

  LOGERROR(F("ConnectMultiWiFi with :"));

  if (fastmode == true)
  {

    for (uint8_t i = 1; i < NUM_WIFI_CREDENTIALS; i++)
    {
      // Don't permit NULL SSID and password len < MIN_AP_PASSWORD_SIZE (8)
      if ((String(WM_config.WiFi_Creds[i].wifi_ssid) != "") && (strlen(WM_config.WiFi_Creds[i].wifi_pw) >= MIN_AP_PASSWORD_SIZE))
      {
        LOGERROR3(F("* Additional SSID = "), WM_config.WiFi_Creds[i].wifi_ssid, F(", PW = "), "**********");
        if (WM_config.WiFi_Creds[i].useStaticIP)
          WiFi.config(WM_config.WiFi_Creds[i].staticIP, WM_config.WiFi_Creds[i].gatewayIP, WM_config.WiFi_Creds[i].subnetIP);
      }
    }
  }
  else
  {
    if ((Router_SSID != "") && (Router_Pass != ""))
    {
      LOGERROR3(F("* Flash-stored Router_SSID = "), Router_SSID, F(", Router_Pass = "), "**********");
    }
    for (uint8_t i = 0; i < NUM_WIFI_CREDENTIALS; i++)
    {
      // Don't permit NULL SSID and password len < MIN_AP_PASSWORD_SIZE (8)
      if ((String(WM_config.WiFi_Creds[i].wifi_ssid) != "") && (strlen(WM_config.WiFi_Creds[i].wifi_pw) >= MIN_AP_PASSWORD_SIZE))
      {
        LOGERROR3(F("* Additional SSID = "), WM_config.WiFi_Creds[i].wifi_ssid, F(", PW = "), "**********");
      }
    }
  }

  LOGERROR(F("Connecting MultiWifi..."));

  WiFi.mode(WIFI_STA);

  int i = 0;
  status = wifiMulti.run();
  delay(WIFI_MULTI_1ST_CONNECT_WAITING_MS);

  while ((i++ < 10) && (status != WL_CONNECTED))
  {
    status = wifiMulti.run();

    if (status == WL_CONNECTED)
      break;
    else
      delay(WIFI_MULTI_CONNECT_WAITING_MS);
  }

  if (status == WL_CONNECTED)
  {
    LOGERROR1(F("WiFi connected after time: "), i);
    LOGERROR3(F("SSID:"), WiFi.SSID(), F(",RSSI="), WiFi.RSSI());
    LOGERROR3(F("Channel:"), WiFi.channel(), F(",IP address:"), WiFi.localIP());
  }
  else
    LOGERROR(F("WiFi not connected"));

  return status;
}

/********************************
 * wm_setup(bool)
 * Starts wifi manager to configure device using a mobile Phone
 * Starts a Wifi Router with SSID as SECURE-XXXXXX
 * Author : Kaushlesh Chandel
 * Last Modified : Build 21-07-08
 *******************************/
void wm_setup(bool ondemand)
{

  ESP_WiFiManager ESP_wifiManager("Secure Sensor");

  //set config save notify callback
  ESP_wifiManager.setSaveConfigCallback(saveConfigCallback);

  ESP_wifiManager.setDebugOutput(false);
  ESP_wifiManager.setAPStaticIPConfig(IPAddress(192, 168, 100, 1), IPAddress(192, 168, 100, 1), IPAddress(255, 255, 255, 0));
  ESP_wifiManager.setMinimumSignalQuality(-1);
  ESP_wifiManager.setConfigPortalChannel(0);
  //////

#if !USE_DHCP_IP
#if USE_CONFIGURABLE_DNS
  // Set static IP, Gateway, Subnetmask, DNS1 and DNS2. New in v1.0.5
  ESP_wifiManager.setSTAStaticIPConfig(stationIP, gatewayIP, netMask, dns1IP, dns2IP);
#else
  // Set static IP, Gateway, Subnetmask, Use auto DNS1 and DNS2.
  ESP_wifiManager.setSTAStaticIPConfig(stationIP, gatewayIP, netMask);
#endif
#endif

  // New from v1.1.1
#if USING_CORS_FEATURE
  ESP_wifiManager.setCORSHeader("Your Access-Control-Allow-Origin");
#endif

  Router_SSID = ESP_wifiManager.WiFi_SSID();
  Router_Pass = ESP_wifiManager.WiFi_Pass();

  if ((Router_SSID == "") && (Router_Pass == ""))
  {
    Router_SSID = DEFAULT_SSID;
    Router_SSID = DEFAULT_WIFI_PWD;
  }

  ESP_wifiManager.setConfigPortalTimeout(120); // Default timeout

  if (Router_SSID != "")
  {
    ESP_wifiManager.setConfigPortalTimeout(CONFIG_PORTAL_TIMEOUT); //If no access point name has been previously entered disable timeout.
    debug_string("Got stored Credentials. Timeout 60s", true);
  }
  else
  {
    debug_string("No stored Credentials. Timeout 120s", true);
  }

  // SSID and PW for Config Portal
  AP_SSID = chipID;
  AP_PASS = "securewifi";

  // From v1.1.0, Don't permit NULL password
  if ((Router_SSID == "") || (Router_Pass == "") || (ondemand == true))
  {
    debug_string("We haven't got any access point credentials, so get them now", true);

    if ((Router_SSID == "") && (Router_Pass == ""))
      initialConfig = true;

    // Starts an access point

    if (!ESP_wifiManager.startConfigPortal(AP_SSID.c_str(), AP_PASS.c_str()))
      debug_string("Not connected to WiFi but continuing anyway.", true);
    else
      debug_string("WiFi connected...yeey :)", true);

    // Stored  for later usage, from v1.1.0, but clear first
    memset(&WM_config, 0, sizeof(WM_config));

    // Add the default Wifi AP at 1st location
    strcpy(WM_config.WiFi_Creds[0].wifi_ssid, DEFAULT_SSID);
    strcpy(WM_config.WiFi_Creds[0].wifi_pw, DEFAULT_WIFI_PWD);

    for (uint8_t i = 0; i < NUM_WIFI_CREDENTIALS - 1; i++)
    {
      String tempSSID = ESP_wifiManager.getSSID(i);
      String tempPW = ESP_wifiManager.getPW(i);

      if (strlen(tempSSID.c_str()) < sizeof(WM_config.WiFi_Creds[i + 1].wifi_ssid) - 1)
        strcpy(WM_config.WiFi_Creds[i + 1].wifi_ssid, tempSSID.c_str());
      else
        strncpy(WM_config.WiFi_Creds[i + 1].wifi_ssid, tempSSID.c_str(), sizeof(WM_config.WiFi_Creds[i + 1].wifi_ssid) - 1);

      if (strlen(tempPW.c_str()) < sizeof(WM_config.WiFi_Creds[i + 1].wifi_pw) - 1)
        strcpy(WM_config.WiFi_Creds[i + 1].wifi_pw, tempPW.c_str());
      else
        strncpy(WM_config.WiFi_Creds[i + 1].wifi_pw, tempPW.c_str(), sizeof(WM_config.WiFi_Creds[i + 1].wifi_pw) - 1);

      // Don't permit NULL SSID and password len < MIN_AP_PASSWORD_SIZE (8)
      if ((String(WM_config.WiFi_Creds[i + 1].wifi_ssid) != "") && (strlen(WM_config.WiFi_Creds[i + 1].wifi_pw) >= MIN_AP_PASSWORD_SIZE))
      {
        LOGERROR3(F("* Add SSID = "), WM_config.WiFi_Creds[i + 1].wifi_ssid, F(", PW = "), WM_config.WiFi_Creds[i + 1].wifi_pw);
        wifiMulti.addAP(WM_config.WiFi_Creds[i + 1].wifi_ssid, WM_config.WiFi_Creds[i + 1].wifi_pw);
      }
    }

    save_config_file();
  }
  else
  {
    wifiMulti.addAP(Router_SSID.c_str(), Router_Pass.c_str());
  }

  if (!initialConfig)
  {
    for (uint8_t i = 0; i < NUM_WIFI_CREDENTIALS; i++)
    {
      // Don't permit NULL SSID and password len < MIN_AP_PASSWORD_SIZE (8)
      if ((String(WM_config.WiFi_Creds[i].wifi_ssid) != "") && (strlen(WM_config.WiFi_Creds[i].wifi_pw) >= MIN_AP_PASSWORD_SIZE))
      {
        LOGERROR3(F("* Add SSID = "), WM_config.WiFi_Creds[i].wifi_ssid, F(", PW = "), WM_config.WiFi_Creds[i].wifi_pw);
        wifiMulti.addAP(WM_config.WiFi_Creds[i].wifi_ssid, WM_config.WiFi_Creds[i].wifi_pw);
      }
    }

    if (WiFi.status() != WL_CONNECTED)
    {
      debug_string("ConnectMultiWiFi in setup", true);

      connectMultiWiFi(false);
    }
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    debug_string("connected. Local IP: " + WiFi.localIP().toString(), true);
  }
  else
    debug_string(String(ESP_wifiManager.getStatus(WiFi.status())), true);

  debug_string("Local IP = " + WiFi.localIP().toString(), true);
}

/********************************
 * connect_to_stored_wifi(int)
 * Connect to a wifi based on ID
 * Author : Kaushlesh Chandel
 * Last Modified : Build 21-07-08
 *******************************/
bool connect_to_stored_wifi(int id)
{

  bool res = false;
  debug_string("Using Stored wifi " + String(id), true);

  debug_string("Start WiFi", true);

  WiFi.mode(WIFI_STA);
  debug_string(WM_config.WiFi_Creds[id].wifi_ssid, true);

  if (WM_config.WiFi_Creds[id].useStaticIP && id > 0)
  {
    //If device should use a static IP Address
    debug_string("Use Static IP", true);
    debug_string(WM_config.WiFi_Creds[id].staticIP.toString(), true);
    debug_string(WM_config.WiFi_Creds[id].gatewayIP.toString(), true);
    debug_string(WM_config.WiFi_Creds[id].subnetIP.toString(), true);

    if (!WiFi.config(WM_config.WiFi_Creds[id].staticIP, WM_config.WiFi_Creds[id].gatewayIP, WM_config.WiFi_Creds[id].subnetIP, DEFAULT_DNS_PRIMARY, DEFAULT_DNS_SECONDARY))
    {
      Serial.println("STA Failed to configure Static IP");
    }
  }
  else
  {
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
  }

  WiFi.setHostname(chipID.c_str()); //Set the device Hostnaem
  WiFi.begin(WM_config.WiFi_Creds[id].wifi_ssid, WM_config.WiFi_Creds[id].wifi_pw);

  //Waits for 10 seconds for wifi to connect
  int i = 0;

  int status = WiFi.status();
  IPAddress gateway;
  IPAddress subnet;

  while ((i++ < 10) && (status != WL_CONNECTED))
  {
    status = WiFi.status();

    if (status == WL_CONNECTED)
    {
      debug_string("WiFi Connected");
      gateway = WiFi.gatewayIP();
      Serial.print("##GATEWAY: ");
      subnet = WiFi.subnetMask();
      Serial.print("##SUBNET: ");
      Serial.println(subnet);
      Serial.print("##ENCRYPTION ");
      Serial.println(WiFi.encryptionType(WIFI_STA));
      Serial.print("##RSSI: ");
      Serial.println(WiFi.RSSI());
      debug_string("connected. Local IP: " + WiFi.localIP().toString(), true);
      res = true;
      break;
    }
    else
    {
      debug_string("waiting for WiFi to connect...", true);
      delay(1000);
    }
  }
  return res;
}

/********************************
 * wifi_fast(ueDefaultwifi)
 * Connects to one of the three wifi's
 * Author : Kaushlesh Chandel
 * Last Modified : Build 21-07-08
 *******************************/
bool wm_fast(bool useDefaultWifi)
{

  bool wifiConnected = false;

  debug_string("Wifi fast mode", true);

  if (useDefaultWifi) //If default wifi then connect to first wifi
  {
    debug_string("Using Default Wifi", true);
    wifiConnected = connect_to_stored_wifi(0);
  }
  else // When device has wifi saved, then connect to wifi 1 & 2
  {
    if (hasWiFi1Credentials)
    {
      wifiConnected = connect_to_stored_wifi(1); //If device has wifi credentials then try connecting to it
    }

    if (wifiConnected == false && hasWiFi2Credentials) //If device has 2nd wifi credentials then try connecting to it
    {
      wifiConnected = connect_to_stored_wifi(2);
    }

    //Finally try connecting to Default Wifi
    if (wifiConnected == false)
    {
      wifiConnected = connect_to_stored_wifi(0);
    }
  }

  return wifiConnected;
}
