#include <FastLED.h>
#include <LEDMatrix.h>
#include <LEDText.h>
#include <FontMatrise.h>

#define LED_PIN 25
#define COLOR_ORDER GRB
#define CHIPSET WS2812B
#define MATRIX_WIDTH 32
#define MATRIX_HEIGHT 8
#define MATRIX_TYPE HORIZONTAL_ZIGZAG_MATRIX

cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;
cLEDText scrollingMsg;

const unsigned char text[] = EFFECT_SCROLL_LEFT " PIXELBOARD  " EFFECT_SCROLL_LEFT " WILLKOMMEN ";

void setup() {
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds[0], leds.Size());
  FastLED.setBrightness(64);
  FastLED.clear(true);

  scrollingMsg.SetFont(MatriseFontData);
  scrollingMsg.Init(&leds, leds.Width(), scrollingMsg.FontHeight() + 1, 0, 0);
  scrollingMsg.SetText((unsigned char *)text, sizeof(text) - 1);
  scrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, 0x00, 0xff, 0xff);
}

void loop() {
  if (scrollingMsg.UpdateText() == -1) {
    scrollingMsg.SetText((unsigned char *)text, sizeof(text) - 1);
  } else {
    FastLED.show();
  }

  delay(10);
}
