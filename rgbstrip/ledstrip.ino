#include <FastLED.h>
 
#define LED_PIN 10 // Der Pin, an dem der LED-Stripe angeschlossen ist
#define NUM_LEDS 144 // Die Anzahl der LEDs in deinem Stripe
 
CRGB leds[NUM_LEDS];
 
void setup() {
 Serial.begin(9600);
 
 // Initialisiere den LED-Stripe
 FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}
 
void loop() {
 // Ändere diese Funktion nach Bedarf, um den LED-Stripe zu steuern
 rainbow();
}
 
// Beispiel: Lauflicht mit Regenbogenfarben
void rainbow() {
 static uint8_t hue = 0;
 
 fill_rainbow(leds, NUM_LEDS, hue, 7);
 FastLED.show();
 
 // Geschwindigkeit und Helligkeit anpassen
 EVERY_N_MILLISECONDS(20) { hue += 1; }
 EVERY_N_MILLISECONDS(10) { FastLED.setBrightness(100); }
}