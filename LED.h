#include "GFadeLED.h"

// How many fade effects per LED should we have?
#define QUEUE_LENGTH 20

// How many leds in your strip?
#define NUM_LEDS 10

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 25

// Define the array of leds
CRGB leds[NUM_LEDS];

uint8_t stage = 0;
uint8_t oldStage = 1; // For knowing when to draw the flash description on the screen.

void updateDisplay(void);

void addFade(uint8_t r, uint8_t g, uint8_t b, uint16_t fadeCountdown, uint16_t fadeCountup, uint16_t transitionSteps, uint8_t led) {
  FadeQueue fq;
  fq.startRGB = CRGB(0, 0, 0);
  fq.targetRGB = CRGB(r, g, b);
  fq.useStartColor = false;
  if (transitionSteps == 0) transitionSteps = 1;
  fq.fadeTransitionSteps = transitionSteps;
  fq.fadeCountdown = fadeCountdown;
  fq.fadeCountup = fadeCountup;
  fade.addFadeToQueue(fq, led);
}

void maybeAddNewFadyStage() {
  if (fade.allQueuesEmpty()) {
    // Green swish...
    if (stage == 0 || stage == 2) {
      for (int i = 0; i < 10; i++) {
        addFade(0, 255, 0, 5 + (5 * i), 0, 3, i);
        addFade(128, 255, 128, 0, 0, 1, i);
        addFade(0, 255, 0, 0, 0, 1, i);
        addFade(0, 0, 0, 0, 0, 15, i);
      }
      stage++;
      return;
    }
    // Red swish...
    if (stage == 1 || stage == 3) {
      for (int i = 0; i < 10; i++) {
        addFade(255, 0, 0, 5 + (5 * i), 0, 3, 9 - i);
        addFade(255, 128, 128, 0, 0, 1, 9 - i);
        addFade(255, 0, 0, 0, 0,  1, 9 - i);
        addFade(0, 0, 0, 0, 0, 15, 9 - i);
      }
      stage++;
      return;
    }
    // Multicoloured rug...
    if (stage == 4) {
      for (int i = 0; i < 90; i++) {
        uint8_t led = random(0, 10);
        addFade(random(0, 255), random(0, 255), random(0, 255),    random(1, 20), 0,  random(5, 20), led);
        addFade(150, 0, 0, 0, 0, 10, led);
      }
      stage++;
      return;
    }
    // Camera flashes...
    if (stage == 5) {
      for (int i = 0; i < 150; i++) {
        uint8_t led = random(0, 10);
        addFade(255, 255, 255, random(1, 50), 0, 1, led);
        addFade(0, 0, 0, 0, 0, 1, led);
      }
      stage ++;
      return;
    }
    // Police flashers...
    if (stage >= 6 && stage < 15) {
      for (int led = 0; led < 5; led++) {
        addFade(255, 0, 0, 26, 0, 1, led);
        addFade(0, 0, 0, 0, 0, 1, led);
        addFade(255, 0, 0, 7, 0, 1, led);
        addFade(0, 0, 0, 0, 0, 1, led);
      }
      for (int led = 5; led < 10; led++) {
        addFade(0, 0, 0, 13, 0, 1, led);
      }
      for (int led = 5; led < 10; led++) {
        addFade(0, 0, 255, 26, 0, 1, led);
        addFade(0, 0, 0, 0, 0, 1, led);
        addFade(0, 0, 255, 7, 0, 1, led);
        addFade(0, 0, 0, 0, 0, 1, led);
      }
      stage ++;
      return;
    }
    // Warning orange flasher
    if (stage >= 15 && stage < 19) {
      for (int i = 0; i < 10; i++) {
        addFade(255, 128, 0,   0, 0,    100, i);
        addFade(0, 0, 0,       0, 25,   1,   i);
        addFade(255, 128, 0,   0, 25,   1,   i);
        addFade(0, 0, 0,       0, 25,   1,   i);
        addFade(255, 128, 0,   0, 25,   1,   i);
        addFade(0, 0, 0,       0, 25,   1,   i);
        addFade(255, 128, 0,   0, 25,   1,   i);
        addFade(0, 0, 0,       0, 25,   1,   i);
        addFade(255, 128, 0,   0, 25,   1,   i);
        addFade(0, 0, 0,       0, 0,    100, i);
      }
      stage++;
      return;
    }
    stage = 0;
  }
}
