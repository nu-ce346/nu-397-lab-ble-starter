// BLE central scanner code
// Demonstrates BLE scanning on the nRF52840DK

#include <bluefruit.h>

// Custom LED service
// Base UUID: 32E6xxxx-2B22-4DB5-A914-43CE51986C70
//
// Service 16-bit UUID: 0900
// Characteristics:
//    0901 - Data
//    0902 - Control
const uint8_t LED_SERVICE_UUID128[16] = {
  0x70, 0x6C, 0x98, 0x41, 0xCE, 0x43, 0x14, 0xA9,
  0xB5, 0x4D, 0x22, 0x2B, 0x00, 0x09, 0xE6, 0x32
};
const uint8_t LED_CHAR_DATA_UUID128[16] = {
  0x70, 0x6C, 0x98, 0x41, 0xCE, 0x43, 0x14, 0xA9,
  0xB5, 0x4D, 0x22, 0x2B, 0x01, 0x09, 0xE6, 0x32
};
const uint8_t LED_CHAR_CONTROL_UUID128[16] = {
  0x70, 0x6C, 0x98, 0x41, 0xCE, 0x43, 0x14, 0xA9,
  0xB5, 0x4D, 0x22, 0x2B, 0x02, 0x09, 0xE6, 0x32
};
// Note that these are the CLIENT version now
BLEClientService led_service = BLEClientService(LED_SERVICE_UUID128);
BLEClientCharacteristic led_data_char = BLEClientCharacteristic(LED_CHAR_DATA_UUID128);
BLEClientCharacteristic led_control_char = BLEClientCharacteristic(LED_CHAR_CONTROL_UUID128);


// the setup function runs once when you press reset or power the board
void setup() {
  // open serial communications at 115200 baud
  Serial.begin(115200);

  // TODO: implement everything here

  Serial.println("Initialization complete!");

  // suspend Loop() to save power, since we didn't have any code there
  suspendLoop();
}

// TODO: you're definitely going to need some callback functions

void loop() {
  // loop is already suspended, CPU will not run loop() at all
}

