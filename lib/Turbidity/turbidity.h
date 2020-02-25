#ifndef _TURBIDITY_
#define _TURBIDITY_

#define <Arduino.h>
#define <EEPROM.h>

namespace tuk_lab{

    class Turbidity{
        private:
        private:
            int sensor_pin;
            int sensorValue = 0;
            float turbidity_voltage = 0.00;
            float turbidity = 0.00;
            float Vclear = 2.85; // Output turbidity_volage to calibrate (with clear water).
            int number_of_samples = 25;
            int sensor = 0;

        public:
        public:
            Turbidity(int sensor_pin);
            void initialize();
            float get_value();
            void calibrate();

    };
}


#endif //_TURBIDITY_