#ifndef TransmitterClasses
#define TransmitterClasses

#include <stdio.h>
#include "pico/stdlib.h"
#include "TransmitterClasses.h"
#include "Constants.h"
#include <algorithm>
#include <cmath>

void latched_serial_write(int clk_io, int data_io, int latch_io, int wordlen, int data) {    
    for(int i=wordlen-1;i>=0;i--) {
        int bit = (data & (1 << i)) >> i;
        printf("%d", bit);
        gpio_put(data_io, bit);
        sleep_us(SPI_DELAY);
        gpio_put(clk_io, 1);
        sleep_us(SPI_DELAY);
        gpio_put(clk_io, 0);
        sleep_us(SPI_DELAY);
    }
    printf("\n");
    gpio_put(data_io, 0);
    sleep_us(SPI_DELAY);
    gpio_put(latch_io, 1);
    sleep_us(SPI_DELAY);
    gpio_put(latch_io, 0);
}

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
    printf("-Setting Att on latch pin %d to state %d\n", this->latch_io, this->att_val);
    latched_serial_write(this->clk_io, this->data_io, this->latch_io, 6, val);
    this->att_val = val;
}

void F1953_att::reset() {
    printf("-Resetting Att on latch pin %d to default state =0\n", this->latch_io);
    this->att_val = 0;
    this->set_atten(0);
}

ADF4351_synth::ADF4351_synth(int clk_io_, int data_io_, int latch_io_) {
    std::copy(SYNTH_MEM_DEFAULT, SYNTH_MEM_DEFAULT + 6, this->mem);
    this->clk_io = clk_io_;
    this->data_io = data_io_;
    this->latch_io = latch_io_;
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

PA_Chain::PA_Chain(int gpio_) {
    gpio = gpio_;
}

void PA_Chain::set_state(bool state_) {
    printf("-Setting PA chain to state %d\n", state_);
    this->state = state_;
    gpio_put(this->gpio, state_);
}

void PA_Chain::reset_to_old_state() {
    printf("-Resetting PA chain to old state %d\n", this->state);
    this->set_state(this->state);
}

void PA_Chain::reset() {
    printf("-Resetting PA chain\n");
    this->state=0;
    this->set_state(this->state);
}


PRBS::PRBS(int seed_) {
    this->seed = seed_;
    this->i = 0;
}

int PRBS::get() {
    int gen = 1; //this based on seed
    this->i++;
    return gen;
    printf("-Getting next val form PRBS, i=%d, val=%d\n", i, gen);
}

void PRBS::reset() {
    printf("-Resetting PRBS\n");
    this->i = 0;
}


SKY13286_sw::SKY13286_sw(int gpio_) {
    this->gpio = gpio_;
}

void SKY13286_sw::set_state(bool state) {
    printf("-Setting SKY Switch to state %d\n", state);
    gpio_put(this->gpio, this->state);
}

void SKY13286_sw::reset_to_old_state() {
    printf("-Resetting SKY Switch to state %d\n", this->state);
    this->set_state(this->state);
}

void SKY13286_sw::reset() {
    printf("-Resetting SKY Switch\n");
    this->state = 1; //TODO enums
    this->set_state(this->state);
}


TransmitterClass::TransmitterClass(int bitrate_) {
    printf("-Instantiating transmitter\n");
    bitrate = bitrate_;   
    int seed = 1;
    state_valid = false;
    printf("--Creating varatt\n");
    varatt1 = new F1953_att(SPI_CLK_GPIO, SPI_MOSI_GPIO, ATT1_LE_GPIO);
    printf("--Creating varatt2\n");
    varatt2 = new F1953_att(SPI_CLK_GPIO, SPI_MOSI_GPIO, ATT2_LE_GPIO);
    printf("--Creating varatt3\n");
    varatt3 = new F1953_att(SPI_CLK_GPIO, SPI_MOSI_GPIO, ATT3_LE_GPIO);
    printf("--Creating synth\n");
    synth = new ADF4351_synth(SPI_CLK_GPIO, SPI_MOSI_GPIO, SPI_CS_GPIO);
    printf("--Creating modswitch\n");
    modSwitch = new SKY13286_sw(DATA_GPIO);
    printf("--Creating PA chain\n");
    PA = new PA_Chain(PA_EN_GPIO);
    printf("--Creating PRBS\n");
    prbs = new PRBS(seed);
    printf("-Done Instantiating Transmitter\n");
}

void TransmitterClass::transmit(int data) {
    printf("-Transmitting data\n");
    int bit;
    for(int i=5;i>=0;i--) {
        bit = (data & (1 << i)) >> i;
        this->transmit_bit(bit);
    }
}

void TransmitterClass::transmit_bit(int bit) {
    printf("--Transmitting bit %d\n", bit);
    this->modSwitch->set_state(bit);
    sleep_us(1000000 *1/this->bitrate); //This
}

void TransmitterClass::reset_to_old_state() {
    printf("-Resetting transmitter to old state\n");
    this->varatt1->reset_to_old_state();
    this->varatt1->reset_to_old_state();
    this->varatt1->reset_to_old_state();
    this->synth->reset_to_old_state();
    this->PA->reset_to_old_state();
    this->modSwitch->reset_to_old_state();
}

void TransmitterClass::reset() {
    printf("Resetting Transmitter\n");
    this->varatt1->reset();
    sleep_ms(1);
    this->varatt2->reset();
    sleep_ms(1);
    this->varatt3->reset();
    sleep_ms(1);
    this->synth->reset();
    sleep_ms(1);
    this->PA->reset();
    sleep_ms(1);
    this->modSwitch->reset();
}

#endif