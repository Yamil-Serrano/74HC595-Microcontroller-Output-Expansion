#include <Arduino.h>

// Pins connected to the 74HC595 shift register
const int dataPin = D2;   // GPIO4 - DS
const int clockPin = D1;  // GPIO5 - SHCP
const int latchPin = D5;  // GPIO14 - STCP

// Segment values for digits 0–9 on a common cathode 7-segment display
byte numbers[10] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

void setup() {
  Serial.begin(115200);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}

// Uncomment only one of the two loops below to use it:

// --- Option A: Show all 256 output combinations on Q0–Q7 ---
// void loop() {
//   for (int i = 0; i < 256; i++) {
//     byte output = (byte)i;

//     // Print the binary pattern to serial monitor
//     Serial.print("Output: ");
//     for (int bit = 7; bit >= 0; bit--) {
//       Serial.print(bitRead(output, bit));
//     }
//     Serial.println();

//     // Send data to shift register
//     digitalWrite(latchPin, LOW);
//     shiftOut(dataPin, clockPin, MSBFIRST, output);
//     digitalWrite(latchPin, HIGH);

//     delay(250);
//   }
// }

// --- Option B: Display digits 0–9 on a 7-segment display ---
void loop() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, numbers[i]);
    digitalWrite(latchPin, HIGH);
    delay(1000);
  }
}
