#ifndef _DEFINE_H
#define _DEFINE_H

/*
 * SYSTEM_MODE:
 *     - AUTOMATIC: Automatically try to connect to Wi-Fi and the Particle Cloud and handle the cloud messages.
 *     - SEMI_AUTOMATIC: Manually connect to Wi-Fi and the Particle Cloud, but automatically handle the cloud messages.
 *     - MANUAL: Manually connect to Wi-Fi and the Particle Cloud and handle the cloud messages.
 *     
 * SYSTEM_MODE(AUTOMATIC) does not need to be called, because it is the default state. 
 * However the user can invoke this method to make the mode explicit.
 * Learn more about system modes: https://docs.particle.io/reference/firmware/photon/#system-modes.
 */
//SYSTEM_MODE(AUTOMATIC); 

/*
 * DEBUG:
 *     - MENU_DEBUG: It allows through the serial interface and a MENU to test all the implemented functions. 
 *     - TIMER_DEBUG: The values of the sensors are shown using a timer
 *     
 *     1:Selected
 *     0:Not selected
 * 
 * *NOTE: Use one or the other, not both at the same time 
 * 
 */
#define MENU_DEBUG  0 
#define TIMER_DEBUG 1 
   
/* BLE scan parameters:
 *     - BLE_SCAN_TYPE     
 *           0x00: Passive scanning, no scan request packets shall be sent.(default)
 *           0x01: Active scanning, scan request packets may be sent.
 *           0x02 - 0xFF: Reserved for future use.
 *     - BLE_SCAN_INTERVAL: This is defined as the time interval from when the Controller started its last LE scan until it begins the subsequent LE scan.
 *           Range: 0x0004 to 0x4000
 *           Default: 0x0010 (10 ms)
 *           Time = N * 0.625 msec
 *           Time Range: 2.5 msec to 10.24 seconds
 *     - BLE_SCAN_WINDOW: The duration of the LE scan. The scan window shall be less than or equal to the scan interval.
 *           Range: 0x0004 to 0x4000
 *           Default: 0x0010 (10 ms)
 *           Time = N * 0.625 msec
 *           Time Range: 2.5 msec to 10240 msec
 */
#define BLE_SCAN_TYPE        0x00   // Passive scanning
#define BLE_SCAN_INTERVAL    0x0060 // 60 ms
#define BLE_SCAN_WINDOW      0x0030 // 30 ms

/* BLE profile parameters:
 *     - NSERV_MAX: Maximum number of Services that can be stored in Device_t    
 *     - NCHAR_MAX: Maximum number of Characteristics that can be stored in Device_t  
 *     - NDESC_MAX: Maximum number of Descriptors that can be stored in Device_t   
 */
#define NSERV_MAX 11
#define NCHAR_MAX 7
#define NDESC_MAX 3

/*! \struct Device_t
    \brief  Struct to save a BLE device and its related data
*/ 
typedef struct {
  uint16_t  connected_handle;
  uint8_t   addr_type;
  bd_addr_t addr;
  struct {
    gatt_client_service_t service;
    struct {
      gatt_client_characteristic_t chars;                                         
      gatt_client_characteristic_descriptor_t descriptor[NDESC_MAX]; 
    } chars[NCHAR_MAX];  
  } service[NSERV_MAX]; // [] Services contain [] characteristics and each characteristic can contain up to [] descriptors.
} Device_t;

//Mask to check the BLE Attributes properties
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)

/*! \enum states
    \brief  Enum for the diferents states of the debug MENU options 
*/
typedef enum states{
    BLE_CENTRAL_READ_CARACTERISTIC_VALUE = 0,   /**< State BLE_CENTRAL_READ_CARACTERISTIC_VALUE */
    BLE_CENTRAL_READ_DESCRIPTOR_VALUE,          /**< State BLE_CENTRAL_READ_DESCRIPTOR_VALUE */
    BLE_CENTRAL_ENABLE_DISABLE_NOTIFICATIONS,   /**< State BLE_CENTRAL_ENABLE_DISABLE_NOTIFICATIONS */
    BLE_CENTRAL_ENABLE_DISABLE_INDICATIONS,     /**< State BLE_CENTRAL_ENABLE_DISABLE_INDICATIONS */
    BLE_CENTRAL_WRITE                           /**< State BLE_CENTRAL_WRITE */
}stateEnum_t;


//UUIDs of the Services and Characrteristics associated with the Thunderboard Sense 2 device
//Services UUID
static uint8_t generic_access_service_uuid[16]                      =     {0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};
static uint8_t generic_attribute_service_uuid[16]                   =     {0x00, 0x00, 0x18, 0x01, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};
static uint8_t device_information_service_uuid[16]                  =     {0x00, 0x00, 0x18, 0x0A, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};
static uint8_t battery_service_uuid[16]                             =     {0x00, 0x00, 0x18, 0x0F, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};
static uint8_t environmental_sensing_service_uuid[16]               =     {0x00, 0x00, 0x18, 0x1A, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};
static uint8_t power_management_service_uuid[16]                    =     {0xEC, 0x61, 0xA4, 0x54, 0xED, 0x00, 0xA5, 0xE8, 0xB8, 0xF9, 0xDE, 0x9E, 0xC0, 0x26, 0xEC, 0x51};
static uint8_t iaq_service_uuid[16]                                 =     {0xEF, 0xD6, 0x58, 0xAE, 0xC4, 0x00, 0xEF, 0x33, 0x76, 0xE7, 0x91, 0xB0, 0x00, 0x19, 0x10, 0x3B};
static uint8_t user_interface_service_uuid[16]                      =     {0xFC, 0xB8, 0x9C, 0x40, 0xC6, 0x00, 0x59, 0xF3, 0x7D, 0xC3, 0x5E, 0xCE, 0x44, 0x4A, 0x40, 0x1B};  
static uint8_t automation_io_service_uuid[16]                       =     {0x00, 0x00, 0x18, 0x15, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};
static uint8_t accleration_orientation_service_uuid[16]             =     {0xA4, 0xE6, 0x49, 0xF4, 0x4B, 0xE5, 0x11, 0xE5, 0x88, 0x5D, 0xFE, 0xFF, 0x81, 0x9C, 0xDC, 0x9F};
static uint8_t hall_effect_service_uuid[16]                         =     {0xF5, 0x98, 0xDB, 0xC5, 0x2F, 0x00, 0x4E, 0xC5, 0x99, 0x36, 0xB3, 0xD1, 0xAA, 0x4F, 0x95, 0x7F}; 


//Characrteristic UUID
//Service 0 Generic Access
static uint8_t Service0_Characrteristic0_Device_Name_uuid[16]       =     {0x00, 0x00, 0x2A, 0x00, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};
static uint8_t Service0_Characrteristic1_Appearance_uuid[16]        =     {0x00, 0x00, 0x2A, 0x01, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};

//Service 1 Generic Attribute
static uint8_t Service1_Characrteristic0_Service_Changed_uuid[16]   =     {0x00, 0x00, 0x2A, 0x05, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};

//Service 2 Device Information
static uint8_t Service2_Characrteristic0_Manufacturer_Name_uuid[16] =     {0x00, 0x00, 0x2A, 0x29, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};
static uint8_t Service2_Characrteristic1_Model_Number_uuid[16]      =     {0x00, 0x00, 0x2A, 0x24, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};
static uint8_t Service2_Characrteristic2_Serial_Number_uuid[16]     =     {0x00, 0x00, 0x2A, 0x25, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};
static uint8_t Service2_Characrteristic3_Hardware_Revision_uuid[16] =     {0x00, 0x00, 0x2A, 0x27, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};
static uint8_t Service2_Characrteristic4_Firmware_Revision_uuid[16] =     {0x00, 0x00, 0x2A, 0x26, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB}; 
static uint8_t Service2_Characrteristic5_System_ID_uuid[16]         =     {0x00, 0x00, 0x2A, 0x23, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};

//Service 3 Battery Service
static uint8_t Service3_Characrteristic0_Battery_Level_uuid[16]     =     {0x00, 0x00, 0x2A, 0x19, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};

//Service 4 Environmental sensing service
static uint8_t Service4_Characrteristic0_UV_Index_uuid[16]          =     {0x00, 0x00, 0x2A, 0x76, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};
static uint8_t Service4_Characrteristic1_Pressure_uuid[16]          =     {0x00, 0x00, 0x2A, 0x6D, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};
static uint8_t Service4_Characrteristic2_Temperature_uuid[16]       =     {0x00, 0x00, 0x2A, 0x6E, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};
static uint8_t Service4_Characrteristic3_Humidity_uuid[16]          =     {0x00, 0x00, 0x2A, 0x6F, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};
static uint8_t Service4_Characrteristic4_Ambient_Light_uuid[16]     =     {0xC8, 0x54, 0x69, 0x13, 0xBF, 0xD9, 0x45, 0xEB, 0x8D, 0xDE, 0x9F, 0x87, 0x54, 0xF4, 0xA3, 0x2E};
static uint8_t Service4_Characrteristic5_Sound_Level_uuid[16]       =     {0xC8, 0x54, 0x69, 0x13, 0xBF, 0x02, 0x45, 0xEB, 0x8D, 0xDE, 0x9F, 0x87, 0x54, 0xF4, 0xA3, 0x2E};
static uint8_t Service4_Characrteristic6_Control_Point_uuid[16]     =     {0xC8, 0x54, 0x69, 0x13, 0xBF, 0x03, 0x45, 0xEB, 0x8D, 0xDE, 0x9F, 0x87, 0x54, 0xF4, 0xA3, 0x2E};

//Service 5 Power Management Service
static uint8_t Service5_Characrteristic0_Power_Source_uuid[16]      =     {0xEC, 0x61, 0xA4, 0x54, 0xED, 0x01, 0xA5, 0xE8, 0xB8, 0xF9, 0xDE, 0x9E, 0xC0, 0x26, 0xEC, 0x51};

//Service 6 IAQ Service
static uint8_t Service6_Characrteristic0_ECO2_uuid[16]              =     {0xEF, 0xD6, 0x58, 0xAE, 0xC4, 0x01, 0xEF, 0x33, 0x76, 0xE7, 0x91, 0xB0, 0x00, 0x19, 0x10, 0x3B};  
static uint8_t Service6_Characrteristic1_TVOC_uuid[16]              =     {0xEF, 0xD6, 0x58, 0xAE, 0xC4, 0x02, 0xEF, 0x33, 0x76, 0xE7, 0x91, 0xB0, 0x00, 0x19, 0x10, 0x3B};  
static uint8_t Service6_Characrteristic2_Control_Point_uuid[16]     =     {0xEF, 0xD6, 0x58, 0xAE, 0xC4, 0x03, 0xEF, 0x33, 0x76, 0xE7, 0x91, 0xB0, 0x00, 0x19, 0x10, 0x3B};  

//Service 7 UI Service
static uint8_t Service7_Characrteristic0_Buttons_uuid[16]           =     {0xFC, 0xB8, 0x9C, 0x40, 0xC6, 0x01, 0x59, 0xF3, 0x7D, 0xC3, 0x5E, 0xCE, 0x44, 0x4A, 0x40, 0x1B};
static uint8_t Service7_Characrteristic1_Leds_uuid[16]              =     {0xFC, 0xB8, 0x9C, 0x40, 0xC6, 0x02, 0x59, 0xF3, 0x7D, 0xC3, 0x5E, 0xCE, 0x44, 0x4A, 0x40, 0x1B};
static uint8_t Service7_Characrteristic2_RGB_Leds_uuid[16]          =     {0xFC, 0xB8, 0x9C, 0x40, 0xC6, 0x03, 0x59, 0xF3, 0x7D, 0xC3, 0x5E, 0xCE, 0x44, 0x4A, 0x40, 0x1B};
static uint8_t Service7_Characrteristic3_Control_Point_uuid[16]     =     {0xFC, 0xB8, 0x9C, 0x40, 0xC6, 0x04, 0x59, 0xF3, 0x7D, 0xC3, 0x5E, 0xCE, 0x44, 0x4A, 0x40, 0x1B}; 

//Service 8 Automation IO Service
static uint8_t Service8_Characrteristic0_Digital_1_uuid[16]         =     {0x00, 0x00, 0x2A, 0x56, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};
static uint8_t Service8_Characrteristic1_Digital_2_uuid[16]         =     {0x00, 0x00, 0x2A, 0x56, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};

//Service 9 IMU
static uint8_t Service9_Characrteristic0_Acceleration_uuid[16]      =     {0xC4, 0xC1, 0xF6, 0xE2, 0x4B, 0xE5, 0x11, 0xE5, 0x88, 0x5D, 0xFE, 0xFF, 0x81, 0x9C, 0xDC, 0x9F};  
static uint8_t Service9_Characrteristic1_Orientation_uuid[16]       =     {0xB7, 0xC4, 0xB6, 0x94, 0xBE, 0xE3, 0x45, 0xDD, 0xBA, 0x9F, 0xF3, 0xB5, 0xE9, 0x94, 0xF4, 0x9A};  
static uint8_t Service9_Characrteristic2_Control_Point_uuid[16]     =     {0x71, 0xE3, 0x0B, 0x8C, 0x41, 0x31, 0x47, 0x03, 0xB0, 0xA0, 0xB0, 0xBB, 0xBA, 0x75, 0x85, 0x6B};  

//Service 10=A Hall Effect Service
static uint8_t ServiceA_Characrteristic0_State_uuid[16]             =     {0xF5, 0x98, 0xDB, 0xC5, 0x2F, 0x01, 0x4E, 0xC5, 0x99, 0x36, 0xB3, 0xD1, 0xAA, 0x4F, 0x95, 0x7F};  
static uint8_t ServiceA_Characrteristic1_Field_Strength_uuid[16]    =     {0xF5, 0x98, 0xDB, 0xC5, 0x2F, 0x02, 0x4E, 0xC5, 0x99, 0x36, 0xB3, 0xD1, 0xAA, 0x4F, 0x95, 0x7F};  
static uint8_t ServiceA_Characrteristic2_Control_Point_uuid[16]     =     {0xF5, 0x98, 0xDB, 0xC5, 0x2F, 0x03, 0x4E, 0xC5, 0x99, 0x36, 0xB3, 0xD1, 0xAA, 0x4F, 0x95, 0x7F};   

//Descriptors UUID
//Caracteristics Descriptors
static uint8_t Client_Characteristic_Configuration_uuid[16]         =     {0x00, 0x00, 0x29, 0x02, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};
static uint8_t Characteristic_Presentation_Format_uuid[16]          =     {0x00, 0x00, 0x29, 0x04, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};
static uint8_t noOfDigitals_uuid[16]                                =     {0x00, 0x00, 0x29, 0x09, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB};

#endif
