
#define INDIA_AQI
//#define USA_AQI

/*************** Standard AQI Index Range *****************/

#define AQI_Index_Range1_Hi 50
#define AQI_Index_Range1_Lo 0

#define AQI_Index_Range2_Hi 100
#define AQI_Index_Range2_Lo 51

#define AQI_Index_Range3_Hi 200
#define AQI_Index_Range3_Lo 101

#define AQI_Index_Range4_Hi 300
#define AQI_Index_Range4_Lo 201

#define AQI_Index_Range5_Hi 400
#define AQI_Index_Range5_Lo 301

#define AQI_Index_Range6_Hi 500
#define AQI_Index_Range6_Lo 401


#ifdef INDIA_AQI
/***************  PM2.5 Indian AQI Range  ****************/
#define PM25_Range1_Hi 30
#define PM25_Range1_Lo 0

#define PM25_Range2_Hi 60
#define PM25_Range2_Lo 31

#define PM25_Range3_Hi 90
#define PM25_Range3_Lo 61

#define PM25_Range4_Hi 120
#define PM25_Range4_Lo 91

#define PM25_Range5_Hi 250
#define PM25_Range5_Lo 121

#define PM25_Range6_Hi 500
#define PM25_Range6_Lo 251


/***************  TVOC Indian AQI Range  ****************/
#define Voc_Range1_Hi 50
#define Voc_Range1_Lo 0

#define Voc_Range2_Hi 100
#define Voc_Range2_Lo 51

#define Voc_Range3_Hi 150
#define Voc_Range3_Lo 101

#define Voc_Range4_Hi 200
#define Voc_Range4_Lo 151

#define Voc_Range5_Hi 300
#define Voc_Range5_Lo 201

#define Voc_Range6_Hi 500
#define Voc_Range6_Lo 301

/***************  CO2 Indian AQI Range  ****************/

#define Co2_Range1_Hi 600
#define Co2_Range1_Lo 0

#define Co2_Range2_Hi 1000
#define Co2_Range2_Lo 601

#define Co2_Range3_Hi 1500
#define Co2_Range3_Lo 1001

#define Co2_Range4_Hi 2000
#define Co2_Range4_Lo 1501

#define Co2_Range5_Hi 2500
#define Co2_Range5_Lo 2001

#define Co2_Range6_Hi 5000
#define Co2_Range6_Lo 2501

/************************** TEMP INDIA Range *********************/

#define temp_Range6_Hi_UP 60
#define temp_Range6_Lo_UP 36

#define temp_Range5_Hi_UP 35
#define temp_Range5_Lo_UP 33

#define temp_Range4_Hi_UP 32
#define temp_Range4_Lo_UP 31

#define temp_Range3_Hi_UP 30
#define temp_Range3_Lo_UP 28

#define temp_Range2_Hi_UP 27
#define temp_Range2_Lo_UP 26

#define temp_Range1_Hi 25
#define temp_Range1_Lo 18

#define temp_Range2_Hi_DW 17
#define temp_Range2_Lo_DW 16

#define temp_Range3_Hi_DW 15
#define temp_Range3_Lo_DW 11

#define temp_Range4_Hi_DW 10
#define temp_Range4_Lo_DW 8

#define temp_Range5_Hi_DW 7
#define temp_Range5_Lo_DW 0

/***************** Humi INDIA Range *******************/

#define Humi_Range5_Hi_UP 100
#define Humi_Range5_Lo_UP 81

#define Humi_Range4_Hi_UP 80
#define Humi_Range4_Lo_UP 66

#define Humi_Range3_Hi_UP 65
#define Humi_Range3_Lo_UP 61

#define Humi_Range2_Hi_UP 60
#define Humi_Range2_Lo_UP 51

#define Humi_Range1_Hi 50
#define Humi_Range1_Lo 40

#define Humi_Range2_Hi_DW 39
#define Humi_Range2_Lo_DW 35

#define Humi_Range3_Hi_DW 34
#define Humi_Range3_Lo_DW 20

#define Humi_Range4_Hi_DW 19
#define Humi_Range4_Lo_DW 15

#define Humi_Range5_Hi_DW 14
#define Humi_Range5_Lo_DW 0



#endif

#ifdef USA_AQI
/***************  PM2.5 USA AQI Range  ****************/
#define PM25_Range1_Hi 30
#define PM25_Range1_Lo 0

#define PM25_Range2_Hi 60
#define PM25_Range2_Lo 31

#define PM25_Range3_Hi 90
#define PM25_Range3_Lo 61

#define PM25_Range4_Hi 120
#define PM25_Range4_Lo 91

#define PM25_Range5_Hi 250
#define PM25_Range5_Lo 121

#define PM25_Range6_Hi 251
#define PM25_Range6_Lo 0


/***************  TVOC USA AQI Range  ****************/
#define Voc_Range1_Hi 50
#define Voc_Range1_Lo 0

#define Voc_Range2_Hi 100
#define Voc_Range2_Lo 51

#define Voc_Range3_Hi 150
#define Voc_Range3_Lo 101

#define Voc_Range4_Hi 200
#define Voc_Range4_Lo 151

#define Voc_Range5_Hi 300
#define Voc_Range5_Lo 201

#define Voc_Range6_Hi 500
#define Voc_Range6_Lo 301

/***************  CO2 USA AQI Range  ****************/

#define Co2_Range1_Hi 600
#define Co2_Range1_Lo 0

#define Co2_Range2_Hi 1000
#define Co2_Range2_Lo 601

#define Co2_Range3_Hi 1500
#define Co2_Range3_Lo 1001

#define Co2_Range4_Hi 2000
#define Co2_Range4_Lo 1501

#define Co2_Range5_Hi 2500
#define Co2_Range5_Lo 2001

#define Co2_Range6_Hi 5000
#define Co2_Range6_Lo 2501

#endif


void AQI_calculator(int raw_pm1, int raw_pm2_5, int raw_pm10, int raw_temp, int raw_humi, int raw_voc, int raw_co2);
void Get_All_AQI_Values(float * ptr_pm25, float * ptr_voc, float * ptr_co2, float * ptr_temp, float * ptr_humi);
String Get_AQI_Mqtt_Str(void);