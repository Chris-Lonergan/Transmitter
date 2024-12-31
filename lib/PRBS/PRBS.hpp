/**
 * @file PRBS.hpp
 * @author Chris Lonergan (lonerganchrisj@gmail.com)
 */

#ifndef PRBS_HPP
#define PRBS_HPP

/**
 * @brief Class to represent a 24bit Fibonacci Linear Feedback Shift Register used to generate a pseudo-random bitstream 
 * 
 * @param seed_ Represents the starting value of the 24bit LFSR
 */
class PRBS {
    int seed;
    int taps[4]; //Represent the polynomial coefficients used to generate feedback bit
    int state; //24bit value represents the current state of the LFSR
    public:
        PRBS(int seed_);
        /**
         * @brief Progresses the LFSR forward one iteration and returns the current state
         * 
         * @return int The current state
         */
        int get();
        /**
         * @brief Resets the LFSR by setting state back to the initial seed value
         * 
         */
        void reset();
};

#endif