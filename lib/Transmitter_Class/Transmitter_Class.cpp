#ifndef TRANSMITTER_CLASS_CPP
#define TRANSMITTER_CLASS_CPP

#include <stdio.h>
#include "pico/stdlib.h"
#include "Transmitter_Class.hpp"
#include "../../src/Constants.hpp"
#include <algorithm>
#include <cstring>

TransmitterClass::TransmitterClass(int bitrate_) {
    printf("-Instantiating transmitter\n");
    bitrate = bitrate_;   
    this->transmitting_prbs = true;
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
    prbs = new PRBS(PRBS_SEED);
    printf("-Done Instantiating Transmitter\n");
}

void TransmitterClass::transmit_32b(int data) {
    printf("-Transmitting data\n");
    int bit;
    for(int i=32;i>=0;i--) {
        bit = (data & (1 << i)) >> i;
        this->transmit_bit(bit);
    }
}

void TransmitterClass::transmit_bit(int bit) {
    printf("--Transmitting bit %d\n", bit);
    this->modSwitch->set_state(bit);
    sleep_us(1000000 *1/this->bitrate); //TODO
}


void TransmitterClass::transmit_prbs() {
    int prbs_val = this->prbs->get();
    this->transmit_bit(prbs_val & 1);
    gpio_put(LED2_GPIO, prbs_val & 1);
    sleep_ms(100);
}

void TransmitterClass::reset_to_old_state() {
    printf("-Resetting transmitter to old state\n");
    this->varatt1->reset_to_old_state();
    this->varatt2->reset_to_old_state();
    this->varatt3->reset_to_old_state();
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

void TransmitterClass::run() {
    if (this->transmitting_prbs) {
        this->transmit_prbs();
    }
}

void TransmitterClass::handle_command(std::vector<std::string> tokens) {
    printf("in handle command");
    sleep_ms(100);
    size_t numTokens = tokens.size();
    printf("Numtokens: %d", numTokens);
    sleep_ms(100);
    if (numTokens == 0) {
        printf("Empty command");
        return;
    }
    //process command 
    if (strcmp(tokens[0].c_str(), "att") == 0) {
        //Allowed command is att (attnum) (attval)
        if (numTokens < 3) {
            printf("Invalid command (att chain)");
            return;
        }

        //Try to cast tokens[2].c_str() to int
        int attval = std::stoi(tokens[2].c_str());

        if (strcmp(tokens[1].c_str(), "1")==0) {
            this->varatt1->set_atten(attval);
        } else if (strcmp(tokens[1].c_str(), "2")==0) {
            this->varatt1->set_atten(attval);
        } else if (strcmp(tokens[1].c_str(), "3")==0) {
            this->varatt1->set_atten(attval);
        } else {
            printf("Invalid atten choice (1, 2, 3)");
        }
    } else if (strcmp("reset", tokens[0].c_str())==0) {
        if ((numTokens) < 2) {
            printf("Reset: Not enough tokens");
        }

        if (strcmp(tokens[1].c_str(), "att1")==0) {
            this->varatt1->reset();
        } else if (strcmp(tokens[1].c_str(), "att2")==0) {
            this->varatt2->reset();
        } else if (strcmp(tokens[1].c_str(), "att3")==0) {
            this->varatt3->reset();
        } else if (strcmp(tokens[1].c_str(), "synth")==0) {
            this->synth->reset();
        } else if (strcmp(tokens[1].c_str(), "pa")==0) {
            this->PA->reset();
        } else if (strcmp(tokens[1].c_str(), "prbs")==0) {
            this->prbs->reset();
        } else if (strcmp(tokens[1].c_str(), "switch")==0) {
            this->modSwitch->reset();
        } else if (strcmp(tokens[1].c_str(), "all")==0) {
            this->reset();
        } else {
            printf("CLI: Not a valid reset target");
            return;
        }
    } else if (strcmp("synth", tokens[0].c_str())==0) {
        if (numTokens < 3) {
            printf("CLI: Not enough tokens for synth commmand (requires 'synth (regnum) (val))");
            return;
        }

        int regnum = std::stoi(tokens[1].c_str());
        int regval = std::stoi(tokens[2].c_str());
    
        this->synth->write_reg(regnum, regval);
    } else if (strcmp("pa", tokens[0].c_str())==0) {
        if (numTokens < 2) {
            printf("CLI: Not enough tokens for pa");
        }
        if ((strcmp(tokens[1].c_str(), "1")==0) || (strcmp(tokens[1].c_str(), "on")==0)) {
            this->PA->set_state(true);
        } else if ((strcmp(tokens[1].c_str(), "0")==0) || (strcmp(tokens[1].c_str(), "off")==0)) {
            this->PA->set_state(false);
        } else {
            printf("CLI: Not a valid option, either 1 or 0");
        }
    } else if (strcmp("prbs", tokens[0].c_str())==0) {
        if (numTokens < 2) {
            printf("CLI: Not enough tokens for prbs");
        }
        if (strcmp(tokens[1].c_str(), "start")==0) {
            this->transmitting_prbs=true;
        } else if (strcmp(tokens[1].c_str(), "stop")==0) {
            this->transmitting_prbs=false;
        } else if (strcmp(tokens[1].c_str(), "get")==0) {
            printf("Next prbs generated number: %d", this->prbs->get());
        } else {
            printf("CLI: Expecting either start/stop for PRBS");
        }
    } else if (strcmp("switch", tokens[0].c_str())==0) {
        if (numTokens < 2) {
            printf("CLI: Not enough tokens for switch");
        }
        if ((strcmp(tokens[1].c_str(), "1")==0) || (strcmp(tokens[1].c_str(), "on")==0)) {
            this->PA->set_state(true);
        } else if ((strcmp(tokens[1].c_str(), "0")==0) || (strcmp(tokens[1].c_str(), "off")==0)) {
            this->PA->set_state(false);
        } else {
            printf("CLI: Not a valid option, either 1 or 0");
        }
    } else if (strcmp("transmit32", tokens[0].c_str())==0) {
        if (numTokens < 2) {
            printf("CLI: not enough tokens for transmit");
        }
        int data = std::stoi(tokens[1].c_str());
        this->transmit_32b(data);
    } else if (strcmp("revert", tokens[0].c_str())==0) {
        this->reset_to_old_state();
    } else if (strcmp("help", tokens[0].c_str())==0) {
        printf("CLI Commands:"
            "\n\tatt (attnum) (val) : Sets attenutator num attnum to val"
            "\n\treset att1/att2/att3/synth/pa/prbs/switch/transmitter"
            "\n\tsynth (regnum) (val): Sets synth mem[regnum].c_str() to int val"
            "\n\tpa 1/0: sets PA chain to on or off"
            "\n\tprbs get/start/stop: retusn PRBS next number"
            "\n\tswitch 1/0: turn mod switch on or off"
            "\n\ttransmit32 (int data): transmits 32bit word MSB first"
            "\n\trevert: reverts to old state, only does anything if you had just switcehd to hardware control, changed things, and we now want to go back to hw control");
    } else {
        printf("Not valid command. please see help");
    } 
}

#endif