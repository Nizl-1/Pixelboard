# Overall Project: Pixelboard

## Hardware

- Joystick
- Display made from 2x (8x32 LEDs)
- DHT22

## Software

- **FreeRTOS** -> enables programming of independent, or largely independent, individual tasks as *tasks* that are processed pseudo-parallel, so that e.g. a `delay` in one task does not block the other tasks. (Similar to threads in Java.)
- Threads / Tasks

## Task Description

- Display the time from a time server
- Fetch weather data from a weather server (at least outside temperature) and display it
- Snake game
- Display data from the DHT22 and write it to a Google Sheet via WLAN

## Development Steps

### Project Structure
1. Joystick class — DONE
2. Control the display. First: text

### Libraries

- `LEDMatrix`
- `LEDText`
  -> by **Aaronliddiment**

### LED Control Notes

- Controlling the LEDs with **Adafruit NeoPixel** does NOT work with the ESP32.
- Use **FastLED** for control instead.

### Coordinate System
- X goes from 0 to 31
- Y goes from 0 to 15

We need a method that determines, for every point in the coordinate system,
which pixel on which of the two displays must be turned on.

The LEDs are controlled via **two separate data pins**, so that we can
simultaneously display text on one display and graphics on the other.

## Working Method

1. New functionality is first tested as a **standalone program**.
2. We write a FreeRTOS program where only this one functionality runs as a task.
3. This task is then integrated into the existing overall FreeRTOS program.
4. Verify: does it actually work with FreeRTOS?

## First Work Steps (without FreeRTOS)

Coordinate system with a small test program:
- A pixel moves diagonally across the screen
- Or: a scrolling text (marquee) with a counter value that increments by one every second

---

## Quick Reference Table

| Area | Detail |
|------|--------|
| Display | 2x 8x32 LED matrix -> 32x16 effective resolution |
| Coordinate system | X: 0-31, Y: 0-15 |
| LED driver | FastLED (NOT Adafruit NeoPixel on ESP32) |
| Text library | LEDMatrix / LEDText by Aaronliddiment |
| Data pins | Two separate data pins (text + graphics simultaneously) |
| RTOS | FreeRTOS (task-based pseudo-parallelism) |
| Sensors | DHT22 (temp + humidity) |
| Input | Joystick |
| Networking | WiFi (time server, weather server, Google Sheets) |

---

## Notes for Future Agents

- **Resolution:** Combined display is **32x16** — plan every app and layout around this.
- **Two data pins = two independent render targets:** One display can show text while the other shows graphics. Design the display driver with this in mind.
- **Do NOT use Adafruit NeoPixel** on ESP32 for this project — use **FastLED**.
- **Library:** `LEDMatrix` + `LEDText` by Aaronliddiment.
- **FreeRTOS structure:** Each feature (clock, weather, snake, DHT22 logger) should be its own task. Avoid blocking delays outside of `vTaskDelay`.
- **Development workflow (important):**
  1. Standalone sketch per feature
  2. Wrap feature in a single FreeRTOS task
  3. Integrate into the main program
  4. Verify FreeRTOS compatibility
- **WiFi shared by multiple tasks:** Time (NTP), weather API, and Google Sheets upload all need WiFi — build one shared WiFi/network module to avoid conflicts.
- **DHT22 polling:** Don't read faster than every 2 seconds (sensor limitation).
- **Google Sheets logging:** Requires an HTTP(S) POST to a Google Apps Script Web App or similar — plan credentials/URL handling.
- **Suggested structure:**
