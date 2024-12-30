#ifndef PRBS_HPP
#define PRBS_HPP

class PRBS {
    int seed;
    int taps[4];
    int state;
    public:
        PRBS(int seed_);
        int get();
        void reset();
};

#endif