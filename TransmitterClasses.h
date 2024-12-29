#ifndef TransmitterClasses_H
#define TransmitterClasses_H

void latched_serial_write(int clk_io, int data_io, int latch_io, int wordlen, int data);
class F1953_att {
    public:
        int att_val;
        int latch_io;
        int clk_io;
        int data_io;

        F1953_att(int clk_io_, int data_io_, int latch_io_);
        void reset_to_old_state();
        void set_atten(int val);
        void reset();
};

class ADF4351_synth {;
    public:
        int latch_io;
        int clk_io;
        int data_io; 

        int mem[6];

        ADF4351_synth(int clk_io_, int data_io_, int latch_io_);
        void reset_to_old_state();
        void write_mem(int mem[6]);
        void write_reg(int addr, int data);
        void reset();
};

class PA_Chain { //also turns on switches
    public:
        int state;
        int gpio;
        
        PA_Chain(int gpio);
        void set_state(bool state);
        void reset_to_old_state();
        void reset();
};

class PRBS {
    int seed;
    int i;
    public:
        PRBS(int seed_);
        int get();
        void reset();
};

class SKY13286_sw {
    public:
        int state;
        int gpio;

        SKY13286_sw(int gpio_);
        void set_state(bool state);
        void reset_to_old_state();
        void reset();
};

class TransmitterClass {
    private:
        int bitrate;
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
        void reset_to_old_state();
        void reset();
};

#endif