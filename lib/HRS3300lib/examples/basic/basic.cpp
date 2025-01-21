#include <Arduino.h>
#include <Wire.h>
#include "HRS3300lib.h"

int refreshTime;

void setup(void)
{
  delay(1000);
  Wire.setPins(8, 7);
  Wire.setClock(800000U);
  Wire.begin();
  Serial.begin(115200);
  Serial.println("HRS3300 HRS sensor test");
  HRS3300_begin(user_i2c_read, user_i2c_write);
}

void loop() {
  if (millis() - refreshTime > 40) {
    refreshTime = millis();
    
    uint8_t hr = HRS3300_getHR();
    Serial.print("HeartRate: ");
    Serial.println(hr);

    uint8_t als = HRS3300_getALS();
    Serial.print("Ambient Light: ");
    Serial.println(als);

    uint16_t hrData = Hrs3300_read_hrs();
    Serial.print("HeartRate Data: ");
    Serial.println(hrData);

    uint16_t alsData = Hrs3300_read_als();
    Serial.print("Ambient Light Data: ");
    Serial.println(alsData);
  }
}

uint8_t user_i2c_read(uint8_t addr, uint8_t reg_addr, uint8_t *reg_data, uint32_t length)
{
  Wire.beginTransmission(addr);
  Wire.write(reg_addr);
  if ( Wire.endTransmission())return -1;
  Wire.requestFrom(addr, length);
  for (int i = 0; i < length; i++) {
    *reg_data++ = Wire.read();
  }
  return 0;
}

uint8_t user_i2c_write(uint8_t addr, uint8_t reg_addr, const uint8_t *reg_data, uint32_t length)
{
  byte error;
  Wire.beginTransmission(addr);
  Wire.write(reg_addr);
  for (int i = 0; i < length; i++) {
    Wire.write(*reg_data++);
  }
  if ( Wire.endTransmission())return -1;
  return 0;
}