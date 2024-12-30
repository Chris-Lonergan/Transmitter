#ifndef TRANSMITTER_CLASS_HPP
#define TRANSMITTER_CLASS_HPP

#include "../../lib/ADF4351_Synth/ADF4351_Synth.hpp"
#include "../../lib/F1953_Att/F1953_Att.hpp"
#include "../../lib/PA_Chain/PA_Chain.hpp"
#include "../../lib/PRBS/PRBS.hpp"
#include "../../lib/SKY13286_Switch/SKY13286_Switch.hpp"
#include <vector>
#include <string>

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
        void transmit_32b(int data);
        void transmit_bit(int bit);
        void transmit_prbs();
        void reset_to_old_state();
        void reset();
        void run();
        void handle_command(std::vector<std::string> tokens);
};

#endif