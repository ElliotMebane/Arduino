Using an Arduino 101 as an Eddystone Beacon.  
  
Board Manager: Curie 2.0.2  
Libary: CurieBLE 2.0.0  

Specific requirements I discovered in this version of the Curie Library:  
— Use Eddystone UUID ("FEAA") for both Service and Characteristic  
— Only BLEBroadcast property is required in second BLECharacteristic constructor parameter (omit BLERead and BLEWrite if you prefer)
— Be sure the third parameter in the BLECharacteristic constructor, valueSize, is at least as long as the Service Data array or the Service Data will be truncated
— Do not set a Local Name for the BLE. If you do it prevents the advertisement from being configured as type ServiceData.
— You must call characteristic.broadcast();
— You must call characteristic.writeValue *after* calling characteristic.broadcast

Reference:  
    
Intel's GitHub Repository for the CurieBLE library  
https://github.com/01org/corelibs-arduino101/tree/master/libraries/CurieBLE/  

Bluetooth GAP Specification (we want 0x16 for configuring the Advertisement as Service Data). This is handled by the CurieBLE library.   https://www.bluetooth.com/specifications/assigned-numbers/generic-access-profile  
  
Eddystone Protocol Specification  
https://github.com/google/eddystone/blob/master/protocol-specification.md  
  
Eddystone URL Expansion Codes  
https://github.com/google/eddystone/tree/master/eddystone-url  
  
Calculating transmission power  
https://altbeacon.github.io/android-beacon-library/eddystone-support.html  
  
Referenced some early work by @bneedhamia  
https://github.com/bneedhamia/CurieEddystoneURL
