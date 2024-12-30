#ifndef PA_CHAIN_CPP
#define PA_CHAIN_CPP

#include <stdio.h>
#include "pico/stdlib.h"
#include "PA_Chain.hpp"

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

#endif