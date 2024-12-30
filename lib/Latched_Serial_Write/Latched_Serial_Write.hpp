#ifndef LATCHED_SERIAL_WRITE_HPP
#define LATCHED_SERIAL_WRITE_HPP

void latched_serial_write(int clk_io, int data_io, int latch_io, int wordlen, int data);

#endif