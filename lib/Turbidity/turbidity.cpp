#include "turbidity.h"

namespace tuk_lab{

    Turbidity::Turbidity(int sensor_pin): sensor_pin(sensor_pin){

    }

    void Turbidity::initialize(){
         //retreive last calibration value from EEPROM Address 500
        EEPROM.get(500, Vclear); 
       
        
    }

    void Turbidity::calibrate(){
        Serial.println("Put the sensor in clear water to calibrate...");


        for (int i = 0; i < number_of_samples; i++) {
            this->sensor += analogRead(sensor_pin); // read the input on analog sensor pin
            delay(10);
        }
        this->sensorValue = this->sensor / this->number_of_samples;
        this->Vclear = this->sensorValue * (5.000 / 1023.000); // Converts analog (0-1023) to turbidity_voltage (0-5V):
        this->sensor = 0;
        EEPROM.put(500, this->Vclear);  // stores Vclear in ROM
        delay(1000);
     }

     float Turbidity::get_value(){
         for (int i = 0; i < number_of_samples; i++) {
            sensor += analogRead(sensor_pin); // read the input on analog sensor pin  (turbidity sensor analog output)
            delay(10);
        }
        this->sensorValue = this->sensor / this->number_of_samples;    // average the n values
        this->turbidity_voltage = sensorValue * (5.000 / 1023.000); // Convert analog (0-1023) to turbidity_voltage (0 - 5V)

        this->turbidity = 100.00 - (this->turbidity_voltage / this->Vclear) * 100.00; // as relative percentage; 0% = clear water;

        EEPROM.put(500, this->Vclear); // guarda el voltaje de calibración actualmente en uso.


        this->sensor = 0;

        return this->turbidity;
     }
}