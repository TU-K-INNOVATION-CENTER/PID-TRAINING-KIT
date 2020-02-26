#include <EEPROM.h>
#include <Arduino.h>

#include "turbidity.h"

#define turbidity_sensor_pin A0
#define calibration_button_pin 2


tuk_lab::Turbidity turbidity_sensor(turbidity_sensor_pin);

void setup() {
  //start serial port at baudrate 9600bits/sec
  Serial.begin(9600);
  pinMode(calibration_button_pin, INPUT);
  digitalWrite(calibration_button_pin,HIGH);
  turbidity_sensor.initialize();

}

void loop() {
  

  uint8_t calibration_push_button = digitalRead(calibration_button_pin);

 


}