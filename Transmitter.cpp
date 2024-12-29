#include <stdio.h>
#include "pico/stdlib.h"
#include "TransmitterClasses.h"
#include "Constants.h"
#include <string>
#include <cstring>

int main()
{
    stdio_init_all();

    uint gpios[10] = {(uint) SPI_CLK_GPIO, (uint) SPI_MOSI_GPIO, (uint) SYNTH_LE_GPIO,
                    (uint) SPI_CS_GPIO, (uint) DATA_GPIO, (uint) PA_EN_GPIO,
                    (uint) ATT1_LE_GPIO, (uint) ATT2_LE_GPIO, (uint) ATT3_LE_GPIO, (uint) LED2_GPIO};
    //Set GPIO as SIO, directions and set them to default state
    for (uint gpio_num : gpios) {
        gpio_set_function(gpio_num, GPIO_FUNC_SIO);
        gpio_set_dir(gpio_num, GPIO_OUT);
    }
    gpio_set_function(HW_SW_GPIO, GPIO_FUNC_SIO);
    gpio_set_dir(HW_SW_GPIO, GPIO_IN);

    sleep_ms(5000);
    printf("Beginning code\n");
    TransmitterClass transmitter(1);
    transmitter.reset();

    bool prbs = true;
    char strg[100];
    char chr;
    int lp = 0;
    memset(strg, 0, sizeof(strg));

    while (true) {
        int hw_sw = gpio_get(HW_SW_GPIO);

        chr = getchar_timeout_us(0);
        while(chr != DEFAULT_CHAR)
        {  
            // printf("Received char: %d", chr);
            strg[lp++] = chr;
            if(chr == NEWLINE_CHAR || lp == (sizeof(strg) - 1))
            {
                //Terminate string prematurely to strip /n

                strg[lp-1] = 0;	
                char strg_stripped[lp-1];
                lp = 0;	

                //tokenize
                char* tokens[100]; 
                int tokenIter = 0;

                char* token = strtok(strg, " ");
                while (token != nullptr) {
                    tokens[tokenIter++] = token;
                    token = strtok(nullptr, " "); 
                }
                
                //for debugging
                // for (int i = 0; i < tokenIter; ++i) {
                //     printf("Token i: %d, = '%s'\n", i, tokens[i]);
                // }
                
                size_t numTokens = sizeof(tokens)/sizeof(tokens[0]);

                if (numTokens == 0) {
                    printf("Empty command");
                    break;
                }
                
                if (hw_sw == 1) {
                    printf("Currently in SW control, no commands possible");
                    break;
                }
                //process command 
                if (strcmp(tokens[0], "att") == 0) {
                    //Allowed command is att (attnum) (attval)
                    if (numTokens < 3) {
                        printf("Invalid command (att chain)");
                        break;
                    }

                    //Try to cast tokens[2] to int
                    int attval = std::stoi(tokens[2]);

                    if (strcmp(tokens[1], "1")==0) {
                        transmitter.varatt1->set_atten(attval);
                    } else if (strcmp(tokens[1], "2")==0) {
                        transmitter.varatt1->set_atten(attval);
                    } else if (strcmp(tokens[1], "3")==0) {
                        transmitter.varatt1->set_atten(attval);
                    } else {
                        printf("Invalid atten choice (1, 2, 3)");
                    }
                } else if (strcmp("reset", tokens[0])==0) {
                    if ((numTokens) < 2) {
                        printf("Reset: Not enough tokens");
                    }

                    if (strcmp(tokens[1], "att1")==0) {
                        transmitter.varatt1->reset();
                    } else if (strcmp(tokens[1], "att2")==0) {
                        transmitter.varatt2->reset();
                    } else if (strcmp(tokens[1], "att3")==0) {
                        transmitter.varatt3->reset();
                    } else if (strcmp(tokens[1], "synth")==0) {
                        transmitter.synth->reset();
                    } else if (strcmp(tokens[1], "pa")==0) {
                        transmitter.PA->reset();
                    } else if (strcmp(tokens[1], "prbs")==0) {
                        transmitter.prbs->reset();
                    } else if (strcmp(tokens[1], "switch")==0) {
                        transmitter.modSwitch->reset();
                    } else if (strcmp(tokens[1], "all")==0) {
                        transmitter.reset();
                    } else {
                        printf("CLI: Not a valid reset target");
                        break;
                    }
                } else if (strcmp("synth", tokens[0])==0) {
                    if (numTokens < 3) {
                        printf("CLI: Not enough tokens for synth commmand (requires 'synth (regnum) (val))");
                        break;
                    }

                    int regnum = std::stoi(tokens[1]);
                    int regval = std::stoi(tokens[2]);
                
                    transmitter.synth->write_reg(regnum, regval);
                } else if (strcmp("pa", tokens[0])==0) {
                    if (numTokens < 2) {
                        printf("CLI: Not enough tokens for pa");
                    }
                    if ((strcmp(tokens[1], "1")==0) || (strcmp(tokens[1], "on")==0)) {
                        transmitter.PA->set_state(true);
                    } else if ((strcmp(tokens[1], "0")==0) || (strcmp(tokens[1], "off")==0)) {
                        transmitter.PA->set_state(false);
                    } else {
                        printf("CLI: Not a valid option, either 1 or 0");
                    }
                } else if (strcmp("prbs", tokens[0])==0) {
                    if (numTokens < 2) {
                        printf("CLI: Not enough tokens for prbs");
                    }
                    if (strcmp(tokens[1], "start")==0) {
                        prbs=true;
                    } else if (strcmp(tokens[1], "stop")==0) {
                        prbs=false;
                    } else if (strcmp(tokens[1], "get")==0) {
                        printf("Next prbs generated number: %d", transmitter.prbs->get());
                    } else {
                        printf("CLI: Expecting either start/stop for PRBS");
                    }
                } else if (strcmp("switch", tokens[0])==0) {
                    if (numTokens < 2) {
                        printf("CLI: Not enough tokens for switch");
                    }
                    if ((strcmp(tokens[1], "1")==0) || (strcmp(tokens[1], "on")==0)) {
                        transmitter.PA->set_state(true);
                    } else if ((strcmp(tokens[1], "0")==0) || (strcmp(tokens[1], "off")==0)) {
                        transmitter.PA->set_state(false);
                    } else {
                        printf("CLI: Not a valid option, either 1 or 0");
                    }
                } else if (strcmp("transmit32", tokens[0])==0) {
                    if (numTokens < 2) {
                        printf("CLI: not enough tokens for transmit");
                    }
                    int data = std::stoi(tokens[1]);
                    transmitter.transmit_32b(data);
                } else if (strcmp("revert", tokens[0])==0) {
                    transmitter.reset_to_old_state();
                } else if (strcmp("help", tokens[0])==0) {
                    printf("CLI Commands:"
                        "\n\tatt (attnum) (val) : Sets attenutator num attnum to val"
                        "\n\treset att1/att2/att3/synth/pa/prbs/switch/transmitter"
                        "\n\tsynth (regnum) (val): Sets synth mem[regnum] to int val"
                        "\n\tpa 1/0: sets PA chain to on or off"
                        "\n\tprbs get/start/stop: retusn PRBS next number"
                        "\n\tswitch 1/0: turn mod switch on or off"
                        "\n\ttransmit32 (int data): transmits 32bit word MSB first"
                        "\n\trevert: reverts to old state, only does anything if you had just switcehd to hardware control, changed things, and we now wan tto go back to hw control");
                } else {
                    printf("Not valid command. please see help");
                } 
            }
            chr = getchar_timeout_us(0);
        }
        if (prbs) {
            int prbs_val = transmitter.prbs->get();
            printf("%d\n", prbs_val);
            //transmitter.transmit_bit(prbs_val & 1);
            gpio_put(LED2_GPIO, prbs_val & 1);
            sleep_ms(100);
        }
        }
}