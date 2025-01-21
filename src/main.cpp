// #include <Arduino.h>
// #include <Wire.h>
// #include "HRS3300lib.h"
// #include <bluefruit.h>

// uint8_t user_i2c_read(uint8_t addr, uint8_t reg_addr, uint8_t *reg_data, uint32_t length);
// uint8_t user_i2c_write(uint8_t addr, uint8_t reg_addr, const uint8_t *reg_data, uint32_t length);
// int refreshTime;

// void setup(void)
// {
//   delay(1000);
//   Wire.setPins(8, 7);
//   pinMode (6,OUTPUT);
//   digitalWrite(6, LOW);
//   Wire.setClock(800000U);
//   Wire.begin();
//   // Serial.begin(115200);
//   // Serial.println("HRS3300 HRS sensor test");
//   HRS3300_begin(user_i2c_read, user_i2c_write);
// }

// void loop() {
//   if (millis() - refreshTime > 40) {
//     refreshTime = millis();
    
//     uint8_t hr = HRS3300_getHR();
//     // Serial.print("HeartRate: ");
//     // Serial.println(hr);

//     uint8_t als = HRS3300_getALS();
//     // Serial.print("Ambient Light: ");
//     // Serial.println(als);

//     uint16_t hrData = Hrs3300_read_hrs();
//     // Serial.print("HeartRate Data: ");
//     // Serial.println(hrData);

//     uint16_t alsData = Hrs3300_read_als();
//     // Serial.print("Ambient Light Data: ");
//     // Serial.println(alsData);
//   }
// }

// uint8_t user_i2c_read(uint8_t addr, uint8_t reg_addr, uint8_t *reg_data, uint32_t length)
// {
//   Wire.beginTransmission(addr);
//   Wire.write(reg_addr);
//   if ( Wire.endTransmission())return -1;
//   Wire.requestFrom(addr, length);
//   for (int i = 0; i < length; i++) {
//     *reg_data++ = Wire.read();
//   }
//   return 0;
// }

// uint8_t user_i2c_write(uint8_t addr, uint8_t reg_addr, const uint8_t *reg_data, uint32_t length)
// {
//   byte error;
//   Wire.beginTransmission(addr);
//   Wire.write(reg_addr);
//   for (int i = 0; i < length; i++) {
//     Wire.write(*reg_data++);
//   }
//   if ( Wire.endTransmission())return -1;
//   return 0;
// }

// #include <Arduino.h>
// #include <Wire.h>
// #include "HRS3300lib.h"
// #include <bluefruit.h>

// uint8_t user_i2c_read(uint8_t addr, uint8_t reg_addr, uint8_t *reg_data, uint32_t length);
// uint8_t user_i2c_write(uint8_t addr, uint8_t reg_addr, const uint8_t *reg_data, uint32_t length);
// // BLE UART object
// BLEUart bleuart;
// int refreshTime;

// // Set I2C bus to use: Wire
// #define WIRE Wire

// // Function to start BLE advertising
// void startAdv(void)
// {
//   Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
//   Bluefruit.Advertising.addService(bleuart);
//   Bluefruit.ScanResponse.addName();
//   Bluefruit.Advertising.restartOnDisconnect(true);
//   Bluefruit.Advertising.setInterval(32, 244);
//   Bluefruit.Advertising.start(0);
// }

// // Function to read Heart Rate
// void readHR() {
//   if (millis() - refreshTime > 40) {
//     refreshTime = millis();

//     // Check if Bluefruit is connected before sending data
//     if (Bluefruit.connected()) {
      
//       // Read heart rate from the HRS3300 sensor
//       uint8_t hr = HRS3300_getHR();
      
//       // Handle heart rate results
//       switch (hr) {
//         case 255:
//           // No data
//           bleuart.println("NO_TOUCH");
//           break;
//         case 254:
//           // Data too short
//           bleuart.println("DATA_TOO_SHORT");
//           break;
//         case 253:
//           // Invalid data
//           bleuart.println("INVALID_DATA");
//           break;
//         default:
//           // Send heart rate data in bpm
//           bleuart.println(String(hr) + " bpm");
//           break;
//       }

//     } else {
//       // If not connected, send a message indicating the connection status
//       bleuart.println("Not connected");
//     }
//   }
// }


// // Function to read Ambient Light
// void readALS() {
//   uint8_t als = HRS3300_getALS();
  
//   // Send ambient light data
//   bleuart.println("Ambient Light: " + String(als));
// }

// void setup(void) {
//   delay(1000);
  
//   // Initialize BLE
//   Bluefruit.begin();
//   bleuart.begin();
  
//   Bluefruit.setTxPower(4);
//   Bluefruit.autoConnLed(true);
//   Bluefruit.setName("WISH_Double");
//   startAdv();

//   // Initialize Wire (I2C)
//   Wire.setPins(8, 7);  // Set SDA/SCL pins if needed
//   Wire.setClock(800000U);  // Set I2C clock speed (800kHz)
//   Wire.begin();
  
//   // Initialize HRS3300 sensor
//   HRS3300_begin(user_i2c_read, user_i2c_write);
//   HRS3300_disable();  // If the sensor needs to be disabled before reading
  
//   refreshTime = millis();  // Initialize refresh time
// }

// void loop() {
//   readHR();   // Read heart rate
//   readALS();  // Read ambient light
// }

// // I2C read function for user-defined reading
// uint8_t user_i2c_read(uint8_t addr, uint8_t reg_addr, uint8_t *reg_data, uint32_t length)
// {
//   Wire.beginTransmission(addr);
//   Wire.write(reg_addr);
//   if (Wire.endTransmission()) return -1;
//   Wire.requestFrom(addr, length);
//   for (int i = 0; i < length; i++) {
//     *reg_data++ = Wire.read();
//   }
//   return 0;
// }

// // I2C write function for user-defined writing
// uint8_t user_i2c_write(uint8_t addr, uint8_t reg_addr, const uint8_t *reg_data, uint32_t length)
// {
//   Wire.beginTransmission(addr);
//   Wire.write(reg_addr);
//   for (int i = 0; i < length; i++) {
//     Wire.write(*reg_data++);
//   }
//   if (Wire.endTransmission()) return -1;
//   return 0;
// }

#include <Arduino.h>
#include <Wire.h>
#include "HRS3300lib.h"
#include <bluefruit.h>

// I2C read and write functions
uint8_t user_i2c_read(uint8_t addr, uint8_t reg_addr, uint8_t *reg_data, uint32_t length);
uint8_t user_i2c_write(uint8_t addr, uint8_t reg_addr, const uint8_t *reg_data, uint32_t length);

// BLE UART object
BLEUart bleuart;
int refreshTime;

// Set I2C bus to use: Wire
#define WIRE Wire

// Function to start BLE advertising
void startAdv(void) {
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addService(bleuart);
  Bluefruit.ScanResponse.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);
  Bluefruit.Advertising.start(0);
}

// Function to read Heart Rate
void readHR() {
  if (millis() - refreshTime > 40) {
    refreshTime = millis();

    // Check if Bluefruit is connected before sending data
    if (Bluefruit.connected()) {
      
      // Read heart rate from the HRS3300 sensor
      uint8_t hr = HRS3300_getHR();
      
      // Handle heart rate results
      switch (hr) {
        case 255:
          // No data
          bleuart.println("NO_TOUCH");
          break;
        case 254:
          // Data too short
          bleuart.println("DATA_TOO_SHORT");
          break;
        case 253:
          // Invalid data
          bleuart.println("INVALID_DATA");
          break;
        default:
          // Enable notifications and send heart rate data in bpm
          bleuart.setNotify(true);
          bleuart.println("Heart Rate Data: " + String(hr) + " bpm");
          break;
      }

    } else {
      // If not connected, send a message indicating the connection status
      bleuart.println("Not connected");
    }
  }
}

// Function to read Ambient Light
void readALS() {
  uint8_t als = HRS3300_getALS();
  
  // Send ambient light data
  bleuart.println("Ambient Light: " + String(als));
}

void setup(void) {
  delay(1000);
  
  // Initialize BLE
  Bluefruit.begin();
  bleuart.begin();
  
  Bluefruit.setTxPower(4);
  Bluefruit.autoConnLed(true);
  Bluefruit.setName("WISH_Double");
  startAdv();

  // Initialize Wire (I2C)
  Wire.setPins(8, 7);  // Set SDA/SCL pins if needed
  Wire.setClock(800000U);  // Set I2C clock speed (800kHz)
  Wire.begin();
  
  // Initialize HRS3300 sensor
  HRS3300_begin(user_i2c_read, user_i2c_write);
  HRS3300_disable();  // If the sensor needs to be disabled before reading
  
  refreshTime = millis();  // Initialize refresh time
}

void loop() {
  readHR();   // Read heart rate
  readALS();  // Read ambient light
}

// I2C read function for user-defined reading
uint8_t user_i2c_read(uint8_t addr, uint8_t reg_addr, uint8_t *reg_data, uint32_t length)
{
  Wire.beginTransmission(addr);
  Wire.write(reg_addr);
  if (Wire.endTransmission()) return -1;
  Wire.requestFrom(addr, length);
  for (int i = 0; i < length; i++) {
    *reg_data++ = Wire.read();
  }
  return 0;
}

// I2C write function for user-defined writing
uint8_t user_i2c_write(uint8_t addr, uint8_t reg_addr, const uint8_t *reg_data, uint32_t length)
{
  Wire.beginTransmission(addr);
  Wire.write(reg_addr);
  for (int i = 0; i < length; i++) {
    Wire.write(*reg_data++);
  }
  if (Wire.endTransmission()) return -1;
  return 0;
}
