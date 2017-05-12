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

// 4 Frame Types EID/URL/TLM/UID
const uint8_t FRAME_TYPE_EDDYSTONE_UID = 0x00;
const uint8_t FRAME_TYPE_EDDYSTONE_URL = 0x10;
const uint8_t FRAME_TYPE_EDDYSTONE_TLM = 0x20;
const uint8_t FRAME_TYPE_EDDYSTONE_EID = 0x40;

// URL Scheme Prefix
const uint8_t URL_PREFIX_HTTP_WWW_DOT = 0x00;
const uint8_t URL_PREFIX_HTTPS_WWW_DOT = 0x01;
const uint8_t URL_PREFIX_HTTP_COLON_SLASH_SLASH = 0x02;
const uint8_t URL_PREFIX_HTTPS_COLON_SLASH_SLASH = 0x03;

// URL Expansion Codes (Complete list of URL expanstion codes at address below)
// https://github.com/google/eddystone/tree/master/eddystone-url
const uint8_t URL_EXPANSION_COM = 0x07;

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
    FRAME_TYPE_EDDYSTONE_URL,
    (uint8_t) TX_POWER_DBM, // Tx Power. Cast to uint8_t or you get a "warning: narrowing conversion"
    // I suppose it's doing 2s Complement conversion to convert from a negative integer to a hex value.  
    URL_PREFIX_HTTP_WWW_DOT, // http://www.
    0x72, 0x6f, 0x67, 0x75, 0x69, 0x73, 0x68, // roguish
    URL_EXPANSION_COM // .com
  };
  characteristic.writeValue( advdatacopy, sizeof(advdatacopy) );

  // start advertising
  BLE.advertise();
}

void loop() {
  // empty
}

