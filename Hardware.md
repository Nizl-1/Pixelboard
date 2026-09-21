# Hardware Setup Documentation

## Components

### LED Displays
- **2x Adafruit LED Matrix**
  - Dimensions: 8 (height) × 32 (length)
  - Total: 8×64 pixels (side by side)

### Microcontroller
- **ESP32** with USB Micro
  - Acts as main controller
  - USB Micro for power/programming

### Sensors
- **DHT22**
  - Temperature & humidity sensor

### Input Devices
- **2x HW-504 Joystick**
  - Analog joystick modules (X/Y + button)

---

## Quick Reference Table

| Component          | Quantity | Type/Model       | Notes                          |
|--------------------|----------|------------------|--------------------------------|
| LED Matrix         | 2        | Adafruit         | 8 high × 32 long, chained      |
| Microcontroller    | 1        | ESP32            | USB Micro connection           |
| Temp/Humidity      | 1        | DHT22            | Digital sensor                 |
| Joystick           | 2        | HW-504           | Analog X/Y + push button       |

---

## Notes for Future Agents

- Total LED resolution when combined: **64×8** (horizontal layout) or **8×64** depending on orientation
- ESP32 has limited GPIO – plan pin assignments carefully (LED data, DHT22 data, 2× joystick X/Y/button = up to 6+ pins)
- HW-504 typically outputs analog values (0–4095 on ESP32 ADC)
- DHT22 requires a pull-up resistor (usually 10kΩ) on data line
- Consider power: 64 LEDs at full brightness can draw significant current — external 5V supply may be needed



# Critical ESP32 Pins

## WiFi Restriction
When WiFi is used: the **ADC2 block** does not work:
`GPIO 25, 26, 27, 14, 12, 13, 4, 0, 2, 15`

## Unusable Pins
- **GPIO 6–11** are not usable (used internally by the flash memory)

## Input-Only Pins
- **GPIO 34–39** are input-only, no internal pull-up/pull-down resistors

## Boot Behavior
- **GPIO 0, 1, 3, 5, 14, 15** are briefly set to HIGH during boot
- **GPIO 1 and 3** must not be used (required for program upload / UART)
- **GPIO 0, 2, 4, 5, 12, 15**: if a load pulls these pins HIGH or LOW during boot, unexpected behavior can occur

## Joystick Recommendation
The ADC2 block and its associated pins are used by the WiFi module.
For the joystick, use **ADC1** pins instead, e.g.:
- **GPIO 32** -> Button
- **GPIO 34** -> X
- **GPIO 35** -> Y

## WARNING: Mislabeled Pin on Some 36-Pin Boards
On some ESP32 boards with 36 pins, the pin between "5V" and "SD3"/"GPIO 11"
is incorrectly labeled **"GND"**. The correct label is **"CMD"**.



ESP32 Pin	
14	Joystick SW
3,3 V	Joystick 5 V
GND	Joystick GND
34	Joystick X
35	Joystick Y
25	Data Pin oberes Panel
26	Data Pin unteres Panel
32	Ext. Joystick X
33	Ext. Joystick Y
27	Ext. Joystick SW
14	DHT22 Data
<img width="281" height="313" alt="grafik" src="https://github.com/user-attachments/assets/288ff612-41f2-4e92-bcc2-77c096e39d86" />
