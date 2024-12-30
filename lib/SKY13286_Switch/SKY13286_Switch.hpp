#ifndef SKY13286_SWITCH_HPP
#define SKY13286_SWITCH_HPP

class SKY13286_sw {
    public:
        bool state;
        int gpio;

        SKY13286_sw(int gpio_);
        void set_state(bool state);
        void reset_to_old_state();
        void reset();
};

#endif
