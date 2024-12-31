/**
 * @file F1953_Att.hpp
 * @author Chris Lonergan (lonerganchrisj@gmail.com)
 */

#ifndef F1953_ATT_H
#define F1953_ATT_H

/**
 * @brief Class to represent F1953 Attenuator. Uses lib/Latched_Serial_Write to perform memory writes
 * 
 * @param clk_io_ GPIO pin number for clock line
 * @param data_io_ GPIO pin number for data line
 * @param latch_io_ GPIO pin number for latch pin
 */
class F1953_att {
    public:
        int att_val; //Represents 6-bit attenuation state
        int latch_io;
        int clk_io;
        int data_io;
        
        F1953_att(int clk_io_, int data_io_, int latch_io_);
        /**
         * @brief Resets attenuation to this->att_val state after possible hardware switching
         */
        void reset_to_old_state();
        /**
         * @brief Sets the attenuation register to the value provided
         * @param val Integer representing attenuation (see datasheet for more details)
         */
        void set_atten(int val);
        /**
         * @brief Resets the device by writing 0b000000 to the attenuation control register
         */
        void reset();
};

#endif