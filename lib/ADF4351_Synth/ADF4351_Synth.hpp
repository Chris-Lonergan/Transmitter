/**
 * @file ADF4351_Synth.hpp
 * @author Chris Lonergan (lonerganchrisj@gmail.com)
 * @brief Representation of ADF4351 Synthesizer/PLL 
 */

#ifndef ADF4351_SYNTH_H
#define ADF4351_SYNTH_H

/**
 * @brief Representation of ADF4351 Synthesizer/PLL
 * 
 * @details This device is controlled through a 6-register 32bit memory which is written to using the Latched_Serial_Write.hpp protocol.
 *  For details on register map, see doc/synthregmap.xlsx
 * 
 * @param clk_io_ GPIO pin number of the clock line for this device
 * @param data_io_ GPIO pin number of the data line for this device
 * @param latch_io_ GPIO pin number of the latch pin for this device
 */
class ADF4351_synth {
    public:
        int latch_io;
        int clk_io;
        int data_io; 

        int mem[6];

        ADF4351_synth(int clk_io_, int data_io_, int latch_io_);
        /**
         * @brief Resets the device to before board level intervention by writing the current values within the class back into memory
         */
        void reset_to_old_state();
        /**
         * @brief Writes array of register values into memory
         * 
         * @param mem[6]: Should be of form {reg0 value, reg1 value, reg2 value, reg3 value, reg4 value, reg5 value}
         */
        void write_mem(int mem[6]);
        /**
         * @brief Function to write a value into a specific register
         * 
         * @param addr: Register number (0-5)
         * @param data: 32bit int 
         */
        void write_reg(int addr, int data);
        /**
         * @brief Resets the device by writing the default values back into memory
         * 
         */
        void reset();
};

#endif