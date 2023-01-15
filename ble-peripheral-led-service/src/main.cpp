// BLE peripheral advertise code
// Demonstrates BLE advertisements on the nRF52840DK

#include <bluefruit.h>

// Function prototypes
void start_adv();
void connect_callback(uint16_t conn_handle);
void disconnect_callback(uint16_t _conn_handle, uint8_t reason);
void control_char_write_callback(uint16_t conn_hdl, BLECharacteristic* chr, uint8_t* data, uint16_t len);

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
BLEService led_service = BLEService(LED_SERVICE_UUID128);
BLECharacteristic led_data_char = BLECharacteristic(LED_CHAR_DATA_UUID128);
BLECharacteristic led_control_char = BLECharacteristic(LED_CHAR_CONTROL_UUID128);

// the setup function runs once when you press reset or power the board
void setup() {
  // open serial communications at 115200 baud
  Serial.begin(115200);

  // initialize LED3 as a GPIO output, initally off
  pinMode(PIN_LED3, OUTPUT);
  digitalWrite(PIN_LED3, HIGH); // active low

  // Initialize Bluefruit library
  Bluefruit.begin();
  Bluefruit.setTxPower(0);

  // Callbacks for connection events
  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);

  // Setup LED service
  Serial.println("Creating LED service");
  err_t error = led_service.begin();
  if (error != ERROR_NONE) {
    Serial.println("ERROR initializing LED service");
  }

  // Data characterisitic properties
  led_data_char.setProperties(CHR_PROPS_READ); // read-only
  led_data_char.setPermission(SECMODE_OPEN, SECMODE_OPEN); // no security restrictions
  led_data_char.setFixedLen(1); // one byte in size
  error = led_data_char.begin();
  if (error != ERROR_NONE) {
    Serial.println("ERROR creating data char");
  }
  led_data_char.write8(0x23); // arbitrary value

  // Control characterisitic properties
  led_control_char.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE); // read & write
  led_control_char.setPermission(SECMODE_OPEN, SECMODE_OPEN); // no security restrictions
  led_control_char.setFixedLen(1); // one byte in size
  error = led_control_char.begin();
  if (error != ERROR_NONE) {
    Serial.println("ERROR creating control char");
  }
  led_control_char.write8(0x01); // initial LED state, active low
  led_control_char.setWriteCallback(control_char_write_callback);

  // begin advertising
  start_adv();

  // print out info about the BLE state of the device
  Bluefruit.printInfo();

  Serial.println("Initialization complete!");

  // suspend Loop() to save power, since we didn't have any code there
  suspendLoop();
}

void start_adv() {
  // TODO: Determine what contents you want in the advertisement
  // Should include some kind of service UUID

  // Bluefruit stops advertising when a connection starts
  // This tells it to start advertising again when a connection terminates
  Bluefruit.Advertising.restartOnDisconnect(true);

  // Bluefruit expects advertisers to have a "fast mode" and "slow mode"
  // Fast mode starts first and goes for some amount of time then moves into slow mode indefinitely
  Bluefruit.Advertising.setIntervalMS(100, 1000);
  Bluefruit.Advertising.setFastTimeout(10); // number of seconds in fast mode

  // Begin advertising
  Bluefruit.Advertising.start(0); // 0 = Don't stop advertising after n seconds
}

void connect_callback(uint16_t conn_handle) {
  // Get the reference to current connection
  BLEConnection* connection = Bluefruit.Connection(conn_handle);

  char central_name[32] = { 0 };
  connection->getPeerName(central_name, sizeof(central_name));

  Serial.print("Connected to ");
  Serial.println(central_name);
}

void disconnect_callback(uint16_t _conn_handle, uint8_t reason) {
  Serial.print("Disconnected, reason = 0x");
  Serial.println(reason, HEX);
  Serial.println("Resuming advertising!");
}

void control_char_write_callback(uint16_t conn_hdl, BLECharacteristic* chr, uint8_t* data, uint16_t len) {
  Serial.println("Data write occurred!");
  // TODO: Control the LED here. The LED is active low.
}

void loop() {
  // loop is already suspended, CPU will not run loop() at all
}
