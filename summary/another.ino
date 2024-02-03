// include and import libraries

#include <Arduino.h>
#include <RTClib.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h> // Zentrale Grafikbibliothek
#include <Adafruit_ST7789.h> // Hardware-spezifische Bibliothek für ST7789
#include <SPI.h>


// define pins for some important components
#define LED_PIN 3 // define led pins
// define pins for display
#define TFT_CS 10
#define TFT_RST 8
#define TFT_DC 7
#define LED_PIN 3

// other important definitions
#define LED_COUNT    64 // Anzahl der LEDs im Streifen
#define NUM_HOURS    12 // Gesamtanzahl der Stunden
#define LEDS_PER_HOUR 7 // Anzahl der LEDs, die pro Stunde eingeschaltet werden sollen



RTC_DS3231 rtc;  // RTC
Servo mechanicsServo;  // servo
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);  // display
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); // led strip


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
void setup() {
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

    // SETUP DISPLAY
    tft.init(240, 280); // Init ST7789 280x240

    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void loop() {
    // print out dates:
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


    //---------------------------------------------------------------------------------------------------------
    // servo strikes at minute 0
    if (now.minute() == 0) {
        for (int schlag = 0; schlag < 1; schlag = schlag = schlag + 1) {
            mechanicsServo.write(0);
            mechanicsServo.write(50);
            mechanicsServo.write(0);
        }
    }

    //--------------------------------------------------------------------------------------------------------
    // program display
    tft.fillScreen(ST77XX_BLACK); // set screen background black
    tft.setTextSize(20); // bigger textsize of the text
    tft.setTextColor(ST77XX_WHITE); // set fourground color white
    tft.setCursor(10,10); // define coordinates of the text
    tft.println(now.hour(), DEC); // show hour
    tft.println(":");
    tft.println(now.minute(), DEC); // show minute
    delay(60000); // wait one minute


    //--------------------------------------------------------------------------------------------------------
    // led program

    int currentHour = now.hour() % NUM_HOURS; // Stunden von 0 bis 11

    // Berechne die Anzahl der LEDs, die pro Stunde eingeschaltet werden sollen
    int ledsToTurnOn = LEDS_PER_HOUR * (currentHour + 1);

    // Schalte die LEDs entsprechend ein
    for (int i = 0; i < LED_COUNT; i++) {
        if (i < ledsToTurnOn) {
            strip.setPixelColor(i, strip.Color(255, 0, 0)); // Rot (kann entsprechend angepasst werden)
        } else {
            strip.setPixelColor(i, strip.Color(0, 0, 0)); // Ausschalten der restlichen LEDs
        }
    }

    // Aktualisiere den LED-Streifen
    strip.show();

    delay(1000); // Verzögerung von einer Sekunde zwischen den Aktualisierungen
}



