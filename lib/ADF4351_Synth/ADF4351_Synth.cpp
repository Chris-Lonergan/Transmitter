#ifndef ADF4351_SYNTH_CPP
#define ADF4351_SYNTH_CPP

#include <cmath>
#include <stdio.h>
#include "ADF4351_Synth.hpp"
#include "../../src/Constants.hpp"
#include "../Latched_Serial_Write/Latched_Serial_Write.hpp"

ADF4351_synth::ADF4351_synth(int clk_io_, int data_io_, int latch_io_) {
    this->clk_io = clk_io_;
    this->data_io = data_io_;
    this->latch_io = latch_io_;
    this->reset();
}

void ADF4351_synth::reset_to_old_state() {
    printf("-Resetting Synth to previous mem R0=%d, R1=%d, R2=%d, R3=%d, R4=%d, R5=%d\n", this->mem[0], this->mem[1], this->mem[2], this->mem[3], this->mem[4], this->mem[5]);
    this->write_mem(this->mem);
}

void ADF4351_synth::write_mem(int mem[6]) {
    printf("-Writing R0=%d, R1=%d, R2=%d, R3=%d, R4=%d, R5=%d to synth memory\n", this->mem[0], this->mem[1], this->mem[2], this->mem[3], this->mem[4], this->mem[5]);
    for(int i=5;i>=0;i--) {
        printf("\tWriting reg %d, with data %d\n", i, mem[i]);
        this->write_reg(i, mem[i]);
    }
}

void ADF4351_synth::write_reg(int addr, int data) {
    int word_len = 32;
    if ((data > pow(2, (word_len + 1)) - 1) | (data < 0)) {
        //invalid data
        printf("\tInvalid data, data = %d is either > %d or < 0\n", data, pow(2, (word_len + 1)) - 1);
        return;
    }
    latched_serial_write(this->clk_io, this->data_io, this->latch_io, word_len, data);
    this->mem[addr] = data;
}

void ADF4351_synth::reset() {
    std::copy(SYNTH_MEM_DEFAULT, SYNTH_MEM_DEFAULT + 6, this->mem);
    printf("-Resetting synth to default state\n");
    this->write_mem(mem);
}

#endif