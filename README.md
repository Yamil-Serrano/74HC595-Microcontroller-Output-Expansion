# 74HC595-ESP8266-Output-Expansion

This project explores how to use the **74HC595 shift register** to expand the number of digital outputs available on an **ESP8266**, using just 3 GPIO pins. It’s built with **PlatformIO**, but you can also upload the same code using the **Arduino IDE**. The example includes code to control all 8 outputs by sending serial data to the shift register.


## Why I Built This?

I recently heard about the 74HC595 shift register and was curious how it could help expand the I/O capabilities of microcontrollers like the ESP8266. Since I had one of these chips lying around, I decided to try it out and learn how to communicate with it directly.

This experiment is part of my ongoing exploration into embedded systems, and it gave me a solid understanding of how to use **serial-to-parallel communication** to control more devices with fewer pins.

This repo documents my process, includes sample code, and provides diagrams and reference material for others who want to try the same.


## What You'll Learn

- What the 74HC595 does and how it works
- How to use `shiftOut()` to control outputs
- How to connect the shift register to an ESP8266
- How to send all 256 possible output combinations
- What the latch pin does and how the internal shift register works


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


## Hardware Used

- ESP8266 (NodeMCU / Wemos D1 mini)
- 74HC595 Shift Register
- Breadboard + Jumper Wires
- LEDs + Resistors (optional for testing outputs)



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



## Code Overview

The example cycles through all 256 possible byte values (0–255), showing every output state combination. Each value lights up a unique combination of output pins. The latch ensures smooth transition between states.

See `src/main.cpp` for the full code.



## Is This a Decoder or Multiplexer?

At first glance, the **74HC595** might look like a decoder or a multiplexer because it has 3 input pins and 8 output lines. But it's actually a different kind of digital IC.

The **74HC595 is a shift register**, not a decoder or mux.

Here’s a quick comparison to avoid confusion:

### Decoder vs Shift Register

| Feature                     | Decoder (e.g. 74HC138)                     | Shift Register (74HC595)                     |
|----------------------------|--------------------------------------------|----------------------------------------------|
| Inputs                     | 3 (binary selector)                        | 3 (Data, Clock, Latch)                       |
| Outputs                    | 8 (Q0 to Q7)                               | 8 (Q0 to Q7)                                 |
| Active Outputs             | Only **one at a time**                     | **Any combination** of outputs               |
| How It Works               | Selects one output line based on binary input | Loads 8 bits serially and pushes to outputs |
| Memory?                    | ❌ No memory                               | ✅ Has internal shift + latch registers      |
| Use Case                   | Device/address selection                   | Controlling multiple outputs (LEDs, etc.)    |

### ✅ 74HC595 Use Case:
With the **74HC595**, you can control any combination of the 8 output pins just by sending 8 bits of data using `shiftOut()` from your microcontroller. The `latch` pin ensures that outputs only update once you're ready, making it very stable for visual displays or multi-output devices.

### ❌ Decoder Use Case:
A decoder like the **74HC138** activates **only one output at a time** based on a binary input (e.g. input `010` activates **Q2** only). This is great for **addressing** or **selecting** one of many devices, but not for driving many outputs simultaneously.



## Diagrams

![image](https://github.com/user-attachments/assets/206d83c9-5519-4396-8ff8-48e9d6738781)

![Screenshot 2025-04-21 142857](https://github.com/user-attachments/assets/e45f2ff4-7d98-48c2-a40f-cb5ce2d4ed36)

## 74HC595 Pinout

![74x595_package-and-pinout-1024x614](https://github.com/user-attachments/assets/79349e0f-a064-4eb7-be7f-ce7c99c4bc18)


## License
This project is licensed under the MIT License – see the [LICENSE](LICENSE.md) file for details.


## Contact

If you have any questions or suggestions, feel free to reach out to me:

GitHub: [Neowizen](https://github.com/Yamil-Serrano)


