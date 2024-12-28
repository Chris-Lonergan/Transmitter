#include <stdio.h>
#include "pico/stdlib.h"
#include "TransmitterClasses.h"
#include "Constants.h"
#include <vector>
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

    bool onoff = 0;
    char strg[100];
    char chr;
    int lp = 0;
    memset(strg, 0, sizeof(strg));

    while (true) {
        chr = getchar_timeout_us(0);
        while(chr != DEFAULT_CHAR)
        {
            strg[lp++] = chr;
            if(chr == NEWLINE_CHAR || lp == (sizeof(strg) - 1))
            {
                strg[lp] = 0;	//terminate string
                lp = 0;		//reset string buffer pointer
                printf("Command: %s\n", strg);
                
                
                //process command 
                
                
                break;
            }
            chr = getchar_timeout_us(0);
        }

        gpio_put(LED2_GPIO, onoff);
        onoff = !onoff;
        sleep_ms(100);
        }
}