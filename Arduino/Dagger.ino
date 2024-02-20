/*
  Dagger LED effects
  Author: Pixis
*/

#include <FastLED.h>
#include <OneButton.h>

#define NUM_LEDS_FRONT  15
#define LED_PIN_FRONT   6
#define NUM_LEDS_BACK   15
#define LED_PIN_BACK    5
#define LED_TYPE        WS2812B
#define COLOR_ORDER     GRB
#define BRIGHTNESS      100
#define NUM_PATTERNS    6
#define NUM_COLORS      11
#define BTN1_PIN        15
#define BTN2_PIN        14

CRGB leds_front[NUM_LEDS_FRONT];
CRGB leds_back[NUM_LEDS_BACK];

CHSV COLORS[NUM_COLORS] = {
  CHSV(0, 255, 0),      // Black
  CHSV(0, 0, 255),      // White
  CHSV(0, 255, 255),    // Red
  CHSV(6, 255, 255),    // Orange Red
  CHSV(14, 255, 255),   // Orange
  CHSV(64, 255, 255),   // Yellow
  CHSV(96, 255, 255),   // Green
  CHSV(130, 255, 255),  // Cyan
  CHSV(160, 255, 255),  // Blue
  CHSV(188, 255, 255),  // Purple
  CHSV(216, 255, 255)   // Pink
};

bool is_running = false;
uint8_t i_pattern = 2;

uint8_t i_color = 3;

uint8_t fire_blade_delay = 60;
uint8_t rainbow_delay = 50;
uint8_t noise_speed = 20;

OneButton btn1 = OneButton(BTN1_PIN, true, true);
OneButton btn2 = OneButton(BTN2_PIN, true, true);

#include "Fire.h"
#include "Laser.h"
#include "Static.h"
#include "Rainbow.h"
#include "ColorfulNoise.h"
#include "Blade.h"

void setup() {
  delay(500);
  
  FastLED.addLeds<LED_TYPE, LED_PIN_FRONT, COLOR_ORDER>(leds_front, NUM_LEDS_FRONT);
  FastLED.addLeds<LED_TYPE, LED_PIN_BACK, COLOR_ORDER>(leds_back, NUM_LEDS_BACK);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.setCorrection(TypicalLEDStrip);
  
  fill_solid(leds_front, NUM_LEDS_FRONT, CRGB::Black);
  fill_solid(leds_back, NUM_LEDS_BACK, CRGB::Black);
  FastLED.show();
  
  btn1.attachClick(changePattern);
  btn2.attachClick(changeColor);
  btn2.attachDoubleClick(changeSpeed);
}

void loop() {
  
  switch (i_pattern) {
    case 0:
      runFire();
      break;

    case 1:
      runLaser();
      break;

    case 2:
      runStatic();
      break;
    
    case 3:
      runRainbow();
      break;
    
    case 4:
      runColorfulNoise();
      break;
      
    case 5:
      runBlade();
      break;      
  }
}

void runFire() {
  is_running = true;
  Fire fire = Fire();
  while(is_running) fire.runPattern();
  fire.end();
}

void runLaser() {
  is_running = true;
  Laser laser = Laser();
  fill_solid(leds_front, NUM_LEDS_FRONT, COLORS[i_color]);
  fill_solid(leds_back, NUM_LEDS_BACK, COLORS[i_color]);
  FastLED.show();
  while(is_running) laser.runPattern();  
}

void runStatic() {
  is_running = true;
  Static static_ = Static();
  fill_solid(leds_front, NUM_LEDS_FRONT, COLORS[i_color]);
  fill_solid(leds_back, NUM_LEDS_BACK, COLORS[i_color]);
  FastLED.show();
  while(is_running) static_.runPattern();
}

void runRainbow() {
  is_running = true;
  Rainbow rainbow = Rainbow();
  while(is_running) rainbow.runPattern();  
}

void runColorfulNoise() {
  is_running = true;
  ColorfulNoise colorfulNoise = ColorfulNoise();
  while(is_running) colorfulNoise.runPattern();  
}

void runBlade() {
  is_running = true;
  Blade blade = Blade();
  while(is_running) blade.runPattern();  
}

void changePattern() {
  is_running = false;
  i_pattern = (i_pattern + 1) % NUM_PATTERNS;
}

void changeColor() {
  i_color = (i_color + 1) % NUM_COLORS;
}

void changeSpeed() {
  fire_blade_delay -= 5;
  if (fire_blade_delay < 45) {
    fire_blade_delay = 60;
  }  

  rainbow_delay -= 10;
  if (rainbow_delay < 20) {
    rainbow_delay = 50;
  }

  noise_speed -= 5;
  if (noise_speed < 5) {
    noise_speed = 20;
  }
}
