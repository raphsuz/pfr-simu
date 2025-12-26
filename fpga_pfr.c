#include "fpga_pfr.h"
#include "flash_sim.h"
#include <string.h>
#include <stdio.h>

void pfr_init(FPGA_Config *config, const char *golden_project_name) {
    strncpy(config->expected_project_name, golden_project_name, PROJECT_NAME_MAX_LEN);
}

PFR_Status pfr_check_firmware(FPGA_Config *config, SPI_Flash *pch_flash, SPI_Flash *bmc_flash) {
    char pch_project_name[PROJECT_NAME_MAX_LEN] = {0};
    char bmc_project_name[PROJECT_NAME_MAX_LEN] = {0};

    printf("[PFR] Starting Firmware Check...\n");
    printf("[PFR] Expected Project Name: %s\n", config->expected_project_name);

    // Check PCH Firmware
    if (spi_read(pch_flash, PROJECT_NAME_OFFSET, (uint8_t *)pch_project_name, PROJECT_NAME_MAX_LEN) != 0) {
        printf("[PFR] Failed to read PCH SPI.\n");
        return PFR_STATUS_FAIL;
    }
    // Ensure null termination for logging safety
    pch_project_name[PROJECT_NAME_MAX_LEN - 1] = '\0';
    
    printf("[PFR] Read PCH Project Name: %s\n", pch_project_name);

    if (strncmp(pch_project_name, config->expected_project_name, PROJECT_NAME_MAX_LEN) != 0) {
        printf("[PFR] Mismatch detected in PCH Firmware!\n");
        return PFR_STATUS_FAIL;
    }

    // Check BMC Firmware
    if (spi_read(bmc_flash, PROJECT_NAME_OFFSET, (uint8_t *)bmc_project_name, PROJECT_NAME_MAX_LEN) != 0) {
        printf("[PFR] Failed to read BMC SPI.\n");
        return PFR_STATUS_FAIL;
    }
    // Ensure null termination
    bmc_project_name[PROJECT_NAME_MAX_LEN - 1] = '\0';

    printf("[PFR] Read BMC Project Name: %s\n", bmc_project_name);

    if (strncmp(bmc_project_name, config->expected_project_name, PROJECT_NAME_MAX_LEN) != 0) {
        printf("[PFR] Mismatch detected in BMC Firmware!\n");
        return PFR_STATUS_FAIL;
    }

    printf("[PFR] Firmware Check PASSED.\n");
    return PFR_STATUS_PASS;
}
