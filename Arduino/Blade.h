#include "Arduino.h"

class Blade {

  public:
    Blade(){};
    void runPattern();
  
  private:
    int dv = -36;

    CHSV current_color = COLORS[i_color];
};

void Blade::runPattern() {
  
  EVERY_N_MILLISECONDS(fire_blade_delay) {
    
    for (int i = NUM_LEDS_FRONT-1; i > 0; i--) {
      leds_front[i] = leds_front[i-1];
    }
    for (int i = NUM_LEDS_BACK-1; i > 0; i--) {
      leds_back[i] = leds_back[i-1];
    }
    
    if (COLORS[i_color].v == 0) {
      current_color.v = 0;
    }
    else {
      if (current_color.v + dv > 255) {
        current_color.v = 255;
      }
      else if (current_color.v + dv < 0) {
        current_color.v = 0;
      }
      else {
        current_color.v += dv;
      }

      if (current_color.v == 0 || current_color.v == 255) {
        dv = -dv;
      }
    }

    if (current_color.h != COLORS[i_color].h) {
      current_color.h = COLORS[i_color].h;      
    }
    if (current_color.s != COLORS[i_color].s) {
      current_color.s = COLORS[i_color].s;      
    }

    leds_front[0] = current_color;
    leds_back[0] = current_color;
    
    FastLED.show();
  }

  btn1.tick();
  btn2.tick();
}
