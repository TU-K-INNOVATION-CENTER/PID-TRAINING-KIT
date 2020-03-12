#include <EEPROM.h>
#include <Arduino.h>

#include "turbidity.h"
#include "ph_sensor.h"

#define turbidity_sensor_pin A0
#define ph_sensor_pin A2
#define calibration_button_pin 2

#define acid_pump 5
#define base_pump 6


tuk_lab::Turbidity turbidity_sensor(turbidity_sensor_pin);
tuk_lab::Ph_sensor ph_sensor(ph_sensor_pin);

const float temperature = 25;

//--------PID variables--------------------------------------
double Kp =100;
double Ki = 60;
double Kd = 150;

double sample_period =10;
unsigned long last_time;
double total_error = 0;
double last_error = 0;
bool error_type = true; //false is negative error true is positive error
double control_signal;
double actual_ph_value = 0;
double desired_ph_value = 5.0;
double error;
//---------------------------------------------------------------------------

void pid_control() {
  unsigned long current_time = millis();
  unsigned long delta_time = current_time - last_time;

  if (delta_time >= sample_period) {
    error = desired_ph_value - actual_ph_value;
   // if((error) == 0.00) total_error = 0;
  //  else  total_error += error;
    
    if (total_error >= 255) total_error = 255;
    if (total_error <= 0) total_error = 0;

    //check if error is positive or negative;
    if (error < 0) error_type = false;
    else if (error > 0) error_type = true;
    //-------------------------------------
    double delta_error = error - last_error;
    last_error = error;


    control_signal = (Kp * error) + (Ki * total_error * sample_period) + ((Kd / sample_period) * delta_error);
    if (control_signal >= 255) control_signal = 255;
    if (control_signal <= -255) control_signal = -255;


    last_time = current_time;

  }
}

void setup() {
  //start serial port at baudrate 9600bits/sec
  Serial.begin(9600);
  turbidity_sensor.initialize();
  ph_sensor.initialize();

  pinMode(calibration_button_pin, INPUT);
  pinMode(acid_pump,OUTPUT);
  pinMode(base_pump,OUTPUT);
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
    //Serial.print("Ph Value : ");
    //Serial.print(ph_sensor.ph_value,2);
   // Serial.print("   Turbidity : ");
   // Serial.println(turbidity_value);

    actual_ph_value = ph_sensor.ph_value;
   
      pid_control();
     Serial.print(error);
      Serial.print(",");
      Serial.print(control_signal);
      Serial.print(",");
      Serial.println(actual_ph_value);

    
    if(error_type == true){ //positive error
      analogWrite(base_pump,(control_signal));
       analogWrite(acid_pump,0);
    }
    if(error_type == false){ //negative error
      analogWrite(acid_pump,(control_signal));
      analogWrite(base_pump,(0));
    }
 


}