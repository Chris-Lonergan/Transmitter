/**
 * @file SKY13286_Switch.cpp
 * @author Chris Lonergan (lonerganchrisj@gmail.com)
 * @brief Implementation of SKY13285 Class
 */
#ifndef SKY13286_SWITCH_CPP
#define SKY13286_SWITCH_CPP

#include <stdio.h>
#include "pico/stdlib.h"
#include "../../src/Constants.hpp"
#include "SKY13286_Switch.hpp"

SKY13286_sw::SKY13286_sw(int gpio_) {
    this->gpio = gpio_;
}

void SKY13286_sw::set_state(bool state) {
    printf("-Setting SKY Switch on gpio %d to state %d\n",this->gpio, state);
    this->state = state;
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

#endif