#ifndef CONSTANTS_H
#define CONSTANTS_H

// const int SPI_CLK_GPIO = 2;
// const int SPI_MOSI_GPIO = 3;
// const int SPI_CS_GPIO = 5;
// const int SYNTH_LE_GPIO = 7;
// const int DATA_GPIO = 9;
// const int PA_EN_GPIO = 10;
// const int ATT1_LE_GPIO = 11;
// const int ATT2_LE_GPIO = 12;
// const int ATT3_LE_GPIO = 13;

const int SPI_CLK_GPIO = 17;
const int SPI_MOSI_GPIO = 16;
const int SPI_CS_GPIO = 15;
const int SYNTH_LE_GPIO = 29;
const int DATA_GPIO = 28;
const int PA_EN_GPIO = 27;
const int ATT1_LE_GPIO = 26;
const int ATT2_LE_GPIO = 23;
const int ATT3_LE_GPIO = 22;

const int LED2_GPIO = 24;
const int SYNTH_EN_GPIO = 8;
const int HW_SW_GPIO = 14;

const int PRBS_SEED = 0xACE1;
const int BITRATE = 10;
const int NEWLINE_CHAR = 10;
const int DEFAULT_CHAR = 254;
const int SPI_DELAY=10; //us

const int SYNTH_REG0_DEFAULT = 11993088;
const int SYNTH_REG1_DEFAULT = 268468241;
const int SYNTH_REG2_DEFAULT = 134241858;
const int SYNTH_REG3_DEFAULT = 8388611;
const int SYNTH_REG4_DEFAULT = 8393252;
const int SYNTH_REG5_DEFAULT = 4194309;

const int SYNTH_MEM_DEFAULT[6] = {SYNTH_REG0_DEFAULT, SYNTH_REG1_DEFAULT, SYNTH_REG2_DEFAULT, SYNTH_REG3_DEFAULT, SYNTH_REG4_DEFAULT, SYNTH_REG5_DEFAULT};
#endif