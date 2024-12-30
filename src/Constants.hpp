#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <vector>
#include <string>

#ifndef DEBUG
const int SPI_CLK_GPIO = 2;
const int SPI_MOSI_GPIO = 3;
const int SPI_CS_GPIO = 5;
const int SYNTH_LE_GPIO = 7;
const int DATA_GPIO = 9;
const int PA_EN_GPIO = 10;
const int ATT1_LE_GPIO = 11;
const int ATT2_LE_GPIO = 12;
const int ATT3_LE_GPIO = 13;
#endif 

#ifdef DEBUG
const int SPI_CLK_GPIO = 17;
const int SPI_MOSI_GPIO = 16;
const int SPI_CS_GPIO = 15;
const int SYNTH_LE_GPIO = 29;
const int DATA_GPIO = 28;
const int PA_EN_GPIO = 27;
const int ATT1_LE_GPIO = 26;
const int ATT2_LE_GPIO = 23;
const int ATT3_LE_GPIO = 22;
#endif

const int LED2_GPIO = 24;
const int SYNTH_EN_GPIO = 8;
const int HW_SW_GPIO = 14;

const int PRBS_SEED = 0xACE1;
const int BITRATE = 10;
const int ATTEN_WORD_LEN = 6;
const int NEWLINE_CHAR = 10;
const int DEFAULT_CHAR = 254;
const int SPI_DELAY=10; //TODO: decrease once done testing
const std::vector<std::string> EMPTY_CMD = {std::string("EMPTY")};

/**
 * For Synth memory explanation, see doc/regmap.xlsx
 */
const int SYNTH_REG0_DEFAULT = 0b0000000101101110000000000000000;
const int SYNTH_REG1_DEFAULT = 0b00010000000000001000000000010001;
const int SYNTH_REG2_DEFAULT = 0b00001000000000000101111001000010;
const int SYNTH_REG3_DEFAULT = 0b00000000100000000000000000000011;
const int SYNTH_REG4_DEFAULT = 0b00000000100000000001001000100100;
const int SYNTH_REG5_DEFAULT = 0b00000000010000000000000000000101;

const int SYNTH_MEM_DEFAULT[6] = {SYNTH_REG0_DEFAULT, SYNTH_REG1_DEFAULT, SYNTH_REG2_DEFAULT, SYNTH_REG3_DEFAULT, SYNTH_REG4_DEFAULT, SYNTH_REG5_DEFAULT};
#endif