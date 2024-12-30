#ifndef ADF4351_SYNTH_H
#define ADF4351_SYNTH_H

class ADF4351_synth {
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

#endif