// Blink and print code
// Demonstrates basic code running on the nRF52840DK

#include <Arduino.h>

// global variable
// counts the number of times we've toggled the LED
uint32_t loop_count = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // open serial communications at 115200 baud
  Serial.begin(115200);

  // initialize first LED as a GPIO output
  pinMode(PIN_LED1, OUTPUT);

  Serial.println("Initialization complete!");
}
     
// the loop function runs over and over again forever
void loop() {
  // print loop iteration count
  Serial.println("Toggling the LED. Iteration: " + String(loop_count));
  loop_count++;

  // toggle on/off the LED
  digitalToggle(PIN_LED1);

  // wait for 1000 ms
  delay(1000);
}
