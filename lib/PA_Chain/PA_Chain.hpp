/**
 * @file PA_Chain.hpp
 * @author Chris Lonergan (lonerganchrisj@gmail.com)
 */

#ifndef PA_CHAIN_HPP
#define PA_CHAIN_HPP

/**
 * @brief Class that represents Power Amplifier chain, including 2x RF switches and 1x Power Amplifier
 * @details The switches share the same GPIO as the PA enable so that when the GPIO is high, the switches pass the 
 * signal through the PA and also enable the PA, but when the PA enable is low, the switches pass the signal through the 
 * 40dB pad and the PA is off.
 * 
 * @param gpio GPIO number of the pin controlling PA switches and PA enable
 */
class PA_Chain { 
    public:
        bool state;
        int gpio;
        
        PA_Chain(int gpio);
        /**
         * @brief Sets the GPIO state
         * 
         * @param state either 1 to send signal through PA path or 0 to send signal through 40dB pad path
         */
        void set_state(bool state);
        /**
         * @brief Resets the chain to this->state state, used after manual board-level state switching
         * 
         */
        void reset_to_old_state();
        /**
         * @brief Resets the chain to the default state (PA disabled)
         * 
         */
        void reset();
};

#endif