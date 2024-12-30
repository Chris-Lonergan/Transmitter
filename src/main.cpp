#include <stdio.h>
#include "pico/stdlib.h"
#include "../lib/Transmitter_Class/Transmitter_Class.hpp"
#include "Constants.hpp"
#include <string>
#include <cstring>
#include <vector>

void init() {
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
}

std::vector<std::string> get_command() {
    char strg[100];
    char chr;
    int lp = 0;
    memset(strg, 0, sizeof(strg));

    chr = getchar_timeout_us(0);
    while(chr != DEFAULT_CHAR) {  
        strg[lp++] = chr;
        if(chr == NEWLINE_CHAR || lp == (sizeof(strg) - 1))
        {
            //Terminate string prematurely to strip /n
            strg[lp-1] = 0;	
            char strg_stripped[lp-1];
            lp = 0;	

            //tokenize
            std::vector<std::string> tokens; 
            char* token = strtok(strg, " ");
            while (token != nullptr) {
                tokens.push_back(std::string(token));
                token = strtok(nullptr, " "); 
            }
            #ifdef DEBUG
            for (int i = 0; i < tokens.size(); ++i) {
                printf("Token i: %d, = '%s'\n", i, tokens[i].c_str());
            }
            #endif

            return tokens;
        }
        chr = getchar_timeout_us(0);
    }
    return EMPTY_CMD;
}


int main()
{
    init();
    #ifdef DEBUG
    sleep_ms(5000); //Sleep to give debugger time to open serial monitor, get logic analyzer started, etc
    #endif
    printf("Beginning OOK Transmitter\n");
    TransmitterClass transmitter(BITRATE);
    transmitter.reset();
   
    while (true) {
        int hw_sw = gpio_get(HW_SW_GPIO);
        std::vector<std::string> cmd = get_command();

        if (hw_sw == 1) {
            printf("Currently in SW control, no commands possible");
            break;
        } else if (cmd != EMPTY_CMD) {
            transmitter.handle_command(cmd);
        }
        transmitter.run();
    }
}

