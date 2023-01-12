#include "WiFi.h"
#include <PubSubClient.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WebServer.h>
// #include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <ESPmDNS.h>
// #include <WiFi.h>
#include <TaskScheduler.h>
#include "camera.h"
#include "types.h"
#include "mqtt.h"
#include "fx.h"
// #include "networking.h"

// #include "config.h"
bool shouldreboot = false;

/******************* Setup Code ********************/
#include "Wifi_BLE_config.h"
#include "timer.h"
#include "config.h"
/**********************************/

void task_send_mqtt_hearbeatCallback();
void task_check_connectivityCallback();
void task_scheduled_rebootCallback();
/******************* Setup Code **********************/

String bid = WiFi.macAddress();

volatile bool connected_to_web = false;
volatile bool credentails_recieved = false;
volatile int wifi_connected = Non;
volatile int deviceConnected = Non;

volatile extern uint8_t isUpdaetAvailable;


// Define a task handle and initialize it to NULL
TaskHandle_t task_handle = NULL;
TaskHandle_t task2_handle = NULL;
#define SCHEDULED_REBOOT_TIMER 1 * 25 * 60 * 60 * 1000 // Hours
#define SCHEDULED_CONNECTIVITY_TIMER 5 * 60 * 1000     // Minutes
#define SCHEDULED_HEARBEAT_TIMER 1 * 10 * 1000         // Seconds

Task task_send_mqtt_hearbeat(SCHEDULED_HEARBEAT_TIMER, TASK_FOREVER, &task_send_mqtt_hearbeatCallback);
Task task_check_connectivity(SCHEDULED_CONNECTIVITY_TIMER, TASK_FOREVER, &task_check_connectivityCallback);
Task task_scheduled_reboot(SCHEDULED_REBOOT_TIMER, TASK_FOREVER, &task_scheduled_rebootCallback);

Scheduler runner;



// Scheduler ts;

extern data_config WM_config;

uint8_t Setup_Mode = 0;

/******************* Setup Code **********************/

void EEPROM_Setup(void)
{
  if (!EEPROM.begin(EEPROM_SIZE))
  {
    delay(1000);
  }
  erase_eeprom();
}


/*************************************************************************
 * void general_process(void)
 * carries out the basic process for obtaining WiFi credentials using BLE.
 * Author : Utkarsh Chitte
 * Last Modified : 22-04-11
 ************************************************************************/
void general_process(void)
{
  if (deviceConnected == Ok && wifi_connected != Ok) // for some reasons ble is connected whe wifi is connected
  {
    // led_colour = BLUE_FAST;
    Serial.println("Device connected via bluetooth");
    deviceConnected = Non;
  }
  else if (deviceConnected == Fail)
  {
    // led_colour = RED_FAIL;
    Serial.println("Bluetooth connection failed!!!");
    deviceConnected = Non;
  }
  else if (credentails_recieved == true)
  {
    // led_colour = WHITE_FAST;
    Serial.println("Credentails Recieved...");
    credentails_recieved = false;
    wifiConnectTask();
  }
  else if (wifi_connected == Ok)
  {
    delay(3000);
    // led_colour = RED_CONST;
    // Serial.println("WiFi Connected!!!");
    Serial.println("Performing OTA Update!!!");
    wifi_connected = Non;
    OTA_Update();
  }
  else if (wifi_connected == Fail)
  {
    // led_colour = RED_FAIL;
    Serial.println("WiFi connection failed!!!");
    wifi_connected = Non;
  }
  else if (isUpdaetAvailable == false)
  {
    // led_colour = RED_FAIL;
    Serial.println("Update failed!!!");
    isUpdaetAvailable = Non;
  }
}

void Failure_action(void)
{
  // vTaskDelete(task_handle); // delete the task when any interrupt occurs in loop.
  erase_eeprom();
  Serial.println("---failed---");
}
/*******************************************************
 * setup_hardawre()
 * Setup the hardware, buttons, Device, Display, etc.
 * Author : Kaushlesh Chandel
 * Last Modified : Build 21/07/06
 ******************************************************/
void setup_hardawre()
{
  String myDeviceCode = WM_config.device_config.device_code; 
  device_mac = WiFi.macAddress();
  device_mac.replace(":", "");
}

/******************************************************************
 * void Device_Connection(void)
 * checks the connection status and if connected performs the task.
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 ******************************************************************/
void Device_Connection(void)
{  
    deviceConnected = Non;
    
}

/***************************************************************************
 * void Credentails_Recieved(void)
 * checks the credentails recieved status and if recieved performs the task.
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 ***************************************************************************/
void Credentails_Recieved(void)
{
  if (credentails_recieved)
  {
     credentails_recieved = false;
  }
}

/**********************************************************************
 * void Wifi_Connection(void)
 * checks the wifi connection status and if connected performs the task.
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 *********************************************************************/
void Wifi_Connection(void)
{
  if (wifi_connected == Ok)
  {
    Serial.println("wifi");
    wifi_connected = Non;
  }
}

/*********************************************************************
 * void Connection_Failure(void)
 * checks if any connection failed and based on that performs the task.
 * Author : Sagar Kota
 * Last Modified : 22-03-09
 *********************************************************************/
void Connection_Failure(void)
{
  if (wifi_connected == Fail || deviceConnected == Fail || isUpdaetAvailable == Fail)
  {
    Failure_action();
    wifi_connected = Non;
    deviceConnected = Non;
  }
}

void initSPIFFS()
{
  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    ESP.restart();
  }
  else 
  {
    delay(500);
    Serial.println("SPIFFS mounted successfully");
  }
}

void initWiFi()
{
  WiFi.disconnect(true);
  delay(1000);
  WiFi.begin(DEFAULT_SSID, DEFAULT_WIFI_PWD);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  OTA_Update();
}

void setup() 
{  
  Serial.begin(115200);
  check_configurations();
  if (deviceHasConfig == true)
  {
    Setup_Mode = 0;
  }
  else
  {
    // Setup_Mode = 1;
    Setup_Mode = 0;
  }
  switch (Setup_Mode)
  {
    case 0: //Normal  mode setup .....Initialize the camera
            pinMode (Flash, OUTPUT);
            initSPIFFS();
            initWiFi();
            setup_hardawre();
            serial_print_config(); // Print Config to Serial port

            // debug_string(String(ESP.getFreeHeap()));         
            
            // Serial.print("Connected to WiFi: ");
            // Serial.println(DEFAULT_SSID);
            
            Serial.println("----------------------------------------------------------------");
            
            // WiFi.onEvent(WiFiEvent);// Bind the wifi event for debug

            WiFi.onEvent(WiFiGotIP, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP); // Fire the event when degvice gets IP Address

            if (deviceHasConfig == false || hasWiFi1Credentials == false)
            {
              debug_string("New device. Connecting to setup wifi");
              wifiOnline = wm_fast(true);
            }
            else if (portalOnDemand)
            {
              debug_string("Portal on demand");
              wm_setup(true);
            }
            else
            {
              debug_string("Has saved wifi. Fast Wifi Connect");
              wifiOnline = wm_fast(false);
            }

            if (wifiOnline)
            {
              Serial.println("checking for update");
              if (checkUpdateFirmware(SW_VERSION, HW_VERSION) == false)
              {
                Serial.println("checking for update");
                debug_string("No OTA updates");
              }

              debug_string("Initialize MQTT ");
              if (init_mqtt() == true)
              {
                debug_string("MQTT Connected");
              }

              debug_string("IP Address : " + WiFi.localIP().toString());
              debug_string("Device mac : " + device_mac);
            }       

            // Runner has list of tasks that must be run at a set period
            runner.init();

            // Add task to Runner.
            runner.addTask(task_send_mqtt_hearbeat);
            runner.addTask(task_check_connectivity);
            runner.addTask(task_scheduled_reboot);

            // Enable the tasks. tasks start after 10 seconds
            task_send_mqtt_hearbeat.enableDelayed(10000);
            task_check_connectivity.enableDelayed(10000);
            task_scheduled_reboot.enableDelayed(10000);
            
            if (wifiOnline)
              debug_string("All Good! Proceed to runway with WiFi");
            else
              debug_string("ERROR! Proceed to runway without WiFI");


     
            // Turn-off the 'brownout detector'
            WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
            initCamera();            
            configTime(0, 0, ntpServer);
            get_Time();            
            delay(1000);
            //Firebase
            // Assign the api key
            configF.api_key = API_KEY;
            //Assign the user sign in credentials
            auth.user.email = USER_EMAIL;
            auth.user.password = USER_PASSWORD;
            //Assign the callback function for the long running token generation task
            configF.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
            Firebase.begin(&configF, &auth);
            Firebase.reconnectWiFi(true);            
            //Clicking Pictures initially helps with setting proper image quality
            for(int i=0 ; i<= 4; i++)
            {
              digitalWrite(Flash,HIGH);
              delay(200);
              digitalWrite(Flash,LOW);
              FILE_PHOTO = make_path();
              capturePhotoSaveSpiffs();
              delay(500);
              SPIFFS.remove(FILE_PHOTO);
            }
            delay(1000);
            break;
    case 1: //setup mode ...........take and store Wifi Credentials
            EEPROM_Setup();
            Serial.print("Device MAC Address : ");
            bid.replace(":", "");
            Serial.println(bid); // mac address
            WiFi_Setup_Using_BLE();
            break;
  }
  Serial.println("Setup complete !!!");
}

void loop()
 {
  switch (Setup_Mode)
  {
    case 0:   //normal mode click pictures and send to firebase and handles mqtt and command processes
              loopsPM++;
              process_cli();     // Process Serial port based commands recevied
              runner.execute();  // Timer execution. Runs timed events like connectivity check, scheduled reboot. etc.
              mqttclient.loop(); // Process messges received by MQTT subscription

              if (takeNewPhoto) 
              {
                FILE_PHOTO = make_path();
                Serial.print(FILE_PHOTO);
                digitalWrite(Flash,HIGH);
                capturePhotoSaveSpiffs();
                delay(500);
                digitalWrite(Flash,LOW);
                takeNewPhoto = false;
              }
              delay(1000);
              
              if (Firebase.ready() && !taskCompleted)
              {
                taskCompleted = true;
                Serial.print("Uploading picture... ");

                //MIME type should be valid to avoid the download problem.
                //The file systems for flash and SD/SDMMC can be changed in FirebaseFS.h.
                if (Firebase.Storage.upload(&fbdo, STORAGE_BUCKET_ID /* Firebase Storage bucket id */, FILE_PHOTO /* path to local file */, mem_storage_type_flash /* memory storage type, mem_storage_type_flash and mem_storage_type_sd */, FILE_PHOTO /* path of remote file stored in the bucket */, "image/jpeg" /* mime type */))
                {
                  Serial.printf("\nDownload URL: %s\n", fbdo.downloadURL().c_str());
                }
                else
                {
                  Serial.println(fbdo.errorReason());
                  SPIFFS.remove(FILE_PHOTO);
                  ESP.restart();
                }
                
                wait();
                SPIFFS.remove(FILE_PHOTO);
                Serial.println("Old file erased Camera ready to click new Picture.");
                takeNewPhoto = true;
                taskCompleted = false;
              }
              break;
    case 1:   void general_process();
              break;
  }
}