#include "Arduino.h"

class ColorfulNoise {

  public:
    ColorfulNoise(){};
    void runPattern();
    
  private:
    uint8_t scale;
    uint16_t x;
    uint8_t t = random8();
};

void ColorfulNoise::runPattern() {
  
  if (i_color == 0) {
      fill_solid(leds_front, NUM_LEDS_FRONT, COLORS[i_color]);
      fill_solid(leds_back, NUM_LEDS_BACK, COLORS[i_color]);      
  }
  else { 
    scale = 15;
    x = millis() / noise_speed;
    
    for (int i = 0; i < NUM_LEDS_FRONT; i++) {
      uint8_t noise = inoise8(i * scale - x, t);
      uint8_t hue = map(noise, 50, 190, 0, 255);
      leds_front[i] = CHSV(hue, 255, 255);
    }
    
    for (int i = 0; i < NUM_LEDS_BACK; i++) {
      uint8_t noise = inoise8(i * scale - x, t);
      uint8_t hue = map(noise, 50, 190, 0, 255);
      leds_back[i] = CHSV(hue, 255, 255);
    }
  }
  
  FastLED.show();
  
  btn1.tick();
  btn2.tick();
}