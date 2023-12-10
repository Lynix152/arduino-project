//Bibliotheken zum ansteuern des Displays
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#define CS  10
#define RES  8
#define RS   9
#define SCK 13
#define SDA 11


Adafruit_ST7735 tft = Adafruit_ST7735(CS, RS, SDA, SCK, RES);


const uint16_t  Black        = 0x0000;
const uint16_t  Blue         = 0x001F;
const uint16_t  Red          = 0xF800;
const uint16_t  Green        = 0x07E0;
const uint16_t  Cyan         = 0x07FF;
const uint16_t  Magenta      = 0xF81F;
const uint16_t  Yellow       = 0xFFE0;
const uint16_t  White        = 0xFFFF;
uint16_t        Text_Color         = White;
uint16_t        Backround_Color    = Black;


void setup() {
    tft.initR(INITR_BLACKTAB);
    tft.setFont();
    //Hintergrundfarbe setzen
    tft.fillScreen(Backround_Color);
}

void loop() {
    //ein gefülltes Rechteck an den Koordinaten
    //der Uptime zeichnen um den Wert zu überschreiben
    //default Schriftart setzen
    tft.fillRect(50, 25, 60, 50, Backround_Color);
    //setzen der Textfarbe
    tft.setTextColor(Text_Color);
    //an den Koordinaten X=10, Y=10
    //die Textzeile "Hello World!" schreiben
    tft.setCursor(10, 10);
    tft.print("Hello World!");
    //an den Koordinaten X=10, Y=30
    //die Textzeile "update" schreiben
    tft.setCursor(10, 30);
}