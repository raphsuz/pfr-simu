#ifndef FPGA_PFR_H
#define FPGA_PFR_H

#include "components.h"

// Initialize PFR internal state
void pfr_init(FPGA_Config *config, const char *golden_project_name);

// Check if the firmware in the SPI flashes matches the golden policy
PFR_Status pfr_check_firmware(FPGA_Config *config, SPI_Flash *pch_flash, SPI_Flash *bmc_flash);

#endif // FPGA_PFR_H
