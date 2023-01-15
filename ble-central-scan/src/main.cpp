// BLE central scanner code
// Demonstrates BLE scanning on the nRF52840DK

#include <bluefruit.h>

// Function prototypes
void scan_callback(ble_gap_evt_adv_report_t* report);

// the setup function runs once when you press reset or power the board
void setup() {
  // open serial communications at 115200 baud
  Serial.begin(115200);

  // initialize Bluefruit library
  // setting maximum connections as Peripheral=0, Central=1
  Bluefruit.begin(0, 1);
  Bluefruit.setTxPower(0);
  Bluefruit.setName("CS397 Scanner");

  // start scanning
  Bluefruit.Scanner.setIntervalMS(1000, 1000); // interval=1000ms, window=1000ms
  Bluefruit.Scanner.setRxCallback(scan_callback);
  Bluefruit.Scanner.start(0);

  // print out info about the BLE state of the device
  Bluefruit.printInfo();

  Serial.println("Initialization complete!");

  // suspend Loop() to save power, since we didn't have any code there
  suspendLoop();
}

void scan_callback(ble_gap_evt_adv_report_t* report) {
  Serial.println("Timestamp Addr              Data");

  Serial.printf("%09d ", millis());
  
  // MAC is in little endian --> print reverse
  Serial.printBufferReverse(report->peer_addr.addr, 6, ':');
  Serial.print(" ");

  Serial.printBuffer(report->data.p_data, report->data.len, '-');
  Serial.println();

  // For Softdevice v6: after received a report, scanner will be paused
  // We need to call Scanner resume() to continue scanning
  Bluefruit.Scanner.resume();
}

void loop() {
  // loop is already suspended, CPU will not run loop() at all
}

