#include "Arduino.h"

class Laser { 
   
  public:
    Laser(){};
    void runPattern();
  
  private:
    CHSV REFLECTION_COLORS[NUM_COLORS] = {
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

    bool blending = false;
    int delay = 30;
    
    int dh;
    int ds;
    int dv;
    CHSV current_color;
    CHSV target_color;
    
    int d = 0;
    uint8_t grey = 255;
    uint8_t target_grey = 0;

    void setDeltas();
};

void Laser::setDeltas () {

  if (i_color == 1) {
    d = ((target_color.v - current_color.v > 0) - (target_color.v - current_color.v < 0)) * 17;
    grey = current_color.v;
    target_grey = target_color.v;
  }
  else {
    dh = (target_color.h - current_color.h > 0) - (target_color.h - current_color.h < 0);
    ds = ((target_color.s - current_color.s > 0) - (target_color.s - current_color.s < 0)) * 5;
    dv = ((target_color.v - current_color.v > 0) - (target_color.v - current_color.v < 0)) * 17;
    grey = 255;
    target_grey = 0;
  }
}

void Laser::runPattern() {

  EVERY_N_MILLISECONDS(delay) {

    if(!blending) {
      if (leds_front[0] != COLORS[i_color]) {
        blending = true;
        current_color = COLORS[(i_color - 1 + NUM_COLORS) % NUM_COLORS];
        target_color = COLORS[i_color];
        setDeltas();
        dh = 1;
      }
      else if (!random8(0, 66)) {
        blending = true;
        current_color = COLORS[i_color];
        target_color = REFLECTION_COLORS[i_color];
        setDeltas();
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
        if (current_color.h != target_color.h) current_color.h += dh;
        if (current_color.s != target_color.s) current_color.s += ds;
        if (current_color.v != target_color.v) current_color.v += dv;

        fill_solid(leds_front, NUM_LEDS_FRONT, current_color);
        fill_solid(leds_back, NUM_LEDS_BACK, current_color);
      }

      FastLED.show();
      
      if (current_color == target_color || grey == target_grey) {
        if (target_color == REFLECTION_COLORS[i_color]) {
          current_color = REFLECTION_COLORS[i_color];
          target_color = COLORS[i_color];
          setDeltas();
        }
        else {
          blending = false;
          d = 0;
        }
      }
    }
  }

  btn1.tick();
  btn2.tick();  
}