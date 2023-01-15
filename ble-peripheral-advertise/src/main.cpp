// BLE peripheral advertise code
// Demonstrates BLE advertisements on the nRF52840DK

#include <bluefruit.h>

// Function prototypes
void start_adv();

// the setup function runs once when you press reset or power the board
void setup() {
  // open serial communications at 115200 baud
  Serial.begin(115200);

  // Initialize Bluefruit library
  Bluefruit.begin();
  Bluefruit.setTxPower(0);

  // begin advertising
  start_adv();

  // print out info about the BLE state of the device
  Bluefruit.printInfo();

  Serial.println("Initialization complete!");

  // suspend Loop() to save power, since we didn't have any code there
  suspendLoop();
}

void start_adv() {
  // Configure what contents the advertisement includes
  Bluefruit.setName("CS397 BLE Device");
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.addTxPower();

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
     
void loop() {
  // loop is already suspended, CPU will not run loop() at all
}
