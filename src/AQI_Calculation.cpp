#include <Arduino.h>
#include <ArduinoJson.h>

#include "AQI_Calculation.h"

float aqi_pm2_5 = 0;
float aqi_voc = 0;
float aqi_co2 = 0;
float aqi_temp = 0;
float aqi_humi = 0;

/******************************************
 * int Get_aqi_pm25(int raw_PM25)
 * 
 * calculates the AQI for PM 2.5 raw data which is passes as argument
 * returns calculated AQI for PM 2.5
 * Author : Sagar Kota
 * Last Modified : Build 08/02/22
*******************************************/
float Get_aqi_pm25(int raw_PM25)
{
  int IHi = 0,Ilo = 0,BPHi = 0,BPLo = 0;
  if (raw_PM25 <= PM25_Range1_Hi)
  {
    IHi = AQI_Index_Range1_Hi; Ilo = AQI_Index_Range1_Lo; BPHi = PM25_Range1_Hi; BPLo = PM25_Range1_Lo;
  }
  else if(raw_PM25 <= PM25_Range2_Hi && raw_PM25 >= PM25_Range2_Lo)
  {
    IHi = AQI_Index_Range2_Hi; Ilo = AQI_Index_Range2_Lo; BPHi = PM25_Range2_Hi; BPLo = PM25_Range2_Lo;
  }
  else if(raw_PM25 <= PM25_Range3_Hi && raw_PM25 >= PM25_Range3_Lo)
  {
    IHi = AQI_Index_Range3_Hi; Ilo = AQI_Index_Range3_Lo; BPHi = PM25_Range3_Hi; BPLo = PM25_Range3_Lo;
  }
  else if(raw_PM25 <= PM25_Range4_Hi && raw_PM25 >= PM25_Range4_Lo)
  {
    IHi = AQI_Index_Range4_Hi; Ilo = AQI_Index_Range4_Lo; BPHi = PM25_Range4_Hi; BPLo = PM25_Range4_Lo;
  }
  else if(raw_PM25 <= PM25_Range5_Hi && raw_PM25 >= PM25_Range5_Lo)
  {
    IHi = AQI_Index_Range5_Hi; Ilo = AQI_Index_Range5_Lo; BPHi = PM25_Range5_Hi; BPLo = PM25_Range5_Lo;
  }
  else if(raw_PM25 <= PM25_Range6_Hi)
  {
    IHi = AQI_Index_Range6_Hi; Ilo = AQI_Index_Range6_Lo; BPHi = PM25_Range6_Hi; BPLo = PM25_Range6_Lo;
  }
  else
  {
    raw_PM25 = PM25_Range6_Hi;
    IHi = AQI_Index_Range6_Hi; Ilo = AQI_Index_Range6_Lo; BPHi = PM25_Range6_Hi; BPLo = PM25_Range6_Lo;
  }
  /*Serial.println("..raw..");
  Serial.println(IHi);
  Serial.println(Ilo);
  Serial.println(BPHi);
  Serial.println(BPLo);*/

  return (( (float) (IHi - Ilo) / (BPHi - BPLo) ) * (raw_PM25 - BPLo) + Ilo);
}

/******************************************
 * int Get_aqi_voc(int raw_voc)
 * 
 * calculates the AQI for TVOC raw data which is passes as argument
 * returns calculated AQI for TVOC
 * Author : Sagar Kota
 * Last Modified : Build 08/02/22
*******************************************/
float Get_aqi_voc(int raw_voc)
{
  int IHi = 0,Ilo = 0,BPHi = 0,BPLo = 0;
  if (raw_voc <= Voc_Range1_Hi)
  {
    IHi = AQI_Index_Range1_Hi; Ilo = AQI_Index_Range1_Lo; BPHi = Voc_Range1_Hi; BPLo = Voc_Range1_Lo;
  }
  else if(raw_voc <= Voc_Range2_Hi && raw_voc >= Voc_Range2_Lo)
  {
    IHi = AQI_Index_Range2_Hi; Ilo = AQI_Index_Range2_Lo; BPHi = Voc_Range2_Hi; BPLo = Voc_Range2_Lo;
  }
  else if(raw_voc <= Voc_Range3_Hi && raw_voc >= Voc_Range3_Lo)
  {
    IHi = AQI_Index_Range3_Hi; Ilo = AQI_Index_Range3_Lo; BPHi = Voc_Range3_Hi; BPLo = Voc_Range3_Lo;
  }
  else if(raw_voc <= Voc_Range4_Hi && raw_voc >= Voc_Range4_Lo)
  {
    IHi = AQI_Index_Range4_Hi; Ilo = AQI_Index_Range4_Lo; BPHi = Voc_Range4_Hi; BPLo = Voc_Range4_Lo;
  }
  else if(raw_voc <= Voc_Range5_Hi && raw_voc >= Voc_Range5_Lo)
  {
    IHi = AQI_Index_Range5_Hi; Ilo = AQI_Index_Range5_Lo; BPHi = Voc_Range5_Hi; BPLo = Voc_Range5_Lo;
  }
  else if(raw_voc <= Voc_Range6_Hi)
  {
    IHi = AQI_Index_Range6_Hi; Ilo = AQI_Index_Range6_Lo; BPHi = Voc_Range6_Hi; BPLo = Voc_Range6_Lo;
  }
  else
  {
    raw_voc = Voc_Range6_Hi;
    IHi = AQI_Index_Range6_Hi; Ilo = AQI_Index_Range6_Lo; BPHi = Voc_Range6_Hi; BPLo = Voc_Range6_Lo;
  }

  return (( (float) (IHi - Ilo) / (BPHi - BPLo) ) * (raw_voc - BPLo) + Ilo);
}


/******************************************
 * int Get_aqi_Co2(int raw_co2)
 * 
 * calculates the AQI for CO2 raw data which is passes as argument
 * returns calculated AQI for CO2
 * Author : Sagar Kota
 * Last Modified : Build 08/02/22
*******************************************/
float Get_aqi_co2(int raw_co2)
{
  int IHi = 0,Ilo = 0,BPHi = 0,BPLo = 0;
  if (raw_co2 <= Co2_Range1_Hi)
  {
    IHi = AQI_Index_Range1_Hi; Ilo = AQI_Index_Range1_Lo; BPHi = Co2_Range1_Hi; BPLo = Co2_Range1_Lo;
  }
  else if(raw_co2 <= Co2_Range2_Hi && raw_co2 >= Co2_Range2_Lo)
  {
    IHi = AQI_Index_Range2_Hi; Ilo = AQI_Index_Range2_Lo; BPHi = Co2_Range2_Hi; BPLo = Co2_Range2_Lo;
  }
  else if(raw_co2 <= Co2_Range3_Hi && raw_co2 >= Co2_Range3_Lo)
  {
    IHi = AQI_Index_Range3_Hi; Ilo = AQI_Index_Range3_Lo; BPHi = Co2_Range3_Hi; BPLo = Co2_Range3_Lo;
  }
  else if(raw_co2 <= Co2_Range4_Hi && raw_co2 >= Co2_Range4_Lo)
  {
    IHi = AQI_Index_Range4_Hi; Ilo = AQI_Index_Range4_Lo; BPHi = Co2_Range4_Hi; BPLo = Co2_Range4_Lo;
  }
  else if(raw_co2 <= Co2_Range5_Hi && raw_co2 >= Co2_Range5_Lo)
  {
    IHi = AQI_Index_Range5_Hi; Ilo = AQI_Index_Range5_Lo; BPHi = Co2_Range5_Hi; BPLo = Co2_Range5_Lo;
  }
  else if(raw_co2 <= Co2_Range6_Hi)
  {
    IHi = AQI_Index_Range6_Hi; Ilo = AQI_Index_Range6_Lo; BPHi = Co2_Range6_Hi; BPLo = Co2_Range6_Lo;
  }
  else
  {
    raw_co2 = Co2_Range6_Hi;
    IHi = AQI_Index_Range6_Hi; Ilo = AQI_Index_Range6_Lo; BPHi = Co2_Range6_Hi; BPLo = Co2_Range6_Lo;
  }

  return (( (float) (IHi - Ilo) / (BPHi - BPLo) ) * (raw_co2 - BPLo) + Ilo);
}

/******************************************
 * float Get_aqi_temp(int raw_temp)
 * 
 * calculates the AQI for temp raw data which is passes as argument
 * returns calculated AQI for temp
 * Author : Sagar Kota
 * Last Modified : Build 09/02/22
*******************************************/
float Get_aqi_temp(int raw_temp)
{
  int IHi = 0,Ilo = 0,BPHi = 0,BPLo = 0;

  raw_temp = (raw_temp - 32) * 5 / 9;    // fahrenheit to celsius

  if (raw_temp <= temp_Range5_Hi_DW)
  {
    IHi = AQI_Index_Range5_Hi; Ilo = AQI_Index_Range5_Lo; BPHi = temp_Range5_Hi_DW; BPLo = temp_Range5_Lo_DW;
  }
  else if(raw_temp <= temp_Range4_Hi_DW)
  {
    IHi = AQI_Index_Range4_Hi; Ilo = AQI_Index_Range4_Lo; BPHi = temp_Range4_Hi_DW; BPLo = temp_Range4_Lo_DW;
  }
  else if(raw_temp <= temp_Range3_Hi_DW)
  {
    IHi = AQI_Index_Range3_Hi; Ilo = AQI_Index_Range3_Lo; BPHi = temp_Range3_Hi_DW; BPLo = temp_Range3_Lo_DW;
  }
  else if(raw_temp <= temp_Range2_Hi_DW)
  {
    IHi = AQI_Index_Range2_Hi; Ilo = AQI_Index_Range2_Lo; BPHi = temp_Range2_Hi_DW; BPLo = temp_Range2_Lo_DW;
  }
  else if(raw_temp <= temp_Range1_Hi)
  {
    IHi = AQI_Index_Range1_Hi; Ilo = AQI_Index_Range1_Lo; BPHi = temp_Range1_Hi; BPLo = temp_Range1_Lo;
  }
  else if(raw_temp <= temp_Range2_Hi_UP)
  {
    IHi = AQI_Index_Range2_Hi; Ilo = AQI_Index_Range2_Lo; BPHi = temp_Range2_Hi_UP; BPLo = temp_Range2_Lo_UP;
  }
  else if(raw_temp <= temp_Range3_Hi_UP)
  {
    IHi = AQI_Index_Range3_Hi; Ilo = AQI_Index_Range3_Lo; BPHi = temp_Range3_Hi_UP; BPLo = temp_Range3_Lo_UP;
  }
  else if(raw_temp <= temp_Range4_Hi_UP)
  {
    IHi = AQI_Index_Range4_Hi; Ilo = AQI_Index_Range4_Lo; BPHi = temp_Range4_Hi_UP; BPLo = temp_Range4_Lo_UP;
  }
  else if(raw_temp <= temp_Range5_Hi_UP)
  {
    IHi = AQI_Index_Range5_Hi; Ilo = AQI_Index_Range5_Lo; BPHi = temp_Range5_Hi_UP; BPLo = temp_Range5_Lo_UP;
  }
  else if(raw_temp <= temp_Range6_Hi_UP)
  {
    IHi = AQI_Index_Range6_Hi; Ilo = AQI_Index_Range6_Lo; BPHi = temp_Range6_Hi_UP; BPLo = temp_Range6_Lo_UP;
  }
  else
  {
    raw_temp = temp_Range6_Hi_UP;
    IHi = AQI_Index_Range6_Hi; Ilo = AQI_Index_Range6_Lo; BPHi = temp_Range6_Hi_UP; BPLo = temp_Range6_Lo_UP;
  }
  return (( (float) (IHi - Ilo) / (BPHi - BPLo) ) * (raw_temp - BPLo) + Ilo);
}

/******************************************
 * float Get_aqi_Humi(int raw_humi)
 * 
 * calculates the AQI for humi raw data which is passes as argument
 * returns calculated AQI for humi
 * Author : Sagar Kota
 * Last Modified : Build 08/02/22
*******************************************/
float Get_aqi_Humi(int raw_humi)
{
  int IHi = 0,Ilo = 0,BPHi = 0,BPLo = 0;

  if (raw_humi <= Humi_Range5_Hi_DW)
  {
    IHi = AQI_Index_Range5_Hi; Ilo = AQI_Index_Range5_Lo; BPHi = Humi_Range5_Hi_DW; BPLo = Humi_Range5_Lo_DW;
  }
  else if(raw_humi <= Humi_Range4_Hi_DW)
  {
    IHi = AQI_Index_Range4_Hi; Ilo = AQI_Index_Range4_Lo; BPHi = Humi_Range4_Hi_DW; BPLo = Humi_Range4_Lo_DW;
  }
  else if(raw_humi <= Humi_Range3_Hi_DW)
  {
    IHi = AQI_Index_Range3_Hi; Ilo = AQI_Index_Range3_Lo; BPHi = Humi_Range3_Hi_DW; BPLo = Humi_Range3_Lo_DW;
  }
  else if(raw_humi <= Humi_Range2_Hi_DW)
  {
    IHi = AQI_Index_Range2_Hi; Ilo = AQI_Index_Range2_Lo; BPHi = Humi_Range2_Hi_DW; BPLo = Humi_Range2_Lo_DW;
  }
  else if(raw_humi <= Humi_Range1_Hi)
  {
    IHi = AQI_Index_Range1_Hi; Ilo = AQI_Index_Range1_Lo; BPHi = Humi_Range1_Hi; BPLo = Humi_Range1_Lo;
  }
  else if(raw_humi <= Humi_Range2_Hi_UP)
  {
    IHi = AQI_Index_Range2_Hi; Ilo = AQI_Index_Range2_Lo; BPHi = Humi_Range2_Hi_UP; BPLo = Humi_Range2_Lo_UP;
  }
  else if(raw_humi <= Humi_Range3_Hi_UP)
  {
    IHi = AQI_Index_Range3_Hi; Ilo = AQI_Index_Range3_Lo; BPHi = Humi_Range3_Hi_UP; BPLo = Humi_Range3_Lo_UP;
  }
  else if(raw_humi <= Humi_Range4_Hi_UP)
  {
    IHi = AQI_Index_Range4_Hi; Ilo = AQI_Index_Range4_Lo; BPHi = Humi_Range4_Hi_UP; BPLo = Humi_Range4_Lo_UP;
  }
  else if(raw_humi <= Humi_Range5_Hi_UP)
  {
    IHi = AQI_Index_Range6_Hi; Ilo = AQI_Index_Range5_Lo; BPHi = Humi_Range5_Hi_UP; BPLo = Humi_Range5_Lo_UP;
  }
  else
  {
    raw_humi = Humi_Range5_Hi_UP;
    IHi = AQI_Index_Range6_Hi; Ilo = AQI_Index_Range5_Lo; BPHi = Humi_Range5_Hi_UP; BPLo = Humi_Range5_Lo_UP;
  }

  return (( (float) (IHi - Ilo) / (BPHi - BPLo) ) * (raw_humi - BPLo) + Ilo);
}



/******************************************
 * AQI_calculator(int raw_pm1, int raw_pm2_5, int raw_pm10,
 *               int raw_temp, int raw_humi, int raw_voc, int raw_co2));
 * calculates the AQI of each raw value of sensor data based on the standards.
 * Author : Sagar Kota
 * Last Modified : Build 08/02/22
*******************************************/
void AQI_calculator(int raw_pm1, int raw_pm2_5, int raw_pm10, int raw_temp, int raw_humi, int raw_voc, int raw_co2)
{
  if (raw_pm2_5 > 0)
    aqi_pm2_5 = Get_aqi_pm25(raw_pm2_5);
 
  if (raw_voc > 0)
    aqi_voc = Get_aqi_voc(raw_voc);
 
  if (raw_co2 > 0)
    aqi_co2 = Get_aqi_co2(raw_co2);
 
  if(raw_temp > 0)
    aqi_temp = Get_aqi_temp(raw_temp);
 
  if (raw_humi > 0)  
    aqi_humi = Get_aqi_Humi(raw_humi);

  /*Serial.println("-------AQI---------");
  Serial.println("PM2.5 : " + String(aqi_pm2_5));
  Serial.println("TVOC : " + String(aqi_voc));
  Serial.println("CO2 : " + String(aqi_co2));
  Serial.println("TEMP : " + String(aqi_temp));
  Serial.println("HUMI : " + String(aqi_humi));*/
}

/******************************************
 * Get_All_AQI_Values(float * ptr_pm25, float * ptr_voc, float * ptr_co2,
 *                         float * ptr_temp, float * ptr_humi);

 * copys the aqi calculated data into ptr varaiables passed as argument.
 * Author : Sagar Kota
 * Last Modified : Build 08/02/22
*******************************************/
void Get_All_AQI_Values(float * ptr_pm25, float * ptr_voc, float * ptr_co2, float * ptr_temp, float * ptr_humi)
{
  *ptr_pm25 = aqi_pm2_5;
  *ptr_voc  = aqi_voc;
  *ptr_co2  = aqi_co2;
  *ptr_temp = aqi_temp;
  *ptr_humi = aqi_humi;
}

/******************************************
 * String Get_AQI_Mqtt_Str(void);
 * makes the json string for AQI calculated past and returns the same.
 * Author : Sagar Kota
 * Last Modified : Build 08/02/22
*******************************************/
String Get_AQI_Mqtt_Str(void)
{
  StaticJsonDocument<200> local_doc;
  char local_data_buffer[100];

  for (int i = 0; i < 100; ++i)
    local_data_buffer[i] = (char)0;

  local_doc["PM_25"] = aqi_pm2_5;
  local_doc["TVOC"]  = aqi_voc;
  local_doc["CO2"]   = aqi_co2;
  local_doc["TEMP"]  = aqi_temp;
  local_doc["HUMI"]  = aqi_humi;

  serializeJson(local_doc, local_data_buffer);
  Serial.print("##");
  Serial.println(local_data_buffer);

  local_doc.garbageCollect();
  local_doc.clear();
  return local_data_buffer;
}
