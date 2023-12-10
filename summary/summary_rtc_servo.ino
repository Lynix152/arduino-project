#include <RTClib.h>
#include <Servo.h>

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

    char now.minute() = minute;
    char now.hour()   = hour;

    // soll jede Viertelstunde bing machen
    if (now.minute() == 15) {
        servoBing();
    }

    if (now.minute() == 30) {
        servoBing();
    }

    if (now.minute() == 45) {
        servoBing();
    }


    // soll jede Stunde Bing machen, kommt drauf an, wie viel Uhr es ist
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

void recognizeHour() {

}