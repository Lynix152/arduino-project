// integrate lib for servo
#include <Servo.h>


// define names for some components
Servo mechanicsServo;


void setup() {
  mechanicsServo.attach(9);
}

void loop() {
  mechanicsServo.write(0);
  delay(100);
  mechanicsServo.write(50);
  delay(5000);
  mechanicsServo.write(0);
}
