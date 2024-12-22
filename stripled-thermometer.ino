/*
 * FastLED
 */ 
#include <FastLED.h>
#define STRIPLED_PIN 3
#define NUM_LEDS 20
CRGB leds[NUM_LEDS];

/* 
 * DHT
 */
#include <DHT.h>
#define DHT_PIN 2
DHT dht(DHT_PIN, DHT22);

/* 
 * temperature display parameters
 */
#define MIN_TEMP -5
#define MAX_TEMP 45
#define TEMP_RANGE (MAX_TEMP - MIN_TEMP)
#define TEMP_LEDS (TEMP_RANGE / NUM_LEDS)
#define TEMP_POLL_MS 1000
#define BRIGHT_SHOW 128
#define BRIGHT_HIDE 8


/* 
 * functions
 */
void setup() {
	FastLED.addLeds<NEOPIXEL, STRIPLED_PIN>(leds, NUM_LEDS);
	dht.begin();
}

void loop() {
  int mesure_led = ((dht.readTemperature() - MIN_TEMP) / TEMP_LEDS);
  for(int i = 0; i < NUM_LEDS; i++)
    leds[i] = CHSV((NUM_LEDS-i)*255/NUM_LEDS, 255, i < mesure_led ? BRIGHT_SHOW : BRIGHT_HIDE);
  FastLED.delay(TEMP_POLL_MS);
}
