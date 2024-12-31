/**
 * @file Transmitter_Class.hpp
 * @author Chris Lonergan (lonerganchrisj@gmail.com)
 */

#ifndef TRANSMITTER_CLASS_HPP
#define TRANSMITTER_CLASS_HPP

#include "../../lib/ADF4351_Synth/ADF4351_Synth.hpp"
#include "../../lib/F1953_Att/F1953_Att.hpp"
#include "../../lib/PA_Chain/PA_Chain.hpp"
#include "../../lib/PRBS/PRBS.hpp"
#include "../../lib/SKY13286_Switch/SKY13286_Switch.hpp"
#include <vector>
#include <string>

/**
 * @brief Class to represent overall transmitter board
 * @details Contains 3 F1953 attenuators, 1 ADF4351 synthesizer/pll, 1 SKY13286 switches, 1 PA chain composed of 2 switches and a PA, and one linear feedback shift register that is purely software-based used to generate a psuedo-random bitstream 
 * 
 * @param bitrate
 */
class TransmitterClass {
    private:
        int bitrate;
        bool transmitting_prbs;
    public:
        bool state_valid;
        F1953_att* varatt1;
        F1953_att* varatt2;
        F1953_att* varatt3;
        ADF4351_synth* synth;
        SKY13286_sw* modSwitch;
        PA_Chain* PA;
        PRBS* prbs;

        TransmitterClass(int bitrate);
        /**
         * @brief Transmits a 32bit word
         * 
         * @param data 32 bit data to send
         */
        void transmit_32b(int data);
        /**
         * @brief Transmits a single bit
         * 
         * @param bit bit to send
         */
        void transmit_bit(int bit);
        /**
         * @brief Transmit a single psuedorandom bit
         * 
         */
        void transmit_prbs();
        /**
         * @brief Resets all devices to before hardware modification of states via DIP switches on board
         * 
         */
        void reset_to_old_state();
        /**
         * @brief Resets all devices to defaults
         * 
         */
        void reset();
        /**
         * @brief Transmits PRBS or does nothing depending on this->prbs setting. May be expanded in future
         * 
         */
        void run();
        /**
         * @brief Parses vector of command words and executes command
         * 
         * @details Command structure \n 
         * - att (attnum) (val) : Sets attenutator number attnum to val \n 
         * - reset att1/att2/att3/synth/pa/prbs/switch/transmitter \n 
         * - synth (regnum) (val): Sets synth mem[regnum].c_str() to int val \n 
         * - pa 1/0: sets PA chain to on or off \n 
         * - prbs get/start/stop: retusn PRBS next number \n 
         * - switch 1/0: turn mod switch on or off \n 
         * - transmit32 (int data): transmits 32bit word MSB first \n 
         * - revert: reverts to old state, only does anything if you had just switcehd to hardware control, changed things, and we now want to go back to hw control \n 
         * 
         * @param tokens Vector of command words
         */
        void handle_command(std::vector<std::string> tokens);
};

#endif