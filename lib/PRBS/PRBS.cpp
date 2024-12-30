#ifndef PRBS_CPP
#define PRBS_CPP

#include <stdio.h>
#include "pico/stdlib.h"
#include "../../src/Constants.hpp"
#include "PRBS.hpp"

PRBS::PRBS(int seed_) {
    /**Up to 24 taps since state is at most a 24 bit int */
    this->seed = seed_ & 0b111111111111111111111111;
    this->reset();
}

int PRBS::get() {
    int feedback_bit = this->state & 1;

    for (int i=0; i<4;i++) {
        if (taps[i] != -1) {
            int val_at_tap_pos = (this->state & (1 << (24-taps[i]))) >> (24-taps[i]);
            feedback_bit = feedback_bit ^ val_at_tap_pos; 
        }
    }

    this->state = ((this->state >> 1) & 0b011111111111111111111111) | (feedback_bit << 23);
    //printf("-Getting next val form PRBS, feedback bit = %d, state=%d\n", feedback_bit, this->state);
    return this->state;
}

void PRBS::reset() {
    printf("-Resetting PRBS\n");
    this->state = this->seed;
}

#endif