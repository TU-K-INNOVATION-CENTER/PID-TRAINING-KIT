#include <EEPROM.h>
#include <Arduino.h>

#include "turbidity.h"
#include "DFRobot_PH.h"

#define turbidity_sensor_pin A0
#define ph_sensor_pin A2
#define calibration_button_pin 2


tuk_lab::Turbidity turbidity_sensor(turbidity_sensor_pin);
DFRobot_PH ph;

float voltage1;
float phValue;
const float temperature = 25;

void setup() {
  //start serial port at baudrate 9600bits/sec
  Serial.begin(9600);
  ph.begin();
  turbidity_sensor.initialize();

  pinMode(calibration_button_pin, INPUT);
  digitalWrite(calibration_button_pin,HIGH);
  

}

void loop() {
    
    static unsigned long timepoint = millis();
    if (millis() - timepoint > 1000U) //time interval: 1s
    {
      timepoint = millis();
       voltage1 = analogRead(ph_sensor_pin) / 1024.0 * 5000; // read the voltage
      
       phValue = ph.readPH(voltage1, temperature); // convert voltage to pH with temperature compensation
      Serial.print("temperature:");
      Serial.print(temperature, 1);
      Serial.print("^C  pH:");
      Serial.println(phValue, 2);
    }
    ph.calibration(voltage1, temperature); // calibration process by Serail CMD

 


}