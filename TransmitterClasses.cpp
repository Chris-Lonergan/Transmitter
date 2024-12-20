#ifndef TransmitterClasses
#define TransmitterClasses

#include "Constants.h"
#include "TransmitterClasses.h"

class F1953_att {
    public:
        att_val = 0;
        F1953_att(latch_io_) {
            latch_io = latch_io_;
        }
        void set_to_old_state() {
            this.set_atten(this.att_val);
        }
        
        void set_atten(int val) {
            //print('setting atten on gpio '' to val)
            std::bitset bitset = std::bitset<6>(val);
            for(int i=5,i>=0;i--) {
                bit = (bitset & (1 << i)) >> i;

                gpio_put(CLK_GPIO, 1);
                sleep_ms(0.1);
                gpio_put(DATA_GPIO, bit);
                sleep_ms(0.1);
                gpio_put(CLK_GPIO, 0);
                sleep_ms(0.1);
            gpio_put(latch_io, 1);
            sleep_ms(0.1);
            gpio_put(latch_io, 0);
            }
        }
}

class ADF4351_synth {

}

class PA_Chain { //also turns on switches
    public:
        state=1;
        
        PA_Chain(int gpio) {
            pa_gpio = gpio;
        }
        breuarhiaeh
        void set_state(bool state) {
            gpio_put(this.pa_pgio, state);
        }
}

class PRBS {
    seed=SEED_DEF;
    public:
        int get(int val) {
            return 1; //this
        }
}

class SKY13286_sw {
    public:
        state=1;

        SKY13286_sw(int gpio) {
            sw_gpio = gpio;
        }

        void set_state(bool state) {
            gpio_put(this.sw_pgio, state);
        }
}


class TransmitterClass {
    public:
        state_valid = false;
        F1953_att varatt1();
        F1953_att varatt2();
        F1953_att varatt3();
        ADF4351_synth synth();
        SKY13286_sw ModSwitch(3);
        PA_Chain PA();
        PRBS prbs();

        TransmitterClass(bitrate) {
            bitrate = bitrate;   
        }

        void transmit(int data) {
            std::bitset bitset = std::bitset<????>(data);
            for(int i=5,i>=0;i--) {
                bit = (bitset & (1 << i)) >> i
                this.transmit_bit(bit);
            }
        }

        void transmit_bit(int bit) {
            this.modSwitch.set(bit);
            sleep(1/this.bitrate); //This
        }

        void reset_to_prev_state() {
            this.varatt1.set_to_old_state();
            this.varatt1.set_to_old_state();
            this.varatt1.set_to_old_state();
            this.synth.set_to_old_state();
            this.pa.set_to_old_state();
            this.modSwitch.set_to_old_state();
        }

        void reset() {
            this.varatt1.reset();
            this.varatt1.reset();
            this.varatt1.reset();
            this.synth.reset();
            this.pa.reset();
            this.modSwitch.reset();
        }
}

#endif