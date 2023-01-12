
#include "config.h"
#include "types.h"

#include "FS.h"

#include <LITTLEFS.h> // https://github.com/lorol/LITTLEFS
FS *filesystem = &LITTLEFS;

IPAddress DEFAULT_DNS_PRIMARY(8, 8, 8, 8);
IPAddress DEFAULT_DNS_SECONDARY(8, 8, 4, 4);

// WiFiClient client;
// PubSubClient mqttclient(client);

WiFiClientSecure client;
PubSubClient mqttclient(client);

#define ESP_getChipId() ((uint32_t)ESP.getEfuseMac())

bool debugMode = false;           // Is device in DebugMode ? when in debug mode, all serial messages are sent to MQTT
bool wifiOnline = false;          // Is wifi connected and device is online?
bool hasWiFi1Credentials = false; // Does EEPROM has stored wifi 1 credentials?
bool hasWiFi2Credentials = false; // Does EEPROM has stored wifi 2 credentials?
String deviceCode = "";
String deviceMac = "";

String chipID = "Secure-" + String(ESP_getChipId(), HEX);

// IPAddress DEFAULT_DNS_PRIMARY(8, 8, 8, 8);
// IPAddress DEFAULT_DNS_SECONDARY(8, 8, 4, 4);

// flag for saving data
bool shouldSaveConfig = false;

// SSID and PW for your Router
String Router_SSID;
String Router_Pass;
//#define CONFIG_PORTAL_TIMEOUT 60

// From v1.1.0
//#define MIN_AP_PASSWORD_SIZE 8

String device_mac;

data_config WM_config;

#define CONFIG_FILENAME F("/config.dat")

// Now support ArduinoJson 6.0.0+ ( tested with v6.14.1 )
#include <ArduinoJson.h> //https://github.com/bblanchon/ArduinoJson

int PM01Value = 0;  // define PM1.0 value of the air detector module
int PM2_5Value = 0; // define PM2.5 value of the air detector module
int PM10Value = 0;  // define PM10 value of the air detector module
int voc_value = 0;  // VOC Sensor

// static char *beaconNameString;

/*********************************************************/

char space_size_in_feet[INTIGER_LEN] = "10";
char space_capacity[INTIGER_LEN] = "3";

/*********************************************************/

// MQTT Related Variables

StaticJsonDocument<256> doc;

const char *mqtt_server = PRIMARY_MQTT_SERVER;
int default_mqtt_port = PRIMARY_MQTT_PORT;
const char *primary_mqtt_user = PRIMARY_MQTT_USER;
const char *primary_mqtt_pass = PRIMARY_MQTT_PASSWORD;
const char *mqtt_subs_topic = DEFAULT_SUB_TOPIC;

const char *mqtts_server = SECONDARY_MQTT_SERVER;
int default_mqtts_port = SECONDARY_MQTT_PORT;
const char *secondary_mqtt_user = SECONDARY_MQTT_USER;
const char *secondary_mqtt_pass = SECONDARY_MQTT_PASSWORD;

// Coutners for Timers
int previousDiagnosticsMillis = 0;
int previousDataMillis;
int previousSystemMillis;

// Counters for diagnositcs
unsigned long packetsSentPM = 0; // MQTT packets sent
unsigned long packetsFailPM = 0; // MQTT packet sent failure
unsigned long dataLoopsPM = 0;   // Loops with data
unsigned long loopsPM = 0;       // Counter to track executions
unsigned long lastpacketsSentPM = 1;
unsigned long wifiErrors = 0;       // Wifi Connectivity Errors
unsigned long mqttErrors = 0;       // MQTT Error
unsigned long sensorReadErrors = 0; // Sensor read errors

bool w = false;
bool m = false;
bool isSetupMode;     // Newly flashed devices default to setup Mode. When in setup mode, it conencts to mqtt.secure.live else to mqtts.secure.live
bool deviceHasConfig; // Set to true if device EEPROM has stored configuration
bool deviceHasWifiCreds;
bool newRun = true;
bool resetButtonPressed = false;
bool portalOnDemand; // Check for On demand Config Portal

bool iswifiSet = false;
bool isCodeSet = false;

// Defined Function Template
bool send_mqtt_string(String topic, String value, bool retain);

bool read_config_file();

String get_beacon_id();

/******************************************
 * debug_string(string,bool)
 * Prints the message to Serial port and sends to MQTT server when device in debug mode
 * Author : Kaushlesh Chandel
 * Last Modified : Build 21-07-08
 *******************************************/
void debug_string(String msg, bool debug_msg /* = false*/)
{
  if (debug_msg == true)
  {
    Serial.print("##");
    Serial.println(msg);
  }
  else
  {
    Serial.print(">>");
    Serial.println(msg);
  }

  if (debugMode == true && mqttclient.connected())
  {
    send_mqtt_string("DEBUG", msg, false);
  }
}

bool check_for_on_demand_portal()
{

  // Check if reset buttons is pressed
  byte cntReset = 0;
  for (int i = 0; i < 10; i++)
  {
    #ifndef HW_ESP32_CAM
    cntReset += digitalRead(HOME_PUSH_BUTTON);
    delay(100);
    #endif
  }

  if (cntReset == 0)
  {
    // display.show_on_demand_screen();
    debug_string("On demand Portal");
    return true;
  }
  else
    return false;
}

/******************************************
 * serial_print_config()
 * Prints the Main configuration values to Serial port
 * Author : Kaushlesh Chandel
 * Last Modified : Build 21/07/06
 *******************************************/
void serial_print_config()
{
  Serial.print("$$Code=");
  Serial.println(WM_config.device_config.device_code);

  Serial.print("$$Mac=");
  Serial.println(get_beacon_id());

  Serial.print("$$Setup=");
  Serial.println(WM_config.device_config.setupMode);

  Serial.print("$$Prefix=");
  Serial.println(WM_config.device_config.topic_prefix);

  Serial.print("$$Version=");
  Serial.println(SW_VERSION);

  Serial.print("$$Hardware=");
  Serial.println(HW_VERSION);

  Serial.print("$$ChipID=");
  Serial.println(chipID);

  Serial.print("$$WiFi1=");
  Serial.println(WM_config.WiFi_Creds[1].wifi_ssid);
}

/******************************************
 * check_configurations()
 * Checks if the device has the Config file saved to EEPROM
 * If Blank, then creates default configuration file
 * Author : Kaushlesh Chandel
 * Last Modified : Build 21/07/06
 *******************************************/
void check_configurations()
{

  deviceHasConfig = read_config_file();
  portalOnDemand = check_for_on_demand_portal();

  if (WM_config.device_config.setupMode == 1)
  {
    debug_string("Mode : Setup");
    isSetupMode = true;
  }
  else
  {
    debug_string("Mode : Normal");
    isSetupMode = false;
  }

  String ssid1 = WM_config.WiFi_Creds[1].wifi_ssid;
  ssid1.trim();

  if (ssid1 == "")
  {
    deviceHasWifiCreds = false;
  }
  else
  {
    deviceHasWifiCreds = true;
  }

  String deviceCode = WM_config.device_config.device_code;
  deviceCode.trim();

  if (deviceCode == "ZZZZ")
    isCodeSet = false;
  else
    isCodeSet = true;
}

/******************************************
 * set_defaults()
 * Loads the default values for all the configurations
 * Author : Kaushlesh Chandel
 * Last Modified :
 *******************************************/
void set_defaults()
{

  debug_string("Setting default values", true);

  WM_config.device_config.data_frequency = DEFAULT_SCANNING_FREQUENCY;
  WM_config.device_config.timeZone = DEFAULT_TIME_ZONE;
  WM_config.device_config.default_unit_C = DEFAULT_UNIT_C;

  WM_config.device_config.blue_distance_max = DEFAULT_MAX_DISTANCE;
  WM_config.device_config.blue_distance_min = DEFAULT_MIN_DISTANCE;
  WM_config.device_config.blue_scan_time = DEFAULT_BLUE_SCANTIME;
  WM_config.device_config.blue_interval = DEFAULT_BLUE_INTERVAL;
  WM_config.device_config.blue_window = DEFAULT_BLUE_WINDOW;
  WM_config.device_config.blue_active_scan = DEFAULT_BLUE_ACTIVE_SCAN;
  WM_config.device_config.calibrateRssi = DEFAULT_CALIBRATION_RSSI;
  strcpy(WM_config.WiFi_Creds[0].wifi_ssid, DEFAULT_SSID);
  strcpy(WM_config.WiFi_Creds[0].wifi_pw, DEFAULT_WIFI_PWD);

  strcpy(WM_config.device_config.primary_mqtt_server, PRIMARY_MQTT_SERVER);
  strcpy(WM_config.device_config.secondary_mqtt_server, SECONDARY_MQTT_SERVER);
  WM_config.device_config.primary_mqtt_port = PRIMARY_MQTT_PORT;
  WM_config.device_config.secondary_mqtt_port = SECONDARY_MQTT_PORT;

  //strcpy(WM_config.device_config.device_code, DEFAULT_DEVICE_CODE);
  strcpy(WM_config.device_config.topic_prefix, DEFAULT_TOPIC_PREFIX); // Use Slast at the end to support the blank topics

  WM_config.device_config.primaryDNS = DEFAULT_DNS_PRIMARY;
  WM_config.device_config.secondaryDNS = DEFAULT_DNS_SECONDARY;

  WM_config.device_config.setupMode = 1;
  WM_config.WiFi_Creds[0].useStaticIP = false;
  WM_config.WiFi_Creds[1].useStaticIP = false;
  WM_config.WiFi_Creds[2].useStaticIP = false;

  // strcpy(WM_config.WiFi_Creds[1].wifi_ssid, BLANK_STRING);
  // strcpy(WM_config.WiFi_Creds[1].wifi_pw, BLANK_STRING);
  // strcpy(WM_config.WiFi_Creds[2].wifi_ssid, BLANK_STRING);
  // strcpy(WM_config.WiFi_Creds[2].wifi_pw, BLANK_STRING);

  WM_config.device_config.calibrate_humidity_a = 1;
  WM_config.device_config.calibrate_humidity_b = 0;

  WM_config.device_config.calibrate_temperature_a = 1;
  WM_config.device_config.calibrate_temperature_b = -8;
}

/******************************************
 * save_config_file(void)
 * Save the configurations to EEPROM
 * Author : Kaushlesh Chandel
 * Last Modified :
 *******************************************/
void save_config_file(void)
{
  File file = FileFS.open(CONFIG_FILENAME, "w");

  if (file)
  {
    file.write((uint8_t *)&WM_config, sizeof(WM_config));
    file.close();
    debug_string("Saved Little FS FIle", true);
  }
  else
  {
    debug_string("FAIL!!! Saving Little FS FIle", true);
  }
}

/******************************************
 * read_config_file()
 * Reads Config from EEPROM. if not found, thenc creates default config file
 * Author : Kaushlesh Chandel
 * Last Modified : Build 21/07/06
 *******************************************/
bool read_config_file()
{
  bool res = false;

  if (!FileFS.begin(true))
  {
    debug_string(F("File System begin : ERROR"), true);
  }
  else
  {
    debug_string(F("File System begin : OK"), true);
  }

  File file = FileFS.open(CONFIG_FILENAME, "r");

  if (file) // File was Opened Succesfully
  {
    debug_string("File read OK", true);
    file.readBytes((char *)&WM_config, sizeof(WM_config));
    file.close();
    set_defaults();
    save_config_file();
    res = true;
  }
  else // New system format & save default config file
  {
    debug_string("New device. Format the File system", true);
    FileFS.format();

    if (!FileFS.begin(true))
    {
      debug_string(F("failed! AutoFormatting."), true);
    }
    else
    {
      debug_string(F("Writing Blank Config File"), true);
      // set_defaults();
      // save_config_file();
    }

    /*File file = FileFS.open(CONFIG_FILENAME, "r");
    if (file) // File was Opened Succesfully
    {
      file.readBytes((char *)&WM_config, sizeof(WM_config));
      file.close();
      debug_string("New Device : File read OK", true);
    }*/

    res = false;
  }

  String wifi1 = WM_config.WiFi_Creds[1].wifi_ssid;
  wifi1.trim();

  if (wifi1 != "")
    hasWiFi1Credentials = true;
  else
    hasWiFi1Credentials = false;

  String wifi2 = WM_config.WiFi_Creds[2].wifi_ssid;
  wifi2.trim();

  if (wifi2 != "")
    hasWiFi2Credentials = true;
  else
    hasWiFi2Credentials = false;

  String deviceCode = WM_config.WiFi_Creds[2].wifi_ssid;
  deviceCode.trim();

  // Handle older version of MQTT with non TLS port.
  // Remove the code in Sep 2021 release

  /*if (WM_config.device_config.primary_mqtt_port == 1883)
  {
    WM_config.device_config.primary_mqtt_port = 8883;
    save_config_file();
  }

  if (WM_config.device_config.secondary_mqtt_port == 1883)
  {
    WM_config.device_config.secondary_mqtt_port = 8883;
    save_config_file();
  }*/

  return res;
}

/******************************************
 * saveConfigCallback(void)
 * Callback used by wifimanager
 * Author : Kaushlesh Chandel
 * Last Modified :
 *******************************************/
void saveConfigCallback(void)
{

#ifdef _DEBUGLOG_
#endif
  debug_string("Should save config", true);
  shouldSaveConfig = true;
}

void format_config_file(void)
{
  FileFS.format();
}