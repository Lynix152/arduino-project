#include <RTClib.h>
#include <Servo.h>
#include <FastLED.h>

#define LED_PIN 10 // Der Pin, an dem der LED-Stripe angeschlossen ist
#define NUM_LEDS 144 // Die Anzahl der LEDs in deinem Stripe
 
CRGB leds[NUM_LEDS];

RTC_DS3231 rtc;
Servo mechanicsServo;


char daysOfTheWeek[7][12] = {
        "Montag",
        "Dienstag",
        "Mittwoch",
        "Donnerstag",
        "Freitag",
        "Samstag",
        "Sonntag"
};

void setup () {
  Serial.begin(9600);

    // SETUP RTC MODULE
  if (! rtc.begin()) {
      Serial.println("Couldn't find RTC");
      Serial.flush();
      while (1);
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  mechanicsServo.attach(9);

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);    
}


void loop () {
    DateTime now = rtc.now();
    Serial.print("Date & Time: ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.println(now.second(), DEC);

    delay(1000); // delay 1 seconds

    ledstrip()
   

    if (now.minute() == 44) {

      for (int schlag = 0; schlag < 1; schlag = schlag + 1) {
        servoBing();
      }
    }
    

}

void rtcTimeDate() {
    DateTime now = rtc.now();
    Serial.print("Date & Time: ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.println(now.second(), DEC);
}

void servoBing() {
    mechanicsServo.write(0);
    mechanicsServo.write(50);
    mechanicsServo.write(0);
}

void rainbow() {
  static uint8_t hue = 0;
 
  fill_rainbow(leds, NUM_LEDS, hue, 7);
  FastLED.show();
 
 // Geschwindigkeit und Helligkeit anpassen
  EVERY_N_MILLISECONDS(20) { hue += 1; }
  EVERY_N_MILLISECONDS(10) { FastLED.setBrightness(100); }
}




void ledstrip() {
    // Warte bis eine volle Stunde erreicht ist
    DateTime now = rtc.now();
    DateTime nextHour = DateTime(now.year(), now.month(), now.day(), now.hour() + 1, 0, 0);

    while (rtc.now() < nextHour) {
        // other task possible
    }

    // Bestimme die Position für die LEDs basierend auf der Stunde
    int hourPosition = (now.hour() - 1) % 12;  // Subtrahiere 1, um 0-11 zu bekommen

    // Setze jede Stunde 3 LEDs auf eine Farbe, beginnend mit der vierten LED
    for (int i = 3 + hourPosition * 8; i < NUM_LEDS; i += 12) {
        leds[i] = CRGB::Red;    // Ändere die Farbe nach Bedarf
        leds[i + 1] = CRGB::Green;
        leds[i + 2] = CRGB::Blue;
    }

    FastLED.show();  // Aktualisiere den LED-Stripe
    delay(3600000);   // Warte für eine Stunde

    // Schalte die fünf LEDs zwischen den leuchtenden LEDs aus
    for (int i = 7 + hourPosition * 8; i < NUM_LEDS; i += 12) {
        leds[i] = CRGB::Black;  // Schwarz entspricht ausgeschaltet
        leds[i + 3] = CRGB::Black;
        leds[i + 4] = CRGB::Black;
        leds[i + 5] = CRGB::Black;
        leds[i + 6] = CRGB::Black;
    }

    FastLED.show();  // Aktualisiere den LED-Stripe
}