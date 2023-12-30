// include and import libraries
#include <RTClib.h>
#include <Servo.h>
#include <FastLED.h>
#include <Adafruit_GFX.h> // Zentrale Grafikbibliothek
#include <Adafruit_ST7789.h> // Hardware-spezifische Bibliothek für ST7789
#include <SPI.h>


// define pins
#define LED_PIN 3 // Der Pin, an dem der LED-Stripe angeschlossen ist
#define NUM_LEDS 144 // Die Anzahl der LEDs in deinem Stripe
#define TFT_CS 10
#define TFT_RST 8
#define TFT_DC 7


// definitions for special components
CRGB leds[NUM_LEDS];  // LEDs
RTC_DS3231 rtc;  // RTC
Servo mechanicsServo;  // servo
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);  // display

// definitions of Days, relevant for RTC
char daysOfTheWeek[7][12] = {
        "Montag",
        "Dienstag",
        "Mittwoch",
        "Donnerstag",
        "Freitag",
        "Samstag",
        "Sonntag"
};


// ---------------------------------------------------------------------------------

// setup declaration
void setup () {
  Serial.begin(9600);  // set Arduino Uno baut rate, ESP32 Baut rate: 115200

  
  // RTC SETUP
  if (! rtc.begin()) {  // if there is no RTC connected, alarm method
      Serial.println("Couldn't find RTC");
      Serial.flush();
      while (1);
  }

  if (! rtc.lostPower()) {  // if battery of the RTC ran out of power, alarm method
    Serial.println("RTC lost power");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // adjust timedate of the RTC


  // SETUP SERVO
  mechanicsServo.attach(9); // attach servo on Pin 9

  // SETUP LEDSTRIP
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);    

  // SETUP DISPLAY
  tft.init(240, 280); // Init ST7789 280x240
  
}


void loop () {

  // print out dates
  DateTime now = rtc.now();  // set Timedate on current time
  Serial.print("Date & Time: ");
  Serial.print(now.year(), DEC); // year
  Serial.print('/');
  Serial.print(now.month(), DEC); // month
  Serial.print('/');
  Serial.print(now.day(), DEC); // day
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);  // day
  Serial.print(") ");
  Serial.print(now.hour(), DEC); // hour
  Serial.print(':');
  Serial.print(now.minute(), DEC); // minute
  Serial.print(':');
  Serial.println(now.second(), DEC); // second
  delay(1000); // delay 1 seconds

  // implement 'ledstrip' function
  ledstrip();
   
  // servo part
  if (now.minute() == 44) { // debug function right now, sually on minute now - imagine clocks in churches

    for (int schlag = 0; schlag < 1; schlag = schlag + 1) { // max. one bing, if not implemented servo would work out bing a whole minute
      servoBing(); // implementation of the 'servoBing' function
    }
  }


  tft.fillScreen(ST77XX_BLACK); // set screen background black
  tft.setTextSize(2); // bigger textsize of the text
  tft.setTextColor(ST77XX_WHITE); // set fourground color white
  tft.setCursor(10,10); // define coordinates of the text
  tft.println(now.hour(), DEC); // show hour
  tft.println(":");
  tft.println(now.minute(), DEC); // show minute
  delay(60000); // wait one minute

}


// same as above in the 'void funtion'-function
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


// ----------------------------------------------------------------

// servo function, how much the servo will move
void servoBing() {
  mechanicsServo.write(0);
  mechanicsServo.write(50);
  mechanicsServo.write(0);
}



// --------------------------------------------------------------

// rainbow function, shows moveable rainbow on the LED Strip
void rainbow() {
  static uint8_t hue = 0;
 
  fill_rainbow(leds, NUM_LEDS, hue, 7);
  FastLED.show();
 
 // Geschwindigkeit und Helligkeit anpassen
  EVERY_N_MILLISECONDS(20) { hue += 1; }
  EVERY_N_MILLISECONDS(10) { FastLED.setBrightness(100); }
}



// ------------------------------------------------------------

// shows some leds after one minute, will be hidden behind a little wall
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




