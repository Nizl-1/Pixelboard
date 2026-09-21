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