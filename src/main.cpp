#include <EEPROM.h>
#include <Arduino.h>

#define turbidity_sensor_pin A0
#define calibration_button_pin 2

int sensorValue = 0;
float turbidity_volage = 0.00;
float turbidity = 0.00;
float Vclear = 2.85; // Output turbidity_volage to calibrate (with clear water).
int number_of_samples = 25;


void setup() {
 //start serial port at baudrate 9600bits/sec
 Serial.begin(9600);
 //retreive last calibration value from EEPROM Address 500
 EEPROM.get(500, Vclear); 
 //set calibration button pin to INPUT PULL UP
 pinMode(calibration_button_pin, INPUT);
 digitalWrite(calibration_button_pin,HIGH);

  
}

void loop() {

  uint8_t calibration_push_button = digitalRead(calibration_button_pin);

  int sensor = 0; //raw value read from the sensor

  if (calibration_push_button == HIGH) {
    // If the push button is not pushed, do the normal sensing routine:
    for (int i = 0; i < number_of_samples; i++) {
      sensor += analogRead(A1); // read the input on analog pin 1 (turbidity sensor analog output)
      delay(10);
    }
    sensorValue = sensor / number_of_samples;    // average the n values
    turbidity_volage = sensorValue * (5.000 / 1023.000); // Convert analog (0-1023) to turbidity_volage (0 - 5V)

   turbidity = 100.00 - (turbidity_volage / Vclear) * 100.00; // as relative percentage; 0% = clear water;

    EEPROM.put(500, Vclear); // guarda el voltaje de calibración actualmente en uso.

    Serial.print("TURBIDITY VALUE =>  ");
    Serial.print(turbidity);
    Serial.println(" %");

  }

  else{
    // Calibration routine, when push button is pushed:

    Serial.println("Put the sensor in clear water to calibrate...");


    for (int i = 0; i < number_of_samples; i++) {
      sensor += analogRead(A1); // read the input on analog pin 1:
      delay(10);
    }
    sensorValue = sensor / number_of_samples;
    Vclear = sensorValue * (5.000 / 1023.000); // Converts analog (0-1023) to turbidity_volage (0-5V):
    sensor = 0;
    EEPROM.put(500, Vclear);  // stores Vclear in ROM
    delay(1000);


  }

}