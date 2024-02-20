#include "Arduino.h"

class Rainbow {

  public:
    Rainbow(){};
    void runPattern();
  
  private:
    uint8_t hue = COLORS[i_color].h;
};

void Rainbow::runPattern() {

  EVERY_N_MILLISECONDS(rainbow_delay) {

    if (i_color == 0) {
      fill_solid(leds_front, NUM_LEDS_FRONT, COLORS[i_color]);
      fill_solid(leds_back, NUM_LEDS_BACK, COLORS[i_color]);      
    }
    else {
      hue++;
      CHSV color = CHSV(hue, 255, 255);

      fill_solid(leds_front, NUM_LEDS_FRONT, color);
      fill_solid(leds_back, NUM_LEDS_BACK, color);
    }
  
    FastLED.show();
  }

  btn1.tick();
  btn2.tick();  
}