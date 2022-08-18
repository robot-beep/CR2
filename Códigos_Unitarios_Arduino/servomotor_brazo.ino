#include <Servo.h>

Servo servo_brazo;
uint8_t pin_servo = 9;

void setup() {
  servo_brazo.attach(pin_servo);

}

void loop() {
  servo_brazo.write(0);
  delay(2000);
  servo_brazo.write(180);
  delay(2000);

}
