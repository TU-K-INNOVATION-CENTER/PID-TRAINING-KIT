#ifndef _PH_SENSOR_
#define _PH_SENSOR_

namespace tuk_lab{

    class Ph_sensor{
        private:
            int ph_sensor_pin;
            float voltage_read;
            
            
        private:
        public:
            float ph_value;
        public:
            Ph_sensor();
            void initialize();
            void get_value(int temperature);
    };
}

#endif //_PH_SENSOR_