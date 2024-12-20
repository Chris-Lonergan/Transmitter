#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/uart.h"
#include "Constants.h"
#include "TransmitterClasses.h"

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 115200

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5



int main()
{
    stdio_init_all();

    // SPI initialisation. This example will use SPI at 1MHz.
    spi_init(SPI_PORT, 1000*1000);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);
    // For more examples of SPI use see https://github.com/raspberrypi/pico-examples/tree/master/spi

    // Set up our UART
    uart_init(UART_ID, BAUD_RATE);
    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
    // Use some the various UART functions to send out data
    // In a default system, printf will also output via the default UART
    
    // Send out a string, with CR/LF conversions
    uart_puts(UART_ID, " Hello, UART!\n");
    
    // For more examples of UART use see https://github.com/raspberrypi/pico-examples/tree/master/uart

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }

    /**
     * try to create serial port if possible
serial_active=^?
wait 3 secs if serial active... if no 'manual' over serial begin prbs for mod switch
print(manual)
manual=^?
mainloop()
     */
    bool state_valid = false;
    TransmitterClass transmitter(2);
}

void mainloop() {
    int state_valid = 0;
    int manual = 0;
    TransmitterClass transmitter(2);
    while (true) {
        if (not state_valid) {
            transmitter.reset_to_prev_state();
        }
        if (manual) {
            /**
             * #Standard is 'object' 'state'
	#Switch, pa, synth, mod switch on/off
	#att value
	#transmit hex?
	#reset 
	#synth read ?
	#synth write ?
	#transmit prbs
	
             * msg.split(' ')
	case msg[0] */
        }
        else {
            int MAX_I = 100;
            for(int i=0;true;i++) {
                if (i>= MAX_I) {
                    i = 0;
                }
                int bit = transmitter.prbsit.get(i);
                transmitter.transmit_bit(bit);
                i += 1;
            }
        }
    }
}

/**      
def print_uart(text)
	try printing if serial is active, if not ignore
    
interrupt hw_sw -> sw #make sure interrupts cant be interrupted (debouncing)
	print(sw mode)
    sleep(0.5s) #debounce
    mainloop()

interrupt hw_sw -> hw
	print(hw mode)
    sleep(0.5s) #debounce
    state_valid = False
    while True:
        #allow interrupting
        if serial comes in, print not allowed */