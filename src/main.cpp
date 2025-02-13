#include <Arduino.h>
#include <Wire.h>
#include <HRS3300lib.h>
#include <bluefruit.h>

// I2C read and write functions
uint8_t user_i2c_read(uint8_t addr, uint8_t reg_addr, uint8_t *reg_data, uint32_t length);
uint8_t user_i2c_write(uint8_t addr, uint8_t reg_addr, const uint8_t *reg_data, uint32_t length);

// BLE UART object
BLEUart bleuart;
int refreshTime;

// Variables to store previous data
uint8_t previousHR = 0;
int16_t previousALS = 0;

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

// Function to read and send Heart Rate and Ambient Light
void readAndSendData() {
  if (millis() - refreshTime > 40) {
    refreshTime = millis();

    // Read heart rate from the HRS3300 sensor
    uint8_t hr = HRS3300_getHR();

    // Read ambient light data
    int16_t als = Hrs3300_read_als();

    // Only process if heart rate is valid
    if (hr < 253) {
      // Check if the data has changed
      if (hr != previousHR || als != previousALS) {
        previousHR = hr;
        previousALS = als;

        // Send combined data via BLE
        bleuart.println(String(hr) + (";") + String(als) + (";"));
      }
    }
  }
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

  refreshTime = millis();  // Initialize refresh time
}

void loop() {
  readAndSendData();  // Read and send heart rate and ambient light data
}

// I2C read function for user-defined reading
uint8_t user_i2c_read(uint8_t addr, uint8_t reg_addr, uint8_t *reg_data, uint32_t length) {
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
uint8_t user_i2c_write(uint8_t addr, uint8_t reg_addr, const uint8_t *reg_data, uint32_t length) {
  Wire.beginTransmission(addr);
  Wire.write(reg_addr);
  for (int i = 0; i < length; i++) {
    Wire.write(*reg_data++);
  }
  if (Wire.endTransmission()) return -1;
  return 0;
}
