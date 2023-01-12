#include "esp_camera.h"
#include "Arduino.h"
#include "soc/soc.h"           // Disable brownout problems
#include "soc/rtc_cntl_reg.h"  // Disable brownout problems
#include "driver/rtc_io.h"
#include <SPIFFS.h>
#include <FS.h>
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include <addons/TokenHelper.h>

// Timestamp
#include "time.h"
const char* ntpServer = "pool.ntp.org";
struct tm timeinfo;

//Replace with your network credentials
// const char* ssid = "Veea_test";
// const char* password = "veea_test";

// Insert Firebase project API Key
//#define API_KEY "AIzaSyBf57JZPv8kG0IffUj6OMvOg6LVaJSedXw"

#define API_KEY "AIzaSyC9VLuawf8jxQ3kXafG5jG1OdEtXnywyfo"
  

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "energy_meter_cam@annet.com"
#define USER_PASSWORD "energy@123"


// Insert Firebase storage bucket ID e.g bucket-name.appspot.com
#define STORAGE_BUCKET_ID "stg-sec-live.appspot.com"

// Photo File Name to save in SPIFFS
//#define FILE_PHOTO  "/data/photo.jpg"
String FILE_PHOTO ;


// OV2640 camera module pins (CAMERA_MODEL_AI_THINKER)
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

#define Flash 4

boolean takeNewPhoto = true;

//Define Firebase Data objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig configF;

bool taskCompleted = false;

// Check if photo capture was successful
bool checkPhoto( fs::FS &fs ) 
{
  File f_pic = fs.open( FILE_PHOTO );
  unsigned int pic_sz = f_pic.size();
  return ( pic_sz > 100 );
}

// Capture Photo and Save it to SPIFFS
void capturePhotoSaveSpiffs( void ) 
{  
  camera_fb_t * fb = NULL; // pointer
  bool ok = 0; // Boolean indicating if the picture has been taken correctly
  do {
      // Take a photo with the camera
      Serial.println("Taking a photo...");
      Serial.println("");
      fb = esp_camera_fb_get();
      if (!fb) 
      {
        Serial.println("Camera capture failed");
        return;
      }
      // Photo file name
      Serial.print("Picture file name");
      Serial.println(FILE_PHOTO); 

      File file = SPIFFS.open(FILE_PHOTO, FILE_WRITE);
      //File file = SPIFFS.open(PATH, FILE_WRITE);
      // Insert the data in the photo file
      if (!file)
      {
        Serial.println("Failed to open file in writing mode");
      }
      else
      {
        file.write(fb->buf, fb->len); // payload (image), payload length
        Serial.print("The picture has been saved in ");
        Serial.print(FILE_PHOTO);
        Serial.print(" - Size: ");
        Serial.print(file.size());
        Serial.println(" bytes");
      }
      // Close the file
      file.close();
      esp_camera_fb_return(fb);

      // check if file has been correctly saved in SPIFFS
      ok = checkPhoto(SPIFFS);
  } while ( !ok );
}

void initCamera()
{
 // OV2640 camera module
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if (psramFound()) 
  {
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } 
  else 
  {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
  // Camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK)
  {
    Serial.printf("Camera init failed with error 0x%x", err);
    ESP.restart();
  } 

  //Setting for the Image
  sensor_t * s = esp_camera_sensor_get();
  s->set_brightness(s,0);     // -2 to 2
  s->set_contrast(s,0);       // -2 to 2
  s->set_saturation(s,0);     // -2 to 2
  s->set_special_effect(s, 0); // 0 to 6 (0 - No Effect, 1 - Negative, 2 - Grayscale, 3 - Red Tint, 4 - Green Tint, 5 - Blue Tint, 6 - Sepia)
  s->set_whitebal(s, 0);       // 0 = disable , 1 = enable
  s->set_awb_gain(s, 1);       // 0 = disable , 1 = enable
  s->set_wb_mode(s, 1);        // 0 to 4 - if awb_gain enabled (0 - Auto, 1 - Sunny, 2 - Cloudy, 3 - Office, 4 - Home)
  s->set_exposure_ctrl(s, 1);  // 0 = disable , 1 = enable
  s->set_aec2(s, 1);           // 0 = disable , 1 = enable
  s->set_ae_level(s, 0);       // -2 to 2
  s->set_aec_value(s, 300);    // 0 to 1200
  s->set_gain_ctrl(s, 0);      // 0 = disable , 1 = enable
  s->set_agc_gain(s, 0);       // 0 to 30
  s->set_gainceiling(s, (gainceiling_t)3);  // 0 to 6
  s->set_bpc(s, 0);            // 0 = disable , 1 = enable
  s->set_wpc(s, 1);            // 0 = disable , 1 = enable
  s->set_raw_gma(s, 1);        // 0 = disable , 1 = enable
  s->set_lenc(s, 1);           // 0 = disable , 1 = enable
  s->set_hmirror(s, 0);        // 0 = disable , 1 = enable
  s->set_vflip(s, 0);          // 0 = disable , 1 = enable
  s->set_dcw(s, 1);            // 0 = disable , 1 = enable
  s->set_colorbar(s, 0);       // 0 = disable , 1 = enable

}

unsigned long get_Time()
{
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    //Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}

String make_path()
{ 
  unsigned long gettime = get_Time();
  String ID = WiFi.macAddress();
  ID.replace(":", "");
  String path;
  path += "/";
  path += ID;
  path += "/";
  //path += ID;
  //path += "_";
  path += gettime;
  path += ".jpg";
  Serial.println(path);

  return path;
}

void wait()
{
  for(int i = 1; i<= 60 ; i++) //put mutliples of 60 to increase duration of intervals
  {
    delay(1000);
    if((i%10) == 0)
    {
      Serial.print(".");
    }
  }
  Serial.println("");
}
