#ifndef TransmitterClasses_H
#define TransmitterClasses_H

class F1953_att {
    public:
        int att_val;
        int latch_io;

        F1953_att(int latch_io_);
        void set_to_old_state();
        void set_atten(int val);
};

class ADF4351_synth {};

class PA_Chain { //also turns on switches
    public:
        int state;
        int pa_gpio;
        
        PA_Chain(int gpio);
        void set_state(bool state);
};

class PRBS {
    int seed;
    public:
        int get(int val);
};

class SKY13286_sw {
    public:
        int state;
        int sw_gpio;

        SKY13286_sw(int gpio);
        void set_state(bool state);
};

class TransmitterClass {
    private:
        int bitrate;
    public:
        bool state_valid;
        F1953_att varatt1;
        F1953_att varatt2;
        F1953_att varatt3;
        ADF4351_synth synth;
        SKY13286_sw ModSwitch;
        PA_Chain PA;
        PRBS prbs;

        TransmitterClass(int bitrate);
        void transmit(int data);
        void transmit_bit(int bit);
        void reset_to_prev_state();
        void reset();
};

#endif