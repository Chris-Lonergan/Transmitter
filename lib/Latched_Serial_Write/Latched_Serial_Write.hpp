/**
 * @file Latched_Serial_Write.hpp
 * @author Chris Lonergan (lonerganchrisj@gmail.com) 
 */

#ifndef LATCHED_SERIAL_WRITE_HPP
#define LATCHED_SERIAL_WRITE_HPP

/**
 * @brief Executes a write using the latched serial protocol
 * @details All devices that have registers on this board only require half-duplex communication where register values are programmed by 
 * the host. This is done by clocking in data of the appropriate size (where the clk's rising edge captures the state of the data line)
 * and sending the latch pin high once the correct number of data bits is sent. Data is sent MSB first
 * 
 * @param clk_io GPIO pin for clock line
 * @param data_io GPIO pin number for data line
 * @param latch_io GPIO pin number for latch io
 * @param wordlen Amount of bits to send, will append 0's to data if necessary
 * @param data Data that should be maximally (wordlen) bits long 
 */
void latched_serial_write(int clk_io, int data_io, int latch_io, int wordlen, int data);

#endif