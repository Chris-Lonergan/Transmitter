/**
 * @file SKY13286_Switch.hpp
 * @author Chris Lonergan (lonerganchrisj@gmail.com)
 */

#ifndef SKY13286_SWITCH_HPP
#define SKY13286_SWITCH_HPP

/**
 * @brief Represents SKY13286 switch used to modulate data onto the carrier wave
 * 
 * @param gpio_ GPIO pin number of the switch
 */
class SKY13286_sw {
    public:
        bool state;
        int gpio;

        SKY13286_sw(int gpio_);
        /**
         * @brief Set the gpio of the device high or low
         * 
         * @param state 
         */
        void set_state(bool state);
        /**
         * @brief Resets the device to before hardware modification via DIP switches
         * 
         */
        void reset_to_old_state();
        /**
         * @brief Resets the device to default state (switch closed)
         * 
         */
        void reset();
};

#endif
