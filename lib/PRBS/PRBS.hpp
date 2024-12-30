#ifndef PRBS_HPP
#define PRBS_HPP

class PRBS {
    int seed;
    int taps[4] = {24,23,22,17};
    int state;
    public:
        PRBS(int seed_);
        int get();
        void reset();
};

#endif