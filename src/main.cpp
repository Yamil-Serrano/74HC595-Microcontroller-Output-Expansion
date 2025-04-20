#include <Arduino.h>

// Safe pins to use with the 74HC595 shift register
const int dataPin = D2;   // GPIO4
const int clockPin = D1;  // GPIO5
const int latchPin = D5;  // GPIO14

void setup() {
  Serial.begin(115200);
  
  // Set all shift register pins as outputs
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}

void loop() {
  // Loop through all 256 possible output combinations (0 to 255 (2^8))
  for (int i = 0; i < 256; i++) {
    byte output = (byte)i;

    // Show binary value on Serial Monitor
    Serial.print("Output: ");
    for (int bit = 7; bit >= 0; bit--) {
      Serial.print(bitRead(output, bit));
    }
    Serial.println();

    // Send output to the shift register
    digitalWrite(latchPin, LOW);                  // Prepare to send data
    shiftOut(dataPin, clockPin, MSBFIRST, output); // Send the byte
    digitalWrite(latchPin, HIGH);                 // Latch the output

    delay(250); // Delay to see the change
  }
}
