#ifndef F1953_ATT_H
#define F1953_ATT_H

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

#endif