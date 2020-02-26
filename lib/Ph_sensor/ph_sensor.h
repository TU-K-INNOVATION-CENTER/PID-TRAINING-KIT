#ifndef _PH_SENSOR_
#define _PH_SENSOR_

#include <Arduino.h>

namespace tuk_lab{

    class Ph_sensor{
        private:
            int sensor_pin;
            float voltage_read;
            
            
        private:
        public:
            float ph_value;
        public:
            Ph_sensor(int sensor_pin);
            void initialize();
            void get_value(float temperature);
    };
}

#endif //_PH_SENSOR_