#define FASTLED_INTERNAL
#include <FastLED.h>

#define LED_PIN     0
#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define NUM_LEDS    3

#define BRIGHTNESS  200
#define FRAMES_PER_SECOND 20

bool gReverseDirection = false;

CRGB leds[NUM_LEDS];
uint8_t colorIndex[NUM_LEDS];
uint8_t brightness[NUM_LEDS];
uint8_t cDirection[NUM_LEDS];
uint8_t bDirection[NUM_LEDS];

CRGBPalette16 currentPalette;
TBlendType    currentBlending;


void setup() {
  delay(3000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );

  // This first palette is the basic 'black body radiation' colors,
  // which run from black to red to bright yellow to white.
  // gPal = HeatColors_p;
  
  // These are other ways to set up the color palette for the 'fire'.
  // First, a gradient from black to red to yellow to white -- similar to HeatColors_p
  currentPalette = CRGBPalette16(CRGB::Red, CRGB::Goldenrod, CRGB::Gold, CRGB::OrangeRed);
  currentBlending = LINEARBLEND; 

  for (int i = 0 ; i < NUM_LEDS; ++i) {
    colorIndex[i] = random8();
  }
  for (int i = 0 ; i < NUM_LEDS; ++i) {
    brightness[i] = random8();
  }
  for (int i = 0 ; i < NUM_LEDS; ++i) {
    cDirection[i] = random8();
  }
  for (int i = 0 ; i < NUM_LEDS; ++i) {
    bDirection[i] = random8();
  }

}

void loop()
{
  for (uint8_t i = 0; i < NUM_LEDS; ++i) {
    leds[i] = ColorFromPalette(currentPalette, colorIndex[i], brightness[i], currentBlending);

    uint8_t cChange = random8();
    if (cChange > 100) { cDirection[i] = random(8); }
    uint8_t bChange = random8();
    if (bChange > 100) { bDirection[i] = random(8); }
    
    colorIndex[i] += ((random8() / 20) * ((cDirection[i] > 128) ? 1 : -1 ));
    brightness[i] += ((random8() / 40) * ((bDirection[i] > 128) ? 1 : -1 ));
  }
  
  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}
