#include "ph_sensor.h"
#include "DFRobot_PH.h"

DFRobot_PH ph;

namespace tuk_lab{
    Ph_sensor::Ph_sensor(int sensor_pin): sensor_pin(sensor_pin){

    }

    void Ph_sensor::initialize(){
        ph.begin();
    }

    void Ph_sensor::get_value(float temperature){
        static unsigned long timepoint = millis();
        if (millis() - timepoint > 1000U) //time interval: 1s
        {
            timepoint = millis();
            this->voltage_read = analogRead(this->sensor_pin) / 1024.0 * 5000; // read the voltage
            
            this->ph_value = ph.readPH(this->voltage_read, temperature); // convert voltage to pH with temperature compensation
           
        }
        ph.calibration(this->voltage_read, temperature); // calibration process by Serail CMD
       
     }
}