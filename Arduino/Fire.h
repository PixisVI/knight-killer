#include "Arduino.h"

class Fire {

  public:
    Fire(){};
    void runPattern();
    void end();
  
  private:
    uint8_t dh = 5;

    CHSV SPARKS_COLORS[NUM_COLORS] = {
      CHSV(0, 255, 0),      // Black
      CHSV(0, 255, 0),      // Black
      CHSV(14, 255, 255),   // Orange
      CHSV(18, 255, 255),   // Dark Yellow
      CHSV(30, 255, 255),   // Yellow
      CHSV(64, 145, 255),   // White
      CHSV(112, 255, 255),  // Light Blue
      CHSV(130, 120, 255),  // Light Cyan
      CHSV(140, 255, 255),  // Dark Cyan
      CHSV(196, 170, 255),  // Light Purple
      CHSV(216, 170, 255)   // Light Pink
    };

    CHSV newPixel();
    bool sameColor();
};

CHSV Fire::newPixel() {
  
  CHSV color;

  if (!random8(0, 6)) {
    uint8_t hue = random8(SPARKS_COLORS[i_color].h - dh, SPARKS_COLORS[i_color].h + dh);
    color = CHSV(hue, SPARKS_COLORS[i_color].s, SPARKS_COLORS[i_color].v);
  }
  else {
    color = COLORS[i_color];
  }

  return color;
}

void Fire::runPattern() {
  
  EVERY_N_MILLISECONDS(fire_blade_delay) {
    
    for (int i = NUM_LEDS_FRONT-1; i > 0; i--) {
      leds_front[i] = leds_front[i-1];
    }
    for (int i = NUM_LEDS_BACK-1; i > 0; i--) {
      leds_back[i] = leds_back[i-1];
    }

    leds_front[0] = newPixel();
    leds_back[0] = newPixel();
    
    FastLED.show();
  }

  btn1.tick();
  btn2.tick();
}

bool Fire::sameColor() {

  bool same_color = true;

  int i = NUM_LEDS_FRONT - 1;
  while (same_color && i >= 0) {
    if (leds_front[i] != COLORS[i_color]) {
      same_color = false;
    }
    i--;
  }
  
  i = NUM_LEDS_BACK - 1;
  while (same_color && i >= 0) {
    if (leds_back[i] != COLORS[i_color]) {
      same_color = false;
    }
    i--;
  }

  return same_color;
}

void Fire::end() {
  
  while (!sameColor()) {
    
    EVERY_N_MILLISECONDS(fire_blade_delay) {
      
      for (int i = NUM_LEDS_FRONT-1; i > 0; i--) {
        leds_front[i] = leds_front[i-1];
      }
      for (int i = NUM_LEDS_BACK-1; i > 0; i--) {
        leds_back[i] = leds_back[i-1];
      }
      
      leds_front[0] = COLORS[i_color];
      leds_back[0] = COLORS[i_color];

      FastLED.show();      
    }
  }
}