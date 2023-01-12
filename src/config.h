
#ifndef CONFIG_H /* include guards */
#define CONFIG_H

#include <Arduino.h>
// #include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

#define FileFS LITTLEFS


#define SW_VERSION "22-05-23"
#define SETUP_SW_VERSION "" // use for setup code

#ifdef HW_ESP32_CAM
#define HW_VERSION "esp32-cam" 
#endif
// hardware specfic Incluide Files
#ifdef HW_M5STICK_PLUS
#define HW_VERSION "m5stick-cb" // Use this for Code selection
#endif

#ifdef HW_M5STICK_C
#define HW_VERSION "m5stick-ca" // Use this for Code selection
#endif

#ifdef HW_M5STACK_PM
#define HW_VERSION "m5stack-pm" // Use this for Code selection
#define SETUP_HW_VERSION "m5stack-pm"
// Hardware pins
#define HOME_PUSH_BUTTON 38
#define PIN_Led 10
#endif

#ifdef HW_M5STICK_ATOM
#define HW_VERSION "m5-atom" // Use this for Code selection
#define SETUP_HW_VERSION "m5-atom"
// Hardware pins
#define HOME_PUSH_BUTTON 39
#define PIN_Led 10
#endif

#ifdef HW_ESP32_CAM
#define HW_VERSION "esp32-cam" // Use this for Code selection
#define SETUP_HW_VERSION "esp32-cam"
#endif

/* All the COnstants defined as ALL CAPS*/

// Wifi Related
#define DEFAULT_SSID "Secure_Veea"
#define DEFAULT_WIFI_PWD "Secure_ATM"


// MQTT related
#define BLANK_STRING ""
//-----------------------------------------------------------------
#define PRIMARY_MQTT_SERVER "mqtt.secure.live"  /* "35.222.6.2" */
#define PRIMARY_MQTT_PORT 8883
#define PRIMARY_MQTT_USER "m5-beacon"
#define PRIMARY_MQTT_PASSWORD "hf*!EYfk4jQQjfG9nGf7SHQbJ5"
//-----------------------------------------------------------------
#define SECONDARY_MQTT_SERVER "mqtts.secure.live"
#define SECONDARY_MQTT_PORT 1883
#define SECONDARY_MQTT_USER "m5-beacon"
#define SECONDARY_MQTT_PASSWORD "hf*!EYfk4jQQjfG9nGf7SHQbJ5"
//-----------------------------------------------------------------
#define DEFAULT_MESSAGE_LENGTH 1024
#define DEFAULT_TOPIC_PREFIX ""
#define DEFAULT_SUB_TOPIC "set/#"

#define DEFAULT_DEVICE_CODE "ZZZZ"

#define DEVICE_NAME_LEN 64 // Captiv portal

#define INTIGER_LEN 8

// Used by Bluetooth Scanning
#define TRACKING_DISTANCE_THRASHHOLD 5 // RSSI Thrashold to consider a change
#define DEFAULT_CALIBRATION_RSSI -75   // Use the RSSI for 1 Meter distance

#define DEFAULT_ACTIVE_SCAN true
#define DEFAULT_MIN_DISTANCE 0        // Default Minimam Distance for counting
#define DEFAULT_MAX_DISTANCE 10       // Default highest RSSI to send data for
#define DEFAULT_SCANNING_FREQUENCY 10 // 30 // Data sending frequency in seconds
#define DEFAULT_BLUE_SCANTIME 5       // BLE Scantime
#define DEFAULT_BLUE_INTERVAL 100     // BLE Scantime
#define DEFAULT_BLUE_WINDOW 99        // BLE Scan Window
#define DEFAULT_BLUE_ACTIVE_SCAN 1    // Bluetooth active scanning
#define DEFAULT_SCAN_ZONE_SIZE 5

#define DEFAULT_TIME_ZONE 0000
#define DEFAULT_UNIT_C 0

void debug_string(String msg, bool debug_msg = false);
bool check_for_on_demand_portal();
void serial_print_config();
void check_configurations();
void set_defaults();
void save_config_file(void);
bool read_config_file();
void saveConfigCallback(void);
void format_config_file(void);

#endif