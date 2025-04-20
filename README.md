# 74HC595-ESP8266-Output-Expansion

This project explores how to use the **74HC595 shift register** to expand the number of digital outputs available on an **ESP8266**, using just 3 GPIO pins. It’s built with **PlatformIO**, but you can also upload the same code using the **Arduino IDE**. The example includes code to control all 8 outputs by sending serial data to the shift register.

---

## Why I Built This?

I recently heard about the 74HC595 shift register and was curious how it could help expand the I/O capabilities of microcontrollers like the ESP8266. Since I had one of these chips lying around, I decided to try it out and learn how to communicate with it directly.

This experiment is part of my ongoing exploration into embedded systems, and it gave me a solid understanding of how to use **serial-to-parallel communication** to control more devices with fewer pins.

This repo documents my process, includes sample code, and provides diagrams and reference material for others who want to try the same.

---

## What You'll Learn

- What the 74HC595 does and how it works
- How to use `shiftOut()` to control outputs
- How to connect the shift register to an ESP8266
- How to send all 256 possible output combinations
- What the latch pin does and how the internal shift register works

---

## How It Works (Shift Register Logic)

The 74HC595 contains two key internal components:

- A **Shift Register (SR)**: where bits are shifted in serially via the `DS` (data) and `SHCP` (clock) pins.
- A **Storage Register (Latch)**: where the bits are copied to when you toggle the `STCP` (latch) pin high.

Here’s what happens in sequence:

1. You call `shiftOut(dataPin, clockPin, MSBFIRST, byteValue);`  
   → This pushes 8 bits (a full byte) into the **shift register**, bit by bit.

2. While the latch pin (`STCP`) is LOW, the output pins (Q0–Q7) don’t change yet.  
   → Think of it like writing to a **buffer**.

3. Once you set the latch pin HIGH, all 8 bits are **copied** from the shift register to the **output storage register**.  
   → This updates all Q0–Q7 simultaneously.

4. You can repeat this process anytime to send new data.

 So the shift register acts like an **internal stack**, constantly being overwritten every time you call `shiftOut()`. The latch ensures outputs only update *when you say so*.

---

## Hardware Used

- ESP8266 (NodeMCU / Wemos D1 mini)
- 74HC595 Shift Register
- Breadboard + Jumper Wires
- LEDs + Resistors (optional for testing outputs)

---

## Wiring Table

| 74HC595 Pin | Connected To (ESP8266) | Purpose        |
|-------------|-------------------------|----------------|
| DS (14)     | D2 (GPIO4)              | Data           |
| SHCP (11)   | D1 (GPIO5)              | Clock          |
| STCP (12)   | D5 (GPIO14)             | Latch          |
| GND         | GND                     | Ground         |
| VCC         | 3.3V or 5V              | Power Supply   |
| Q0–Q7       | Output Pins             | LED/Device     |

> ⚠️ Use level shifting if powering the chip with 5V while using a 3.3V microcontroller.

---

## Code Overview

The example cycles through all 256 possible byte values (0–255), showing every output state combination. Each value lights up a unique combination of output pins. The latch ensures smooth transition between states.

See `src/main.cpp` for the full code.

---

## Diagrams

_(Coming soon — feel free to add your own schematic or breadboard image here!)_

---

## 74HC595 Pinout

_(Coming soon — can include a labeled diagram or table here.)_

---

## PlatformIO or Arduino IDE

You can build and upload this project using either PlatformIO or Arduino IDE.
