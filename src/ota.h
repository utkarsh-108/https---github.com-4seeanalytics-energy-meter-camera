#ifndef OTA_H /* include guards */
#define OTA_H

#include <HTTPClient.h>
#include <ESP32httpUpdate.h>
#include <Update.h>
#include "common.h"


#include <HTTPClient.h>
#define FIRMWARE_SERVER "http://app.secure.live/update_"

/*
Update the firmware to provided file as sURL
*/

volatile uint8_t isUpdaetAvailable = Non;

void updateFirmware(String sURL)
{
  if ((WiFi.status() == WL_CONNECTED))
  {
    // Check if the Firmware file exists
    debug_string("Checking for Firmware " + sURL, true);

    t_httpUpdate_return ret = ESPhttpUpdate.update(sURL);
    switch (ret)
    {
    case HTTP_UPDATE_FAILED:
      debug_string("HTTP_UPDATE_FAILD Error ", true);
      break;

    case HTTP_UPDATE_NO_UPDATES:
      debug_string("HTTP_UPDATE_NO_UPDATES", true);
      break;

    case HTTP_UPDATE_OK:
      debug_string("HTTP_UPDATE_OK", true);
      break;
    }
  }
}

/*****************************************************************************
 * checkUpdateFirmware(String, String)
 * Checks app.secure.live server for Firmware updates.
 * If updates are found, it will automatically update the firmware and reboot
 * Author : Kaushlesh Chandel
 * Last Modified :
 *****************************************************************************/
bool checkUpdateFirmware(String currentFirmware, String HardwareVersion)
{
  String sURL = FIRMWARE_SERVER;

  if (currentFirmware == "")
  {
    sURL += HardwareVersion;
    sURL += ".bin";
  }
  else
  {
    sURL += HardwareVersion;
    sURL += "_";
    sURL += currentFirmware;
    sURL += ".bin";
  }
  // sURL = "http://app.secure.live/update_m5-atom_21-07-02.bin";

  debug_string("Checking for new firmware " + sURL, true);
  // Serial.println(sURL);

  HTTPClient http;

  http.begin(sURL); // HTTP
  int httpCode = http.GET();

  // httpCode will be negative on error
  if (httpCode > 0)
  {
    if (httpCode == HTTP_CODE_OK)
    {
      isUpdaetAvailable = true;
      debug_string("Updating firmware", true);
      // display.show_ota_screen();
      updateFirmware(sURL);
    }
  }
  else
  {
    debug_string("No Firmware update", true);
    isUpdaetAvailable = false;
  }

  http.end();
  // Serial.println("Download finished");
  return isUpdaetAvailable;
}

/*************************************************************
 * void OTA_Update(void)
 * Perform the OTA Update after the wifi connection sucessfull.
 * Author : Sagar Kota
 * Last Modified : 22-03-01
 ************************************************************/

void OTA_Update(void)
{
  checkUpdateFirmware(SETUP_SW_VERSION, SETUP_HW_VERSION);
}

#endif