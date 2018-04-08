/* 
Copyright 2017 Roguish, Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
 
#include <CurieBLE.h>

// Eddystone Protocol Specification
// https://github.com/google/eddystone/blob/master/protocol-specification.md

// Eddystone uses UUID FEAA
BLEService service = BLEService("FEAA");

// UUID FEAA also used for Characteristic
// Only BLEBroadcast is required
// Set the third param to the length of your ServiceData string (or longer). 
// If it's not long enough the Service Data will be truncated
BLECharacteristic characteristic( "FEAA", BLEBroadcast, 50 );

// 4 Frame Types EID/URL/TLM/UID for UID example only use a Frame Type UID
const uint8_t FRAME_TYPE_EDDYSTONE_UID = 0x00;
/*
const uint8_t FRAME_TYPE_EDDYSTONE_URL = 0x10;
const uint8_t FRAME_TYPE_EDDYSTONE_TLM = 0x20;
const uint8_t FRAME_TYPE_EDDYSTONE_EID = 0x40;
*/
/*
// URL Scheme Prefix for UID example dont be use
const uint8_t URL_PREFIX_HTTP_WWW_DOT = 0x00;
const uint8_t URL_PREFIX_HTTPS_WWW_DOT = 0x01;
const uint8_t URL_PREFIX_HTTP_COLON_SLASH_SLASH = 0x02;
const uint8_t URL_PREFIX_HTTPS_COLON_SLASH_SLASH = 0x03;
*/
// URL Expansion Codes (Complete list of URL expanstion codes at address below)
// https://github.com/google/eddystone/tree/master/eddystone-url
//const uint8_t URL_EXPANSION_COM = 0x07;

// Transmission Power
// Beacon Transmission Power is calibrated by measuring the rssi value at 1 meter from the beacon
// and adding 41
// https://altbeacon.github.io/android-beacon-library/eddystone-support.html
const int8_t TX_POWER_DBM = -29; // (-70 + 41);


void setup() {
  // enable if you want to log values to Serial Monitor
  // Serial.begin(9600);

  // begin initialization
  BLE.begin();

  // No not set local name 
  // BLE.setLocalName("DO_NOT_SET");

  // set service
  BLE.setAdvertisedService(service);
  
  // add the characteristic to the service
  service.addCharacteristic( characteristic );

  // add service 
  BLE.addService( service );

  // call broadcast otherwise Service Data is not included in advertisement value
  characteristic.broadcast();

  // characteristic.writeValue *after* calling characteristic.broadcast
  uint8_t advdatacopy[] =
  {
    FRAME_TYPE_EDDYSTONE_UID,
    (uint8_t) TX_POWER_DBM,
    0x50, 0xA9, 0x1D, 0x91, 0x5C, 0x01, 0x33, 0x41, 0xFA, 0x85, //NameSpace
    0x1E, 0x8D, 0xD9, 0xB0, 0x94, 0x51,  //Instance
    0x00, 0x00 //Reserved for future use, must be 0x00     
  };
  
 
  characteristic.writeValue( advdatacopy, sizeof(advdatacopy) );
  
  // start advertising
  BLE.advertise();
}

void loop() {
  // empty
}
