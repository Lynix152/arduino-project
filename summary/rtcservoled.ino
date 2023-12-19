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

    servoBing();
   

    if (now.minute() == 44) {
      rainbow();

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
