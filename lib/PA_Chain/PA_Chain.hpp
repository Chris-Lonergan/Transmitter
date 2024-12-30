#ifndef PA_CHAIN_HPP
#define PA_CHAIN_HPP

class PA_Chain { //also turns on switches
    public:
        bool state;
        int gpio;
        
        PA_Chain(int gpio);
        void set_state(bool state);
        void reset_to_old_state();
        void reset();
};

#endif