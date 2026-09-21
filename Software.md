# Software Setup Documentation

## Applications

### Snake
- Classic Snake game
- Rendered on the 8x64 LED matrix (2x Adafruit 8x32 panels)
- Controlled via **HW-504 Joystick(s)**
  - Likely: Joystick #1 for direction input
  - Button for start/pause/restart

### Uhrzeit (Clock)
- Displays current time on the LED matrix
- Requires time sync (e.g. NTP via WiFi on ESP32)
- Consider timezone handling (CET/CEST if local)

### Feuchtigkeit / Temperatur / Wetterstation
- Reads data from **DHT22** (temperature + humidity)
- Displays values on the LED matrix
- "Wetterstation" (weather station) implies possible extension:
  - Fetch weather data via WiFi (e.g. OpenWeatherMap API)
  - Combine local DHT22 readings with online forecast

---

## Quick Reference Table

| App | Input / Sensor | Output | Notes |
|-----|----------------|--------|-------|
| Snake | HW-504 Joystick | LED Matrix 8x64 | Game loop, collision detection |
| Uhrzeit | WiFi (NTP) | LED Matrix 8x64 | Timezone handling needed |
| Feuchtigkeit/Temperatur/Wetter | DHT22 (+ WiFi/API) | LED Matrix 8x64 | Local sensor + optional online weather |

---

## Notes for Future Agents

- **Shared display driver:** All three apps write to the same 8x64 LED matrix - build a common rendering layer.
- **App switching:** Consider a menu system to select between Snake / Clock / Weather, likely navigated by a joystick.
- **Joystick roles:**
  - Joystick #1 -> primary navigation / game control
  - Joystick #2 -> secondary (menu scroll, brightness, mode toggle?)
- **WiFi usage:** Required for NTP (clock) and online weather. Snake should work offline.
- **DHT22 polling:** Don't read faster than every 2 seconds (sensor limitation).
- **Suggested structure:**

text
/src
  /apps
    snake.*
    clock.*
    weather.*
  /drivers
    led_matrix.*
    dht22.*
    joystick.*
  /core
    display_manager.*
    menu.*
    wifi.*