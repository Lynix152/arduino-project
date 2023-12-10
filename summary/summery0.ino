#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <Wire.h>

#define TFT_CS    10
#define TFT_RST   9
#define TFT_DC    8

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

int centerX = 120;
int centerY = 140;
int radius = 60;

void setup() {
    Serial.begin(9600);

    tft.init(240, 280);
    tft.setRotation(1);

    tft.fillScreen(ST77XX_BLACK);
}

void loop() {
    drawClockFace();
    drawClockHands();
    delay(1000);
}

void drawClockFace() {
    tft.fillScreen(ST77XX_BLACK);
    tft.fillCircle(centerX, centerY, radius, ST77XX_WHITE);
    tft.fillCircle(centerX, centerY, 2, ST77XX_WHITE);

    for (int i = 0; i < 360; i += 30) {
        float angle = radians(i);
        int x = centerX + radius * cos(angle);
        int y = centerY + radius * sin(angle);
        tft.fillCircle(x, y, 5, ST77XX_WHITE);
    }
}

void drawClockHands() {
    int second = second() % 60;
    int minute = minute() % 60;
    int hour = hour() % 12;

    float secondAngle = map(second, 0, 60, 0, 360);
    float minuteAngle = map(minute, 0, 60, 0, 360);
    float hourAngle = map(hour, 0, 12, 0, 360) + map(minute, 0, 60, 0, 30);

    drawClockHand(centerX, centerY, radius - 10, secondAngle, ST77XX_RED);
    drawClockHand(centerX, centerY, radius - 20, minuteAngle, ST77XX_WHITE);
    drawClockHand(centerX, centerY, radius - 30, hourAngle, ST77XX_WHITE);
}

void drawClockHand(int x, int y, int length, float angle, uint16_t color) {
    int x2 = x + length * cos(radians(angle));
    int y2 = y + length * sin(radians(angle));

    tft.drawLine(x, y, x2, y2, color);
}