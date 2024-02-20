#include "Arduino.h"

class Static {
  
  public:
    Static(){};
    void runPattern();    
  
  private:
    bool changing_color = false;
    int delay = 30;

    int dh;
    int dv;
    int ds;
    CHSV current_color;
    
    int d = 0;
    uint8_t grey = 255;
    uint8_t target_grey = 0;
};

void Static::runPattern() {

  EVERY_N_MILLISECONDS(delay) {
    
    if(!changing_color) {
      if (leds_front[0] != COLORS[i_color]) {
        changing_color = true;
        current_color = COLORS[(i_color - 1 + NUM_COLORS) % NUM_COLORS];
        if (i_color == 1) {
          d = ((COLORS[i_color].v - current_color.v > 0) - (COLORS[i_color].v - current_color.v < 0)) * 17;
          grey = current_color.v;
          target_grey = COLORS[i_color].v;
        }  
        else {
          dh = 1;
          ds = ((COLORS[i_color].s - current_color.s > 0) - (COLORS[i_color].s - current_color.s < 0)) * 17;
          dv = ((COLORS[i_color].v - current_color.v > 0) - (COLORS[i_color].v - current_color.v < 0)) * 17;
          grey = 255;
          target_grey = 0;
        }
      }
    }
    else {
      if (d != 0) {
        grey += d;
        CRGB color = CRGB(grey, grey, grey);
        
        fill_solid(leds_front, NUM_LEDS_FRONT, color);
        fill_solid(leds_back, NUM_LEDS_BACK, color);
      }
      else {
        if (current_color.h != COLORS[i_color].h) current_color.h += dh;
        if (current_color.v != COLORS[i_color].v) current_color.v += dv;
        if (current_color.s != COLORS[i_color].s) current_color.s += ds;

        fill_solid(leds_front, NUM_LEDS_FRONT, current_color);
        fill_solid(leds_back, NUM_LEDS_BACK, current_color);        
      }
      
      
      if (current_color == COLORS[i_color] || grey == target_grey) {
        changing_color = false;
        d = 0;
      }

      FastLED.show();
    }
  }
  
  btn1.tick();
  btn2.tick();
}