#include <EEPROM.h>
#include <Arduino.h>

#include "turbidity.h"
#include "ph_sensor.h"

#define turbidity_sensor_pin A0
#define ph_sensor_pin A2
#define calibration_button_pin 2


tuk_lab::Turbidity turbidity_sensor(turbidity_sensor_pin);
tuk_lab::Ph_sensor ph_sensor(ph_sensor_pin);

const float temperature = 25;

void setup() {
  //start serial port at baudrate 9600bits/sec
  Serial.begin(9600);
  turbidity_sensor.initialize();
  ph_sensor.initialize();

  pinMode(calibration_button_pin, INPUT);
  digitalWrite(calibration_button_pin,HIGH);
  

}

void loop() {
    
    int calibration_button_status = digitalRead(calibration_button_pin);
    float turbidity_value;

    if(calibration_button_status == HIGH){ 
       turbidity_value = turbidity_sensor.get_value();
    }

    else if(calibration_button_status == LOW){
        turbidity_sensor.calibrate();
    }
    
    
    ph_sensor.get_value(temperature);
    Serial.print("Ph Value : ");
    Serial.print(ph_sensor.ph_value,2);
    Serial.print("   Turbidity : ");
    Serial.println(turbidity_value);
   

 


}