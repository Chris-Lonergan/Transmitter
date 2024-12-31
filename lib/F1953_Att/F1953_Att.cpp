/**
 * @file F1953_Att.cpp
 * @author Chris Lonergan (lonerganchrisj@gmail.com)
 * @brief Implementation of F1953 Attenuator IC Class
 */

#ifndef F1935_ATT_CPP
#define F1953_ATT_CPP

#include <stdio.h>
#include "pico/stdlib.h"
#include "../../src/Constants.hpp"
#include "../Latched_Serial_Write/Latched_Serial_Write.hpp"
#include "F1953_Att.hpp"

F1953_att::F1953_att(int clk_io_, int data_io_, int latch_io_) {
    this->att_val = 0;
    this->latch_io = latch_io_;
    this->clk_io = clk_io_;
    this->data_io = data_io_;
}
void F1953_att::reset_to_old_state() {
    printf("-Resetting Att on latch pin %d to previous state %d\n", this->latch_io, this->att_val);
    this->set_atten(this->att_val);
}

void F1953_att::set_atten(int val) {
    printf("-Setting Att on latch pin %d to state %d\n", this->latch_io, val);
    latched_serial_write(this->clk_io, this->data_io, this->latch_io, ATTEN_WORD_LEN, val);
    this->att_val = val;
}

void F1953_att::reset() {
    printf("-Resetting Att on latch pin %d to default state =0\n", this->latch_io);
    this->att_val = 0;
    this->set_atten(0);
}

#endif