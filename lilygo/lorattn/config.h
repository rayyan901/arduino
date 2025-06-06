#ifndef _CONFIG_H
#define _CONFIG_H

#include <RadioLib.h>

// How often to send an uplink - consider legal & FUP constraints - see notes
const uint32_t uplinkIntervalSeconds = 5UL * 60UL;    // minutes x seconds

// JoinEUI - previous versions of LoRaWAN called this AppEUI
// for development purposes you can use all zeros - see wiki for details
#define RADIOLIB_LORAWAN_JOIN_EUI  0x0000000000000000

// The Device EUI & two keys can be generated on the TTN console 
#ifndef RADIOLIB_LORAWAN_DEV_EUI   // Replace with your Device EUI
#define RADIOLIB_LORAWAN_DEV_EUI   0x70B3D57ED006F3F0  //0x70B3D57ED006B6C2
#endif
#ifndef RADIOLIB_LORAWAN_APP_KEY   // Replace with your App Key 
#define RADIOLIB_LORAWAN_APP_KEY   0xF3, 0x7E, 0x96, 0xFE, 0x1B, 0x8F, 0xE4, 0xEC, 0xDE, 0x11, 0x96, 0x6B, 0xE8, 0xD0, 0xB9, 0x06  //0x40, 0xDB, 0xFD, 0x29, 0x81, 0x63, 0xF9, 0x01, 0x98, 0x97, 0x33, 0x0D, 0x80, 0xF2, 0xC9, 0xFE //
#endif
#ifndef RADIOLIB_LORAWAN_NWK_KEY   // Put your Nwk Key here
#define RADIOLIB_LORAWAN_NWK_KEY   0x39, 0x36, 0x73, 0x79, 0x2E, 0x17, 0xD5, 0xB7, 0x79, 0x1C, 0x22, 0x03, 0x5E, 0x19, 0x3D, 0x06 //0xA6, 0x33, 0x12, 0xC3, 0xC8, 0x7F, 0x63, 0xA6, 0x93, 0x23, 0xA4, 0xEA, 0xA5, 0xD2, 0xAE, 0x6B  // 
#endif

// For the curious, the #ifndef blocks allow for automated testing &/or you can
// put your EUI & keys in to your platformio.ini - see wiki for more tips



// Regional choices: EU868, US915, AU915, AS923, IN865, KR920, CN780, CN500
const LoRaWANBand_t Region = AU915; //EU868;
const uint8_t subBand = 2;  // For US915, change this to 2, otherwise leave on 0


// ============================================================================
// Below is to support the sketch - only make changes if the notes say so ...

// Auto select MCU <-> radio connections
// If you get an error message when compiling, it may be that the 
// pinmap could not be determined - see the notes for more info

// Adafruit
#if defined(ARDUINO_SAMD_FEATHER_M0)
    #pragma message ("Adafruit Feather M0 with RFM95")
    #pragma message ("Link required on board")
    SX1276 radio = new Module(8, 3, 4, 6);


// LilyGo 
#elif defined(ARDUINO_TTGO_LORA32_V1)
  #pragma message ("TTGO LoRa32 v1 - no Display")
  SX1276 radio = new Module(18, 26, 14, 33);

#elif defined(ARDUINO_TTGO_LORA32_V2)
   #pragma error ("ARDUINO_TTGO_LORA32_V2 awaiting pin map")

#elif defined(ARDUINO_TTGO_LoRa32_v21new) // T3_V1.6.1
  #pragma message ("Using TTGO LoRa32 v2.1 marked T3_V1.6.1 + Display")
  SX1276 radio = new Module(18, 26, 23, 33); //SX1276 radio = new Module(18, 26, 14, 33);

#elif defined(ARDUINO_TBEAM_USE_RADIO_SX1262)
  #pragma error ("ARDUINO_TBEAM_USE_RADIO_SX1262 awaiting pin map")

#elif defined(ARDUINO_TBEAM_USE_RADIO_SX1276)
  #pragma message ("Using TTGO LoRa32 v2.1 marked T3_V1.6.1 + Display")
  SX1276 radio = new Module(18, 26, 23, 33);


// Heltec
#elif defined(ARDUINO_HELTEC_WIFI_LORA_32)
  #pragma error ("ARDUINO_HELTEC_WIFI_LORA_32 awaiting pin map")

#elif defined(ARDUINO_heltec_wifi_kit_32_V2)
  #pragma message ("ARDUINO_heltec_wifi_kit_32_V2 awaiting pin map")
  SX1276 radio = new Module(18, 26, 14, 35);

#elif defined(ARDUINO_heltec_wifi_kit_32_V3)
  #pragma message ("Using Heltec WiFi LoRa32 v3 - Display + USB-C")
  SX1262 radio = new Module(8, 14, 12, 13);

#elif defined(ARDUINO_CUBECELL_BOARD)
  #pragma message ("Using TTGO LoRa32 v2.1 marked T3_V1.6.1 + Display")
  SX1262 radio = new Module(RADIOLIB_BUILTIN_MODULE);

#elif defined(ARDUINO_CUBECELL_BOARD_V2)
  #pragma error ("ARDUINO_CUBECELL_BOARD_V2 awaiting pin map")


#else
  #pragma message ("Unknown board - no automagic pinmap available")

  // SX1262  pin order: Module(NSS/CS, DIO1, RESET, BUSY);
  // SX1262 radio = new Module(8, 14, 12, 13);
  SX1276 radio = new Module(18, 26, 14, 33);

  // SX1278 pin order: Module(NSS/CS, DIO0, RESET, DIO1);
  // SX1278 radio = new Module(10, 2, 9, 3);

#endif


// Copy over the EUI's & keys in to the something that will not compile if incorrectly formatted
uint64_t joinEUI =   RADIOLIB_LORAWAN_JOIN_EUI;
uint64_t devEUI  =   RADIOLIB_LORAWAN_DEV_EUI;
uint8_t appKey[] = { RADIOLIB_LORAWAN_APP_KEY };
uint8_t nwkKey[] = { RADIOLIB_LORAWAN_NWK_KEY };

// Create the LoRaWAN node
LoRaWANNode node(&radio, &Region, subBand);


// Helper function to display any issues
void debug(bool isFail, const __FlashStringHelper* message, int state, bool Freeze) {
  if (isFail) {
    Serial.print(message);
    Serial.print("(");
    Serial.print(state);
    Serial.println(")");
    while (Freeze);
  }
}

// Helper function to display a byte array
void arrayDump(uint8_t *buffer, uint16_t len) {
  for (uint16_t c = 0; c < len; c++) {
    Serial.printf("%02X", buffer[c]);
  }
  Serial.println();
}


#endif