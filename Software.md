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

### Jump 'n' Run
- Side-scrolling platformer
- Rendered on the 8x64 LED matrix
- Controlled via **HW-504 Joystick(s)**
  - Joystick #1: left/right movement + jump (button or up)
  - Possible: Joystick #2 for camera / secondary actions
- Core mechanics needed:
  - Gravity & jump physics
  - Platform collision
  - Scrolling camera (only 8px tall - very limited vertical space!)
  - Enemy / obstacle handling
  - Level data (likely hardcoded or from a small tilemap)
- WARNING: 8px height is extremely restrictive for a platformer. Consider:
  - Single-screen levels (no vertical scroll)
  - Auto-scroll "endless runner" style
  - 1-2 platforms max on screen at a time

### Schiffe versenken (Battleship) - Online Multiplayer
- Classic Battleship game
- **Online multiplayer** via WiFi on ESP32
- Needs:
  - WiFi connection (STA mode)
  - A server / matchmaking backend **or** direct ESP-to-ESP connection
  - Turn-based networking protocol (send/receive shots)
  - Game state sync (fleet placement, hits, misses)
- Display challenge: 8x64 matrix is too small for a full 10x10 grid
  - Options: smaller grid (e.g. 5x5), zoomed viewport, or use matrix as status/turn indicator + external display
- Input: HW-504 joystick to move cursor + place ships + fire
- WARNING - Networking choice matters:
  - **Direct P2P (ESP-NOW or raw TCP):** no server needed, but requires both players online simultaneously
  - **Backend server (MQTT / WebSocket / REST):** more flexible, supports matchmaking & turn persistence
  - Consider a simple MQTT broker for turn-based message passing

---

## Quick Reference Table

| App | Input / Sensor | Output | Notes |
|-----|----------------|--------|-------|
| Snake | HW-504 Joystick | LED Matrix 8x64 | Game loop, collision detection |
| Uhrzeit | WiFi (NTP) | LED Matrix 8x64 | Timezone handling needed |
| Feuchtigkeit/Temperatur/Wetter | DHT22 (+ WiFi/API) | LED Matrix 8x64 | Local sensor + optional online weather |
| Jump 'n' Run | HW-504 Joystick | LED Matrix 8x64 | Gravity, collision, scrolling; 8px height is tight |
| Schiffe versenken | HW-504 Joystick + WiFi | LED Matrix 8x64 | Online multiplayer; needs network protocol |

---

## Notes for Future Agents

- **Shared display driver:** All apps write to the same 8x64 LED matrix - build a common rendering layer.
- **App switching:** Consider a menu system to select between apps, navigated by a joystick.
- **Joystick roles:**
  - Joystick #1 -> primary navigation / game control
  - Joystick #2 -> secondary (menu scroll, brightness, mode toggle?)
- **WiFi usage:** Required for NTP (clock), online weather, and Schiffe versenken multiplayer. Snake and Jump 'n' Run should work offline.
- **Networking layer:** Build a reusable WiFi/network module - Schiffe versenken will need it, and it can also serve NTP + weather API calls.
- **DHT22 polling:** Don't read faster than every 2 seconds (sensor limitation).
- **8x64 constraint:** Every app must be designed around 8px height. For grid-based games (Battleship), consider scaled-down grids or viewport scrolling.
- **Suggested structure:**

/src
/apps
snake.*
clock.*
weather.*
jumpnrun.*
battleship.*
/drivers
led_matrix.*
dht22.*
joystick.*
/core
display_manager.*
menu.*
wifi.*
network.* <- shared networking (MQTT/TCP/ESP-NOW)
game_engine.* <- shared loop/collision helpers