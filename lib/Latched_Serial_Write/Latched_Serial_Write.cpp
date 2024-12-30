#ifndef LATCHED_SERIAL_WRITE_CPP
#define LATCHED_SERIAL_WRITE_CPP

#include "Latched_Serial_Write.hpp"
#include <stdio.h>
#include "pico/stdlib.h"
#include "../../src/Constants.hpp"

void latched_serial_write(int clk_io, int data_io, int latch_io, int wordlen, int data) {    
    for(int i=wordlen-1;i>=0;i--) {
        int bit = (data & (1 << i)) >> i;
        gpio_put(data_io, bit);
        sleep_us(SPI_DELAY);
        gpio_put(clk_io, 1);
        sleep_us(SPI_DELAY);
        gpio_put(clk_io, 0);
        sleep_us(SPI_DELAY);
    }
    gpio_put(data_io, 0);
    sleep_us(SPI_DELAY);
    gpio_put(latch_io, 1);
    sleep_us(SPI_DELAY);
    gpio_put(latch_io, 0);
}

#endif