#include <Servo.h>;

//int targetSensor[3] = []

Servo servo;
int servoPos = 0;
int count = 0;

void setup() {
  Serial.begin(9600);
  servo.attach(9);
}
void loop() {
  Serial.println(analogRead(A2));
  if(analogRead(A2) > 1000) {
    Serial.println(count++);

  }
}
void reloadTarget() {
  servoPos = 180;
  servo.write(180);
}
